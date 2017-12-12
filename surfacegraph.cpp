/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "surfacegraph.h"
#include <iostream>

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>
#include <QtGui/QImage>
#include <QtCore/qmath.h>

using namespace QtDataVisualization;

int sampleCountX;
int sampleCountZ;
const int heightMapGridStepX = 1;
const int heightMapGridStepZ = 1;

float sampleMin_X;
float sampleMax_X;
float sampleMin_Z;
float sampleMax_Z;
float sampleMin_Y;
float sampleMax_Y;

//SurfaceGraph::SurfaceGraph(Q3DSurface *surface, QImage heightMapImage, QSurfaceDataArray* dataArray)
SurfaceGraph::SurfaceGraph(Q3DSurface *surface, QImage heightMapImage, std::vector<std::vector<long> > &data_XP, std::vector<std::vector<long> > &data_YP, std::vector<std::vector<long> > &data_ZP)
    : m_graph(surface)
{
    m_graph->setAxisX(new QValue3DAxis);
    m_graph->setAxisY(new QValue3DAxis);
    m_graph->setAxisZ(new QValue3DAxis);

    //! [0]
//    m_sqrtSinProxy = new QSurfaceDataProxy();
//    m_sqrtSinSeries = new QSurface3DSeries(m_sqrtSinProxy);
    m_xyzSurfaceProxy = new QSurfaceDataProxy();
    m_xyzSurfaceSeries = new QSurface3DSeries(m_xyzSurfaceProxy);

    //! [0]

    data_X = data_XP;
    data_Y = data_YP;
    data_Z = data_ZP;
    convertData();
    //    convertData(data_X, data_Z, data_Y);

    //! [2]
    m_heightMapProxy = new QHeightMapSurfaceDataProxy(heightMapImage);
    m_heightMapSeries = new QSurface3DSeries(m_heightMapProxy);
    m_heightMapSeries->setItemLabelFormat(QStringLiteral("(@xLabel, @zLabel): @yLabel"));
    m_heightMapProxy->setValueRanges(0.0f, heightMapImage.width(), 0.0f, heightMapImage.height());
    //! [2]
    m_heightMapWidth = heightMapImage.width();
    m_heightMapHeight = heightMapImage.height();
}

SurfaceGraph::~SurfaceGraph()
{
    data_X.clear();
    data_Y.clear();
    data_Z.clear();
    delete m_graph;
}


//void SurfaceGraph::convertData(std::vector<std::vector<long> > data_X, std::vector<std::vector<long> > data_Z, std::vector<std::vector<long> > data_Y)
void SurfaceGraph::convertData()
{
    std::vector<long> vec_X_min;
    std::vector<long> vec_X_max;
    std::vector<long> vec_Y_min;
    std::vector<long> vec_Y_max;
    std::vector<long> vec_Z_min;
    std::vector<long> vec_Z_max;

    std::vector<long> vec_X_temp;
    std::vector<long> vec_Y_temp;
    std::vector<long> vec_Z_temp;

    QSurfaceDataArray* dataArray = new QSurfaceDataArray;
    dataArray->reserve(data_Z.size());
    for (uint i = 0 ; i < data_Z.size() ; i++)
    {
        QSurfaceDataRow* newRow = new QSurfaceDataRow(data_Z[0].size());
        int index = 0;
        for (uint j = 0; j < data_Z[0].size(); j++)
        {
            vec_X_temp.push_back(data_X[i][j]);
            vec_Y_temp.push_back(data_Y[i][j]);
            vec_Z_temp.push_back(data_Z[i][j]);
            (*newRow)[index++].setPosition(QVector3D((float)data_X[i][j], (float)data_Y[i][j], (float)data_Z[i][j]));
        }
        vec_X_min.push_back(*min_element(vec_X_temp.begin(), vec_X_temp.end()));
        vec_X_max.push_back(*max_element(vec_X_temp.begin(), vec_X_temp.end()));
        vec_Y_min.push_back(*min_element(vec_Y_temp.begin(), vec_Y_temp.end()));
        vec_Y_max.push_back(*max_element(vec_Y_temp.begin(), vec_Y_temp.end()));
        vec_Z_min.push_back(*min_element(vec_Z_temp.begin(), vec_Z_temp.end()));
        vec_Z_max.push_back(*max_element(vec_Z_temp.begin(), vec_Z_temp.end()));

        *dataArray << newRow;
        m_xyzSurfaceProxy->resetArray(dataArray);
    }
    vec_X_temp.clear();
    vec_Y_temp.clear();
    vec_Z_temp.clear();

    sampleMin_X = (float)*min_element(vec_X_min.begin(), vec_X_min.end());
    sampleMax_X = (float)*max_element(vec_X_max.begin(), vec_X_max.end());
    sampleMin_Y = (float)*min_element(vec_Y_min.begin(), vec_Y_min.end());
    sampleMax_Y = (float)*max_element(vec_Y_max.begin(), vec_Y_max.end());
    sampleMin_Z = (float)*min_element(vec_Z_min.begin(), vec_Z_min.end());
    sampleMax_Z = (float)*max_element(vec_Z_max.begin(), vec_Z_max.end());

    sampleCountX = data_X[0].size();
    sampleCountZ = data_Z.size();

    vec_X_min.clear();
    vec_X_max.clear();
    vec_Y_min.clear();
    vec_Y_max.clear();
    vec_Z_min.clear();
    vec_Z_max.clear();
}

//! [1]
//void SurfaceGraph::fillSqrtSinProxy()
//{
//}
//! [1]

void SurfaceGraph::enableXYZSurfaceModel(bool enable)
{
    if (enable) {
        //! [3]
//        m_sqrtSinSeries->setDrawMode(QSurface3DSeries::DrawSurface);
//        m_sqrtSinSeries->setFlatShadingEnabled(false);
        m_xyzSurfaceSeries->setDrawMode(QSurface3DSeries::DrawSurface);
        m_xyzSurfaceSeries->setFlatShadingEnabled(false);

        m_graph->axisX()->setLabelFormat("%.0f mm");
        m_graph->axisZ()->setLabelFormat("%.0f mm");
        m_graph->axisY()->setLabelFormat("%.0f mm");
        m_graph->axisX()->setRange(sampleMin_X, sampleMax_X);
        m_graph->axisY()->setRange(sampleMin_Y, sampleMax_Y);
        m_graph->axisZ()->setRange(sampleMin_Z, sampleMax_Z);
        m_graph->axisX()->setLabelAutoRotation(30);
        m_graph->axisY()->setLabelAutoRotation(90);
        m_graph->axisZ()->setLabelAutoRotation(30);

        m_graph->removeSeries(m_heightMapSeries);
        m_graph->addSeries(m_xyzSurfaceSeries);
        //! [3]

        //! [8]
        // Reset range sliders for Sqrt&Sin
        m_rangeMinX = sampleMin_X;
        m_rangeMinZ = sampleMin_Z;
        m_stepX = (sampleMax_X - sampleMin_X) / float(sampleCountX - 1);
        m_stepZ = (sampleMax_Z - sampleMin_Z) / float(sampleCountZ - 1);
        m_axisMinSliderX->setMaximum(sampleCountX - 2);
        m_axisMinSliderX->setValue(0);
        m_axisMaxSliderX->setMaximum(sampleCountX - 1);
        m_axisMaxSliderX->setValue(sampleCountX - 1);
        m_axisMinSliderZ->setMaximum(sampleCountZ - 2);
        m_axisMinSliderZ->setValue(0);
        m_axisMaxSliderZ->setMaximum(sampleCountZ - 1);
        m_axisMaxSliderZ->setValue(sampleCountZ - 1);
        //! [8]
    }
}

void SurfaceGraph::enableHeightMapModel(bool enable)
{
    if (enable) {
        //! [4]
        m_heightMapSeries->setDrawMode(QSurface3DSeries::DrawSurface);
        m_heightMapSeries->setFlatShadingEnabled(false);

        m_graph->axisX()->setLabelFormat("%.0f Step");
        m_graph->axisZ()->setLabelFormat("%.0f Step");
        m_graph->axisY()->setLabelFormat("%.0f Step");
        m_graph->axisX()->setAutoAdjustRange(true);
        m_graph->axisY()->setAutoAdjustRange(true);
        m_graph->axisZ()->setAutoAdjustRange(true);
        m_graph->axisX()->setTitle(QStringLiteral("Width"));
        m_graph->axisY()->setTitle(QStringLiteral("Height"));
        m_graph->axisZ()->setTitle(QStringLiteral("Length"));

        m_graph->removeSeries(m_xyzSurfaceSeries);
        m_graph->addSeries(m_heightMapSeries);
        //! [4]

        // Reset range sliders for height map
        int mapGridCountX = m_heightMapWidth  / heightMapGridStepX;
        int mapGridCountZ = m_heightMapHeight / heightMapGridStepZ;
        m_rangeMinX = 0.0f;
        m_rangeMinZ = 0.0f;
        m_stepX = m_heightMapWidth  / float(mapGridCountX - 1);
        m_stepZ = m_heightMapHeight / float(mapGridCountZ - 1);
        m_axisMinSliderX->setMaximum(mapGridCountX - 2);
        m_axisMinSliderX->setValue(0);
        m_axisMaxSliderX->setMaximum(mapGridCountX - 1);
        m_axisMaxSliderX->setValue(mapGridCountX - 1);
        m_axisMinSliderZ->setMaximum(mapGridCountZ - 2);
        m_axisMinSliderZ->setValue(0);
        m_axisMaxSliderZ->setMaximum(mapGridCountZ - 1);
        m_axisMaxSliderZ->setValue(mapGridCountZ - 1);
    }
}

void SurfaceGraph::adjustXMin(int min)
{
    float minX = m_stepX * float(min) + m_rangeMinX;

    int max = m_axisMaxSliderX->value();
    if (min >= max) {
        max = min + 1;
        m_axisMaxSliderX->setValue(max);
    }
    float maxX = m_stepX * max + m_rangeMinX;

    setAxisXRange(minX, maxX);
}

void SurfaceGraph::adjustXMax(int max)
{
    float maxX = m_stepX * float(max) + m_rangeMinX;

    int min = m_axisMinSliderX->value();
    if (max <= min) {
        min = max - 1;
        m_axisMinSliderX->setValue(min);
    }
    float minX = m_stepX * min + m_rangeMinX;

    setAxisXRange(minX, maxX);
}

void SurfaceGraph::adjustZMin(int min)
{
    float minZ = m_stepZ * float(min) + m_rangeMinZ;

    int max = m_axisMaxSliderZ->value();
    if (min >= max) {
        max = min + 1;
        m_axisMaxSliderZ->setValue(max);
    }
    float maxZ = m_stepZ * max + m_rangeMinZ;

    setAxisZRange(minZ, maxZ);
}

void SurfaceGraph::adjustZMax(int max)
{
    float maxX = m_stepZ * float(max) + m_rangeMinZ;

    int min = m_axisMinSliderZ->value();
    if (max <= min) {
        min = max - 1;
        m_axisMinSliderZ->setValue(min);
    }
    float minX = m_stepZ * min + m_rangeMinZ;

    setAxisZRange(minX, maxX);
}

//! [5]
void SurfaceGraph::setAxisXRange(float min, float max)
{
    m_graph->axisX()->setRange(min, max);
}

void SurfaceGraph::setAxisZRange(float min, float max)
{
    m_graph->axisZ()->setRange(min, max);
}
//! [5]

//! [6]
void SurfaceGraph::changeTheme(int theme)
{
    m_graph->activeTheme()->setType(Q3DTheme::Theme(theme));
}
//! [6]

void SurfaceGraph::setBlackToYellowGradient()
{
    //! [7]
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::black);
    gr.setColorAt(0.33, Qt::blue);
    gr.setColorAt(0.67, Qt::red);
    gr.setColorAt(1.0, Qt::yellow);

    m_graph->seriesList().at(0)->setBaseGradient(gr);
    m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
    //! [7]
}

void SurfaceGraph::setGreenToRedGradient()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::darkGreen);
    gr.setColorAt(0.5, Qt::yellow);
    gr.setColorAt(0.8, Qt::red);
    gr.setColorAt(1.0, Qt::darkRed);

    m_graph->seriesList().at(0)->setBaseGradient(gr);
    m_graph->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

