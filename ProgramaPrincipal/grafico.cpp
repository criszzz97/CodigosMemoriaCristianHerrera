#include "grafico.h"
#include "qdebug.h"

Grafico::Grafico():QChartView()
{
    series = new QLineSeries();
    chart = new QChart();
    this->setChart(chart);
    flag_serie = false;
    tipoo = "Consumo Acumulado Casa";
    flag_zero = true;
    flag_unidad_consumo = false;
    unit = "Agua [L/Dia]";
}


void Grafico::setUnidadConsumo(QString unidad){
    if(unidad == "Anual"){
        unit = "Agua [L/Año]";
    }
    else if(unidad == "Mensual"){
        unit = "Agua [L/Mes]";
    }
    else if(unidad == "Diario"){
        unit = "Agua [L/Dia]";
    }
    else unit = "Agua [L/Minuto]";
}

void Grafico::setValues(vector<DatosConsumo> *x,QString tipo,bool debug){
    tipoo = tipo;
    if(flag_serie){
        chart->removeSeries(series);
        series->clear();
        chart->removeAxis(axisX);
        chart->removeAxis(axisY);
        delete axisX;
        delete axisY;
    }
    axisX = new QDateTimeAxis;
    axisY = new QValueAxis;
    flag_zero = true;
    if(debug) axisX->setFormat("dd MM yyyyThh:mm::ss");
    else axisX->setFormat("dd MM yyyy");
    for (int i=0;i<int(x->size());i++){
        series->append((*x)[i].getFecha(),(*x)[i].getConsumoAcumulado());
        if((*x)[i].getConsumoAcumulado() !=0 && flag_zero) flag_zero = false;
    }
    if(flag_zero) axisY->setRange(0,1);
}

Grafico* Grafico::viewGraph() {
    flag_serie = true;
    chart->legend()->hide();
    chart->addSeries(series);
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle(tipoo);
    QPen pen(QRgb(0x000000));
    pen.setWidth(5);
    series->setPen(pen);

    chart->setAnimationOptions(QtCharts::QChart::NoAnimation);
    this->setRenderHint(QPainter::Antialiasing);
    chart->legend()->hide();
    axisX->setTitleText("Fecha");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    if(tipoo == "Consumo Casa"){
        flag_unidad_consumo = true;
        axisY->setTitleText(unit);
    }
    else{
        axisY->setTitleText("Agua [L]");
        flag_unidad_consumo = false;
    }
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return this;
}

void Grafico:: operator = (Grafico & G){
    valores = G.valores;
    series = G.series;
    chart = G.chart;
}

Grafico::~Grafico(){
    delete axisX;
    delete axisY;
    delete series;
    delete chart;
}

