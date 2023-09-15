#ifndef SENSOR_H
#define SENSOR_H
#include <QDateTime>
#include "datosconsumo.h"

using namespace std;
class Sensor
{
public:
    virtual void readData(QDateTime init,QDateTime fin,int formato, QString periodo) = 0;
    virtual ~Sensor() {};
    virtual vector<DatosConsumo>* getData(QDateTime init,QDateTime fin,int formato, QString periodo) = 0;
    virtual void CleanBase(QString conexion) = 0;
    virtual void ConfigurarConexion(QString conexion) = 0;
    virtual QString getTipo() = 0;
    virtual vector<DatosConsumo> * getUltimosDatos(int acumulado) = 0;
    virtual qreal DataCheck(QDateTime fecha, QString periodo) = 0;
};

#endif // SENSOR_H
