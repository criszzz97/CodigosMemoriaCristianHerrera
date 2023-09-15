#include "proyectomemoria.h"
#include "ui_proyectomemoria.h"
/////////////////////////////////////////////////
#include "nodo.h"
#include "valvula.h"
#include "sensorflujo.h"
#include "datosconsumo.h"
#include "casa.h"
#include "casainiciovsta.h"
#include "condominio.h"
#include "condominioview.h"
#include "timerreglas.h"
#include "detallescondominios.h"
#include <QThread>
/////////////////////////////////////////////////
ProyectoMemoria::ProyectoMemoria(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProyectoMemoria)
{
    ui->setupUi(this);
    string con = "proyecto-elo308";
    VistaInicio = new CasaInicioVsta();
    co = new Condominio(QString::fromStdString(con));
    co->llenarCasas();
    cv = new CondominioView(co);
    act = ui->menubar->addMenu("Condominios")->addAction("proyecto-elo308");
    QObject::connect(act,SIGNAL(triggered()),
                     this,SLOT(actionReaction()));
    detalles = new DetallesCondominios();
    thread1 = new QThread(this);
    timer = new TimerReglas(co);
    cv->setDetalles(detalles);
    detalles->setTimer(timer);

    connect(cv,SIGNAL(nueva_fecha(QDate)),detalles,SLOT(n_fecha(QDate)));
    connect(cv,SIGNAL(nueva_fecha(QDate)),co->getInicio(),SLOT(nu_fecha(QDate)));
    connect(detalles,SIGNAL(borrar(QString)),co->getInicio(),SLOT(deleteData(QString)));
    connect(detalles,SIGNAL(hoy(QString,QString)),co->getInicio(),SLOT(readData(QString,QString)));
    connect(co->getCasaVista(),SIGNAL(Contador(bool)),timer,SLOT(AccionContador(bool)));
    connect(cv,SIGNAL(ContadorConf(bool)),timer,SLOT(AccionContador(bool)));
    connect(cv,SIGNAL(inicio_t()),timer,SLOT(ini_t()));
    connect(cv,SIGNAL(parar_t()),timer,SLOT(fin_t()));
    connect(cv,SIGNAL(eliminar_casa(QString)),detalles,SLOT(DeleteCasa(QString)));
    thread1->start();
    timer->moveToThread(thread1);


}

ProyectoMemoria::~ProyectoMemoria()
{
    delete act;
    delete ui;
    delete co;
    delete cv;
    delete detalles;
    delete timer;
    thread1->quit();
    thread1->wait();
    thread1->deleteLater();
}


void ProyectoMemoria::actionReaction() {
    this->setCentralWidget(cv);
}

