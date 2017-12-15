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
        //übernehme Parameter benutzerdefiniert, Pöndorf oder Labor
        if (ui->enUserSettings->isChecked()) {

            gedreht           = ui->turned->text().toInt();
            scannerUeberBoden = ui->groundDist->text().toInt();
            inkrementSize     = ui->inkrSize->text().toInt();
            leftAngle         = ui->leftAngle->text().toInt();
            rightAngle        = ui->rightAngle->text().toInt();
            leftBorder        = ui->leftBorder->text().toInt();
            rightBorder       = ui->rightBorder->text().toInt();
            vRatio            = ui->vRatio->text().toInt();
        }
        else if (ui->enPoendorf->isChecked()) {
            gedreht           = true;
            scannerUeberBoden = 6800;
            inkrementSize     = 40;
            leftAngle         = 45 + 45; //36;
            rightAngle        = 315 - 45; //38;
            leftBorder        = -8500;
            rightBorder       = 12000; //11700;
            vRatio            = 10;
        } else {
            gedreht           = true;
            scannerUeberBoden = 2880;
            inkrementSize     = 300.0 / 1024.0;
            leftAngle         =  45 + 90; //36;
            rightAngle        = 315 - 90; //38;
            leftBorder        = -1000;
            rightBorder       =  1000; //11700;
            vRatio            = 10;
        }

        gripPoint = new GripPoint(nullptr, gedreht, scannerUeberBoden, inkrementSize, leftAngle, rightAngle, leftBorder, rightBorder, vRatio, fileName, ui->showHist->isChecked(), ui->showSurface->isChecked(), ui->enSopas->isChecked());
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


void MainWindow::on_enUserSettings_toggled(bool checked)
{   // Eingabefelder werden aktiviert
    ui->turned->setEnabled(checked); ui->groundDist->setEnabled(checked); ui->inkrSize->setEnabled(checked);
    ui->leftAngle->setEnabled(checked); ui->rightAngle->setEnabled(checked); ui->leftBorder->setEnabled(checked);
    ui->rightBorder->setEnabled(checked); ui->vRatio->setEnabled(checked);

    //übernehme Pöndorf Parameter
    if (checked) {
        if(ui->enPoendorf->isChecked()){
            gedreht           = true;
            scannerUeberBoden = 6800;
            inkrementSize     = 40;
            leftAngle         = 45 + 45; //36;
            rightAngle        = 315 - 45; //38;
            leftBorder        = -8500;
            rightBorder       = 12000; //11700;
            vRatio            = 10;
        }
    //übernehme Pöndorf Parameter
        if(!ui->enPoendorf->isChecked()){
            gedreht           = true;
            scannerUeberBoden = 2880;
            inkrementSize     = 300.0 / 1024.0;
            leftAngle         =  45 + 90; //36;
            rightAngle        = 315 - 90; //38;
            leftBorder        = -1000;
            rightBorder       =  1000; //11700;
            vRatio            = 10;
        }

   //wenn KEIN Feld verändert wurde, übernehme aktuelle Parameter (je nachdem ob enPoendorf checked, welche sie IFs darüber)
        if (!ui->turned->isModified() && !ui->groundDist->isModified() && !ui->inkrSize->isModified()
                && !ui->leftAngle->isModified() && !ui->rightAngle->isModified() && !ui->leftBorder->isModified()
                && !ui->rightBorder->isModified() && !ui->vRatio->isModified()) {
        ui->turned->setText(QString::number(gedreht));
        ui->groundDist->setText(QString::number(scannerUeberBoden));
        ui->inkrSize->setText(QString::number(inkrementSize));
        ui->leftAngle->setText(QString::number(leftAngle));
        ui->rightAngle->setText(QString::number(rightAngle));
        ui->leftBorder->setText(QString::number(leftBorder));
        ui->rightBorder->setText(QString::number(rightBorder));
        ui->vRatio->setText(QString::number(vRatio));
        }
    }
   //deaktiviere Pöndorf Scan und setzte es unchecked
   ui->enPoendorf->setChecked(false);
   ui->enPoendorf->setDisabled(checked);



}
