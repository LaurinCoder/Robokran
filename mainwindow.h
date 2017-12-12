#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QSignalMapper>
#include <QDebug>
#include <QTime>
#include <QLCDNumber>
#include <QTimer>
#include <QMessageBox>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QStatusBar>
#include <QProcess>
#include <QtMath>
//OPC class
#include "open62541.h"
//for csv files
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItemModel>

//for GripPoint
#include "grippoint.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    //Für GP
        GripPoint* gripPoint;
        int xGp = 0;
        int yGp = 0;
        int zGp = 0;
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    bool conversion_OK;
    void update_UI();
    void TeachIn();

// for Inverskinematik
//    float Zsoll = 0;
//    float Ysoll = 0;
//    float Xsoll = 0;
//    float a = 710;
//    float b = 1550;
//    float c = 0;
//    float d = 6800 + 1800;
//    float e = 1106;
//    float f = 279;
//    float g = 258;
//    float i = 449;
//    float q30 = 1470;

//    cosB0 = qSqrt(a*a + b*b -q30*q30)/(2*a*b);
//    sinB0 = (1 - qPow(cosB0, 2));
//    float h = qSqrt(qPow(g,2) + c);
//    float sinA1 = g/h;
//    float cosA1 = c/h;
//    float cosB0B1 = (qPow(a,2) + qPow(b,2))/(2*a*b);
//    float p = 2*sinB0*cosB0B1;
//    float q = qPow(cosB0B1,2) - qPow(cosB0,2);
//    float sinB1 = -p/2 + qSqrt(qPow((p/2),2) -q);
//    float cosB1 = qSqrt(1 - qPow(sinB1,2));
//    float sinA1B1 = sinA1*cosB1 + cosA1*sinB1;
//    float DeltaZ = h * sinA1B1;
//    float DeltaX = h * qSqrt(1 -qPow(sinA1B1,2));
//    float cosB; //wird überhaupt gebraucht?


//    UA_Float posSollTestValue[8] ;



//Message Boxen
    QMessageBox msgBox_invalidPose;
    QMessageBox msgBox_movementWarning;
    QAbstractButton* retryButton;

// for TeachIn
    bool teachInLast = 0; //Hysterese Speicherplatz der Steuerung in cm
    int wartezeitZaehler = 0; //Zähler für Wartezeit, Zählgeschw abhängig vom Cylce
    float liftRatioUp = 0.97; /*liftRatio ist prozentual wie viel kürzer die Hubzylinderlänge sein soll in wayPoint 250 als wayPoint 251; unter 1 ist kürzer als 251*/
    float liftRatioDown = 1.1; /*liftRatio ist prozentual wie viel kürzer die Hubzylinderlänge sein soll in wayPoint 250 als wayPoint 251; unter 1 ist kürzer als 251*/
    int hubHighestPoint = 1550; /*gibt an, wie hoch der Hub bei den Greifwaypoints fahren soll*/
    bool cyclic = 0;    //path wird wiederholend ausgeführt
    bool resetPath = 0; //resetet den waypoint auf 0
    bool saveWayPoint = 0; //Speichert die aktuellen Gelenkskoordinaten als neuen wayPoint
    bool setGPActive = 0; //TRUE schaltet die wayPoints aus dem Telegram vom Laserscanner im TeachIn Pfad aktiv

//for csv files
    QList<QStringList> csv;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;

//von Arduino Control
    int getDataFloat(QByteArray waypointsByteArray);
    int searchIndex; //für Datenextraktion



    QString uhrzeitString = "";
    QTime timerWaypoint;


 // für TeachIn
    bool teachIn = 0; //startet teachIn
    int wayPointPause = 5;

    QString startTeachIn = "0";
    QByteArray inString;
    int wayPointNr = 0;
    bool flanke = 0;
    bool runPath = 0;  //starte den gespeicherten Pfad

 //für Qfile
    QFile waypointsRead;
    QFile waypointsWrite;

 //FÜR LASERSCANNER
    QString LMS_data;
    QString IP_LMS;  //festgelegt IPs der Laserscanner
    QString datadirectory;
    QTcpSocket *LMS_111;
    QFile laserdata;     //file für Laserdaten
    bool LMS_connected = 0;
    bool scan_inProcess = 0;
    short int sequenceCounter = -1;
    int scanFrom = 0;
    int scanTo = 0;
    QProcess process; //zum Ausführen von Programmen, hier gedit

  //Für GP Berechnung
//    QFile gripPoint; //enthält den berechneten Greifpunkt
    QString fileName = tr("./20170714_01.log");
    bool showHist = 0;
    bool showSurface = 1;

 /* AB HIER FÜR OPC_UA */
    QTimer *activeTimer;  //für OPC_UA
    UA_Client *client;
    UA_StatusCode retval;
    UA_Variant posIst; /* Variants can hold scalar values and arrays of any type */
    UA_Variant posSoll;
    UA_Variant posSollInv;
    UA_Variant Xsoll;
    UA_Variant Ysoll;
    UA_Variant Zsoll;
    UA_Variant posOk;
    UA_Variant Auto;
    UA_Variant hys;
    UA_Variant oldHys;
    float path[8][256] = {{0}};  /*wayPoints / path des TeachIns*/
//    int pathSaveFile[8][256] = {{0}}; //für path in file speichern und umgekehrt
    UA_Boolean AutoValue;
    UA_Boolean posOkValue[8] ={0};
    UA_Float posIstValue[8] ;
    UA_Float posSollValue[8] = {0};
    UA_Float posSollInvValue[8] = {0};
    UA_Float XsollValue = 0;
    UA_Float YsollValue = 0;
    UA_Float ZsollValue = 0;
    UA_Float hysValue[8];
    UA_Float oldHysValue[8];

    const UA_NodeId nodePosIst = UA_NODEID_STRING(6, "::AsGlobalPV:posIst");
    const UA_NodeId nodePosSoll = UA_NODEID_STRING(6, "::AsGlobalPV:posSoll");
    const UA_NodeId nodePosSollInv = UA_NODEID_STRING(6, "::InversKine:posSollTest");
    const UA_NodeId nodeXsoll = UA_NODEID_STRING(6, "::AsGlobalPV:Xsoll");
    const UA_NodeId nodeYsoll = UA_NODEID_STRING(6, "::AsGlobalPV:Ysoll");
    const UA_NodeId nodeZsoll = UA_NODEID_STRING(6, "::AsGlobalPV:Zsoll");
    const UA_NodeId nodePosOk = UA_NODEID_STRING(6, "::AsGlobalPV:posOk");
    const UA_NodeId nodeAuto = UA_NODEID_STRING(6, "::AsGlobalPV:Auto");
    const UA_NodeId nodePath = UA_NODEID_STRING(6, "::AsGlobalPV:path");
    const UA_NodeId nodeHys = UA_NODEID_STRING(6, "::AsGlobalPV:hys");



/* BIS HIER FÜR OPC_UA */

    QString lineEditStyleYellow = ("QLineEdit{background: yellow;}");
    QString lineEditStyleGreen = ("QLineEdit{background: lightgreen;}");
    QString lineEditStyleRed = ("QLineEdit{background: red;}");
    QString pushButtonStyleGreen = ("QPushButton{ background-color: lightgreen }");
    QString pushButtonStyleNone = ("QPushButton{  }");

private slots:

    void on_copyIstPos_clicked();

    void activateOpcSync();  //für OPC_UA

    void on_enableJoints_clicked(bool checked);

    void on_startTeachIn_clicked(bool checked);

    void on_saveWaypoint_clicked();

    void on_setGrippingPoint_clicked();

    void on_setGrippingPointManual_clicked();

    void checkString(QString &temp, QChar character = 0);

    void on_actionchooseFile_triggered();

    void sendSollLFahrt();void sendSollDrehung();void sendSollAusschub();void sendSollHub();void sendSollGreifer();

    void on_writeCsv_clicked();

    void on_runPath_clicked(bool checked);

    void on_cyclePath_clicked(bool checked);

    void on_includeGP_clicked(bool checked);

    void on_resetPath_clicked();

    void on_actionVerbinde_mit_SPS_triggered();

    void on_actionVerbindung_trennen_triggered();

    void on_wayPointPause_valueChanged(double arg1);

    //AB HIER FÜR LASERSCANNER

   void on_actionVerbinde_mit_Laserscanner_triggered();

   void connected();

   void on_actionPfad_des_Arrays_anzeigen_triggered();


   void on_uebernehmePfad_clicked();

   void on_speicherortFestlegen_clicked();

   void on_singleScan_clicked();

   void readyRead();

   void on_scanSequence_toggled(bool checked);

   void scanSequence();

   //Ab hier für Greifpunktberechnung

   void on_selectData_clicked();

   void on_calculateGP_clicked();

   void on_calculateInvers_clicked();

   void on_copySollPos_clicked();

signals:




};



#endif // MAINWINDOW_H
