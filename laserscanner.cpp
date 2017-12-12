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
}

void MainWindow::on_singleScan_clicked()
{
    if(!datadirectory.isEmpty())
    {
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
        if(LMS_connected)
        {
            laserdata.setFileName(datadirectory);

            if(checked)
            {
                int ret = msgBox_movementWarning.exec();
                if (ret == QMessageBox::AcceptRole) {
                    scanFrom    = ui->scanFrom->value(); //Werte von Feldern in der Gui übernehmen
                    scanTo      = ui->scanTo->value();

                    if (scanFrom == posIstValue[0]) {           //Prüfung für definierte Kranstellung einfügen, die sicher für die Scanfahrt ist.

                            scan_inProcess = 1; sequenceCounter = 0;
                            ui->progressBar->setValue(10);
                        }
                    else
                    {
                        ui->scanSequence->setChecked(false); //ScanSequence beenden, darin wird Laserscanner gestoppt.
                            msgBox_invalidPose.exec();

                     }
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


