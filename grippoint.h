#ifndef GRIPPOINT_H
#define GRIPPOINT_H

//#include <QMainWindow>
#include <QObject>
//#include <qstring.h>
//#include <iostream>
//#include <vector>
#include <mutex>

#include <opencv.hpp>

//namespace Ui {
//class GripPoint;
//}

class GripPoint: public QObject// : public QMainWindow
{
    Q_OBJECT

public:
    long xGp, yGp, zGp;
    //    explicit GripPoint(QWidget *parent = 0, bool Gedreht = false, long ScannerUeberBoden = 20000, long SchrittweiteEncoder = 40);
    //    GripPoint(QObject *parent = nullptr, bool Gedreht = false, long ScannerUeberBoden = 20000, double SchrittweiteEncoder = 40, unsigned int leftAngle = 45, unsigned int rightAngle = 315, long leftBorder = -850, long rightBorder = 1200, uint VRatio = 1);
    GripPoint(QObject *parent = nullptr, bool Gedreht = false, long ScannerUeberBoden = 20000, double SchrittweiteEncoder = 40, unsigned int leftAngle = 45, unsigned int rightAngle = 315, long leftBorder = -850, long rightBorder = 1200, uint VRatio = 1, QString fileName = "../Laserdata.txt", bool showHist = true, bool showDia = true, bool Receive = false);
    ~GripPoint();

private:
    //    Ui::GripPoint* ui;
    bool Hist;
    bool Gedreht;
    int sync;
    std::mutex mtx;
    QString StringLMS;
    std::vector<int> Leerzeichen;
    std::vector< std::vector<long> > data;
    std::vector< std::vector<long> > data_X;
    std::vector< std::vector<long> > data_Y;
    std::vector< std::vector<long> > data_Z;
    //    std::vector<long> data_X_min;
    //    std::vector<long> data_X_max;
    std::vector< std::vector<long> > data_Xr;
    std::vector< std::vector<long> > data_Yr;
    std::vector< std::vector<long> > data_Zr;
    std::vector< std::vector<long> > Xr;
    std::vector< std::vector<long> > Yr;
    std::vector< std::vector<long> > Zr;
    std::vector< std::vector<long> > Xrs;
    std::vector< std::vector<long> > Yrs;
    std::vector< std::vector<long> > Zrs;
    std::vector< std::vector<double> > FMXrs;
    std::vector< std::vector<double> > Vrs;
    std::vector< std::vector<double> > Xks;
    std::vector< std::vector<double> > Yks;
    std::vector< std::vector<double> > Zks;
    std::vector< std::vector<long> > Xksl;
    std::vector< std::vector<long> > Yksl;
    std::vector< std::vector<long> > Zksl;
    std::vector< std::vector<long> > Xksp;
    std::vector< std::vector<long> > Yksp;
    std::vector< std::vector<long> > Zksp;
    std::vector< std::vector<double> > Vks;

    //    unsigned int IncrementSize;

    void Raster(std::vector< std::vector<long> > & vec_X, std::vector< std::vector<long> > & vec_Y, std::vector< std::vector<long> > & vec_Z, std::vector< std::vector<long> > & vec_Xr, std::vector< std::vector<long> > & vec_Yr, std::vector< std::vector<long> > & vec_Zr);
    void Transponieren(std::vector<std::vector<long> > &vec);
    void Schwerpunkt(std::vector< std::vector<long> > & vec_Xr, std::vector< std::vector<long> > & vec_Yr, std::vector< std::vector<long> > & vec_Zr, std::vector< std::vector<long> > & vec_Xrs, std::vector< std::vector<long> > & vec_Yrs, std::vector< std::vector<long> > & vec_Zrs, std::vector< std::vector<double> > & vec_FMXrs, std::vector< std::vector<double> > & vec_Vrs);
    void Histogramm(std::vector<float>& vec_data, std::vector<long>& vec_hist, float &min, float &max, const std::string &title);
    void Manhattan(uint& VRatio);
    void Display(const std::string &title, cv::Mat &histImage);


    //    void Diagramm(QImage heightMapImage);

};

#endif // GRIPPOINT_H
