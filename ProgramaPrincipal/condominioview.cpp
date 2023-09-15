#include "condominioview.h"

CondominioView::CondominioView(Condominio *con,QWidget *parent)
    : QWidget{parent}
{
    condominio = con;
    gridGroupBox = new QGroupBox(condominio->getCondominioId());
    boton_config = new QPushButton("Configuraciones");
    boton_iniciar = new QPushButton("Iniciar");//
    boton_parar = new QPushButton("Parar");//
    boton_detalles = new QPushButton("Detalles");//
    config = new ConfiguracionesCondominioView(condominio);
    gridLayout = new QGridLayout;
    layoutGrupoSeleccion = new QHBoxLayout;
    label_casa = new QLabel("Elegir Casa");
    boton_casa = new QPushButton("Ver Casa");
    ComboBoxCasas = new QComboBox(this);
    layoutGrupoSeleccion->addWidget(label_casa);
    layoutGrupoSeleccion->addWidget(ComboBoxCasas);
    layoutGrupoSeleccion->addWidget(boton_casa);
    gridGroupBox->setLayout(layoutGrupoSeleccion);
    gridLayout->addWidget(gridGroupBox,0,0,0,4);
    gridLayout->addWidget(boton_iniciar,1,0);
    gridLayout->addWidget(boton_parar,1,1);
    gridLayout->addWidget(boton_detalles,1,2);
    gridLayout->addWidget(boton_config,1,3);
    llenarCuadro(con);
    this->setLayout(gridLayout);
    connect(config,SIGNAL(eliminacion(QString)),this,SLOT(eliminar_c(QString)));
    connect(config,SIGNAL(cambio_fecha(QDate)),this,SLOT(c_fecha(QDate)));
    connect(boton_config,SIGNAL(clicked()),this,SLOT(SeleccionConfiguracion()));
    connect(boton_casa,SIGNAL(clicked()),this,SLOT(VerCasa()));
    connect(ComboBoxCasas,SIGNAL(currentTextChanged(QString)),this,SLOT(EleccionCasa(QString)));
    connect(config,SIGNAL(rejected()),this,SLOT(CierreConfiguracion()));
    connect(boton_iniciar,SIGNAL(clicked()),this,SLOT(inicio_timer()));
    connect(boton_parar,SIGNAL(clicked()),this,SLOT(parar_timer()));
}


Condominio* CondominioView::getCondominio(){
    return condominio;
}

void CondominioView::eliminar_c(QString c){
    emit eliminar_casa(c);
}


void CondominioView::inicio_timer(){
    emit inicio_t();
}


void CondominioView::parar_timer(){
    emit parar_t();
}

CondominioView::~CondominioView(){
    delete boton_iniciar;//
    delete boton_parar;//
    delete boton_detalles;//
    delete label_casa;
    delete ComboBoxCasas;
    delete boton_casa;
    delete config;
    delete boton_config;
    delete layoutGrupoSeleccion;
    delete gridGroupBox;
    delete gridLayout;
}

void CondominioView::llenarCuadro(Condominio *con) {
    hogares = con->getCasas();
    ComboBoxCasas->clear();
    bool flag_casa_inicial = false;
    for (auto it = hogares->begin(); it != hogares->end();) {
        if(!flag_casa_inicial){
            CasaSeleccionada = it.value()->getNombre();
            flag_casa_inicial = true;
        }
        ComboBoxCasas->addItem(it.value()->getNombre());
        ++it;
    }
}


void CondominioView::EleccionCasa(QString c) {
    qDebug()<<"presion";
    CasaSeleccionada = c;
}

void CondominioView::CierreConfiguracion(){
    emit ContadorConf(true);
}

void CondominioView::SeleccionConfiguracion() {
    emit ContadorConf(false);
    config->exec();
    llenarCuadro(condominio);
}

void CondominioView::VerCasa(){
    QString seleccion;
    for (auto it = hogares->begin(); it != hogares->end();) {
        if(it.value()->getNombre() == CasaSeleccionada){
            seleccion = QString::number(it.value()->getId());
        }
        ++it;
    }
    condominio->openDialogCasaView(seleccion);
}


ConfiguracionesCondominioView * CondominioView::getConfiguracionesView(){
    return config;
}


void CondominioView::setDetalles(DetallesCondominios * d){
    detalle = d;
    connect(boton_detalles,SIGNAL(clicked()),detalle,SLOT(show()));
}

void CondominioView::c_fecha(QDate fecha){
    emit nueva_fecha(fecha);
}
