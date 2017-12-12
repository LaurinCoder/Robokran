#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::scanSequence()
{if (scan_inProcess) {
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

}


