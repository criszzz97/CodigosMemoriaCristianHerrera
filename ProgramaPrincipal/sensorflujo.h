#ifndef SENSORFLUJO_H
#define SENSORFLUJO_H
//#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include "datosconsumo.h"
#include "sensor.h"

using namespace std;
class SensorFlujo:public Sensor
{
   // Q_OBJECT
public:
    SensorFlujo(){};
    SensorFlujo(string deviceID, string condominio);
    virtual ~SensorFlujo();
    vector<DatosConsumo>* getData(QDateTime init,QDateTime fin,int formato, QString periodo); //retornaria datos de un tipo especifico, en este caso como ejemplo retornaria int.
    void verGrafico();
    void CleanBase(QString conexion);//Limpia el vector de datos
    void ConfigurarConexion(QString conexion);
    void readData(QDateTime init,QDateTime fin,int formato, QString periodo);
    qreal DataCheck(QDateTime fecha, QString periodo);
    QString getTipo();
    vector<DatosConsumo> * getUltimosDatos(int acumulado);
private:
    vector<DatosConsumo> *datos;
    QSqlDatabase db;
    std::vector<int> valores;
    QString deviceID;
    QString condominio;
    QString tipo;
    QString connName;
    QString connName2;
    qreal yValCheck;
};



#endif // SENSORFLUJO_H
