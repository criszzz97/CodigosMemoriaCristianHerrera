#ifndef TIMERREGLAS_H
#define TIMERREGLAS_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include "condominio.h"

class TimerReglas : public QObject
{
    Q_OBJECT
public:
    explicit TimerReglas(Condominio * con,QObject *parent = nullptr);
    QDateTime getFechaInit();

public slots:
    void updateCount();
    void AccionContador(bool);
    void ini_t();
    void fin_t();
    QDateTime getFecha();

signals:
    void timer_timeout();
    void pausa();

private:
    QTimer *timer;
    int count;
    bool m_wantToSleep;
    Condominio * condominio;
    QDateTime fecha;
    bool flag_cuenta_actual;
    bool flag_pausa;
    int interval;
    int tiempo_remanente;
    bool flag_pausa_init;
    int intervalo_inicial;
    QDateTime init;
    bool f_inicio;
    //bool sinc;

};

#endif // TIMERREGLAS_H
