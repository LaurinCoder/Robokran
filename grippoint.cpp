#include <iostream>
#include <functional>
#include <thread>
//#include <mutex>
//#include <string>

#include "diagramm.h"
#include "qfile.h"
#include <qtextstream.h>
#include "grippoint.h"
//#include <raster.h>
//#include "ui_grippoint.h"

//#include <opencv.hpp>
#include "highgui.hpp"
#include "imgproc.hpp"

#include <algorithm>
#include <cmath>
#define _USE_MATH_DEFINES
#define WURZEL(n,x) pow(x, 1.0/n)

//GripPoint::GripPoint(QObject *parent, bool Gedreht, long ScannerUeberBoden, double SchrittweiteEncoder, unsigned int leftAngle, unsigned int rightAngle, long leftBorder, long rightBorder, uint VRatio) : QObject(parent)
GripPoint::GripPoint(QObject *parent, bool Gedreht, long ScannerUeberBoden, double SchrittweiteEncoder, unsigned int leftAngle, unsigned int rightAngle, long leftBorder, long rightBorder, uint VRatio, QString fileName, bool showHist, bool showDia, bool Receive) : QObject(parent)
{
    Hist = showHist;
    //    ui->setupUi(this);
    //    IncrementSize = 40;
    {
        //    QFile ScanLMS("/home/szuegyi/Dokumente/laborscan_00.txt");
        //        QFile ScanLMS("/media/szuegyi/01D2DF7F04A8AED0/BuR_Projekte/2017_KW_28/LMS111/20170714_01.log");
        //        QFile ScanLMS("/media/Win_7/BuR_Projekte/2017_KW_28/LMS111/20170714_01.log");
        //        QFile ScanLMS("/media/Win_7/Users/Szügyi/Scanfile/sopasScanLabor.log");
        //        printf("läuft\n\n");
        //        QFile ScanLMS("/media/Win_7/Users/Szügyi/Scanfile/qtScanLabor.txt");
        //        QFile ScanLMS("/media/Win_7/Dokumente und Einstellungen/Szügyi/Dropbox (Institut für Landtechnik)/2017_Robokran_Basisprogramm_1u2/20_Scans/TestScanKegel/laserdata.txt");
        QFile ScanLMS(fileName);

        if (!ScanLMS.open(QIODevice::ReadOnly | QIODevice::Text)) { std::cout << "can't find file " << qUtf8Printable(fileName); return; }

        QTextStream StreamLMS(&ScanLMS);
        QString w, r;
        QStringList listReplay_r;
        //        int k = 0;
        std::vector<long> data_temp;
        while (!StreamLMS.atEnd())
        {
            StringLMS = StreamLMS.readLine();

            //            k++;
            int j = 0;
            while ((j = StringLMS.indexOf(" ", j)) != -1)
            {
                Leerzeichen.push_back(j);
                ++j;
            }

            uint startWeg  = Leerzeichen[18 + 4*Receive];
            uint stopWeg   = Leerzeichen[19 + 4*Receive];
            uint start     = Leerzeichen[27 + 4*Receive      +round((leftAngle   -45) / 0.5)];
            uint stop      = Leerzeichen[27 + 4*Receive +541 -round((315 -rightAngle) / 0.5)];

            //            uint startWeg  = Leerzeichen[18 +0];
            //            uint stopWeg   = Leerzeichen[19 +0];
            //            uint start     = Leerzeichen[27 +0      +round((leftAngle   -45) / 0.5)];
            //            uint stop      = Leerzeichen[27 +0 +541 -round((315 -rightAngle) / 0.5)];

            //            std::cout << Leerzeichen.size() << "\n";

            if ((Leerzeichen.size() > 573)/* && (k >= 400)*/)
            {
                w = StringLMS.mid(startWeg, stopWeg -startWeg);
                r = StringLMS.mid(start   , stop    -start);

                bool ok;
                data_temp.push_back(w.toLong(&ok, 16));

                listReplay_r = r.split(' ');
                for (int i = 0; i != listReplay_r.count(); i++)data_temp.push_back(strtol((listReplay_r[i].toLatin1()).data(), NULL, 16));
                //                {
                //                    data_temp.push_back(listReplay_r[i].toInt(&ok, 16));
                //                for (int i = 0; i != listReplay_r.count(); i++) data_temp.push_back(atoi(qUtf8Printable(listReplay_r[i])));
                //                    const char* buffer = (listReplay_r[i].toLatin1()).data();
                //                    std::cout << strtol((listReplay_r[i].toLatin1()).data(), NULL, 16) << ", " << listReplay_r[i].toInt(&ok, 16) << ", ";
                //                }
                //                std::cout << "\n\n";
                data.push_back(data_temp);
                data_temp.resize(0);
                listReplay_r.clear();
            }
            Leerzeichen.resize(0);
        }
        data_temp.clear();
        ScanLMS.close();
    }


    {
        int w0   = data[0][0];
        int walt = w0;
        //        bool* ok = nullptr;
        //        int wmax = QString("3FFF").toInt(ok, 16) +1;
        int wmax = strtol("3FFF", NULL, 16) +1;
        long min = 0;

        //        std::cout << "\n";
        for (unsigned int i = 0; i != data.size(); ++i)
        {
            w0         = w0 +((data[i][0] -walt) > (wmax/2))*wmax -((walt -data[i][0]) > (wmax/2))*wmax;
            walt       = data[i][0];
            data[i][0] = round((data[i][0] -w0) * SchrittweiteEncoder);
            min        = (data[i][0] < min) * data[i][0] + (data[i][0] >= min) * min;
            //            printf("data[i][0] =    ->%8d<-    ->%8ld<-\n", walt, data[i][0]);
        }
        //        std::cout << "\n";
        //        if ( min < 0 ) for ( uint i = 0; i != data.size(); i++){ data[i][0] = data[i][0] - min; printf("Rückfahrt: data[i][0] = ->%8ld<-\n", data[i][0]);}
        if ( min < 0 ) for ( uint i = 0; i != data.size(); i++) data[i][0] = data[i][0] - min;
    }

    for (unsigned int i = 0; i != data.size(); ++i)
    {
        for (unsigned int j = 1; j != data[i].size(); ++j)
        {
            data[i][j] = (10 <= data[i][j])*data[i][j] +(10 > data[i][j])*20000;
        }
    }


    {
        std::vector<long> data_X_temp;
        std::vector<long> data_Y_temp;
        std::vector<long> data_Z_temp;
        for (unsigned int i = 0; i != data.size(); ++i)
        {
            for (unsigned int j = 0; j != data[i].size()-1; ++j)
            {
                data_Y_temp.push_back((long)( (double)data[i][0] + (j +(45 +leftAngle)/0.5) * ((double)data[i +(uint)(i < data.size() -1)][0] -(double)data[i -(uint)(i == data.size() -1)][0]) / (360 / 0.5) ));
                //                data_Y_temp.push_back( data[i][0] );
                data_X_temp.push_back((data[i][j+1] < 20000) * data[i][j+1] * std::sin((leftAngle +0.5*j)*M_PI/180) + (data[i][j+1] >= 20000 )*20000);
                data_Z_temp.push_back( data[i][j+1]                         * std::cos((leftAngle +0.5*j)*M_PI/180));
            }
            data_Y.push_back(data_Y_temp);
            data_X.push_back(data_X_temp);
            data_Z.push_back(data_Z_temp);
            data_Y_temp.resize(0);
            data_X_temp.resize(0);
            data_Z_temp.resize(0);
        }
        data_Y_temp.clear();
        data_X_temp.clear();
        data_Z_temp.clear();
    }


    if (Gedreht)
    {
        long delta = (SchrittweiteEncoder <= 10) * 20000 + (SchrittweiteEncoder > 10) * SchrittweiteEncoder * round(20000 / SchrittweiteEncoder);
        std::vector<long> data_X_temp;
        std::vector<long> data_Z_temp;
        for (unsigned int i = 0; i != data_X.size(); ++i)
        {
            for (unsigned int j = data_X[i].size(); j >0; --j)
            {
                data_X_temp.push_back( -data_X[i][j -1] +delta);
                data_Z_temp.push_back(( data_Z[i][j -1] +ScannerUeberBoden) * (long)((data_Z[i][j-1] +ScannerUeberBoden) >= 0) * (data_X[i][j-1] < 20000));
            }
            data_X[i] = data_X_temp;
            data_Z[i] = data_Z_temp;
            data_X_temp.clear();
            data_Z_temp.clear();
        }
    }
    else
    {
        std::vector< std::vector<long> > puffer_X(data_X.size(), std::vector<long> (data_X[0].size()));
        std::vector< std::vector<long> > puffer_Z(data_Z.size(), std::vector<long> (data_Z[0].size()));

        for (uint i = 0; i != puffer_X.size(); ++i)
        {
            for (uint j = 0; j != puffer_X[0].size(); ++j)
            {
                puffer_X[i][j] = data_X[i][j];
                puffer_Z[i][j] = data_Z[i][j];
            }
        }

        long delta = (SchrittweiteEncoder <= 10) * 20000 + (SchrittweiteEncoder > 10) * SchrittweiteEncoder * round(20000 / SchrittweiteEncoder);
        for (unsigned int i = 0; i != data_X.size(); ++i)
        {
            for (unsigned int j =0; j != data_X[i].size(); ++j)
            {
                data_X[i][j] = puffer_X[i][j] +delta;
                data_Z[i][j] = (puffer_Z[i][j] +ScannerUeberBoden) * (long)((puffer_Z[i][j] +ScannerUeberBoden) >= 0) * (puffer_X[i][j] < 20000);
            }
        }
    }

    {
        long Puffer;
        bool Fertig;
        for (unsigned int n = 0; n != data_X.size(); ++n)
        {
            Fertig = false;
            while (!Fertig)
            {
                Fertig = true;
                for (unsigned int m = 0; m != data_X[n].size() -1; ++m)
                {
                    if (data_X[n][m] < data_X[n][m +1])
                    {
                        Fertig = false;

                        Puffer          = data_X[n][m];
                        data_X[n][m]    = data_X[n][m +1];
                        data_X[n][m +1] = Puffer;

                        Puffer          = data_Y[n][m];
                        data_Y[n][m]    = data_Y[n][m +1];
                        data_Y[n][m +1] = Puffer;

                        Puffer          = data_Z[n][m];
                        data_Z[n][m]    = data_Z[n][m +1];
                        data_Z[n][m +1] = Puffer;
                    }
                }
            }
        }
    }


    {
        long teiler = (long)(SchrittweiteEncoder <= 10) * 10 + (long)(SchrittweiteEncoder > 10) * SchrittweiteEncoder;
        {
            std::vector<long> data_X_temp;
            std::vector<long> data_Y_temp;
            std::vector<long> data_Z_temp;
            for (unsigned int i = 0; i != data_X.size(); ++i)
            {
                for (unsigned int j =0; j != data_X[i].size(); ++j)
                {
                    data_X_temp.push_back(round(data_X[i][j] / teiler));
                    data_Y_temp.push_back(round(data_Y[i][j] / teiler));
                    data_Z_temp.push_back(round(data_Z[i][j] / teiler));
                }
                data_X[i] = data_X_temp;
                data_Y[i] = data_Y_temp;
                data_Z[i] = data_Z_temp;
                data_X_temp.clear();
                data_Y_temp.clear();
                data_Z_temp.clear();
            }
        }
    }

    //    Transponieren(data_X);
    //    Transponieren(data_Y);
    //    Transponieren(data_Z);

    Raster(data_X, data_Y, data_Z, data_Xr, data_Yr, data_Zr);

    Transponieren(data_Xr);
    Transponieren(data_Yr);
    Transponieren(data_Zr);

    for (uint i = 0; i != data_X.size(); ++i)
    {
        data_X[i].resize(0);
        data_Y[i].resize(0);
        data_Z[i].resize(0);
    }
    data_X.resize(0);
    data_Y.resize(0);
    data_Z.resize(0);

    Raster(data_Yr, data_Xr, data_Zr, data_Y, data_X, data_Z);

    data_Xr.clear();
    data_Yr.clear();
    data_Zr.clear();

    Transponieren(data_X);
    Transponieren(data_Y);
    Transponieren(data_Z);

    std::vector < std::vector <long> > cv_Z(data_Z.size(), std::vector<long> (data_Z[0].size()));
    {
        long teiler = (long)(SchrittweiteEncoder <= 10) * 10 + (long)(SchrittweiteEncoder > 10) * SchrittweiteEncoder;
        {
            std::vector<long> data_X_temp;
            std::vector<long> data_Y_temp;
            std::vector<long> data_Z_temp;
            std::vector<long>   cv_Z_temp;
            for (unsigned int i = 0; i != data_X.size(); ++i)
            {
                for (unsigned int j =0; j != data_X[i].size(); ++j)
                {
                    data_X_temp.push_back(teiler * data_X[i][j]);
                    data_Y_temp.push_back(teiler * data_Y[i][j]);
                    data_Z_temp.push_back(teiler * data_Z[i][j]);
                    cv_Z_temp.push_back(         data_Z[i][j]);
                    //                     std::cout << data_X_temp[j] << ", ";
                }
                //                std::cout << "\n\n";
                data_X[i] = data_X_temp;
                data_Y[i] = data_Y_temp;
                data_Z[i] = data_Z_temp;
                cv_Z[i] =   cv_Z_temp;
                data_X_temp.clear();
                data_Y_temp.clear();
                data_Z_temp.clear();
                cv_Z_temp.clear();
            }
        }
    }

    if (leftBorder > rightBorder)
    {
        long puffer = leftBorder;
        leftBorder  = rightBorder;
        rightBorder = puffer;
    }

    //    std::printf("leftBorder = %8ld    rightBorder = %8ld\n", leftBorder, rightBorder );

    leftBorder  = (SchrittweiteEncoder <= 10) * (leftBorder  + 20000) + (SchrittweiteEncoder > 10) * SchrittweiteEncoder * round((leftBorder  +20000) / SchrittweiteEncoder);
    rightBorder = (SchrittweiteEncoder <= 10) * (rightBorder + 20000) + (SchrittweiteEncoder > 10) * SchrittweiteEncoder * round((rightBorder +20000) / SchrittweiteEncoder);

    //    std::printf("leftBorder = %8ld    rightBorder = %8ld\n", leftBorder, rightBorder );

    {
        uint n, m;
        if (*data_X[0].begin() < *--data_X[0].end())
        {
            n = 0;
            m = 1;
        }
        else
        {
            n = data_X[0].size() -1;
            m = -1;
        }

        while (data_X[0][n] != leftBorder  && *min_element(data_X[0].begin(), data_X[0].end()) < leftBorder )
        {
            n = n + m;
        }
        leftBorder = n;
    }


    {
        uint n, m;
        if (*data_X[0].begin() < *--data_X[0].end())
        {
            n = data_X[0].size() -1;
            m = -1;
        }
        else
        {
            n = 0;
            m = 1;
        }

        while (data_X[0][n] != rightBorder && *max_element(data_X[0].begin(), data_X[0].end()) > rightBorder)
        {
            n = n + m;
        }
        rightBorder = n;
    }

    //    std::printf("leftBorder = %8ld    rightBorder = %8ld\n", leftBorder, rightBorder );
    //    std::printf("leftBorder = %8ld    rightBorder = %8ld\n", data_X[0][leftBorder], data_X[0][rightBorder] );

    if (leftBorder > rightBorder)
    {
        long puffer = leftBorder;
        leftBorder  = rightBorder;
        rightBorder = puffer;
    }

    //    std::printf("leftBorder = %8ld    rightBorder = %8ld\n", leftBorder, rightBorder );
    //    std::printf("leftBorder = %8ld    rightBorder = %8ld\n", data_X[0][leftBorder], data_X[0][rightBorder] );

    {
        std::vector< std::vector<long> >    puffer_X(data_X.size(), std::vector<long> (data_X[0].size()));
        std::vector< std::vector<long> >    puffer_Y(data_Y.size(), std::vector<long> (data_Y[0].size()));
        std::vector< std::vector<long> >    puffer_Z(data_Z.size(), std::vector<long> (data_Z[0].size()));
        std::vector< std::vector<long> > puffer_cv_Z(  cv_Z.size(), std::vector<long> (  cv_Z[0].size()));

        for (uint i = 0; i != puffer_X.size(); ++i)
        {
            for (uint j = 0; j != puffer_X[0].size(); ++j)
            {
                puffer_X[i][j] = data_X[i][j];
                puffer_Y[i][j] = data_Y[i][j];
                puffer_Z[i][j] = data_Z[i][j];
                puffer_cv_Z[i][j] =   cv_Z[i][j];
                //                std::cout << data_X[i][j] << ", ";
            }
            //            std::cout << "\n\n";
            data_X[i].resize(rightBorder -leftBorder +1);
            data_Y[i].resize(rightBorder -leftBorder +1);
            data_Z[i].resize(rightBorder -leftBorder +1);
            cv_Z[i].resize(rightBorder -leftBorder +1);
        }

        for (unsigned int i = 0; i != puffer_X.size(); ++i)
        {
            for (unsigned int j =leftBorder; j != rightBorder +1; ++j)
            {
                data_X[i][j -leftBorder] = puffer_X[i][j];
                data_Y[i][j -leftBorder] = puffer_Y[i][j];
                data_Z[i][j -leftBorder] = puffer_Z[i][j] * (puffer_Z[i][j] > 35);
                cv_Z[i][j -leftBorder] = puffer_cv_Z[i][j];
                //                                std::cout << data_Z[i][j -leftBorder] << ", ";
            }
            //                        std::cout << "\n\n";
        }
        puffer_X.clear();
        puffer_Y.clear();
        puffer_Z.clear();
        puffer_cv_Z.clear();
    }

    Schwerpunkt(data_X, data_Y, data_Z, Xrs, Yrs, Zrs, FMXrs, Vrs);
    //        sync = 1;
    //        std::thread t;
    //        t = std::thread(&GripPoint::Schwerpunkt, this, std::ref(data_X), std::ref(data_Y), std::ref(data_Z), std::ref(Xrs), std::ref(Yrs), std::ref(Zrs), std::ref(FMXrs), std::ref(Vrs));
    //        t.detach();
    //        while (sync != 0){}



    cv::Mat inputImage_01(cv_Z.size(), cv_Z[0].size(), CV_32F);
    cv::Mat inputImage_01_hist(cv_Z.size() * cv_Z[0].size(), 1, CV_32F);


    if (data_Y[0][0] < data_Y[1][0])
    {
        for (uint i = 0; i < cv_Z.size(); i++)
        {
            for (uint j = 0; j < cv_Z[0].size(); j++)
            {
                inputImage_01.at<float>(i,j) = (float)cv_Z[cv_Z.size() -1 -i][cv_Z[0].size() -1 -j]; /** 255 / max*/;
                inputImage_01_hist.at<float>(i*cv_Z[0].size() +j, 1) = (float)cv_Z[cv_Z.size() -1 -i][cv_Z[0].size() -1 -j]; /** 255 / max*/;
            }
        }
    }
    else
    {
        for (uint i = 0; i < cv_Z.size(); i++)
        {
            for (uint j = 0; j < cv_Z[0].size(); j++)
            {
                inputImage_01.at<float>(i,j) = (float)cv_Z[i][cv_Z[0].size() -1 -j]; /** 255 / max*/;
                inputImage_01_hist.at<float>(i*cv_Z[0].size() +j, 1) = (float)cv_Z[i][cv_Z[0].size() -1 -j]; /** 255 / max*/;
            }
        }
    }

    std::string Uebergabe_00 ="../data_Z.png";
    cv::imwrite(Uebergabe_00, inputImage_01);
    //    QString Uebergabe_00 ="../data_Z.png";
    //    cv::imwrite(qUtf8Printable(Uebergabe_00), inputImage_01);

    if (SchrittweiteEncoder <= 10)
    {
        for (uint i = 0; i != data_X.size(); ++i)
        {
            for (unsigned int j =0; j != data_X[i].size(); ++j)
            {
                data_X[i][j] = data_X[i][j] -20000;
            }
        }

        for (uint i = 0; i != Xrs.size(); ++i)
        {
            for (unsigned int j =0; j != Xrs[i].size(); ++j)
            {
                Xrs[i][j] = Xrs[i][j] -20000;
            }
        }
    }
    else
    {
        for (uint i = 0; i != data_X.size(); ++i)
        {
            for (unsigned int j =0; j != data_X[i].size(); ++j)
            {
                data_X[i][j] = data_X[i][j] - SchrittweiteEncoder * round(20000 / SchrittweiteEncoder);
                //                std::cout << data_X[i][j] << ", ";
            }
            //            std::cout << "\n\n";
        }

        for (uint i = 0; i != Xrs.size(); ++i)
        {
            for (unsigned int j =0; j != Xrs[i].size(); ++j)
            {
                Xrs[i][j] = Xrs[i][j] - SchrittweiteEncoder * round(20000 / SchrittweiteEncoder);
                //                std::cout << Xrs[i][j] << ", ";
            }
            //            std::cout << "\n\n";
        }
    }

    //    QString Uebergabe_01 ="../data_Zr.png";
    //    cv::imwrite(qUtf8Printable(Uebergabe_01), inputImage_01);
    std::string Uebergabe_01 ="../data_Zr.png";
    cv::imwrite(Uebergabe_01, inputImage_01);


    //    Diagramm(Uebergabe_00, data_X, data_Y, data_Z);

    if (showDia)
    {
        Diagramm* Dia_00 = new Diagramm;
        (*Dia_00)(Uebergabe_00, data_X, data_Y, data_Z);

        //        std::thread t_00(*Dia_00, std::cref(Uebergabe_00), std::ref(data_X), std::ref(data_Y), std::ref(data_Z));
        //        t_00.join();
    }

    //    std::vector<long> hist;
    //    int min, max;

    //    Histogramm(data_Z[0], hist, &min, &max);


    Manhattan(VRatio);



}

void GripPoint::Transponieren(std::vector< std::vector<long> > & vec)
{

    std::vector< std::vector<long> >::iterator row;
    std::vector<long>::iterator col;

    std::vector<std::vector<long>> puffer(vec.size(), std::vector<long> (vec[0].size()));
    std::vector< std::vector<long> >::iterator row_puffer;
    std::vector<long>::iterator col_puffer;

    for (row = vec.begin(), row_puffer = puffer.begin(); row != vec.end(); ++row, ++row_puffer)
    {
        for (col = row->begin(), col_puffer = row_puffer->begin(); col != row->end(); ++col, ++col_puffer)
        {
            *col_puffer = *col;
        }
    }

    vec.clear();
    //    Transponieren(data_Xr);
    //    Transponieren(data_Yr);
    //    Transponieren(data_Zr);
    std::vector<long> temp;

    for (uint j = 0; j < puffer[0].size(); ++j)
    {
        for (uint i = 0; i < puffer.size(); ++i)
        {
            temp.push_back(puffer[i][j]);
        }
        vec.push_back(temp);
        temp.clear();
    }
    puffer.clear();
}

void GripPoint::Raster(std::vector< std::vector<long> > & vec_X, std::vector< std::vector<long> > & vec_Y, std::vector< std::vector<long> > & vec_Z, std::vector< std::vector<long> > & vec_Xr, std::vector< std::vector<long> > & vec_Yr, std::vector< std::vector<long> > & vec_Zr)
{
    std::vector< std::vector<long> > puffer_X(vec_X.size(), std::vector<long> (vec_X[0].size()));
    std::vector< std::vector<long> > puffer_Y(vec_Y.size(), std::vector<long> (vec_Y[0].size()));
    std::vector< std::vector<long> > puffer_Z(vec_Z.size(), std::vector<long> (vec_Z[0].size()));

    for (uint i = 0; i != puffer_X.size(); ++i)
    {
        for (uint j = 0; j != puffer_X[0].size(); ++j)
        {
            puffer_X[i][j] = vec_X[i][j];
            puffer_Y[i][j] = vec_Y[i][j];
            puffer_Z[i][j] = vec_Z[i][j];
        }
    }

    long min, max;
    {
        std::vector<long> vec_X_min(puffer_X.size());
        std::vector<long> vec_X_max(puffer_X.size());
        {
            for (unsigned int i = 0; i != puffer_X.size(); ++i)
            {
                vec_X_min[i] = *--puffer_X[i].end();
                vec_X_max[i] = *puffer_X[i].begin();
            }
        }
        min = *min_element(vec_X_min.begin(), vec_X_min.end());
        max = *max_element(vec_X_max.begin(), vec_X_max.end());
        vec_X_min.clear();
        vec_X_max.clear();
    }

    {
        std::vector<long> vec_X_temp;
        std::vector<long> vec_Y_temp;
        std::vector<long> vec_Z_temp;
        if (max > min)
        {
            for (unsigned int i = 0; i != puffer_Z.size(); ++i)
            {
                for (int j = 0; j <= max -min; ++j)
                {
                    vec_X_temp.push_back(max -j);
                    vec_Y_temp.push_back(0);
                    vec_Z_temp.push_back(0);
                }
                vec_Xr.push_back(vec_X_temp);
                vec_Yr.push_back(vec_Y_temp);
                vec_Zr.push_back(vec_Z_temp);
                vec_X_temp.clear();
                vec_Y_temp.clear();
                vec_Z_temp.clear();
            }
        }
        else
        {
            long puffer;
            puffer = min;
            min = max;
            max = puffer;
            for (unsigned int i = 0; i != puffer_Z.size(); ++i)
            {
                for (int j = 0; j <= max -min; ++j)
                {
                    vec_X_temp.push_back(min +j);
                    vec_Y_temp.push_back(0);
                    vec_Z_temp.push_back(0);
                }
                vec_Xr.push_back(vec_X_temp);
                vec_Yr.push_back(vec_Y_temp);
                vec_Zr.push_back(vec_Z_temp);
                vec_X_temp.clear();
                vec_Y_temp.clear();
                vec_Z_temp.clear();
            }
        }
    }

    uint j, m, mr;
    long deltaX, deltaY, deltaZ;
    for (unsigned int n = 0; n != puffer_X.size(); ++n)
    {
        mr = 0;
        for(m = 0; m != puffer_X[0].size() -1; ++m)
        {
            while (vec_Xr[n][mr] > puffer_X[n][m] && mr <= vec_Xr[n].size() -1)
            {
                vec_Yr[n][mr] = round(puffer_Y[n][m]);
                vec_Zr[n][mr] = round(puffer_Z[n][m]);
                ++mr;
            }

            deltaX = puffer_X[n][m +1] -puffer_X[n][m];
            deltaY = puffer_Y[n][m +1] -puffer_Y[n][m];
            deltaZ = puffer_Z[n][m +1] -puffer_Z[n][m];

            if (abs(deltaX) < 1/* && mr <= vec_Xr[n].size() -1*/)
            {
                vec_Yr[n][mr] = round((puffer_Y[n][m] +puffer_Y[n][m +1]) / 2);
                vec_Zr[n][mr] = round((puffer_Z[n][m] +puffer_Z[n][m +1]) / 2);
            }
            else
            {
                j = 0;
                while (j < (uint)abs(deltaX) && mr <= vec_Xr[n].size() -1)
                {
                    vec_Yr[n][mr] = round(puffer_Y[n][m] +j * deltaY/abs(deltaX));
                    vec_Zr[n][mr] = round(puffer_Z[n][m] +j * deltaZ/abs(deltaX));
                    ++mr;
                    ++j;
                }
            }
        }
        while (mr <= vec_Xr[n].size() -1)
        {
            vec_Yr[n][mr] = round(puffer_Y[n][m]);
            vec_Zr[n][mr] = round(puffer_Z[n][m]);
            ++mr;
        }
    }
    puffer_X.clear();
    puffer_Y.clear();
    puffer_Z.clear();
}

void GripPoint::Schwerpunkt(std::vector< std::vector<long> > & vec_Xr, std::vector< std::vector<long> > & vec_Yr, std::vector< std::vector<long> > & vec_Zr, std::vector< std::vector<long> > & vec_Xrs, std::vector< std::vector<long> > & vec_Yrs, std::vector< std::vector<long> > & vec_Zrs, std::vector< std::vector<double> > & vec_FMXrs, std::vector< std::vector<double> > & vec_Vrs)
{    
    vec_Xrs.resize(0, std::vector<long> (0));
    vec_Yrs.resize(0, std::vector<long> (0));
    vec_Zrs.resize(0, std::vector<long> (0));
    vec_Vrs.resize(0, std::vector<double> (0));

    uint ar = 0, cr = 0;
    uint br = vec_Xr[0].size();
    uint dr = vec_Xr.size();
    uint n = cr, m = 0;
    //    int i = -1, j = -1;

    double FlaechenmomentX = 0, FlaechenmomentZ = 0, FlaecheXZ = 0;
    double Volumen = 0, deltaFlaecheXZ, deltaVolumen;
    long deltaX, deltaY;

    std::vector<long> vec_Xrs_temp;
    std::vector<long> vec_Yrs_temp;
    std::vector<long> vec_Zrs_temp;
    std::vector<double> vec_FMXrs_temp;
    std::vector<double> vec_Vrs_temp;

    while (n < dr -1)
    {

        while (n < dr -1 && std::accumulate(vec_Zr[n].begin(), vec_Zr[n].end(), 0.0)/vec_Zr[n].size() <= 0)
        {
            n++;
        }

        m = ar +1;
        //        i = -1;
        if (m <= br -2 && std::accumulate(vec_Zr[n].begin(), vec_Zr[n].end(), 0.0)/vec_Zr[n].size() > 0)
        {

            //            j++;
            while (m <= br -2 && std::accumulate(vec_Zr[n].begin(), vec_Zr[n].end(), 0.0)/vec_Zr[n].size() > 0 && n < dr -1)
            {
                while (m <= br -2 && vec_Zr[n][m] <= 0)
                {
                    m++;
                }

                if (m <= br -2 && vec_Zr[n][m] > 0)
                {

                    //                    i++;
                    while (m <= br -2 && vec_Zr[n][m] > 0 && n < dr -1)
                    {
                        deltaX = abs(vec_Xr[n][m +1] -vec_Xr[n][m -1]) * 0.5;
                        deltaY = abs(vec_Yr[n +1][m] -vec_Yr[n][m]);
                        deltaFlaecheXZ = deltaX * vec_Zr[n][m];
                        deltaVolumen = deltaX * deltaY * vec_Zr[n][m];
                        FlaechenmomentX = deltaFlaecheXZ * vec_Xr[n][m] +FlaechenmomentX;
                        FlaechenmomentZ = deltaFlaecheXZ * vec_Zr[n][m] * 0.5 +FlaechenmomentZ;
                        FlaecheXZ = deltaFlaecheXZ +FlaecheXZ;
                        Volumen = Volumen + deltaVolumen;
                        m++;
                    }
                }

                if (FlaechenmomentX > 0 && FlaechenmomentZ > 0)
                {
                    vec_Xrs_temp.push_back((FlaechenmomentX / FlaecheXZ));
                    vec_Zrs_temp.push_back((FlaechenmomentZ / FlaecheXZ));
                    vec_Yrs_temp.push_back(vec_Yr[n][0]);
                    vec_FMXrs_temp.push_back(FlaechenmomentX);
                    vec_Vrs_temp.push_back(Volumen/1000000);
                    //                    printf("%10.1f   %ld    %ld    \n", *--vec_Vrs_temp.end(), *--vec_Xrs_temp.end(), *--vec_Yrs_temp.end() );
                    FlaechenmomentX = 0;
                    FlaechenmomentZ = 0;
                    FlaecheXZ = 0;
                    Volumen = 0;
                    //                    std::printf("%8ld    %8ld    %8ld\n", *--vec_Xrs_temp.end(), *--vec_Yrs_temp.end(), *--vec_Zrs_temp.end());
                    //                    std::cout << *--vec_Xrs_temp.end() -20000 << ",  ";
                }
            }
            //            std::cout <<"\n";
            vec_Xrs.push_back(vec_Xrs_temp);
            //            std::cout << "vec_Xrs.size() = " << vec_Xrs.size() << ",    vec_Xrs[n].size() = " << vec_Xrs[n].size() << "\n";
            vec_Yrs.push_back(vec_Yrs_temp);
            //            std::cout << "vec_yrs.size() = " << vec_Yrs.size() << ",    vec_Yrs[n].size() = " << vec_Yrs[n].size() << "\n";
            vec_Zrs.push_back(vec_Zrs_temp);
            //            std::cout << "vec_Zrs.size() = " << vec_Zrs.size() << ",    vec_Zrs[n].size() = " << vec_Zrs[n].size() << "\n\n";
            vec_FMXrs.push_back(vec_FMXrs_temp);
            vec_Vrs.push_back(vec_Vrs_temp);
            vec_Xrs_temp.resize(0);
            vec_Yrs_temp.resize(0);
            vec_Zrs_temp.resize(0);
            vec_FMXrs_temp.resize(0);
            vec_Vrs_temp.resize(0);
            n++;
            //            std::cout << "\n\n";
        }
    }
    sync = 0;
}

void GripPoint::Histogramm(std::vector<float>& vec_data, std::vector<long>& vec_hist, float& min, float& max, const std::string& title)
{
    cv::Mat inputImage_01_hist(1, vec_data.size(), CV_32F);
    cv::Mat hist;

    for (uint i = 0; i < vec_data.size(); i++)
    {
        inputImage_01_hist.at<float>(0, i) = (float)vec_data[i];
    }
    cv::sort(inputImage_01_hist, inputImage_01_hist, cv::SORT_ASCENDING);
    min = inputImage_01_hist.at<float>(0, 0);
    max = inputImage_01_hist.at<float>(0, inputImage_01_hist.cols -1);
    //    std::cout << "\nmin = " << min << "\n";
    //    std::cout << "max = " << max << "\n";
    //    std::cout << inputImage_01_hist << "\n\n";

    int histSize; float BinWidth;
    /// Establish the number of bins
    //    for (uint i = 0; i != O.size(); i++) std::cout << O[i] << ",  ";
    /// Freedman-Diaconis 0
    //        {
    //            cv::sort(inputImage_01_hist, inputImage_01_hist, cv::SORT_ASCENDING);

    //            float untereQuartil, obereQuartil;

    //            if (inputImage_01_hist.cols * 0.25 == cvRound(inputImage_01_hist.cols * 0.25))
    //            {
    //                untereQuartil = (inputImage_01_hist.at<float>(1, (int)(inputImage_01_hist.cols * 0.25)) + inputImage_01_hist.at<float>(1, (int)(inputImage_01_hist.cols * 0.25 +1))) / 2;
    //            }
    //            else
    //            {
    //                untereQuartil = inputImage_01_hist.at<float>(1, cvCeil(inputImage_01_hist.cols * 0.25));
    //            }
    //            //            std::cout << "untereQuartil = " << untereQuartil << "\n\n";

    //            if (inputImage_01_hist.cols * 0.75 == cvRound(inputImage_01_hist.cols * 0.75))
    //            {
    //                obereQuartil = (inputImage_01_hist.at<float>(1, (int)(inputImage_01_hist.cols * 0.75)) + inputImage_01_hist.at<float>(1, (int)(inputImage_01_hist.cols * 0.75 +1))) / 2;
    //            }
    //            else
    //            {
    //                obereQuartil = inputImage_01_hist.at<float>(1, cvCeil(inputImage_01_hist.cols * 0.75));
    //            }
    //            //            std::cout << "obereQuartil = " << obereQuartil << "\n\n";

    //            float IQA = obereQuartil - untereQuartil;
    //            histSize = cvRound(2 * IQA / WURZEL(3, inputImage_01_hist.cols));
    //        }


    /// Scott 400.405
    float sd = 0.0;
    {
        float mean = 0.0;
        for (int i = 0; i < inputImage_01_hist.cols; i++) {mean += inputImage_01_hist.at<float>(0, i);}
        mean /= inputImage_01_hist.cols;
        //        std::cout << "mean = " << mean << "\n";

        //        float sd = 0.0;
        for (int i = 0; i < inputImage_01_hist.cols; i++) {sd += (inputImage_01_hist.at<float>(0, i) - mean) * (inputImage_01_hist.at<float>(0, i) - mean);}
        //        if (sd > 0) {sd = sqrt(sd / (inputImage_01_hist.cols -1));}
        //        sd = sqrt(sd / (inputImage_01_hist.cols -1));
        //        std::cout << "sd = " << sd << "\n";
        //        std::cout << "inputImage_01_hist.cols = " << inputImage_01_hist.cols << "\n";

        histSize = 1;
        BinWidth = mean;
        min = 0;
        if (sd > 0)
        {
            sd = sqrt(sd / (inputImage_01_hist.cols -1));
            histSize = ceil((max -min) / (3.49 * sd / WURZEL(3, inputImage_01_hist.cols)));
            BinWidth = 3.49 * sd / WURZEL(3, inputImage_01_hist.cols);
            min = inputImage_01_hist.at<float>(0, 0);
        }

        //        std::cout << "NumBins = " << histSize << ",    BinWidth = " << BinWidth <<"\n\n";
    }



    /// Square Root 445.879
    //                histSize = ceil(sqrt(inputImage_01_hist.cols));


    /// Sturges 449.514
    //                histSize = ceil(1 +log2(inputImage_01_hist.cols));


    //    max = min +histSize * 3.49 * sd / WURZEL(3, inputImage_01_hist.cols);
    max = min +histSize * BinWidth;
    //    printf("\nmax = %f\n\n", max);


    /// Set the ranges ( for B,G,R) )
    float range[] = { min, max } ;
    const float* histRange = { range };

    bool uniform = true, accumulate = false;

    //    cv::Mat hist;

    /// Compute the histograms:
    cv::calcHist( &inputImage_01_hist, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );
    //    std::cout << hist << "\n\n";

    //    for( int i = 0; i != histSize ; i++ )
    //    {
    //        printf("\nbin_w*(i) = ->%5d<-     hist.at<float>(i) = ->%10.3f<-     bin_w*(i+1) = ->%5d<-", (int)(min +(3.49 * sd / WURZEL(3, inputImage_01_hist.cols))*(i)), hist.at<float>(i), (int)(min +(3.49 * sd / WURZEL(3, inputImage_01_hist.cols))*(i+1)));
    //        //        std::cout << "hist.at<float>(i-1) = " << hist.at<float>(i-1) << "\n";

    //    }
    //    std::cout << "\n";

    vec_hist.resize(0);
    for (int i = 0; i < histSize; i++)
    {
        vec_hist.push_back((long)round(hist.at<float>(i)));
        //        std::cout << "hist.at<float>(i) = " << hist.at<float>(i) << "\n";
    }

    if (Hist)
    {
        // Draw the histograms for B, G and R
        //    int hist_w = 3 * histSize, hist_h = 750;
        int hist_w = 750, hist_h = hist_w * 2 / 3;
        int bin_w = cvRound( (double) hist_w / histSize );

        cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 255, 255, 255) );

        /// Normalize the result to [ 0, histImage.rows ]
        cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

        /// Draw for each channel
        //        float graph_length = 0;
        //        cv::sort(inputImage_01_hist, inputImage_01_hist, cv::SORT_ASCENDING);
        for( int i = 0; i != histSize ; i++ )
        {
            cv::rectangle( histImage,
                           cv::Point( bin_w*(i)    , hist_h - cvRound(hist.at<float>(i))),
                           cv::Point( bin_w*(i+1) - 1, hist_h                               ),
                           cv::Scalar(0, 0, 0),
                           2, 8, 0);
            //        printf("\nbin_w*(i) = ->%5d<-     hist.at<float>(i) = ->%10.3f<-     bin_w*(i+1) = ->%5d<-", (int)(min +(3.49 * sd / WURZEL(3, inputImage_01_hist.cols))*(i)), hist.at<float>(i), (int)(min +(3.49 * sd / WURZEL(3, inputImage_01_hist.cols))*(i+1)));
            //        std::cout << "hist.at<float>(i-1) = " << hist.at<float>(i-1) << "\n";

        }
        //    std::cout << "\n";
        Display(title, histImage);
    }
}

void GripPoint::Display(const std::string& title, cv::Mat &histImage)
{
    cv::namedWindow(title, CV_WINDOW_AUTOSIZE );
    cv::imshow(title, histImage );
    //    cv::waitKey(0);
    //    cv::waitKey(0);
    //    cv::destroyWindow(title);
}

void GripPoint::Manhattan(uint &VRatio)
{
    std::vector<std::vector<long>> M(Xrs.size(), std::vector<long> (0));
    std::vector<std::vector<uint>> N(Xrs.size(), std::vector<uint> (0));
    std::vector<float> O(0);
    std::vector<float> Q(0);
    uint r = 0, A = 0;

    for (uint q = 0; q != Xrs.size() -1; q++)
    {
        //        std::cout << "\n";
        M[q].resize( Xrs[q].size() );
        N[q].resize( Xrs[q].size() );
        O.resize( O.size() + Xrs[q].size() );
        Q.resize( Q.size() + Xrs[q].size() );
        for (uint o = 0; o != Xrs[q].size(); o++)
        {
            M[q][o] = 0;
            N[q][o] = 0;
            //            printf("->%8.2lf<-/->%5ld<-", Vrs[q][o], Xrs[q][o]);
            if (Yrs[q][o] > 0)
            {
                for (uint p = 0; p != Xrs[q +1].size(); p++)
                {
                    A = abs(Xrs[q][o] - Xrs[q +1][p]) + abs(Yrs[q][o] - Yrs[q +1][p]) + 0.5 * abs(Zrs[q][o] - Zrs[q +1][p]);
                    //                    A = abs(Xrs[q][o] - Xrs[q +1][p] + Yrs[q][o] - Yrs[q +1][p] + 0.5 * (Zrs[q][o] - Zrs[q +1][p]));
                    if ( A < M[q][o] || M[q][o] == 0 )
                    {
                        M[q][o] = A;
                        N[q][o] = p +1;
                        O[r +o] = (float)A;
                        Q[r +o] = (float)Vrs[q][o];
                        //                        O.push_back((float)A);
                        //                        Q.push_back((float)Vrs[q][o]);
                        //                        printf("\nO.size() = %d     Q.size() = %d", O.size(), Q.size());
                        //                        std::cout << o << "  ";
                    }
                }
            }
        }
        r = O.size();
        //        std::cout << "\n";
    }

    //    printf("\nO.size() = %ld     Q.size() = %ld", O.size(), Q.size());

    //    std::cout << "\n";
    //    for (uint i = 0; i != N.size(); i++)
    //    {
    //        std::cout << "N[i].size() = " << N[i].size() << "\n";
    //        for (uint j = 0; j != N[i].size(); j++)
    //        {
    //            std::cout << N[i][j] << "  ";
    //        }
    //        std::cout << "\n\n";
    //    }
    //    std::cout << "N.size() = " << N.size() << "\n";

    //    M_temp.clear();
    //    N_temp.clear();

    //    std::thread t[2];

    std::vector<long> hist1;
    float min1 = 0, max1 = 0;
    std::string title1 = "Häufigkeitsverteilung: Manhattan-Distanz";

    std::vector<long> hist2;
    float min2 = 0, max2 = 0;
    std::string title2 = "Häufigkeitsverteilung: Schnittflächen-Volumina";


    Histogramm( O, hist1, min1, max1, title1);
    //    t[0] = std::thread(&GripPoint::Histogramm, this, std::ref(O), std::ref(hist1), std::ref(min1), std::ref(max1), std::cref(title1));

    Histogramm( Q, hist2, min2, max2, title2);
    //    t[1] = std::thread(&GripPoint::Histogramm, this, std::ref(Q), std::ref(hist2), std::ref(min2), std::ref(max2), std::cref(title2));

    //    t[0].join();
    //    t[1].join();

    //    std::cout << "min1 = " << min1 << ",   max1 = " << max1 << "\n\n";
    //    std::cout << "min2 = " << min2 << ",   max2 = " << max2 << "\n\n";

    float h1 = min1 + (max1 -min1) / hist1.size();
    int Messgrenze = 3;
    h1 = h1 * (h1 >= Messgrenze) + Messgrenze * (h1 < Messgrenze);

    float h2 = min2 + (hist2.size() > 1) * (max2 -min2) / hist2.size();

    //    printf("\n\nh1 = %f       h2 = %f\n\n", h1, h2);


    for (uint q = 0; q != M.size() -1; q++)
    {
        for (uint p = 0; p != M[q].size(); p++)

        {
            //            std::cout << "M[q][p] > h1 = " << (uint)(M[q][p] > h1) << ",    Vrs[q][p] < h2 = " << (uint)(Vrs[q][p] < h2) << "\n";
            //                        std::cout << "Vrs[q][p] = " << Vrs[q][p] << ",       h2 = " << h2 << "\n";
            if (M[q][p] > h1 || Vrs[q][p] < h2)
            {
                N[q][p] = 0;
            }
            //            std::cout << N[q][p] << ", ";
        }
        //        std::cout << "\n";
    }
    //    std::cout << "\n";


    Xks.resize(0, std::vector<double> (0));
    Yks.resize(0, std::vector<double> (0));
    Zks.resize(0, std::vector<double> (0));
    Vks.resize(0, std::vector<double> (0));
    std::vector<double> Xks_temp(0);
    std::vector<double> Yks_temp(0);
    std::vector<double> Zks_temp(0);
    std::vector<double> Vks_temp(0);

    for ( uint qi, q = 0; q != N.size() -1; q++)
    {
        for ( uint pb, pi, p = 0; p != N[q].size(); p++ )
        {
            if ( N[q][p] > 0 )
            {
                pi = p;
                qi = q;
                while ( qi <= N.size() && pi < N[qi].size() && N[qi][pi] > 0)
                {
                    Xks_temp.push_back((double)Xrs[qi][pi]);
                    Yks_temp.push_back((double)Yrs[qi][pi]);
                    Zks_temp.push_back((double)Zrs[qi][pi]);
                    Vks_temp.push_back(Vrs[qi][pi]);
                    pb = N[qi][pi] -1;
                    N[qi][pi] = 0;
                    pi = pb;
                    qi++;
                    //                    std::cout << "qi = " << qi << ",   pi = " << pi <<  ",   Xrs[qi][pi] = " << Xrs[qi][pi] << "\n";
                    //                    std::cout << "Vks_temp.size() = " << Vks_temp.size() << "\n\n";
                }
                Xks.push_back(Xks_temp);
                Yks.push_back(Yks_temp);
                Zks.push_back(Zks_temp);
                Vks.push_back(Vks_temp);
                Xks_temp.resize(0);
                Yks_temp.resize(0);
                Zks_temp.resize(0);
                Vks_temp.resize(0);
            }
        }
    }
    Xks_temp.clear();
    Yks_temp.clear();
    Zks_temp.clear();
    Vks_temp.clear();

    //    std::cout << "\n";
    //    for (uint i = 0; i != Vks.size(); i++)
    //    {
    ////        std::cout << "Vks[i].size() = " << Vks[i].size() << "\n";
    //        for (uint j = 0; j != Vks[i].size(); j++)
    //        {
    //            std::cout << Vks[i][j] << "  ";
    //        }
    //        std::cout << "\n\n";
    //    }
    //    std::cout << "Vks.size() = " << Vks.size() << "\n";

    std::vector<float> Vkssum(0);
    double sum = 0;
    //    for (uint i = 0; i != Vks.size(); i++) Vkssum.push_back(std::accumulate(Vks[i].begin(), Vks[i].end(), 0.0));
    for (uint i = 0; i != Vks.size(); i++)
    {
        //        printf("\n\n");
        sum = 0;
        for (uint j = 0; j != Vks[i].size(); j++)
        {
            sum += Vks[i][j];
            //            printf("->%8.3lf<-->%8.3lf<-\n", Vks[i][j], sum);
        }
        Vkssum.push_back((float)sum);
        //        printf("\n->%20.3lf<-\n\n", *--Vkssum.end() );
    }

    //    printf("\n\nVkssum.size() = %20d\n\n", Vkssum.size());

    //        std::cout << "\n\n";

    std::vector<long> hist3;
    float min3 = 0, max3 = 0;
    std::string title3 = "Häufigkeitsverteilung: Schwerpunkt-Volumina";

    Histogramm(Vkssum, hist3, min3, max3, "Häufigkeitsverteilung: Schwerpunkt-Volumina");
    //    std::cout << "min3 = " << min3 << ",   max3 = " << max3 <<  ",   hist3.size() = " << hist3.size() << "\n\n";
    double h3 = max3 - (max3 -min3) / hist3.size();
    //    std::cout << "h3 = " << h3 << "\n\n";

    std::vector<double> Xksp(0);
    std::vector<double> Yksp(0);
    std::vector<double> Zksp(0);
    std::vector<double> Vksp(0);
    std::vector<std::vector<double>> Xksl(0);
    std::vector<std::vector<double>> Yksl(0);
    std::vector<std::vector<double>> Zksl(0);

    for (uint /*o = 0, */p = 0; p != Vkssum.size(); p++)
    {
        //        long sum;
        //        std::cout << "\n";
        if (Vkssum[p] > h3 || Vkssum[p] > h3/VRatio )
        {
            sum = 0;
            for (uint q = 0; q != Xks[p].size(); q++) {/*printf("->%10.2lf<-       ->%10.2lf<-       ->%10.2lf<-\n", Xks[p][q], Vks[p][q], Vkssum[p]); */sum += Xks[p][q] * Vks[p][q] / (double)Vkssum[p];}
            Xksp.push_back(sum);

            sum = 0;
            for (uint q = 0; q != Yks[p].size(); q++) {/*printf("->%10.2lf<-       ->%10.2lf<-       ->%10.2lf<-\n", Yks[p][q], Vks[p][q], Vkssum[p]); */sum += Yks[p][q] * Vks[p][q] / (double)Vkssum[p];}
            Yksp.push_back(sum);

            sum = 0;
            for (uint q = 0; q != Zks[p].size(); q++) {/*printf("->%10.2lf<-       ->%10.2lf<-       ->%10.2lf<-\n", Zks[p][q], Vks[p][q], Vkssum[p]); */sum += Zks[p][q] * Vks[p][q] / (double)Vkssum[p];}
            Zksp.push_back(sum);

            Xksl.push_back(Xks[p]);
            Yksl.push_back(Yks[p]);
            Zksl.push_back(Zks[p]);
            Vksp.push_back((double)Vkssum[p]);
            //            o++;
        }
    }

    bool Fertig = false;
    while ( !Fertig )
    {
        double Puffer;
        std::vector<double> Puffer_vec(Xksl.size());
        Fertig = true;
        for (uint r = 0; r != Vksp.size() -1; r++)
        {
            if ( Vksp[r] < Vksp[r +1] )
            {
                Fertig = false;

                Puffer = Vksp[r];
                Vksp[r] = Vksp[r +1];
                Vksp[r +1] = Puffer;

                Puffer = Xksp[r];
                Xksp[r] = Xksp[r +1];
                Xksp[r +1] = Puffer;

                Puffer = Yksp[r];
                Yksp[r] = Yksp[r +1];
                Yksp[r +1] = Puffer;

                Puffer = Zksp[r];
                Zksp[r] = Zksp[r +1];
                Zksp[r +1] = Puffer;

                Puffer_vec = Xksl[r];
                Xksl[r] = Xksl[r +1];
                Xksl[r +1] = Puffer_vec;

                Puffer_vec = Yksl[r];
                Yksl[r] = Yksl[r +1];
                Yksl[r +1] = Puffer_vec;

                Puffer_vec = Zksl[r];
                Zksl[r] = Zksl[r +1];
                Zksl[r +1] = Puffer_vec;
            }
        }
    }

    std::printf("\n\n->Volumen[Liter]<-         ->       X[mm]<-         ->       Y[mm]<-         ->       Z[mm]<-\n");
    for (uint i = 0; i != Xksp.size(); i++)printf("->%14.3lf<-         ->%12.0lf<-         ->%12.0lf<-         ->%12.0lf<-\n", Vksp[i], round(Xksp[i]), round(Yksp[i]), round(Zksp[i]));
    std::printf("\n");

    xGp = round(Xksp[0]);
    yGp = round(Yksp[0]);
    zGp = round(Zksp[0]);

    cv::waitKey(0);
    //    cv::destroyWindow(title1);
    //    cv::destroyWindow(title2);
    //    cv::destroyWindow(title3);
    cv::destroyAllWindows();

}

GripPoint::~GripPoint()
{
    data_X.clear();
    data_Y.clear();
    data_Z.clear();
    //    delete ui;
}
