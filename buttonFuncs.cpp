#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_actionVerbinde_mit_SPS_triggered()
{   client = UA_Client_new(UA_ClientConfig_standard);
//    retval = UA_Client_connect(client, "opc.tcp://169.254.123.90:4840");  //IP Adresse bei Lasco Vor-Ort
    retval = UA_Client_connect(client, "opc.tcp://169.254.25.28:4840");    //IP Adresse Labor Tests mit AutomationPC
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        ui->statusBar->showMessage(tr("ERRIOR: Verbindung fehlgeschlagen."),5000);
    }
    else     ui->statusBar->showMessage(tr("Verbindung zur SPS hergestellt."),5000);
    timerWaypoint.start(); //timer für waypointpause starten

    ui->wayPointPause->setValue(wayPointPause);
}

void MainWindow::on_actionVerbindung_trennen_triggered()
{
    if (UA_Client_getState(client) == true)
    {
        UA_Client_delete(client);
        if (UA_Client_getState(client) != true)   ui->statusBar->showMessage(tr("Verbindung erfolgreich getrennt."),5000);

    }
    else  ui->statusBar->showMessage(tr("Trennen nicht möglich, keine bestehende Verbindung."),5000);


}


void MainWindow::on_copyIstPos_clicked()
{
    ui->sollLFahrt->setValue(ui->istLFahrt->text().toDouble());
    ui->sollDrehen->setValue(ui->istDrehen->text().toDouble());
    ui->sollHub->setValue(ui->istHub->text().toDouble());
    ui->sollAusschub->setValue(ui->istAusschub->text().toDouble());
    ui->sollGreifer->setValue(ui->istGreifer->text().toDouble());
}


void MainWindow::on_enableJoints_clicked(bool checked)
{
    if (UA_Client_getState(client) == 1) {
        //Auto schreiben
        AutoValue = checked;
        UA_Variant_setScalar(&Auto,&AutoValue,&UA_TYPES[UA_TYPES_BOOLEAN]);
        retval = UA_Client_writeValueAttribute(client, nodeAuto,&Auto);
    }
    else
    {
        ui->enableJoints->setChecked(false);
        ui->statusBar->showMessage(tr("Verbindung zur SPS nicht hergestellt."),5000);
    }

}



void MainWindow::on_startTeachIn_clicked(bool checked)
{
    teachIn = checked;
}

void MainWindow::on_saveWaypoint_clicked()
{
    if (teachIn == true) {
        saveWayPoint = true;
    }
    else saveWayPoint = false;
}

void MainWindow::on_runPath_clicked(bool checked)
{
    runPath = checked;
}

void MainWindow::on_cyclePath_clicked(bool checked)
{
    cyclic = checked;
}

void MainWindow::on_includeGP_clicked(bool checked)
{
    setGPActive = checked;
}

void MainWindow::on_resetPath_clicked()
{
    resetPath = true;
}

void MainWindow::on_setGrippingPoint_clicked()
{
    //posSollInvValue[i] an path übergeben
    for (int i = 0; i < 8; ++i) {

        path[i][247] = posSollInvValue[i];
        path[i][248] = posSollInvValue[i];
        path[i][249] = posSollInvValue[i];
        path[i][250] = posSollInvValue[i];
        path[i][251] = posSollInvValue[i];
        path[i][252] = posSollInvValue[i];
        path[i][253] = posSollInvValue[i];
        path[i][254] = posSollInvValue[i];
    }

    //path[2,x] setzen
    path[2][247] = 0;
    path[2][254] = 0;

    //path[3,250 UND 253 und 254] aus 251 berechnen und neu speichern - liftRatioDown / Up ist prozentual wie viel kürzer/länger die Hubzylinderlänge sein soll
    path[3][247] = hubHighestPoint;
    path[3][248] = hubHighestPoint;
    path[3][249] = hubHighestPoint;
    path[3][250] = posSollInvValue[3] * liftRatioDown;
    path[3][251] = posSollInvValue[3] * liftRatioDown;
    path[3][253] = hubHighestPoint;
    path[3][254] = hubHighestPoint;

    //path[4,x] setzen
    path[4][247] = 370;
    path[4][248] = 370;
    path[4][253] = 450;
    path[4][254] = 370;

    //path[7,250..254] neu setzen
    path[7][247] = 0;
    path[7][248] = 0;
    path[7][249] = 0;
    path[7][250] = 0;
    path[7][251] = 1;
    path[7][252] = 1;
    path[7][253] = 1;
    path[7][254] = 1;

    ui->statusBar->showMessage(tr("Greifpunkt in Pfad übetragen. Wegpunkte 247 bis 254 überschrieben."),5000);
}

void MainWindow::on_setGrippingPointManual_clicked()
{
    //posIstValue[i] an path übergeben
    for (int i = 0; i < 8; ++i) {

        path[i][247] = posIstValue[i];
        path[i][248] = posIstValue[i];
        path[i][249] = posIstValue[i];
        path[i][250] = posIstValue[i];
        path[i][251] = posIstValue[i];
        path[i][252] = posIstValue[i];
        path[i][253] = posIstValue[i];
        path[i][254] = posIstValue[i];
    }

    //path[2,x] setzen
    path[2][247] = 0;
    path[2][254] = 0;

    //path[3,250 UND 253 und 254] aus 251 berechnen und neu speichern - liftRatioDown / Up ist prozentual wie viel kürzer/länger die Hubzylinderlänge sein soll
    path[3][247] = hubHighestPoint;
    path[3][248] = hubHighestPoint;
    path[3][249] = hubHighestPoint;
    path[3][250] = posIstValue[3] * liftRatioDown;
    path[3][251] = posIstValue[3] * liftRatioDown;
    path[3][253] = hubHighestPoint;
    path[3][254] = hubHighestPoint;

    //path[4,x] setzen
    path[4][247] = 370;
    path[4][248] = 370;
    path[4][253] = 450;
    path[4][254] = 370;

    //path[7,250..254] neu setzen
    path[7][247] = 0;
    path[7][248] = 0;
    path[7][249] = 0;
    path[7][250] = 0;
    path[7][251] = 1;
    path[7][252] = 1;
    path[7][253] = 1;
    path[7][254] = 1;
}

void MainWindow::on_wayPointPause_valueChanged(double arg1)
{
    wayPointPause = arg1;

}
