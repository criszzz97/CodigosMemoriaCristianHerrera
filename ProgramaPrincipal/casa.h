#ifndef CASA_H
#define CASA_H
#include "nodo.h"
#include <QDateTime>



class Casa
{
public:
    Casa(){nodo = nullptr;};
    Casa(int casaid,string con,QDateTime Union,QString nombre);
    ~Casa();
    void moverLimitador(float porcentaje/*grados*/,QString tipo);
    Nodo * getNodo();//al obtener el nodo se puede ver el grafico despues.
    void setNodo(Nodo *node);
    int getId();
    QMap<QString, Sensor*> * getSensors();
    QMap<QString, Actuador*> * getActuators();
    Grafico * GraficoConsumoAcumulado(QDateTime init,QDateTime fin,QString tipo, QString periodo);
    Grafico * GraficoConsumo(QDateTime init,QDateTime fin,QString tipo, QString periodo);
    int * UltimaPosicionLimitador(QString tipo);
    string getCondominio();
    QString getNombre();
    Grafico * getConusmoUltimosDatos(QString tipo,int acumulado);
    void setConfig(ConfiguracionesCondominio * config);
    void setFechaUnion(QDateTime Fecha_u) {Fecha_union = Fecha_u;}
private:
        Nodo *nodo = NULL;//Este se añade luego de consultar a la tabla de nodos la cual tiene la misma
        QDateTime Fecha_union;
        QString nombre;
        string condominio;
        int casa_id; //una casa id va a tener un nodo id especifico el cual va a obtener de la vbase de datos
};
#endif // CASA_H

