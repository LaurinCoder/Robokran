#include "mainwindow.h"
#include "ui_mainwindow.h"

//Verbindung zu LMS herstellen, IP im HEADER "mainwindow.h" festgelegt
void MainWindow::on_connectLMS_triggered()
{
        qDebug() << "Verbinde mit Laserscanner, IP: " << IP_LMS;
        LMS_111->connectToHost(IP_LMS, 2111);

//        warten bis Verbingung steht und Ausgabe falls Error auftritt
        if(!LMS_111->waitForConnected(3000))
        {
             qDebug() << "Verbindung fehlgeschlagen! Laserscanner eingeschaltet? IP richtig?";
        }
}

//Slot für SIGNAL "Connected" von LMS_111 Objekt
void MainWindow::connected()
{
    LMS_connected = 1;
    statusBar()->showMessage(tr("Verbunden mit Laserscanner LMS110."),5000);
    qDebug() << "Laserscanner verbunden!";   //ausgabe der erfolgreichen Herstellung der Verbindung
}

//Datei für Laserscandaten auswählen
void MainWindow::on_saveAs_clicked()
{
    datadirectory = QFileDialog::getSaveFileName(this, tr("Speicherort festlegen..."),
                                                 "/home/iltuser/Schreibtisch/QT_Sources/",tr("Text Files (*.txt);;log Files (*.log)"));
    qDebug() << "Speicherort festgelegt:  \n" << datadirectory;

    //wenn file existiert, File löschen, um es neu zu erstellen. Diese Warnung gibt auch das Dialogfenster aus, wenn ein bestehendes File ausgewählt wird. Ohne die Datei zu löschen würde allerdings nur an die bestehende Datei angehängt werden.
    laserdata.setFileName(datadirectory);
    if (laserdata.exists()) {
        laserdata.remove();
    }
}

//Einzelnen Scanfächer in Datei speichern. Überschreiben, falls Datei bereits vorhanden.
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
            statusBar()->showMessage(tr("LMS nicht verbunden."), 5000);
    }

    else
        statusBar()->showMessage(tr("Speicherort nicht ausgewählt"), 5000);
}

//Slot für SIGNAL "readyRead" von LMS_111 Objekt. Einlesen der Daten vom LMS und Übergabe an Datei
void MainWindow::readyRead()
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
        int barValue = 100 - int(100 * ((posIstValue[0]-scanTo)/(scanFrom - scanTo) )); //Fortschritt berechnen

        ui->progressBar->setValue(barValue);
    }
}

//Schalter-Funktion für Aktivierung/Deaktivierung der Scanfahrt und speichern der Start-/Endposition der Scanfahrt
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
                    scan_inProcess = 1;
                    sequenceCounter = 0;
                    ui->progressBar->setValue(10);
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
            statusBar()->showMessage(tr("LMS nicht verbunden."), 5000);
            ui->scanSequence->setChecked(0);
        }
    }

    else
    {
        statusBar()->showMessage(tr("Speicherort nicht ausgewählt."), 5000);
        ui->scanSequence->setChecked(0);
    }
}

//tatsächeliches Switch_case für die Scanfahrt. Mit/ohne Posenprüfung.
void MainWindow::scanSequence()
{if (scan_inProcess) {
        //Prüfen ob Pose vor dem Scan überprüft werden soll (nein --> schnelle Scanfahrt || ja --> Kran wird in Scanpose gebracht, vor der Scanfahrt)
        if (ui->noPoseCheck->isChecked()) {
//Schnelle Scanfahrt ohne Posenprüfung vor der Scanfahrt
        switch (sequenceCounter) {
        case 0:
                statusBar()->showMessage(tr("Fahre zur Startposition"));
                on_enableJoints_clicked(true);
                ui->sollLFahrt->setValue(scanFrom);
                sendSollLFahrt();
                counterLaserscan = 0;
                sequenceCounter++;
            break;
        case 1:
            if ((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
                    posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7] && counterLaserscan > (caseBrakeLaserscan + 180)))
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
            counterLaserscan = 0;
            sequenceCounter ++;
            }

            break;
        case 2:
            if ((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
                    posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7] && counterLaserscan > caseBrakeLaserscan))
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
        //Kran wird in Scanpose gebracht, bevor er die Startposition anfährt.
        switch (sequenceCounter) {
        //Ausschub vor dem Scannen einziehen
        case 0:
                statusBar()->showMessage(tr("Ausschub in Position bringen."));
                on_enableJoints_clicked(true);
                ui->sollAusschub->setValue(scanFromAusschub1);
                sendSollAusschub();
                qDebug() << "Ausschub einziehen.";
                sequenceCounter++;
            break;
        // wenn Ausschub < "scanFromAusschub2" dann auch heben.
        case 1:
            if (posIstValue[4] < scanFromAusschub2)
        {
                statusBar()->showMessage(tr("Arm und Ausschub in Position bringen."));
                ui->sollHub->setValue(scanFromHub);
                sendSollHub();
                qDebug() << "Mindestausschub erreicht. Hubsteuerung aktivieren.";
                counterLaserscan = 0;
                sequenceCounter++;
            }
            break;
        //wenn Ausschub und Hub erreicht, dann 0° ausrichten.
        case 2:
            if ((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
                    posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7] && counterLaserscan > caseBrakeLaserscan))
            {
                statusBar()->showMessage(tr("0° ausrichten."));
                ui->sollDrehen->setValue(scanFromDrehung);
                sendSollDrehung();
                qDebug() << "Hub und Ausschubposition erreicht. Drehe auf 0 Grad.";
                counterLaserscan = 0;
                sequenceCounter++;
            }
            break;
        //wenn Position erreicht, dann zur Startposition fahren.
        case 3:
            if ((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
                    posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7]&& counterLaserscan > caseBrakeLaserscan))
            {
                statusBar()->showMessage(tr("Fahre zur Startposition."));
                ui->sollLFahrt->setValue(scanFrom);
                sendSollLFahrt();
                qDebug() << "Scanstellung erreicht. Fahre zur Startposition.";
                counterLaserscan = 0;
                sequenceCounter++;
            }
            break;
        //Scannen starten und tatsächliche Scannposition in "scanFromReal" speichern
        case 4:
            if ((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
                    posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7]&& counterLaserscan > (caseBrakeLaserscan + 80)))
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
            counterLaserscan = 0;
            sequenceCounter ++;
            }

            break;
        case 5:
            if ((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
                    posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7]&& counterLaserscan > caseBrakeLaserscan))
            {
            qDebug() << "Zielposition erreicht";
            qDebug() << "Scanner stoppen";
            process.start("gedit", QStringList() << datadirectory); // Scanfile wird geöffnet
            ui->scanSequence->setChecked(false); //ScanSequence beenden, darin wird Laserscanner gestoppt.
            statusBar()->showMessage(tr("Scan abgeschlossen!"));
            counterLaserscan = 0;
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

