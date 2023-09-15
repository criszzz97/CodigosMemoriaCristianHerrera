#ifndef PROYECTOMEMORIA_H
#define PROYECTOMEMORIA_H

#include <QMainWindow>
#include "condominioview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ProyectoMemoria; }
QT_END_NAMESPACE

class ProyectoMemoria : public QMainWindow
{
    Q_OBJECT

public:
    ProyectoMemoria(QWidget *parent = nullptr);
    ~ProyectoMemoria();


private slots:
    void actionReaction();

private:
    Ui::ProyectoMemoria *ui;
    CondominioView * cv;
    Condominio* co;
    DetallesCondominios * detalles;
    QThread * thread1;
    TimerReglas * timer;
    CasaInicioVsta * VistaInicio;
    QAction *act;
};
#endif // PROYECTOMEMORIA_H
