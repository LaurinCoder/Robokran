#include "mainwindow.h"
#include "ui_mainwindow.h"

//TeachIn, speichert aktuelle Kranposition als Wegpunkt (Knopf schaltet )
void MainWindow::TeachIn()
{
    //TeachIn Funktion
    if(teachIn)
    {
        //Automatikmodus deakitvieren
        AutoValue = 0;
        on_enableJoints_clicked(AutoValue);

        if(saveWayPoint && wayPointNr < 246)
        {
            //speichert alle Gelenkskoordinaten als Wegpunkt
            for(int i = 0; i < 8; i++) path[i][wayPointNr] = posIstValue[i];

            // ins Log schreiben
            ui->teachInLog->append("Waypoint "+ QString::number(wayPointNr+1) + " saved.");

            //Plausibilät des nächsten Wegpunktes entfernen
            path[4][wayPointNr + 1] = 0;
            wayPointNr++;
            saveWayPoint = 0;
        }
        else {
            ui->teachInLog->append("Fehler: Maximale Anzahl an Waypoints erreicht.");
        }
    }
    //Flanke in Teach in erkennen
    if (teachIn != teachInLast) wayPointNr = 0;
    teachInLast = teachIn;
}

//Pfadsteuerung
void MainWindow::runPath()
{
    //Automatikmodus deaktivieren, deaktiviert auch die Pfadsteuerung
    if(!AutoValue) {enableRunPath = 0; ui->runPath->setChecked(false);}

    //start der Pfadsteuerung aktiviert Automatikmodus

    if(enableRunPath && AutoValue)
    {
        //Überprüfen ob alle Sollwerte des Wegpunktes.. //... ob posIst gleich posSoll ist, weil posOk von der SPS kommt und dann gibts ein Timing Problem, also muss beides posOk und posSoll == posIst passen
        //...oder letzter Wegpunkt erreicht wurde
        if((posOkValue[0]&&posOkValue[1]&&posOkValue[2]&&posOkValue[3]&&
            posOkValue[4]&&posOkValue[5]&&posOkValue[6]&&posOkValue[7])
                /*&& posIstValue[0] == posSollValue[0] && posIstValue[1] == posSollValue[1] && posIstValue[2] == posSollValue[2]
                && posIstValue[3] == posSollValue[3] && posIstValue[4] == posSollValue[4]  && posIstValue[5] == posSollValue[5]
                && posIstValue[6] == posSollValue[6] && posIstValue[7] == posSollValue[7]*/ //nur im Labor wichtig!!!!!, in Pöndorf letzte 3 Zeilen deaktivieren!!!

                //...oder letzter Wegpunkt erreicht wurde
                && path[4][wayPointNr] != 0)

        {
            if (flanke)
            {
                timerWaypoint.restart();
                flanke = false;
            }
            //path[3][252] wird manipuliert, abhängig von der tatsächlich erreichten Position in 251
            if (wayPointNr == 252) path[3][wayPointNr] = posIstValue[3] * liftRatioUp;

            if( timerWaypoint.elapsed() > (1000 * wayPointBreak) )
            {
                //setzt alle Gelenkskoordinaten des Wegpunkts auf Sollwerte
                for(int i = 0; i < 8; i++) posSollValue[i] = path[i][wayPointNr];
               wayPointNr++;

                //Hysteresen werden gespeichert und für 250,251, 252 vergrößert
                if (wayPointNr == 250)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        oldHysValue[i] = hysValue[i];
                    }
                    hysValue[0] = oldHysValue[0] * 5;
                    hysValue[2] = oldHysValue[2] * 5;
                    //hys schreiben
                    UA_Variant_setArray(&hys, &hysValue, 8, &UA_TYPES[UA_TYPES_FLOAT]);
                    retval = UA_Client_writeValueAttribute(client, nodeHys,&hys);
                }
                //Hysteresen werden wieder zurückgesetzt
                else if (wayPointNr == 253)
                {
                    //oldHys schreiben
                    UA_Variant_setArray(&hys, &oldHysValue, 8, &UA_TYPES[UA_TYPES_FLOAT]);
                    retval = UA_Client_writeValueAttribute(client, nodeHys,&hys);
                }


                //posSoll schicken
                UA_Variant_setArray(&posSoll, &posSollValue, 8, &UA_TYPES[UA_TYPES_FLOAT]);
                retval = UA_Client_writeValueAttribute(client, nodePosSoll,&posSoll);
                flanke = true;
            }

        }

        //Überprüfen ob zyklisch oder antizyklisch, mit Greifpunkt oder ohne
        if      (path[4][wayPointNr] == 0 && setGPActive && wayPointNr < 247)			wayPointNr = 247;
        else if (path[4][wayPointNr] == 0 && setGPActive)	           					wayPointNr = 0;
        else if (cyclic && path[4][wayPointNr] == 0 && !setGPActive) 					wayPointNr = 0;
        else if (path[4][wayPointNr] == 0) 												{wayPointNr = 0; enableRunPath = false; AutoValue = false;}
    }

    //bei Reset und außerhalb von TeachIn wird Pfad auf Startposition zurückgesetzt
    if(resetPath && !teachIn) {wayPointNr = 0; resetPath = 0;}

    ui->waypointNr->display(wayPointNr);
}

//SPS Verbindung herstellen
void MainWindow::on_connectSPS_triggered()
{   client = UA_Client_new(UA_ClientConfig_standard);
    retval = UA_Client_connect(client, SpsIp);
    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        ui->statusBar->showMessage(tr("ERRIOR: Verbindung fehlgeschlagen."),5000);
    }
    else    {
            ui->statusBar->showMessage(tr("Verbindung zur SPS hergestellt."),5000);
            activeTimer->start(); //timer für OPC Aktualisierung starten
            timerWaypoint.start(); //timer für waypointpause starten
        }
    ui->wayPointBreak->setValue(wayPointBreak);
}

//SPS Verbindung trennen
void MainWindow::on_disconnectSPS_triggered()
{
    if (UA_Client_getState(client) == true)
    {
        UA_Client_delete(client);
        if (UA_Client_getState(client) != true)   ui->statusBar->showMessage(tr("Verbindung erfolgreich getrennt."),5000);

    }
    else  ui->statusBar->showMessage(tr("Trennen nicht möglich, keine bestehende Verbindung."),5000);
}

//momentane Ist Positionswerte in Soll-Positionswerte der GUI kopieren
void MainWindow::on_copyIstPos_clicked()
{
    ui->sollLFahrt->setValue(ui->istLFahrt->text().toDouble());
    ui->sollDrehen->setValue(ui->istDrehen->text().toDouble());
    ui->sollHub->setValue(ui->istHub->text().toDouble());
    ui->sollAusschub->setValue(ui->istAusschub->text().toDouble());
    ui->sollGreifer->setValue(ui->istGreifer->text().toDouble());
}

//Aktivieren des Auto Modus. Auto wird nur aktiviert, wenn OPC Client verbunden.
void MainWindow::on_enableJoints_clicked(bool checked)
{
    if (UA_Client_getState(client) == 1) {
        //Auto schreiben
        AutoValue = checked;
        UA_Variant_setScalar(&Auto,&AutoValue,&UA_TYPES[UA_TYPES_BOOLEAN]);
        retval = UA_Client_writeValueAttribute(client, nodeAuto,&Auto);
        //Falls Scan gerade abläuft und auto deaktiviert wird, wird der Scan unterbrochen
        if (scan_inProcess && !checked) {
            ui->scanSequence->setChecked(false);
            scan_inProcess = 0; sequenceCounter = -1;
            ui->progressBar->setValue(0);
            LMS_111->write("\02sEN LMDscandata 0\03");
            ui->statusBar->showMessage(tr("Scan gestoppt, weil Auto deaktiviert wurde."),10000);
        }
     }
    else
    {
        ui->enableJoints->setChecked(false);
        ui->statusBar->showMessage(tr("Verbindung zur SPS nicht hergestellt."),5000);
    }

}

//Brechneten Greifpunkt aus der Inverskinematik in den Pfad speichern.
void MainWindow::on_setGrippingPointInv_clicked()
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

    //path[2,x] setzen, zu Beginn und Ende des Greifvorganges, soll der Kran 0° ausgerichtet sein. Damit der Kran im Pfad für das TeachIn des restlichen Pfades eine definierten Start und Endpose einnimmt.
    path[2][247] = 0;
    path[2][254] = 0;

    //path[3,250, 251] neu speichern - liftRatioDown / Up ist prozentual wie viel kürzer/länger die Hubzylinderlänge sein soll. hubHighestPoint ist hardcoded höchster Hub.
    path[3][247] = hubHighestPoint;
    path[3][248] = hubHighestPoint;
    path[3][249] = hubHighestPoint;
    path[3][250] = path[3][252] * liftRatioDown;
    path[3][251] = path[3][252] * liftRatioDown;
  //path[3][252 ] =
    path[3][253] = hubHighestPoint;
    path[3][254] = hubHighestPoint;

    //path[4,x] setzen
    path[4][247] = 370;
    path[4][248] = 370;
    path[4][253] = 420;
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

//Aktuelle Position als Greifpunkt in den Pfad speichern.
void MainWindow::on_setGrippingPointTeachIn_clicked()
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

    //path[2,x] setzen, zu Beginn und Ende des Greifvorganges, soll der Kran 0° ausgerichtet sein. Damit der Kran im Pfad für das TeachIn des restlichen Pfades eine definierten Start und Endpose einnimmt.
    path[2][247] = 0;
    path[2][254] = 0;

    //path[3,250, 251] neu speichern - liftRatioDown / Up ist prozentual wie viel kürzer/länger die Hubzylinderlänge sein soll. hubHighestPoint ist hardcoded höchster Hub.
    path[3][247] = hubHighestPoint;
    path[3][248] = hubHighestPoint;
    path[3][249] = hubHighestPoint;
    path[3][250] = path[3][252] * liftRatioDown;
    path[3][251] = path[3][252] * liftRatioDown;
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

//Flanke zum Wegpunkt speichern setzen
void MainWindow::on_saveWaypoint_clicked() {
    if (teachIn == true) {saveWayPoint = true;}
    else {
        saveWayPoint = false;
        ui->statusBar->showMessage(tr("TeachIn nicht aktiv."),5000);
    }
}

//teachIn BOOL aktivieren/deaktivieren
void MainWindow::on_enableTeachIn_clicked(bool checked) {
    if (UA_Client_getState(client) == 1){
       teachIn = checked;
    }
    else {
        teachIn = false;
        ui->enableTeachIn->setChecked(false);
        ui->statusBar->showMessage(tr("Verbindung zur SPS nicht hergestellt."),5000);
    }
    }

//runPath BOOL aktivieren/deaktivieren
void MainWindow::on_runPath_clicked(bool checked) {enableRunPath = checked;}

//cyclePath BOOL aktivieren/deaktivieren
void MainWindow::on_cyclePath_clicked(bool checked) {cyclic = checked;}

//include Greifpunkt BOOL aktivieren/deaktivieren
void MainWindow::on_includeGP_clicked(bool checked) {setGPActive = checked;}

//Flanke zum Path reseten setzen
void MainWindow::on_resetPath_clicked() {resetPath = true;}

//Pause der Pfadsteuerung zwischen - Wegpunkt erreicht und neuen Wegpunkt setzen - setzen
void MainWindow::on_wayPointBreak_valueChanged(double arg) {wayPointBreak = arg;}
