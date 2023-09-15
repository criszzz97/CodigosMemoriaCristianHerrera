#ifndef GRAFICO_H
#define GRAFICO_H

#include <QtCharts/QChartView>

#include <QtCharts/QBarSeries>

#include <QtCharts/QBarSet>

#include <QtCharts/QLegend>

#include <QtCharts/QBarCategoryAxis>

#include <QHorizontalStackedBarSeries>

#include <QLineSeries>

#include <QtCharts/QCategoryAxis>

#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "datosconsumo.h"
#include <QDateTimeAxis>

using namespace QtCharts;
using namespace std;
class Grafico: public QChartView
{
public:
    Grafico();
    virtual ~Grafico();
    Grafico * viewGraph();
    void operator=(Grafico & G);
    void setValues(vector<DatosConsumo> *x,QString tipo,bool debug);
    void setUnidadConsumo(QString unidad);
private:
    vector<int> valores;
    QLineSeries *series;
    QChart *chart;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    bool flag_serie;
    QString tipoo;
    bool flag_zero;
    QString unit;
    bool flag_unidad_consumo;
};

#endif // GRAFICO_H

