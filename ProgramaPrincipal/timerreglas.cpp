#include "timerreglas.h"
#include "qthread.h"

/*Para probar este timer se partiria en una fecha especifica escogida (anterior a la fecha actual
 * y donde ademas se posean muchos datos posteriores a esta fecha) luego se configuraria una frecuencia de muestreo y un periodo de consumo
por ejemplo el periodo de consumo puede ser mensual y la frecuencia de muestreo y chequeo diaria*/
TimerReglas::TimerReglas(Condominio * con,QObject *parent)
    : QObject{parent}
{

    this->setObjectName("timer");
    condominio = con;
    m_wantToSleep = false;
    count = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCount()));
    interval = 6000;
    intervalo_inicial = interval;
    timer->setInterval(interval);//cada timeout de este timer va a simular un periodo de mmuestreo (puede ser dias)
    if(condominio->getConfiguraciones()->getFechaRegla()<QDate::currentDate()){
        init = QDateTime(condominio->getConfiguraciones()->getFechaRegla(), QTime(0, 0, 0));
    }
    else{
       init = QDateTime::currentDateTime();
    }
    fecha = init;
    flag_cuenta_actual = false;
    flag_pausa = false;
    tiempo_remanente = 5000;
    f_inicio = false;
}

void TimerReglas::updateCount() //el timer va aumentando la fecha constantemente.
{
    if(flag_pausa){
        flag_pausa = false;
        timer->setInterval(interval);
    }
    QMap<QString, Casa*> * casas = condominio->getCasas();
    if(fecha<QDateTime::currentDateTime()&&(!flag_cuenta_actual)){
        for (auto it = casas->begin(); it != casas->end(); ++it){
            it.value()->getNodo()->ChequearRegla(fecha);
        }
        fecha = fecha.addDays(1);
    }
    else{
        if(!flag_cuenta_actual){
            interval = 10000;
            timer->setInterval(interval);
            flag_cuenta_actual = true;
        }
        for (auto it = casas->begin(); it != casas->end(); ++it){
            it.value()->getNodo()->ChequearRegla(QDateTime::currentDateTime().addSecs(-60));
            fecha = QDateTime::currentDateTime();
        }
    }
    emit timer_timeout();
}


void TimerReglas::AccionContador(bool c) {
    if(f_inicio){
        if(c == false) {
            tiempo_remanente = timer->remainingTime();
            timer->stop();
            flag_pausa = true;
            flag_pausa_init = true;
        }
        else {
            if(flag_pausa_init){
               timer->start(tiempo_remanente);
               flag_pausa_init = false;
            }
        }
    }
}


void TimerReglas::ini_t(){
    init = QDateTime(condominio->getConfiguraciones()->getFechaRegla(), QTime(0, 0, 0));
    fecha = init;
    timer->start(intervalo_inicial);
    qDebug()<<fecha;
    f_inicio = true;
}


void TimerReglas::fin_t(){
    timer->stop();
    f_inicio = false;
    flag_cuenta_actual = false;
    init = QDateTime(condominio->getConfiguraciones()->getFechaRegla(), QTime(0, 0, 0));
    emit pausa();
    qDebug()<<"fintimer";
    QMap<QString, Casa*> * casas = condominio->getCasas();
    for (auto it = casas->begin(); it != casas->end(); ++it){
            it.value()->getNodo()->Chequeoa0();
    }
}

QDateTime TimerReglas::getFecha(){
    return fecha;
}

QDateTime TimerReglas::getFechaInit(){
    return init;
}


