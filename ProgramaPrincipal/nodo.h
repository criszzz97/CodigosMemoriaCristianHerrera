#ifndef NODO_H
#define NODO_H
#include "valvula.h"
#include "sensorflujo.h"
#include "grafico.h"
#include "sensor.h"
#include "configuracionescondominio.h"
#include <QThread>
#include <QTimer>

class Nodo
{
    //Q_OBJECT
public:
    Nodo(){};
    Nodo(string devID,int casaid,string con);
    ~Nodo();
    void mLimitador(float cantidad,QString tipo);
    vector<DatosConsumo> * getConsumo(QDateTime init,QDateTime fin,QString tipo,int formato,QString periodo);//Obtendria datos de la base de datos a traves de la clase sensor
    Grafico * GraficoConsumoAcumulado(QDateTime init,QDateTime fin,QString tipo, QString periodo);
    Grafico * GraficoConsumo(QDateTime init,QDateTime fin,QString tipo, QString periodo);
    void addSensor(Sensor * sens);
    void addActuator(Actuador* act);
    int * UltimaPosicionLimitador(QString tipo);
    QMap<QString, Sensor*> * getSensors();
    QMap<QString, Actuador*> * getActuators();
    void setConfiguracion(ConfiguracionesCondominio * configuracion);
    void BorrarConfiguracion();
    void ChequearRegla(QDateTime fecha_actual);
    void ConfigurarConexion();
    void CleanBase();
    void AgregarSobrePaso(QDateTime fecha);
    bool Penalizado(QDateTime date);
    void Chequeoa0();
    vector<DatosConsumo> * getUltimosDatos(QString tipo,int acumulado);
    Grafico * GraficoConsumoMinutal(QString tipo, int acumulado);
    void UnidadConsumo(QString);
    bool UltimoMesMarcado(QDateTime fecha_actual);
    Grafico * getGrafico(){return grafico;}
private:
    QString connName;
    QSqlDatabase db;
    Grafico *grafico;
    SensorFlujo *sensorFlujo;
    Valvula *valvula;
    string deviceID;
    int casa_id;
    string condominio;
    QMap<QString, Sensor*> * sensors;
    QMap<QString, Actuador*> * actuators;
    ConfiguracionesCondominio * config;
    qreal cuenta;
    bool flag_consumo_maximo;
    int limite_Agua;
    bool checkeo_penalizacion;
};


#endif // NODO_H
