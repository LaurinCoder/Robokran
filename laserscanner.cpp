#include "mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::on_actionVerbinde_mit_Laserscanner_triggered()
{

        IP_LMS = "169.254.56.85";
        qDebug() << "Connecting to Laserscanner IP:" <<IP_LMS;

        LMS_111->connectToHost(IP_LMS, 2111);

//        warten bis Verbingung steht und Ausgabe falls Error auftritt
        if(!LMS_111->waitForConnected(2000))
        {
             qDebug() << "Connection failed.";
        }
}

void MainWindow::connected()
{
    LMS_connected = 1;
    statusBar()->showMessage(tr("Connected to LMS"),5000);
    qDebug() << "Connected!";   //ausgabe der erfolgreichen Herstellung der Verbindung
}

void MainWindow::on_speicherortFestlegen_clicked()
{
    datadirectory = QFileDialog::getSaveFileName(this, tr("Speicherort festlegen..."),
                                                 "/home/iltuser/Schreibtisch/QT_Sources/",tr("Text Files (*.txt);;log Files (*.log)"));
    qDebug() << "Speicherort festgelegt:  \n" << datadirectory;

    //wenn file existiert, File löschen, um es zu überschreiben, das sagt auch die Dialogfenster, wenn ein bestehendes File ausgewählt wird.
    laserdata.setFileName(datadirectory);
    if (laserdata.exists()) {
        laserdata.remove();
    }

}

void MainWindow::on_singleScan_clicked()
{
    if(!datadirectory.isEmpty())
    {
        laserdata.setFileName(datadirectory);
        if (laserdata.exists()) {
            laserdata.remove();
        }
        if(LMS_connected)
        {
            laserdata.setFileName(datadirectory);
            LMS_111->write("\02sRN LMDscandata\03");
            statusBar()->showMessage(tr("Messfächer gespeichert"), 5000);
        }
        else
            statusBar()->showMessage(tr("LMS not connected"), 5000);
    }

    else
        statusBar()->showMessage(tr("Speicherort nicht ausgewählt"), 5000);
}

void MainWindow::readyRead()  //einlesen der Daten vom LMS und Übergabe an Datei
{
    //Öffnen der Datei
    laserdata.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text);

    //Übergabe des Streams an String
    LMS_data=(LMS_111->readAll());



    LMS_data.replace(QString((char)3), QString("\n"));
    LMS_data.replace(QString((char)2), QString(""));

    QTextStream datastream(&laserdata);
    datastream << LMS_data;// << "\n";
    datastream.flush();

    laserdata.close();

    if(scan_inProcess)
    {
//        int barValue = ui->progressBar->value();
//        barValue += 1;
        int barValue = 100 - int(100 * ((posIstValue[0]-scanTo)/(scanFrom - scanTo) )); //Fortschritt berechnen

        ui->progressBar->setValue(barValue);
    }
}

void MainWindow::on_scanSequence_toggled(bool checked)
{


    if(!datadirectory.isEmpty())
    {
        laserdata.setFileName(datadirectory);
        if (laserdata.exists() && checked) {
            laserdata.remove();
        }
        if(LMS_connected)
        {
            if(checked)
            {
                int ret = msgBox_movementWarning.exec();
                if (ret == QMessageBox::AcceptRole) {
                    scanFrom    = ui->scanFrom->value(); //Werte von Feldern in der Gui übernehmen
                    scanTo      = ui->scanTo->value();

//                    if (scanFrom == posIstValue[0]) {           //Prüfung für definierte Kranstellung einfügen, die sicher für die Scanfahrt ist.

                            scan_inProcess = 1; sequenceCounter = 0;
                            ui->progressBar->setValue(10);
//                        }
//                    else
//                    {
//                        ui->scanSequence->setChecked(false); //ScanSequence beenden, darin wird Laserscanner gestoppt.
//                            msgBox_invalidPose.exec();

//                     }
                }
                else              ui->scanSequence->setChecked(0);


            }

            else
            {
                scan_inProcess = 0; sequenceCounter = -1;
                on_enableJoints_clicked(checked); //AUTO AUSSCHALTEN
                ui->progressBar->setValue(0);
                LMS_111->write("\02sEN LMDscandata 0\03");
            }
        }
        else
        {
            statusBar()->showMessage(tr("LMS not connected"), 5000);
            ui->scanSequence->setChecked(0);
        }
    }

    else
    {
        statusBar()->showMessage(tr("Speicherort nicht ausgewählt"), 5000);
        ui->scanSequence->setChecked(0);
    }
}

void MainWindow::scanSequence()
{if (scan_inProcess) {
        //Prüfen ob Position vor dem Scan überprüft werden soll (schnelle Scanfahrt)
        if (ui->noPositionCheck->isChecked()) {
//Schnelle Scanfahrt ohne Positionsüberprüfung aller Achsen
        switch (sequenceCounter) {
        case 0:
                statusBar()->showMessage(tr("Fahre zur Startposition"));
                on_enableJoints_clicked(true);
                ui->sollLFahrt->setValue(scanFrom);
                sendSollLFahrt();
                sequenceCounter++;
            break;
        case 1:
            if ((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
                    posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7])
                        && posIstValue[0] == posSollValue[0] && posIstValue[1] == posSollValue[1] && posIstValue[2] == posSollValue[2]
                        && posIstValue[3] == posSollValue[3] && posIstValue[4] == posSollValue[4]  && posIstValue[5] == posSollValue[5]
                        && posIstValue[6] == posSollValue[6] && posIstValue[7] == posSollValue[7]) //nur im Labor wichtig!!!!!, in Pöndorf letzte 3 Zeilen deaktivieren!!!) {
        {
            qDebug() << "Startposition erreicht";
            qDebug() << "Scanner starten";
            qDebug() << "tatsächliche Scanposition einlesen";

            //posIst[0] einlesen
            retval = UA_Client_readValueAttribute(client, nodePosIst,&posIst);
            if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasArrayType(&posIst,&UA_TYPES[UA_TYPES_FLOAT]) ) {
                    scanFromReal =(int)*(UA_Float*)posIst.data;
                }
            ui->scanFromReal->setEnabled(true);
            ui->scanFromReal->setValue(scanFromReal);
            LMS_111->write("\02sEN LMDscandata 1\03");  //starte Scanner
            qDebug() << "Zielposition anfahren";
            ui->sollLFahrt->setValue(scanTo);
            sendSollLFahrt();
            statusBar()->showMessage(tr("Scanne..."));
            sequenceCounter ++;
            }

            break;
        case 2:
            if ((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
                    posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7])
                        && posIstValue[0] == posSollValue[0] && posIstValue[1] == posSollValue[1] && posIstValue[2] == posSollValue[2]
                        && posIstValue[3] == posSollValue[3] && posIstValue[4] == posSollValue[4]  && posIstValue[5] == posSollValue[5]
                        && posIstValue[6] == posSollValue[6] && posIstValue[7] == posSollValue[7] //nur im Labor wichtig!!!!!, in Pöndorf letzte 3 Zeilen deaktivieren!!!) {
                )
            {
            qDebug() << "Zielposition erreicht";
            qDebug() << "Scanner stoppen";
            process.start("gedit", QStringList() << datadirectory);
            ui->scanSequence->setChecked(false); //ScanSequence beenden, darin wird Laserscanner gestoppt.
            statusBar()->showMessage(tr("Scan abgeschlossen!"));
            sequenceCounter = -1;
            }
            break;
        case 3:

            break;
        default:
            break;
        }
        }

 else {
        //komplette Positionsüberprüfung aller Achsen
        switch (sequenceCounter) {
        //Ausschub vor dem Scannen einziehen
        case 0:
                statusBar()->showMessage(tr("Ausschub in Position bringen."));
                on_enableJoints_clicked(true);
                ui->sollAusschub->setValue(scanFromAusschub1);
                sendSollAusschub();
                sequenceCounter++;
            break;
        // wenn Ausschub < "scanFromAusschub2" dann auch heben.
        case 1:
            if (posIstValue[4] < scanFromAusschub2)
        {
                statusBar()->showMessage(tr("Arm und Ausschub in Position bringen."));
                ui->sollHub->setValue(scanFromHub);
                sendSollHub();
                sequenceCounter++;
            }
        //wenn Position erreicht, dann 0° ausrichten.
        case 2:
            if ((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
                    posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7])
                        && posIstValue[0] == posSollValue[0] && posIstValue[1] == posSollValue[1] && posIstValue[2] == posSollValue[2]
                        && posIstValue[3] == posSollValue[3] && posIstValue[4] == posSollValue[4]  && posIstValue[5] == posSollValue[5]
                        && posIstValue[6] == posSollValue[6] && posIstValue[7] == posSollValue[7]) //nur im Labor wichtig!!!!!, in Pöndorf letzte 3 Zeilen deaktivieren!!!) {
        {
                statusBar()->showMessage(tr("0° ausrichten."));
                ui->sollDrehen->setValue(scanFromDrehung);
                sendSollDrehung();
                sequenceCounter++;
            }
        //wenn Position erreicht, dann zur Startposition fahren.
        case 3:
            if ((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
                    posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7])
                        && posIstValue[0] == posSollValue[0] && posIstValue[1] == posSollValue[1] && posIstValue[2] == posSollValue[2]
                        && posIstValue[3] == posSollValue[3] && posIstValue[4] == posSollValue[4]  && posIstValue[5] == posSollValue[5]
                        && posIstValue[6] == posSollValue[6] && posIstValue[7] == posSollValue[7]) //nur im Labor wichtig!!!!!, in Pöndorf letzte 3 Zeilen deaktivieren!!!) {
        {
                statusBar()->showMessage(tr("Fahre zur Startposition."));
                ui->sollLFahrt->setValue(scanFrom);
                sendSollLFahrt();
                sequenceCounter++;
            }
        //Scannen starten und tatsächliche Scannposition in "scanFromReal" speichern
        case 4:
            if ((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
                    posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7])
                        && posIstValue[0] == posSollValue[0] && posIstValue[1] == posSollValue[1] && posIstValue[2] == posSollValue[2]
                        && posIstValue[3] == posSollValue[3] && posIstValue[4] == posSollValue[4]  && posIstValue[5] == posSollValue[5]
                        && posIstValue[6] == posSollValue[6] && posIstValue[7] == posSollValue[7]) //nur im Labor wichtig!!!!!, in Pöndorf letzte 3 Zeilen deaktivieren!!!) {
        {
            qDebug() << "Startposition erreicht";
            qDebug() << "Scanner starten";
            qDebug() << "tatsächliche Scanposition einlesen";

            //posIst[0] einlesen
            retval = UA_Client_readValueAttribute(client, nodePosIst,&posIst);
            if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasArrayType(&posIst,&UA_TYPES[UA_TYPES_FLOAT]) ) {
                    scanFromReal =(int)*(UA_Float*)posIst.data;
                }
            ui->scanFromReal->setEnabled(true);
            ui->scanFromReal->setValue(scanFromReal);
            LMS_111->write("\02sEN LMDscandata 1\03");  //starte Scanner
            qDebug() << "Zielposition anfahren";
            ui->sollLFahrt->setValue(scanTo);
            sendSollLFahrt();
            statusBar()->showMessage(tr("Scanne..."));
            sequenceCounter ++;
            }

            break;
        case 5:
            if ((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
                    posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7])
                        && posIstValue[0] == posSollValue[0] && posIstValue[1] == posSollValue[1] && posIstValue[2] == posSollValue[2]
                        && posIstValue[3] == posSollValue[3] && posIstValue[4] == posSollValue[4]  && posIstValue[5] == posSollValue[5]
                        && posIstValue[6] == posSollValue[6] && posIstValue[7] == posSollValue[7] //nur im Labor wichtig!!!!!, in Pöndorf letzte 3 Zeilen deaktivieren!!!) {
                )
            {
            qDebug() << "Zielposition erreicht";
            qDebug() << "Scanner stoppen";
            process.start("gedit", QStringList() << datadirectory);
            ui->scanSequence->setChecked(false); //ScanSequence beenden, darin wird Laserscanner gestoppt.
            statusBar()->showMessage(tr("Scan abgeschlossen!"));
            sequenceCounter = -1;
            }
            break;
        case 6:

            break;
        default:
            break;
        }
    }
   }
}


