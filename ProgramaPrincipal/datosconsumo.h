#ifndef DATOSCONSUMO_H
#define DATOSCONSUMO_H
#include <QDateTime>

class DatosConsumo
{
public:
    DatosConsumo(double cons, int ano, int mes, int dia);
    DatosConsumo(double cons, int ano, int mes, int dia,int hora, int minuto);
    double getConsumoAcumulado();
    double getNumero();
    qint64 getFecha();
    //~DatosConsumo();
private:
    double ConsumoAcumulado;
    //QDateTime Fecha;
    //ouble numero;
    int Ano;
    int Mes;
    int Dia;
    int Hora;
    int Minuto;
    bool flag;
    //double ConsumoDiferencial;
};

#endif // DATOSCONSUMO_H
