#include "datosconsumo.h"

DatosConsumo::DatosConsumo(double cons, int ano, int mes, int dia)
{
    flag = true;
    ConsumoAcumulado = cons;
    Ano = ano;
    Mes = mes;
    Dia = dia;
}

DatosConsumo::DatosConsumo(double cons, int ano, int mes, int dia,int hora, int minuto)
{
    flag = false;
    ConsumoAcumulado = cons;
    Ano = ano;
    Mes = mes;
    Dia = dia;
    Hora = hora;
    Minuto = minuto;
}

double DatosConsumo::getConsumoAcumulado() {
    return ConsumoAcumulado;
}

double DatosConsumo::getNumero() {
    return Dia;
}

qint64 DatosConsumo::getFecha() {
    QDateTime fecha;
    if(flag){
        fecha = QDateTime(QDate(Ano, Mes, Dia), QTime(0, 0, 0));
    }
    else{
        fecha = QDateTime(QDate(Ano, Mes, Dia), QTime(Hora,Minuto, 0));
    }
    return fecha.toMSecsSinceEpoch();
}
