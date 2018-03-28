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
    void runPath();
    void opcSync();      //Synchronisation mit OPC Server
    void scanSequence(); //Switch_Case Scanfahrt

//GUI
//Message Boxen
    QMessageBox         msgBox_invalidPose;
    QMessageBox         msgBox_movementWarning;
    QAbstractButton*    retryButton;
//csv Handling / Tabelle in der GUI
    QList<QStringList> csv;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;
    int getDataFloat(QByteArray waypointsByteArray);
    int searchIndex; //für Datenextraktion
    QString uhrzeitString = "";
    QTime waypointTimer;
    QFile waypointsRead;
    QFile waypointsWrite;




// für TeachIn und Pfadsteuerung
    bool teachInLast =      0;      //Hysterese Speicherplatz der Steuerung in cm
    float liftRatioUp =     0.97;   /*liftRatio ist prozentual wie viel kürzer die Hubzylinderlänge sein soll in wayPoint 250 als wayPoint 251; kleiner 1 ist kürzer als 251*/
    float liftRatioDown =   1.1;    /*liftRatio ist prozentual wie viel kürzer die Hubzylinderlänge sein soll in wayPoint 250 als wayPoint 251; kleiner 1 ist kürzer als 251*/
    int hubHighestPoint =   1550;   /*gibt an, wie hoch der Hub bei den Greifwaypoints fahren soll*/
    bool cyclic =           0;      //path wird wiederholend ausgeführt
    bool resetPath =        0;      //resetet den waypoint auf 0
    bool saveWayPoint =     0;      //Speichert die aktuellen Gelenkskoordinaten als neuen wayPoint
    bool setGPActive =      0;      //TRUE schaltet die wayPoints aus dem Telegram vom Laserscanner im TeachIn Pfad aktiv
    bool teachIn = 0;               //startet teachIn
    int wayPointBreak = 5;
    QString startTeachIn = "0";
    QByteArray inString;
    int wayPointNr = 0;
    bool flanke = 1;
    bool enableRunPath = 0;  //starte den gespeicherten Pfad



 //LASERSCANNER
    QString LMS_data;
    QString IP_LMS =    "169.254.0.3";      //IP des Laserscanners
    QString datadirectory;
    QTcpSocket *LMS_111;
    QFile laserdata;        //file für Laserdaten
    bool LMS_connected = 0;
    bool scan_inProcess = 0;
    short int sequenceCounter = -1;
    int scanFrom = 0;
    int scanTo = 0;
    int scanFromAusschub1 = 380;
    int scanFromAusschub2 = 480;
    int scanFromHub = 1470;
    int scanFromDrehung = 0;
    int scanFromReal = -1;
    QProcess process;       //zum Ausführen von Anwendungen, hier gedit
    int counterLaserscan = 0;
    int caseBrakeLaserscan = 20;
    bool flankeLaser = 0;

  //Für GP Berechnung
    QString fileName = tr("./20170714_01.log");
    bool showHist           = 0;
    bool showSurface        = 0;
    bool gedreht            = 0;
    long scannerUeberBoden  = 0;
    double inkrementSize    = 0;
    unsigned int leftAngle  = 0;
    unsigned int rightAngle = 0;
    long leftBorder         = 0;
    long rightBorder        = 0;
    unsigned int vRatio     = 0;

 /* AB HIER FÜR OPC_UA */
    //#define SpsIp "opc.tcp://192.168.0.1:4840"   //IP Adresse Boku Keller
    //#define SpsIp "opc.tcp://169.254.25.28:4840"   //IP Adresse Labor Tests mit AutomationPC
    #define SpsIp "opc.tcp://169.254.123.90:4840"   //IP Adresse Lasco Vor-Ort
    QTimer *cycleTimer;  //für OPC_UA
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

    const UA_NodeId nodePosIst = UA_NODEID_STRING(6, (char*)"::AsGlobalPV:posIst");
    const UA_NodeId nodePosSoll = UA_NODEID_STRING(6, (char*)"::AsGlobalPV:posSoll");
    const UA_NodeId nodePosSollInv = UA_NODEID_STRING(6, (char*)"::InversKine:posSollTest");
    const UA_NodeId nodeXsoll = UA_NODEID_STRING(6, (char*)"::AsGlobalPV:Xsoll");
    const UA_NodeId nodeYsoll = UA_NODEID_STRING(6, (char*)"::AsGlobalPV:Ysoll");
    const UA_NodeId nodeZsoll = UA_NODEID_STRING(6, (char*)"::AsGlobalPV:Zsoll");
    const UA_NodeId nodePosOk = UA_NODEID_STRING(6, (char*)"::AsGlobalPV:posOk");
    const UA_NodeId nodeAuto = UA_NODEID_STRING(6, (char*)"::AsGlobalPV:Auto");
    const UA_NodeId nodePath = UA_NODEID_STRING(6, (char*)"::AsGlobalPV:path");
    const UA_NodeId nodeHys = UA_NODEID_STRING(6, (char*)"::AsGlobalPV:hys");



/* BIS HIER FÜR OPC_UA */

    //QlineEdit Schaltflächen Styles
    QString lineEditStyleYellow = ("QLineEdit{background: yellow;}");
    QString lineEditStyleGreen = ("QLineEdit{background: lightgreen;}");
    QString lineEditStyleRed = ("QLineEdit{background: red;}");
    QString pushButtonStyleGreen = ("QPushButton{ background-color: lightgreen }");
    QString pushButtonStyleNone = ("QPushButton{  }");

private slots:

    void on_openReadme_triggered();

    void on_copyIstPos_clicked();

    void x_milliCycle();

    void on_enableJoints_clicked(bool checked);

    void on_enableTeachIn_clicked(bool checked);

    void on_saveWaypoint_clicked();

    void on_setGrippingPointInv_clicked();

    void on_setGrippingPointTeachIn_clicked();

    void checkString(QString &temp, QChar character = 0);

    void on_chooseFile_triggered();

    void sendSollLFahrt();void sendSollDrehung();void sendSollAusschub();void sendSollHub();void sendSollHochsteller();void sendSollRotator();void sendSollGreifer();

    void on_saveCsv_clicked();

    void on_runPath_clicked(bool checked);

    void on_cyclePath_clicked(bool checked);

    void on_includeGP_clicked(bool checked);

    void on_resetPath_clicked();

    void on_connectSPS_triggered();

    void on_disconnectSPS_triggered();

    void on_wayPointBreak_valueChanged(double arg1);

    //AB HIER FÜR LASERSCANNER

   void on_connectLMS_triggered();

   void connected();

   void on_showArrayPath_triggered();

   void on_acceptPath_clicked();

   void on_saveAs_clicked();

   void on_singleScan_clicked();

   void readyRead();

   void on_scanSequence_toggled(bool checked);

   //Ab hier für Greifpunktberechnung

   void on_selectData_clicked();

   void on_calculateGP_clicked();

   void on_calculateInvers_clicked();

   void on_copySollPos_clicked();

   void on_enUserParameter_toggled(bool checked);



signals:




};



#endif // MAINWINDOW_H
