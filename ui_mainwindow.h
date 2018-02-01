/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *connectSPS;
    QAction *disconnectSPS;
    QAction *chooseFile;
    QAction *connectLMS;
    QAction *actionPfad_des_Arrays_anzeigen;
    QAction *openReadme;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_26;
    QHBoxLayout *horizontalLayout_50;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer_6;
    QPushButton *enableTeachIn;
    QPushButton *saveWaypoint;
    QPushButton *setGrippingPointTeachIn;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_9;
    QLCDNumber *waypointNr;
    QTextEdit *teachInLog;
    QSpacerItem *verticalSpacer_5;
    QVBoxLayout *verticalLayout_8;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_20;
    QDoubleSpinBox *wayPointBreak;
    QPushButton *runPath;
    QPushButton *cyclePath;
    QPushButton *includeGP;
    QPushButton *resetPath;
    QSpacerItem *verticalSpacer_7;
    QWidget *tab_3;
    QTableView *tableView;
    QWidget *widget;
    QPushButton *acceptPath;
    QPushButton *saveCsv;
    QWidget *tab_4;
    QPushButton *saveAs;
    QPushButton *singleScan;
    QPushButton *scanSequence;
    QProgressBar *progressBar;
    QGroupBox *groupBox;
    QLabel *label_22;
    QLabel *label_6;
    QSpinBox *scanFrom;
    QSpinBox *scanTo;
    QLabel *label_31;
    QSpinBox *scanFromReal;
    QCheckBox *noPoseCheck;
    QWidget *tab_5;
    QPushButton *selectData;
    QLineEdit *selectedFile;
    QCheckBox *showHist;
    QCheckBox *showSurface;
    QLabel *label_3;
    QLabel *label_12;
    QLineEdit *zGp;
    QLineEdit *yGp;
    QCheckBox *enPoendorf;
    QPushButton *calculateGP;
    QLabel *label;
    QFrame *frame_2;
    QLineEdit *rightBorder;
    QLabel *label_28;
    QLineEdit *leftAngle;
    QCheckBox *enUserSettings;
    QLabel *label_14;
    QLineEdit *rightAngle;
    QLineEdit *leftBorder;
    QLabel *label_15;
    QLabel *label_29;
    QLineEdit *vRatio;
    QLabel *label_30;
    QLabel *label_36;
    QLineEdit *inkrSize;
    QLabel *label_37;
    QLineEdit *groundDist;
    QLineEdit *turned;
    QLabel *label_38;
    QCheckBox *enSopas;
    QLineEdit *xGp;
    QLabel *label_2;
    QWidget *tab_6;
    QLineEdit *zGp_2;
    QLabel *label_10;
    QLineEdit *yGp_2;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_23;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_24;
    QSpinBox *sollLFahrtInvers;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_25;
    QSpinBox *sollDrehenInvers;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_26;
    QSpinBox *sollHubInvers;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_27;
    QSpinBox *sollAusschubInvers;
    QPushButton *calculateInvers;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *xGp_2;
    QLabel *label_13;
    QPushButton *copySollPos;
    QPushButton *setGrippingPointInv;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QLabel *label_21;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_16;
    QSpinBox *sollLFahrt;
    QLineEdit *istLFahrt;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_17;
    QSpinBox *sollDrehen;
    QLineEdit *istDrehen;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_18;
    QSpinBox *sollHub;
    QLineEdit *istHub;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_19;
    QSpinBox *sollAusschub;
    QLineEdit *istAusschub;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_11;
    QDoubleSpinBox *sollGreifer;
    QLineEdit *istGreifer;
    QPushButton *copyIstPos;
    QCheckBox *enableJoints;
    QHBoxLayout *horizontalLayout_12;
    QLabel *AutoLabel;
    QLineEdit *Automode;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_8;
    QLineEdit *Modus;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menuVerbindungen;
    QMenu *menuopenFile;
    QMenu *menuHilfe;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1200, 800);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1000, 800));
        connectSPS = new QAction(MainWindow);
        connectSPS->setObjectName(QStringLiteral("connectSPS"));
        connectSPS->setCheckable(false);
        disconnectSPS = new QAction(MainWindow);
        disconnectSPS->setObjectName(QStringLiteral("disconnectSPS"));
        chooseFile = new QAction(MainWindow);
        chooseFile->setObjectName(QStringLiteral("chooseFile"));
        connectLMS = new QAction(MainWindow);
        connectLMS->setObjectName(QStringLiteral("connectLMS"));
        actionPfad_des_Arrays_anzeigen = new QAction(MainWindow);
        actionPfad_des_Arrays_anzeigen->setObjectName(QStringLiteral("actionPfad_des_Arrays_anzeigen"));
        openReadme = new QAction(MainWindow);
        openReadme->setObjectName(QStringLiteral("openReadme"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(500, 350));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        tabWidget->setAutoFillBackground(true);
        tabWidget->setTabPosition(QTabWidget::South);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_26 = new QHBoxLayout(tab_2);
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        horizontalLayout_50 = new QHBoxLayout();
        horizontalLayout_50->setSpacing(6);
        horizontalLayout_50->setObjectName(QStringLiteral("horizontalLayout_50"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(4);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalSpacer_6 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_7->addItem(verticalSpacer_6);

        enableTeachIn = new QPushButton(tab_2);
        enableTeachIn->setObjectName(QStringLiteral("enableTeachIn"));
        enableTeachIn->setLayoutDirection(Qt::LeftToRight);
        enableTeachIn->setCheckable(true);
        enableTeachIn->setChecked(false);
        enableTeachIn->setAutoRepeat(false);

        verticalLayout_7->addWidget(enableTeachIn);

        saveWaypoint = new QPushButton(tab_2);
        saveWaypoint->setObjectName(QStringLiteral("saveWaypoint"));

        verticalLayout_7->addWidget(saveWaypoint);

        setGrippingPointTeachIn = new QPushButton(tab_2);
        setGrippingPointTeachIn->setObjectName(QStringLiteral("setGrippingPointTeachIn"));

        verticalLayout_7->addWidget(setGrippingPointTeachIn);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy2);

        horizontalLayout_18->addWidget(label_9);

        waypointNr = new QLCDNumber(tab_2);
        waypointNr->setObjectName(QStringLiteral("waypointNr"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        waypointNr->setFont(font);
        waypointNr->setLineWidth(1);
        waypointNr->setSmallDecimalPoint(false);
        waypointNr->setDigitCount(5);
        waypointNr->setSegmentStyle(QLCDNumber::Flat);
        waypointNr->setProperty("value", QVariant(0));
        waypointNr->setProperty("intValue", QVariant(0));

        horizontalLayout_18->addWidget(waypointNr);


        verticalLayout_7->addLayout(horizontalLayout_18);

        teachInLog = new QTextEdit(tab_2);
        teachInLog->setObjectName(QStringLiteral("teachInLog"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(teachInLog->sizePolicy().hasHeightForWidth());
        teachInLog->setSizePolicy(sizePolicy3);
        teachInLog->setLayoutDirection(Qt::LeftToRight);
        teachInLog->setFrameShape(QFrame::WinPanel);
        teachInLog->setFrameShadow(QFrame::Sunken);
        teachInLog->setLineWidth(2);
        teachInLog->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        teachInLog->setAutoFormatting(QTextEdit::AutoNone);
        teachInLog->setUndoRedoEnabled(true);
        teachInLog->setReadOnly(true);
        teachInLog->setOverwriteMode(false);

        verticalLayout_7->addWidget(teachInLog);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_7->addItem(verticalSpacer_5);


        horizontalLayout_50->addLayout(verticalLayout_7);


        horizontalLayout_26->addLayout(horizontalLayout_50);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(2);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_2);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        label_20 = new QLabel(tab_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        label_20->setFont(font1);

        horizontalLayout_25->addWidget(label_20);

        wayPointBreak = new QDoubleSpinBox(tab_2);
        wayPointBreak->setObjectName(QStringLiteral("wayPointBreak"));
        wayPointBreak->setDecimals(0);
        wayPointBreak->setMaximum(20);
        wayPointBreak->setSingleStep(1);

        horizontalLayout_25->addWidget(wayPointBreak);


        verticalLayout_8->addLayout(horizontalLayout_25);

        runPath = new QPushButton(tab_2);
        runPath->setObjectName(QStringLiteral("runPath"));
        runPath->setCheckable(true);
        runPath->setChecked(false);

        verticalLayout_8->addWidget(runPath);

        cyclePath = new QPushButton(tab_2);
        cyclePath->setObjectName(QStringLiteral("cyclePath"));
        cyclePath->setCheckable(true);

        verticalLayout_8->addWidget(cyclePath);

        includeGP = new QPushButton(tab_2);
        includeGP->setObjectName(QStringLiteral("includeGP"));
        includeGP->setCheckable(true);

        verticalLayout_8->addWidget(includeGP);

        resetPath = new QPushButton(tab_2);
        resetPath->setObjectName(QStringLiteral("resetPath"));

        verticalLayout_8->addWidget(resetPath);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_7);


        horizontalLayout_26->addLayout(verticalLayout_8);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tableView = new QTableView(tab_3);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(0, 0, 821, 631));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(1);
        sizePolicy4.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy4);
        tableView->setFrameShape(QFrame::StyledPanel);
        tableView->horizontalHeader()->setCascadingSectionResizes(false);
        tableView->horizontalHeader()->setDefaultSectionSize(70);
        tableView->horizontalHeader()->setMinimumSectionSize(10);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setDefaultSectionSize(25);
        tableView->verticalHeader()->setMinimumSectionSize(20);
        widget = new QWidget(tab_3);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 300, 481, 41));
        acceptPath = new QPushButton(tab_3);
        acceptPath->setObjectName(QStringLiteral("acceptPath"));
        acceptPath->setGeometry(QRect(30, 640, 271, 31));
        saveCsv = new QPushButton(tab_3);
        saveCsv->setObjectName(QStringLiteral("saveCsv"));
        saveCsv->setGeometry(QRect(490, 640, 271, 31));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        saveAs = new QPushButton(tab_4);
        saveAs->setObjectName(QStringLiteral("saveAs"));
        saveAs->setGeometry(QRect(30, 40, 191, 31));
        singleScan = new QPushButton(tab_4);
        singleScan->setObjectName(QStringLiteral("singleScan"));
        singleScan->setGeometry(QRect(30, 80, 191, 31));
        singleScan->setCheckable(false);
        scanSequence = new QPushButton(tab_4);
        scanSequence->setObjectName(QStringLiteral("scanSequence"));
        scanSequence->setGeometry(QRect(30, 150, 191, 31));
        scanSequence->setCheckable(true);
        progressBar = new QProgressBar(tab_4);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(20, 650, 551, 23));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy5);
        progressBar->setMinimumSize(QSize(50, 0));
        progressBar->setMaximumSize(QSize(600, 16777215));
        progressBar->setAutoFillBackground(false);
        progressBar->setValue(0);
        groupBox = new QGroupBox(tab_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 250, 301, 80));
        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(20, 30, 89, 17));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(170, 30, 88, 17));
        scanFrom = new QSpinBox(groupBox);
        scanFrom->setObjectName(QStringLiteral("scanFrom"));
        scanFrom->setGeometry(QRect(20, 50, 89, 26));
        scanFrom->setMaximum(6400);
        scanFrom->setSingleStep(5);
        scanFrom->setValue(4200);
        scanTo = new QSpinBox(groupBox);
        scanTo->setObjectName(QStringLiteral("scanTo"));
        scanTo->setGeometry(QRect(170, 50, 88, 26));
        scanTo->setMaximum(6400);
        scanTo->setSingleStep(5);
        scanTo->setValue(4800);
        label_31 = new QLabel(tab_4);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(40, 350, 331, 20));
        scanFromReal = new QSpinBox(tab_4);
        scanFromReal->setObjectName(QStringLiteral("scanFromReal"));
        scanFromReal->setEnabled(false);
        scanFromReal->setGeometry(QRect(40, 380, 111, 29));
        scanFromReal->setReadOnly(true);
        scanFromReal->setMinimum(0);
        scanFromReal->setMaximum(5700);
        scanFromReal->setValue(0);
        noPoseCheck = new QCheckBox(tab_4);
        noPoseCheck->setObjectName(QStringLiteral("noPoseCheck"));
        noPoseCheck->setGeometry(QRect(30, 120, 261, 26));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        selectData = new QPushButton(tab_5);
        selectData->setObjectName(QStringLiteral("selectData"));
        selectData->setGeometry(QRect(30, 10, 191, 25));
        selectedFile = new QLineEdit(tab_5);
        selectedFile->setObjectName(QStringLiteral("selectedFile"));
        selectedFile->setGeometry(QRect(30, 50, 451, 25));
        QFont font2;
        font2.setPointSize(6);
        selectedFile->setFont(font2);
        selectedFile->setDragEnabled(false);
        selectedFile->setReadOnly(true);
        showHist = new QCheckBox(tab_5);
        showHist->setObjectName(QStringLiteral("showHist"));
        showHist->setGeometry(QRect(30, 80, 221, 26));
        showSurface = new QCheckBox(tab_5);
        showSurface->setObjectName(QStringLiteral("showSurface"));
        showSurface->setGeometry(QRect(30, 110, 281, 26));
        label_3 = new QLabel(tab_5);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(320, 600, 80, 20));
        label_12 = new QLabel(tab_5);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(40, 570, 251, 20));
        QFont font3;
        font3.setBold(true);
        font3.setItalic(true);
        font3.setWeight(75);
        label_12->setFont(font3);
        zGp = new QLineEdit(tab_5);
        zGp->setObjectName(QStringLiteral("zGp"));
        zGp->setGeometry(QRect(310, 630, 113, 28));
        zGp->setReadOnly(true);
        yGp = new QLineEdit(tab_5);
        yGp->setObjectName(QStringLiteral("yGp"));
        yGp->setGeometry(QRect(170, 630, 113, 28));
        yGp->setReadOnly(true);
        enPoendorf = new QCheckBox(tab_5);
        enPoendorf->setObjectName(QStringLiteral("enPoendorf"));
        enPoendorf->setGeometry(QRect(30, 170, 321, 26));
        calculateGP = new QPushButton(tab_5);
        calculateGP->setObjectName(QStringLiteral("calculateGP"));
        calculateGP->setGeometry(QRect(30, 530, 391, 31));
        label = new QLabel(tab_5);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 600, 80, 20));
        frame_2 = new QFrame(tab_5);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(20, 200, 611, 321));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        rightBorder = new QLineEdit(frame_2);
        rightBorder->setObjectName(QStringLiteral("rightBorder"));
        rightBorder->setEnabled(false);
        rightBorder->setGeometry(QRect(160, 220, 113, 28));
        rightBorder->setReadOnly(false);
        label_28 = new QLabel(frame_2);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(12, 134, 141, 20));
        leftAngle = new QLineEdit(frame_2);
        leftAngle->setObjectName(QStringLiteral("leftAngle"));
        leftAngle->setEnabled(false);
        leftAngle->setGeometry(QRect(160, 130, 113, 28));
        leftAngle->setReadOnly(false);
        enUserSettings = new QCheckBox(frame_2);
        enUserSettings->setObjectName(QStringLiteral("enUserSettings"));
        enUserSettings->setGeometry(QRect(10, 0, 281, 26));
        label_14 = new QLabel(frame_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 224, 141, 20));
        rightAngle = new QLineEdit(frame_2);
        rightAngle->setObjectName(QStringLiteral("rightAngle"));
        rightAngle->setEnabled(false);
        rightAngle->setGeometry(QRect(160, 160, 113, 28));
        rightAngle->setReadOnly(false);
        leftBorder = new QLineEdit(frame_2);
        leftBorder->setObjectName(QStringLiteral("leftBorder"));
        leftBorder->setEnabled(false);
        leftBorder->setGeometry(QRect(160, 190, 113, 28));
        leftBorder->setReadOnly(false);
        label_15 = new QLabel(frame_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(11, 165, 141, 20));
        label_29 = new QLabel(frame_2);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(10, 194, 141, 20));
        vRatio = new QLineEdit(frame_2);
        vRatio->setObjectName(QStringLiteral("vRatio"));
        vRatio->setEnabled(false);
        vRatio->setGeometry(QRect(160, 250, 113, 28));
        vRatio->setReadOnly(false);
        label_30 = new QLabel(frame_2);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(9, 254, 141, 20));
        label_36 = new QLabel(frame_2);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(12, 104, 141, 20));
        inkrSize = new QLineEdit(frame_2);
        inkrSize->setObjectName(QStringLiteral("inkrSize"));
        inkrSize->setEnabled(false);
        inkrSize->setGeometry(QRect(160, 100, 113, 28));
        inkrSize->setReadOnly(false);
        label_37 = new QLabel(frame_2);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setGeometry(QRect(12, 74, 141, 20));
        groundDist = new QLineEdit(frame_2);
        groundDist->setObjectName(QStringLiteral("groundDist"));
        groundDist->setEnabled(false);
        groundDist->setGeometry(QRect(160, 70, 113, 28));
        groundDist->setReadOnly(false);
        turned = new QLineEdit(frame_2);
        turned->setObjectName(QStringLiteral("turned"));
        turned->setEnabled(false);
        turned->setGeometry(QRect(160, 40, 113, 28));
        turned->setReadOnly(false);
        label_38 = new QLabel(frame_2);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setGeometry(QRect(12, 44, 141, 20));
        enSopas = new QCheckBox(tab_5);
        enSopas->setObjectName(QStringLiteral("enSopas"));
        enSopas->setGeometry(QRect(30, 140, 281, 26));
        xGp = new QLineEdit(tab_5);
        xGp->setObjectName(QStringLiteral("xGp"));
        xGp->setGeometry(QRect(30, 630, 113, 28));
        xGp->setReadOnly(true);
        label_2 = new QLabel(tab_5);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(180, 600, 80, 20));
        tabWidget->addTab(tab_5, QString());
        frame_2->raise();
        selectData->raise();
        selectedFile->raise();
        showHist->raise();
        showSurface->raise();
        label_3->raise();
        label_12->raise();
        zGp->raise();
        yGp->raise();
        enPoendorf->raise();
        calculateGP->raise();
        label->raise();
        enSopas->raise();
        xGp->raise();
        label_2->raise();
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        tab_6->setEnabled(true);
        zGp_2 = new QLineEdit(tab_6);
        zGp_2->setObjectName(QStringLiteral("zGp_2"));
        zGp_2->setGeometry(QRect(310, 39, 113, 28));
        label_10 = new QLabel(tab_6);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(320, 20, 80, 20));
        yGp_2 = new QLineEdit(tab_6);
        yGp_2->setObjectName(QStringLiteral("yGp_2"));
        yGp_2->setGeometry(QRect(170, 39, 113, 28));
        frame_5 = new QFrame(tab_6);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setEnabled(true);
        frame_5->setGeometry(QRect(30, 110, 330, 250));
        sizePolicy.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
        frame_5->setSizePolicy(sizePolicy);
        frame_5->setMinimumSize(QSize(330, 0));
        frame_5->setMaximumSize(QSize(500, 16777215));
        frame_5->setFrameShape(QFrame::Box);
        frame_5->setFrameShadow(QFrame::Sunken);
        verticalLayout_10 = new QVBoxLayout(frame_5);
        verticalLayout_10->setSpacing(3);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        label_23 = new QLabel(frame_5);
        label_23->setObjectName(QStringLiteral("label_23"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy6);
        label_23->setMinimumSize(QSize(0, 14));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setItalic(true);
        font4.setWeight(75);
        label_23->setFont(font4);
        label_23->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_23);


        verticalLayout_10->addLayout(horizontalLayout_6);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        label_24 = new QLabel(frame_5);
        label_24->setObjectName(QStringLiteral("label_24"));
        sizePolicy.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy);

        horizontalLayout_24->addWidget(label_24);

        sollLFahrtInvers = new QSpinBox(frame_5);
        sollLFahrtInvers->setObjectName(QStringLiteral("sollLFahrtInvers"));
        QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(sollLFahrtInvers->sizePolicy().hasHeightForWidth());
        sollLFahrtInvers->setSizePolicy(sizePolicy7);
        sollLFahrtInvers->setMinimumSize(QSize(100, 0));
        sollLFahrtInvers->setMaximum(6400);
        sollLFahrtInvers->setSingleStep(10);

        horizontalLayout_24->addWidget(sollLFahrtInvers);


        verticalLayout_10->addLayout(horizontalLayout_24);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        label_25 = new QLabel(frame_5);
        label_25->setObjectName(QStringLiteral("label_25"));
        sizePolicy.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy);

        horizontalLayout_27->addWidget(label_25);

        sollDrehenInvers = new QSpinBox(frame_5);
        sollDrehenInvers->setObjectName(QStringLiteral("sollDrehenInvers"));
        sizePolicy7.setHeightForWidth(sollDrehenInvers->sizePolicy().hasHeightForWidth());
        sollDrehenInvers->setSizePolicy(sizePolicy7);
        sollDrehenInvers->setMinimumSize(QSize(100, 0));
        sollDrehenInvers->setMinimum(-365);
        sollDrehenInvers->setMaximum(365);

        horizontalLayout_27->addWidget(sollDrehenInvers);


        verticalLayout_10->addLayout(horizontalLayout_27);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        label_26 = new QLabel(frame_5);
        label_26->setObjectName(QStringLiteral("label_26"));
        sizePolicy.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy);

        horizontalLayout_28->addWidget(label_26);

        sollHubInvers = new QSpinBox(frame_5);
        sollHubInvers->setObjectName(QStringLiteral("sollHubInvers"));
        sizePolicy7.setHeightForWidth(sollHubInvers->sizePolicy().hasHeightForWidth());
        sollHubInvers->setSizePolicy(sizePolicy7);
        sollHubInvers->setMinimumSize(QSize(100, 0));
        sollHubInvers->setMaximum(3000);

        horizontalLayout_28->addWidget(sollHubInvers);


        verticalLayout_10->addLayout(horizontalLayout_28);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        label_27 = new QLabel(frame_5);
        label_27->setObjectName(QStringLiteral("label_27"));
        sizePolicy.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy);

        horizontalLayout_29->addWidget(label_27);

        sollAusschubInvers = new QSpinBox(frame_5);
        sollAusschubInvers->setObjectName(QStringLiteral("sollAusschubInvers"));
        sizePolicy7.setHeightForWidth(sollAusschubInvers->sizePolicy().hasHeightForWidth());
        sollAusschubInvers->setSizePolicy(sizePolicy7);
        sollAusschubInvers->setMinimumSize(QSize(100, 0));
        sollAusschubInvers->setMinimum(346);
        sollAusschubInvers->setMaximum(1500);
        sollAusschubInvers->setSingleStep(10);

        horizontalLayout_29->addWidget(sollAusschubInvers);


        verticalLayout_10->addLayout(horizontalLayout_29);

        calculateInvers = new QPushButton(tab_6);
        calculateInvers->setObjectName(QStringLiteral("calculateInvers"));
        calculateInvers->setGeometry(QRect(30, 77, 241, 25));
        label_4 = new QLabel(tab_6);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 20, 80, 20));
        label_5 = new QLabel(tab_6);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(180, 20, 80, 20));
        xGp_2 = new QLineEdit(tab_6);
        xGp_2->setObjectName(QStringLiteral("xGp_2"));
        xGp_2->setGeometry(QRect(30, 39, 113, 28));
        label_13 = new QLabel(tab_6);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(30, 0, 251, 20));
        QFont font5;
        font5.setBold(true);
        font5.setItalic(false);
        font5.setWeight(75);
        label_13->setFont(font5);
        copySollPos = new QPushButton(tab_6);
        copySollPos->setObjectName(QStringLiteral("copySollPos"));
        copySollPos->setGeometry(QRect(30, 380, 321, 29));
        QSizePolicy sizePolicy8(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(copySollPos->sizePolicy().hasHeightForWidth());
        copySollPos->setSizePolicy(sizePolicy8);
        setGrippingPointInv = new QPushButton(tab_6);
        setGrippingPointInv->setObjectName(QStringLiteral("setGrippingPointInv"));
        setGrippingPointInv->setGeometry(QRect(30, 420, 256, 29));
        tabWidget->addTab(tab_6, QString());

        horizontalLayout->addWidget(tabWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(5, -1, -1, -1);
        verticalSpacer_3 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        frame_4 = new QFrame(centralWidget);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setEnabled(true);
        sizePolicy.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy);
        frame_4->setMinimumSize(QSize(340, 0));
        frame_4->setMaximumSize(QSize(340, 16777215));
        frame_4->setFrameShape(QFrame::Box);
        frame_4->setFrameShadow(QFrame::Sunken);
        verticalLayout_9 = new QVBoxLayout(frame_4);
        verticalLayout_9->setSpacing(3);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        label_21 = new QLabel(frame_4);
        label_21->setObjectName(QStringLiteral("label_21"));
        sizePolicy6.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy6);
        label_21->setMinimumSize(QSize(0, 14));
        label_21->setFont(font);
        label_21->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_21);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        label_7 = new QLabel(frame_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy6.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy6);
        label_7->setMinimumSize(QSize(0, 14));
        label_7->setFont(font);
        label_7->setMouseTracking(true);
        label_7->setAlignment(Qt::AlignCenter);
        label_7->setWordWrap(false);

        horizontalLayout_5->addWidget(label_7);


        verticalLayout_9->addLayout(horizontalLayout_5);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_16 = new QLabel(frame_4);
        label_16->setObjectName(QStringLiteral("label_16"));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);

        horizontalLayout_19->addWidget(label_16);

        sollLFahrt = new QSpinBox(frame_4);
        sollLFahrt->setObjectName(QStringLiteral("sollLFahrt"));
        sizePolicy7.setHeightForWidth(sollLFahrt->sizePolicy().hasHeightForWidth());
        sollLFahrt->setSizePolicy(sizePolicy7);
        sollLFahrt->setMinimumSize(QSize(100, 0));
        sollLFahrt->setMaximum(6400);
        sollLFahrt->setSingleStep(10);

        horizontalLayout_19->addWidget(sollLFahrt);

        istLFahrt = new QLineEdit(frame_4);
        istLFahrt->setObjectName(QStringLiteral("istLFahrt"));
        sizePolicy7.setHeightForWidth(istLFahrt->sizePolicy().hasHeightForWidth());
        istLFahrt->setSizePolicy(sizePolicy7);
        istLFahrt->setMaximumSize(QSize(100, 16777215));
        istLFahrt->setStyleSheet(QStringLiteral(""));
        istLFahrt->setFrame(true);
        istLFahrt->setReadOnly(true);

        horizontalLayout_19->addWidget(istLFahrt);


        verticalLayout_9->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_17 = new QLabel(frame_4);
        label_17->setObjectName(QStringLiteral("label_17"));
        sizePolicy.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy);

        horizontalLayout_20->addWidget(label_17);

        sollDrehen = new QSpinBox(frame_4);
        sollDrehen->setObjectName(QStringLiteral("sollDrehen"));
        sizePolicy7.setHeightForWidth(sollDrehen->sizePolicy().hasHeightForWidth());
        sollDrehen->setSizePolicy(sizePolicy7);
        sollDrehen->setMinimumSize(QSize(100, 0));
        sollDrehen->setMinimum(-365);
        sollDrehen->setMaximum(365);

        horizontalLayout_20->addWidget(sollDrehen);

        istDrehen = new QLineEdit(frame_4);
        istDrehen->setObjectName(QStringLiteral("istDrehen"));
        sizePolicy7.setHeightForWidth(istDrehen->sizePolicy().hasHeightForWidth());
        istDrehen->setSizePolicy(sizePolicy7);
        istDrehen->setMaximumSize(QSize(100, 16777215));
        istDrehen->setReadOnly(true);

        horizontalLayout_20->addWidget(istDrehen);


        verticalLayout_9->addLayout(horizontalLayout_20);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        label_18 = new QLabel(frame_4);
        label_18->setObjectName(QStringLiteral("label_18"));
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);

        horizontalLayout_21->addWidget(label_18);

        sollHub = new QSpinBox(frame_4);
        sollHub->setObjectName(QStringLiteral("sollHub"));
        sizePolicy7.setHeightForWidth(sollHub->sizePolicy().hasHeightForWidth());
        sollHub->setSizePolicy(sizePolicy7);
        sollHub->setMinimumSize(QSize(100, 0));
        sollHub->setMaximum(3000);

        horizontalLayout_21->addWidget(sollHub);

        istHub = new QLineEdit(frame_4);
        istHub->setObjectName(QStringLiteral("istHub"));
        sizePolicy7.setHeightForWidth(istHub->sizePolicy().hasHeightForWidth());
        istHub->setSizePolicy(sizePolicy7);
        istHub->setMaximumSize(QSize(100, 16777215));
        istHub->setReadOnly(true);

        horizontalLayout_21->addWidget(istHub);


        verticalLayout_9->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        label_19 = new QLabel(frame_4);
        label_19->setObjectName(QStringLiteral("label_19"));
        sizePolicy.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy);

        horizontalLayout_22->addWidget(label_19);

        sollAusschub = new QSpinBox(frame_4);
        sollAusschub->setObjectName(QStringLiteral("sollAusschub"));
        sizePolicy7.setHeightForWidth(sollAusschub->sizePolicy().hasHeightForWidth());
        sollAusschub->setSizePolicy(sizePolicy7);
        sollAusschub->setMinimumSize(QSize(100, 0));
        sollAusschub->setMinimum(346);
        sollAusschub->setMaximum(1500);
        sollAusschub->setSingleStep(10);

        horizontalLayout_22->addWidget(sollAusschub);

        istAusschub = new QLineEdit(frame_4);
        istAusschub->setObjectName(QStringLiteral("istAusschub"));
        sizePolicy7.setHeightForWidth(istAusschub->sizePolicy().hasHeightForWidth());
        istAusschub->setSizePolicy(sizePolicy7);
        istAusschub->setMaximumSize(QSize(100, 16777215));
        istAusschub->setReadOnly(true);

        horizontalLayout_22->addWidget(istAusschub);


        verticalLayout_9->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        label_11 = new QLabel(frame_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);

        horizontalLayout_23->addWidget(label_11);

        sollGreifer = new QDoubleSpinBox(frame_4);
        sollGreifer->setObjectName(QStringLiteral("sollGreifer"));
        sizePolicy7.setHeightForWidth(sollGreifer->sizePolicy().hasHeightForWidth());
        sollGreifer->setSizePolicy(sizePolicy7);
        sollGreifer->setMinimumSize(QSize(100, 0));
        sollGreifer->setDecimals(1);
        sollGreifer->setMaximum(1);
        sollGreifer->setSingleStep(0.5);

        horizontalLayout_23->addWidget(sollGreifer);

        istGreifer = new QLineEdit(frame_4);
        istGreifer->setObjectName(QStringLiteral("istGreifer"));
        sizePolicy7.setHeightForWidth(istGreifer->sizePolicy().hasHeightForWidth());
        istGreifer->setSizePolicy(sizePolicy7);
        istGreifer->setMaximumSize(QSize(100, 16777215));
        istGreifer->setReadOnly(true);

        horizontalLayout_23->addWidget(istGreifer);


        verticalLayout_9->addLayout(horizontalLayout_23);

        copyIstPos = new QPushButton(frame_4);
        copyIstPos->setObjectName(QStringLiteral("copyIstPos"));
        sizePolicy8.setHeightForWidth(copyIstPos->sizePolicy().hasHeightForWidth());
        copyIstPos->setSizePolicy(sizePolicy8);

        verticalLayout_9->addWidget(copyIstPos);


        verticalLayout->addWidget(frame_4);

        enableJoints = new QCheckBox(centralWidget);
        enableJoints->setObjectName(QStringLiteral("enableJoints"));
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(enableJoints->sizePolicy().hasHeightForWidth());
        enableJoints->setSizePolicy(sizePolicy9);
        enableJoints->setMaximumSize(QSize(330, 16777215));
        enableJoints->setFont(font);
        enableJoints->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(enableJoints);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(5, 0, 5, -1);
        AutoLabel = new QLabel(centralWidget);
        AutoLabel->setObjectName(QStringLiteral("AutoLabel"));
        sizePolicy.setHeightForWidth(AutoLabel->sizePolicy().hasHeightForWidth());
        AutoLabel->setSizePolicy(sizePolicy);
        AutoLabel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_12->addWidget(AutoLabel);

        Automode = new QLineEdit(centralWidget);
        Automode->setObjectName(QStringLiteral("Automode"));
        Automode->setMaximumSize(QSize(200, 16777215));
        Automode->setFont(font4);
        Automode->setAlignment(Qt::AlignCenter);
        Automode->setReadOnly(true);

        horizontalLayout_12->addWidget(Automode);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(5, -1, 5, -1);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_17->addWidget(label_8);

        Modus = new QLineEdit(centralWidget);
        Modus->setObjectName(QStringLiteral("Modus"));
        Modus->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_17->addWidget(Modus);


        verticalLayout->addLayout(horizontalLayout_17);

        verticalSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 25));
        menuVerbindungen = new QMenu(menuBar);
        menuVerbindungen->setObjectName(QStringLiteral("menuVerbindungen"));
        menuopenFile = new QMenu(menuBar);
        menuopenFile->setObjectName(QStringLiteral("menuopenFile"));
        menuHilfe = new QMenu(menuBar);
        menuHilfe->setObjectName(QStringLiteral("menuHilfe"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuVerbindungen->menuAction());
        menuBar->addAction(menuopenFile->menuAction());
        menuBar->addAction(menuHilfe->menuAction());
        menuVerbindungen->addAction(connectSPS);
        menuVerbindungen->addAction(disconnectSPS);
        menuVerbindungen->addSeparator();
        menuVerbindungen->addAction(connectLMS);
        menuopenFile->addAction(chooseFile);
        menuopenFile->addAction(actionPfad_des_Arrays_anzeigen);
        menuHilfe->addAction(openReadme);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "RobocraneOpcControl", Q_NULLPTR));
        connectSPS->setText(QApplication::translate("MainWindow", "Verbinde mit SPS", Q_NULLPTR));
        disconnectSPS->setText(QApplication::translate("MainWindow", "Verbindung trennen", Q_NULLPTR));
        chooseFile->setText(QApplication::translate("MainWindow", "CSV Datei ausw\303\244hlen", Q_NULLPTR));
        connectLMS->setText(QApplication::translate("MainWindow", "Verbinde mit Laserscanner", Q_NULLPTR));
        actionPfad_des_Arrays_anzeigen->setText(QApplication::translate("MainWindow", "Pfad des Arrays", Q_NULLPTR));
        openReadme->setText(QApplication::translate("MainWindow", "Liesmich Datei \303\266ffnen", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        enableTeachIn->setToolTip(QApplication::translate("MainWindow", "Startet das TeachIn bei Wegpunkt 0. Nochmaliges Dr\303\274cken beendet TeachIn", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        enableTeachIn->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        enableTeachIn->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        enableTeachIn->setText(QApplication::translate("MainWindow", "TeachIn On/Off", Q_NULLPTR));
        saveWaypoint->setText(QApplication::translate("MainWindow", "Wegpunkt speichern", Q_NULLPTR));
        setGrippingPointTeachIn->setText(QApplication::translate("MainWindow", "Greifpunkt speichern", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Wegpunkt Nr.</span></p></body></html>", Q_NULLPTR));
        teachInLog->setDocumentTitle(QString());
        label_20->setText(QApplication::translate("MainWindow", "Pause zw. Wegpunkten", Q_NULLPTR));
        runPath->setText(QApplication::translate("MainWindow", "Pfad ausf\303\274hren", Q_NULLPTR));
        cyclePath->setText(QApplication::translate("MainWindow", "Pfad Endlosschleife aktivieren", Q_NULLPTR));
        includeGP->setText(QApplication::translate("MainWindow", "Greifroutine aktivieren", Q_NULLPTR));
        resetPath->setText(QApplication::translate("MainWindow", "Pfad WP 0 setzen / Reset", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "TeachIn", Q_NULLPTR));
        acceptPath->setText(QApplication::translate("MainWindow", "Tabelle als Pfad \303\274bernehmen", Q_NULLPTR));
        saveCsv->setText(QApplication::translate("MainWindow", "speichere Tabelle in CSV", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Pfad konfigurieren", Q_NULLPTR));
        saveAs->setText(QApplication::translate("MainWindow", "Speicherort festlegen", Q_NULLPTR));
        singleScan->setText(QApplication::translate("MainWindow", "Messf\303\244cher speichern", Q_NULLPTR));
        scanSequence->setText(QApplication::translate("MainWindow", "Bereich Scannen", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Scanbereich [cm]", Q_NULLPTR));
        label_22->setText(QApplication::translate("MainWindow", "von", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "bis", Q_NULLPTR));
        label_31->setText(QApplication::translate("MainWindow", "letzter Scan tats\303\244chlich ab [cm]", Q_NULLPTR));
        noPoseCheck->setText(QApplication::translate("MainWindow", "Scan ohne Posenpr\303\274fung", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Laserscanner", Q_NULLPTR));
        selectData->setText(QApplication::translate("MainWindow", "Laserdaten ausw\303\244hlen", Q_NULLPTR));
        showHist->setText(QApplication::translate("MainWindow", "Histogramm anzeigen", Q_NULLPTR));
        showSurface->setText(QApplication::translate("MainWindow", "Oberfl\303\244chenprofil anzeigen", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "berechneter Greifpunkt:", Q_NULLPTR));
        enPoendorf->setText(QApplication::translate("MainWindow", "P\303\266ndorf Scan (Standard: Labor Scan)", Q_NULLPTR));
        calculateGP->setText(QApplication::translate("MainWindow", "Greifpunkt berechnen", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        label_28->setText(QApplication::translate("MainWindow", "linker Winkel", Q_NULLPTR));
        enUserSettings->setText(QApplication::translate("MainWindow", "benutzerdefinierte Auswertungsgrenzen", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "rechte Grenze", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "rechter Winkel", Q_NULLPTR));
        label_29->setText(QApplication::translate("MainWindow", "linke Grenze", Q_NULLPTR));
        label_30->setText(QApplication::translate("MainWindow", "Vol. Verh\303\244ltnis", Q_NULLPTR));
        label_36->setText(QApplication::translate("MainWindow", "Inkrement Gr\303\266\303\237e", Q_NULLPTR));
        label_37->setText(QApplication::translate("MainWindow", "Abstand Boden", Q_NULLPTR));
        label_38->setText(QApplication::translate("MainWindow", "gedreht", Q_NULLPTR));
        enSopas->setText(QApplication::translate("MainWindow", "Sopas Scan (Standard: QT Scan)", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Greifpunkt berechnen", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        label_23->setText(QApplication::translate("MainWindow", "berechnete Soll Position ", Q_NULLPTR));
        label_24->setText(QApplication::translate("MainWindow", "L\303\244ngsfahrt", Q_NULLPTR));
        label_25->setText(QApplication::translate("MainWindow", "Drehung", Q_NULLPTR));
        label_26->setText(QApplication::translate("MainWindow", "Hub", Q_NULLPTR));
        label_27->setText(QApplication::translate("MainWindow", "Ausschub", Q_NULLPTR));
        calculateInvers->setText(QApplication::translate("MainWindow", "Inverskinematik berechnen", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "Greifpunkt aus Punktewolke", Q_NULLPTR));
        copySollPos->setText(QApplication::translate("MainWindow", "\303\234bernehme berechnete Soll Position", Q_NULLPTR));
        setGrippingPointInv->setText(QApplication::translate("MainWindow", "Greifpunkt in Pfad speichern", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("MainWindow", "InvKine berechnen", Q_NULLPTR));
        label_21->setText(QApplication::translate("MainWindow", "Soll Position ", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Ist Position</span></p></body></html>", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "L\303\244ngsfahrt", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "Drehung", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "Hub", Q_NULLPTR));
        label_19->setText(QApplication::translate("MainWindow", "Ausschub", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Greifer", Q_NULLPTR));
        copyIstPos->setText(QApplication::translate("MainWindow", "\303\234bernehme Ist Position", Q_NULLPTR));
        enableJoints->setText(QApplication::translate("MainWindow", "Auto on/off", Q_NULLPTR));
        AutoLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Automode</span></p></body></html>", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\"> Modus </span></p></body></html>", Q_NULLPTR));
        menuVerbindungen->setTitle(QApplication::translate("MainWindow", "Verbindungen", Q_NULLPTR));
        menuopenFile->setTitle(QApplication::translate("MainWindow", "Pfad anzeigen", Q_NULLPTR));
        menuHilfe->setTitle(QApplication::translate("MainWindow", "Hilfe", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
