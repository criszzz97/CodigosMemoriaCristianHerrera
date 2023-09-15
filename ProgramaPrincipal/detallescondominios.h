#ifndef DETALLESCONDOMINIOS_H
#define DETALLESCONDOMINIOS_H

#include <QWidget>
#include "timerreglas.h"

namespace Ui {
class DetallesCondominios;
}

class DetallesCondominios : public QWidget
{
    Q_OBJECT

public:
    explicit DetallesCondominios(QWidget *parent = nullptr);
    ~DetallesCondominios();
    void AgregarDetalle(QString casa, QString fechin, QString fechafin);
    void setTimer(TimerReglas * t);
    void ConfigurarConexion();
    void CleanBase();
private:
    Ui::DetallesCondominios *ui;
    TimerReglas * tm;
    QSqlDatabase db;
    QString connName;
    QString fecha_inic;
    QString fecha_fin;
    QString casaid;  
private slots:
    void readData();
    void deleteData();
    void DeleteCasa(QString casa_id);
    void n_fecha(QDate fech);
signals:
    void hoy(QString,QString);
    void borrar(QString);
};

#endif // DETALLESCONDOMINIOS_H
