#ifndef CASABOTON_H
#define CASABOTON_H
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include "condominio.h"

class CondominioView;
class CasaBoton : public QPushButton
{
    Q_OBJECT
public:
    CasaBoton(QString id="",QWidget *parent = nullptr,Condominio *con = nullptr);
    virtual ~CasaBoton();
private slots:
    void presionado();
private:
    QString id;
    CondominioView *padre;
    Condominio *condominio;
};
#endif // CASABOTON_H
