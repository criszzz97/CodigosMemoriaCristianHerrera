#ifndef CONFIGURACIONESCONDOMINIO_H
#define CONFIGURACIONESCONDOMINIO_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSql>
#include <QSqlQuery>
#include <QDate>

class ConfiguracionesCondominio
{
public:
    ConfiguracionesCondominio();
    void ConfigurarConexion();
    void CleanBase();
    int getLimiteConsumo();
    int getCapacidadConfigurada();
    int getDias();
    QDate getFechaRegla();
    void ActualizarCondominio(QString Limite, QString Capacidad, QString d, QDate initregla);
    void LlamarDatos();
    void setView(QObject * vista);
private:
    QSqlDatabase db;
    int LimiteConsumo;
    int CapacidadConfigurada;
    int dias;
    QString connName;
    QObject * vista;
    QDate FechaRestriccion;

};

#endif // CONFIGURACIONESCONDOMINIO_H
