#ifndef ACTUADOR_H
#define ACTUADOR_H
#include <QString>

class Actuador
{
public:
    //Actuador();
    virtual void ActualizarPosicionLimitador(int cantidad) = 0;//Escribir en la base de datos el estado del limitador
    virtual ~Actuador() {};
    virtual  double ActivarLimitador(float porcentaje) = 0; //Actia el limitador por un determinado tiempo o se setea este en un determinado porcentaje
    virtual QString getTipo() = 0;
    virtual int * UltimaPosicion()=0;
};

#endif // ACTUADOR_H
