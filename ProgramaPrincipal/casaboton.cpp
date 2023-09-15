#include "casaboton.h"

CasaBoton::CasaBoton(QString id,QWidget *parent, Condominio * con):QPushButton{parent}{
    this->id = id.section('a', 2, 2);
    QPushButton::setText(id);
    connect(this,SIGNAL(clicked()),this,SLOT(presionado()));
    condominio = con;
}

void CasaBoton::presionado() {
    qDebug()<<"presion";
    condominio->openDialogCasaView(id);
}

CasaBoton::~CasaBoton(){
    //condominio = nullptr;
}
