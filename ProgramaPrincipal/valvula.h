#ifndef VALVULA_H
#define VALVULA_H
#include "actuador.h"
#include <QUrl>
#include <QNetworkAccessManager>
#include <QHttpPart>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QJsonArray>
#include <QSqlDatabase>
#include <QSqlQuery>
using namespace std;
class Valvula:public Actuador
{
public:
    Valvula(){};
    virtual ~Valvula(){CleanBase();};
    Valvula(string deviceID, string condominio);
    double ActivarLimitador(float porcentaje);
    void ActualizarPosicionLimitador(int cantidad);
    int * UltimaPosicion();
    void ConfigurarConexion();
    void CleanBase();
    void JsonClear();

    QString getTipo();
private:
    QJsonArray jsonArrayData;
    QJsonObject jsonDownlink;
    QJsonObject jsonData;
    QJsonObject jsonValvula;
    QString deviceID;
    QString condominio;
    QSqlDatabase db;
    int apertura;
    QString tipo;
    QString connName;

};


#endif // VALVULA_H
