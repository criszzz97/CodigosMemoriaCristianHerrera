#ifndef CONDOMINIO_H
#define CONDOMINIO_H
#include "casa.h"
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include "nodo.h"
#include "valvula.h"
#include "sensorflujo.h"
#include "datosconsumo.h"
#include "casa.h"
#include "casaview.h"
#include "configuracionescondominio.h"
#include <QList>


class Condominio
{
public:
    Condominio(QString con);
    ~Condominio();
    void sendCMD();//Envia comandos a la nube.
    void selectCasa();//Selecciona una casa especifica entre todas la que tiene el condominio.
    void agregarCasa(Casa* hogar);
    void elminiarCasa(QString idcasa);
    void llenarCasas();
    QMap<QString, Casa*> *getCasas();
    void openDialogCasaView(QString id);
    void setVistaCasa(CasaView * cv);
    void agregarCasaLista(Casa* hogar);
    void agregarCasaBase(Casa* hogar);
    void CleanBase();
    void ConfigurarConexion();
    QString getCondominioId();
    ConfiguracionesCondominio * getConfiguraciones();
    QMap<int, QList<QString>> * mapa();
    QList<QList<QString>> DispositivosSinCasa();
    QList<QList<QString>> CasasEnCondominio();
    void setConfiguraciones();
    CasaView * getCasaVista();
    CasaInicioVsta * getInicio();
private:
    QMap<QString, Casa*> *Casas;
    QString condominio_id;
    QSqlDatabase db;

    QString devid;
    QString fech;
    QString casaid;
    QString nombre;
    QDateTime fecha;
    Casa *casa;
    CasaView *casavista;
    QString connName;
    ConfiguracionesCondominio * config;
    QMap<int, QList<QString>> * mapa_valores;
};

#endif // CONDOMINIO_H

