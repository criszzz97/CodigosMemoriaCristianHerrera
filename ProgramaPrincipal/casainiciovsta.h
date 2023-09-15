#ifndef CASAINICIOVSTA_H
#define CASAINICIOVSTA_H

#include <QWidget>
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QDate>

class TimerReglas;
namespace Ui {
class CasaInicioVsta;
}

class CasaInicioVsta : public QWidget
{
    Q_OBJECT

public:
    explicit CasaInicioVsta(QWidget *parent = nullptr);
    ~CasaInicioVsta();
    void SetNombre(QString nom);
    void AgregarFecha(QString fechin, QString fechfin);
    void ConfigurarConexion();
    void CleanBase();
    void IniciarCasa();

private:
    Ui::CasaInicioVsta *ui;
    QSqlDatabase db;
    QString connName;
    QString nombre;
    QString devid;
    QString fecha_inic;
    QString fecha_fin;
    QString fecha_conexion_in;
    QString fecha_conexion_hoy;
    bool flag_iniciado;
private slots:
    void readData(QString inicio, QString fecha);
    void deleteData(QString inicio);
    void nu_fecha(QDate);
};

#endif // CASAINICIOVSTA_H
