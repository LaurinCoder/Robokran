#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <qvariant.h>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    activeTimer = new QTimer(this);
    activeTimer->setInterval(50);
    activeTimer->setSingleShot(false);

    connect(activeTimer, SIGNAL(timeout()), this, SLOT(activateOpcSync()));


    ui->setupUi(this);

    //Message Boxen
//    msgBox_movementWarning.setText("Achtung, die ausgewählte Funktion führt zu einer Bewegung des Krans.");
//    retryButton = msgBox_connectionFailed.addButton("Erneut verbinden", QMessageBox::AcceptRole);
//    msgBox_connectionFailed.addButton("Abbrechen", QMessageBox::RejectRole);    //Message Boxen

    msgBox_movementWarning.setText("Achtung, die ausgewählte Funktion führt zu einer Bewegung des Krans.");
    msgBox_movementWarning.setInformativeText("Soll die Bewegung ausgeführt werden?");
    msgBox_movementWarning.addButton("Ja", QMessageBox::AcceptRole);
    msgBox_movementWarning.addButton("Nein", QMessageBox::RejectRole);

    msgBox_invalidPose.setText("Stellung des Krans verhindert Scanfahrt.\n\nKran in Scanposition bringen!");
    msgBox_invalidPose.setWindowTitle("ACHTUNG - falsche Kranstellung");
    msgBox_invalidPose.addButton(QMessageBox::Ok);

//    msgBox_MatlabFAIL.setText("Fehler im Matlab");
//    msgBox_MatlabFAIL.addButton(QMessageBox::Ok);

//    msgBox_ManuelMode.setText("Manuel Modus aktiviert");
//    msgBox_ManuelMode.addButton(QMessageBox::Ok);


    //FÜR LASERSCANNER
    LMS_111 = new QTcpSocket(this);
    connect(LMS_111, SIGNAL(connected()),this, SLOT(connected()));
    connect(LMS_111, SIGNAL(readyRead()), this, SLOT(readyRead()));

    //connect Soll Felder zu Variablen zur Übergabe an SPS
    connect(ui->sollLFahrt, SIGNAL(editingFinished()), this, SLOT(sendSollLFahrt()));
    connect(ui->sollDrehen, SIGNAL(editingFinished()), this, SLOT(sendSollDrehung()));
    connect(ui->sollAusschub, SIGNAL(editingFinished()), this, SLOT(sendSollAusschub()));
    connect(ui->sollHub, SIGNAL(editingFinished()), this, SLOT(sendSollHub()));
    connect(ui->sollGreifer, SIGNAL(editingFinished()), this, SLOT(sendSollGreifer()));


    ui->istLFahrt->setText("-");
    ui->istDrehen->setText("-");
    ui->istHub->setText("-");
    ui->istAusschub->setText("-");
    ui->istGreifer->setText("-");
    ui->Automode->setText("-");


    ui->istLFahrt->setStyleSheet(lineEditStyleYellow);
    ui->istDrehen->setStyleSheet(lineEditStyleYellow);
    ui->istHub->setStyleSheet(lineEditStyleYellow);
    ui->istAusschub->setStyleSheet(lineEditStyleYellow);
    ui->istGreifer->setStyleSheet(lineEditStyleYellow);

    ui->selectedFile->setText(fileName);
    ui->showHist->setChecked(0);
    ui->showSurface->setChecked(1);

    //setzt alle Punkte des Ausschubs auf Null und löscht damit den aktuellen Pfad
    for (int i = 0; i < 256; i++) path [4][i] = 0;

    //OPC Client initialisieren
    client = UA_Client_new(UA_ClientConfig_standard);

    UA_Variant_init(&posIst); /* Variants can hold scalar values and arrays of any type */
    UA_Variant_init(&posSoll);
    UA_Variant_init(&posSollInv);
    UA_Variant_init(&Xsoll);
    UA_Variant_init(&Ysoll);
    UA_Variant_init(&Zsoll);
    UA_Variant_init(&posOk);
    UA_Variant_init(&Auto);
    UA_Variant_init(&hys);
    UA_Variant_init(&oldHys);
}

MainWindow::~MainWindow()
{   delete gripPoint;
    on_enableJoints_clicked(false);
    LMS_111->close();

    UA_Client_delete(client); /* Disconnects the client internally */
    delete ui;
    }

void MainWindow::update_UI() {
    if (posOkValue[0] == true) {
        ui->istLFahrt->setStyleSheet(lineEditStyleGreen);
    } else {
        ui->istLFahrt->setStyleSheet(lineEditStyleYellow);
    }
    if (posOkValue[2] == true) {
        ui->istDrehen->setStyleSheet(lineEditStyleGreen);
    } else {
        ui->istDrehen->setStyleSheet(lineEditStyleYellow);
    }
    if (posOkValue[3] == true) {
        ui->istHub->setStyleSheet(lineEditStyleGreen);
    } else {
        ui->istHub->setStyleSheet(lineEditStyleYellow);
    }
    if (posOkValue[4] == true) {
        ui->istAusschub->setStyleSheet(lineEditStyleGreen);
    } else {
        ui->istAusschub->setStyleSheet(lineEditStyleYellow);
    }
    if (posOkValue[7] == true) {
        ui->istGreifer->setStyleSheet(lineEditStyleGreen);
    } else {
        ui->istGreifer->setStyleSheet(lineEditStyleYellow);
    }

    if (AutoValue == true) {
        ui->Automode->setText("ON");
    }
    else ui->Automode->setText("OFF");


    ui->enableJoints->setChecked(AutoValue);
    ui->istLFahrt->setText(QString::number(posIstValue[0]));
    ui->istDrehen->setText(QString::number(posIstValue[2]));
    ui->istHub->setText(QString::number(posIstValue[3]));
    ui->istAusschub->setText(QString::number(posIstValue[4]));
    ui->istGreifer->setText(QString::number(posIstValue[7]));
    ui->runPath->setChecked(runPath);
    ui->cyclePath->setChecked(cyclic);
    ui->includeGP->setChecked(setGPActive);

    ui->sollLFahrtInvers->setValue(posSollInvValue[0]);
    ui->sollDrehenInvers->setValue(posSollInvValue[2]);
    ui->sollHubInvers->setValue(posSollInvValue[3]);
    ui->sollAusschubInvers->setValue(posSollInvValue[4]);

}

void MainWindow::activateOpcSync() {

    if (UA_Client_getState(client) == 1) { //alles nur wenn Client verbunden

        //posIst einlesen
        retval = UA_Client_readValueAttribute(client, nodePosIst,&posIst);
        if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasArrayType(&posIst,&UA_TYPES[UA_TYPES_FLOAT]) ) {
            float *dataPointer = (UA_Float*)posIst.data;
            for (int i = 0; i < 8; ++i) {
                posIstValue[i] = *(dataPointer);
                ++dataPointer;
            }

            //posSollInv einlesen
            retval = UA_Client_readValueAttribute(client, nodePosSollInv,&posSollInv);
            if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasArrayType(&posSollInv,&UA_TYPES[UA_TYPES_FLOAT]) ) {
                float *dataPointer = (UA_Float*)posSollInv.data;
                for (int i = 0; i < 8; ++i) {
                    posSollInvValue[i] = *(dataPointer);
                    ++dataPointer;
                }}


            //Auto einlesen
            retval = UA_Client_readValueAttribute(client, nodeAuto,&Auto);
            if(retval == UA_STATUSCODE_GOOD && UA_Variant_isScalar(&Auto) ) {
                AutoValue = *(UA_Boolean*)Auto.data;
            }


            //posOk lesen
            retval = UA_Client_readValueAttribute(client, nodePosOk,&posOk);
            if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasArrayType(&posOk,&UA_TYPES[UA_TYPES_BOOLEAN]) ) {
                bool *dataPointer = (UA_Boolean*)posOk.data;
                for (int i = 0; i < 8; ++i) {
                    posOkValue[i] = *(dataPointer);
                    ++dataPointer;
                }}

            //hys lesen
            retval = UA_Client_readValueAttribute(client, nodeHys,&hys);
            if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasArrayType(&hys,&UA_TYPES[UA_TYPES_FLOAT]) ){
                float *dataPointer = (UA_Float*)hys.data;
                for (int i = 0; i < 8; ++i) {
                    hysValue[i] = *(dataPointer);
                    ++dataPointer;
                }}


            //posSoll schreiben wenn AutoValue = true

            if (AutoValue) {
                UA_Variant_setArray(&posSoll, &posSollValue, 8, &UA_TYPES[UA_TYPES_FLOAT]);
                retval = UA_Client_writeValueAttribute(client, nodePosSoll,&posSoll);
            }
            else {
                for (int i = 0; i < 8; ++i) {
                    posSollValue[i] = posIstValue[i];
                }
                ui->sollLFahrt->setValue((int)posSollValue[0]);
                ui->sollDrehen->setValue((int)posSollValue[2]);
                ui->sollHub->setValue((int)posSollValue[3]);
                ui->sollAusschub->setValue((int)posSollValue[4]);
                ui->sollGreifer->setValue(posSollValue[7]);
            }

            //TeachIn Funktion aufrufen wenn TeachIn = true
            TeachIn();
            //update posIst der GUI aufrufen
            MainWindow::update_UI();
            //scanSequence aufrufen wenn scan_inProcess == 1
            MainWindow::scanSequence();

        }
    }
}

void MainWindow::sendSollLFahrt() {
    posSollValue[0] = ui->sollLFahrt->value();
}
void MainWindow::sendSollDrehung()
{
    posSollValue[2] = ui->sollDrehen->value();
}
void MainWindow::sendSollHub()
{
    posSollValue[3] = ui->sollHub->value();
}
void MainWindow::sendSollAusschub()
{
    posSollValue[4] = ui->sollAusschub->value();

}
void MainWindow::sendSollGreifer()
{
    posSollValue[7] = ui->sollGreifer->value();
}



