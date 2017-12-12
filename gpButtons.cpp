#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "grippoint.h"


void MainWindow::on_selectData_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Laserdaten auswählen"),
                                            QDir::currentPath(),"log Files (Text Files (*.txt);;*.log);;CSV (*.csv);;All files (*.*)");
    ui->selectedFile->setText(fileName);

}


void MainWindow::on_calculateGP_clicked()
{
    if (!fileName.isEmpty()) {
        //START added for Grippoint

            bool Gedreht                   = true;
            long ScannerUeberBoden = 6800;
            double InkrementSize     = 40;
            unsigned int leftAngle         =  45 + 45; //36;
            unsigned int rightAngle        = 315 - 45; //38;
            long leftBorder                 = -8500;
            long rightBorder                =  12000; //11700;
            unsigned int VRatio                    = 10;

        if(!ui->enPoendorf->isChecked()){
            Gedreht           = true;
            ScannerUeberBoden = 2880;
            InkrementSize     = 300.0 / 1024.0;
            leftAngle         =  45 + 90; //36;
            rightAngle        = 315 - 90; //38;
            leftBorder        = -1000;
            rightBorder       =  1000; //11700;
            VRatio            = 10;
        }

        gripPoint = new GripPoint(nullptr, Gedreht, ScannerUeberBoden, InkrementSize, leftAngle, rightAngle, leftBorder, rightBorder, VRatio, fileName, ui->showHist->isChecked(), ui->showSurface->isChecked(), ui->enSopas->isChecked());
        xGp = gripPoint->xGp;
        yGp = gripPoint->yGp;
        zGp = gripPoint->zGp;
        ui->xGp->setText(QString::number(xGp));
        ui->yGp->setText(QString::number(yGp));
        ui->zGp->setText(QString::number(zGp));
        delete gripPoint;

        ui->xGp_2->setText(ui->xGp->text());
        ui->yGp_2->setText(ui->yGp->text());
        ui->zGp_2->setText(ui->zGp->text());
        statusBar()->showMessage(tr("Greifpunkt berechnet."),7000);


        //END added for Grippoint
    }

    else statusBar()->showMessage(tr("Kein File ausgewählt."),7000);

}

void MainWindow::on_calculateInvers_clicked()
{
    if (UA_Client_getState(client) == 1){  //nur wenn Verbindung zur SPS besteht.

    //x aus ui.xGp_2 an SPS Xsoll senden
    XsollValue = ui->xGp_2->text().toFloat();
    UA_Variant_setScalar(&Xsoll, &XsollValue, &UA_TYPES[UA_TYPES_FLOAT]);
    retval = UA_Client_writeValueAttribute(client, nodeXsoll,&Xsoll);

    //y aus ui.xGp_2 an SPS Ysoll senden
    YsollValue = ui->yGp_2->text().toFloat();
    UA_Variant_setScalar(&Ysoll, &YsollValue, &UA_TYPES[UA_TYPES_FLOAT]);
    retval = UA_Client_writeValueAttribute(client, nodeYsoll,&Ysoll);

    //z aus ui.xGp_2 an SPS Zsoll senden
    ZsollValue = ui->zGp_2->text().toFloat();
    UA_Variant_setScalar(&Zsoll, &ZsollValue, &UA_TYPES[UA_TYPES_FLOAT]);
    retval = UA_Client_writeValueAttribute(client, nodeZsoll,&Zsoll);
}
    else ui->statusBar->showMessage(tr("Verbindung zur SPS nicht hergestellt."),5000);
}


void MainWindow::on_copySollPos_clicked()
{   if (AutoValue == 1) {
        ui->sollLFahrt->setValue(ui->sollLFahrtInvers->text().toDouble());
        sendSollLFahrt();
        ui->sollDrehen->setValue(ui->sollDrehenInvers->text().toDouble());
        sendSollDrehung();
        ui->sollHub->setValue(ui->sollHubInvers->text().toDouble());
        sendSollHub();
        ui->sollAusschub->setValue(ui->sollAusschubInvers->text().toDouble());
        sendSollAusschub();
    }
    else ui->statusBar->showMessage(tr("Automodus ist deaktiviert, Übernahme nicht möglich."),5000);
}
