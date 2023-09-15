#include "casa.h"

/*Esta clase corresponde al controlador de la casa en el modelo MVC*/

Casa::Casa(/*string devid,*/ int casaid,string con,QDateTime Union,QString nombre)
{
    this->nombre = nombre;
    casa_id = casaid;
    condominio = con;
    Fecha_union = Union;
    //nodo = new Nodo(devid,casaid,con);
}

void Casa::moverLimitador(float porcentaje,QString tipo/*grados*/){
    nodo->mLimitador(porcentaje,tipo);
}

void Casa::setNodo(Nodo *node) {
    nodo = node;
}

void Casa::setConfig(ConfiguracionesCondominio * config) {
    nodo->setConfiguracion(config);
}

Grafico * Casa::getConusmoUltimosDatos(QString tipo,int acumulado){
    return nodo->GraficoConsumoMinutal(tipo,acumulado);
}


Grafico * Casa::GraficoConsumoAcumulado(QDateTime init,QDateTime fin,QString tipo,QString periodo) {
    return nodo->GraficoConsumoAcumulado(init,fin,tipo,periodo);
}

Grafico * Casa::GraficoConsumo(QDateTime init,QDateTime fin,QString tipo, QString periodo) {
    return nodo->GraficoConsumo(init,fin,tipo,periodo);
}

QMap<QString, Sensor*> * Casa::getSensors(){
    return nodo->getSensors();
}

int * Casa::UltimaPosicionLimitador(QString tipo){
    return nodo->UltimaPosicionLimitador(tipo);
}

QMap<QString, Actuador*> * Casa::getActuators(){
    return nodo->getActuators();
}

Nodo * Casa::getNodo(){
    return nodo;
}

Casa::~Casa() {
    delete nodo;
}

int Casa::getId() {
    return casa_id;
}


string Casa::getCondominio(){
    return condominio;
}

QString Casa::getNombre() {
    return nombre;
}
