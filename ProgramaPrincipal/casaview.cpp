#include "casaview.h"
#include "qmainwindow.h"
#include <QSizePolicy>

CasaView::CasaView(QWidget *parent) : QDialog(parent)
{
    flags = 0;
    flags |= Qt::WindowMaximizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    tipoConsumo = "";
    QPixmap pixmap("C://PruebaQT//calendar.png");
    QIcon ButtonIcon(pixmap);
    boton_desde = new QPushButton("Desde");
    boton_hasta = new QPushButton("Hasta");
    boton_desde->setIcon(ButtonIcon);
    boton_desde->setIconSize(pixmap.rect().size());
    boton_hasta->setIcon(ButtonIcon);
    boton_hasta->setIconSize(pixmap.rect().size());
    boton_acumulado = new QPushButton("ConsumoAcumulado");
    boton_consumo = new QPushButton("Consumo");
    pantalla = new QGridLayout(this);
    acum = 0;

    stackedWidget = new QStackedWidget(this);
    widgetSensor = new QWidget;
    widgetActuador = new QWidget;
    widgetInicio = new CasaInicioVsta();
    widgetInicio->resize(stackedWidget->width(),stackedWidget->height());
    stackedWidget->addWidget(widgetInicio);
    stackedWidget->setCurrentWidget(widgetInicio);
    botonActuador = new QPushButton(widgetActuador);
    botonActuador->setText("Actualizar Apertura");
    LayoutBotonesSensor = new QHBoxLayout();
    LayoutFecha = new QHBoxLayout();
    gridSensor = new QGridLayout(widgetSensor);
    gridActuador = new QGridLayout(widgetActuador);
    stackedWidget->addWidget(widgetSensor);
    stackedWidget->addWidget(widgetActuador);
    pantalla->addWidget(stackedWidget);

    fechainit = QDate(2022,10,31);
    fechafin = QDate(2022,10,31);

    SliderActuacion = new QSlider(Qt::Horizontal,widgetActuador);
    SliderActuacion->setTickInterval(1);
    SliderActuacion->setMaximum(100);
    SliderActuacion->setMinimum(0);
    SliderActuacion->setValue(0);
    LCDActuador = new QLCDNumber(widgetActuador);
    connect(SliderActuacion,SIGNAL(valueChanged(int)),LCDActuador,SLOT(display(int)));

    QFont f( "Arial", 10);
    label_Apertura = new QLabel("% de apertura");//
    label_Apertura->setFont(f);
    label_Muestreo = new QLabel("Periodo de Muestreo");//
    LayoutPeriodo = new QHBoxLayout();//
    ComboBoxPeriodo = new QComboBox(widgetSensor);//
    ComboBoxPeriodo->addItem("Diario");
    ComboBoxPeriodo->addItem("Mensual");
    ComboBoxPeriodo->addItem("Anual");
    ComboBoxPeriodo->addItem("Minutal");
    LayoutPeriodo->addWidget(label_Muestreo);
    LayoutPeriodo->addWidget(ComboBoxPeriodo);
    label_Desde = new QLabel("Desde");
    label_Hasta = new QLabel("Hasta");
    LayoutFecha->addWidget(boton_desde, 2, Qt::AlignCenter);
    LayoutFecha->addWidget(boton_hasta, 2, Qt::AlignCenter);
    LayoutBotonesSensor->addWidget(boton_acumulado);
    LayoutBotonesSensor->addWidget(boton_consumo);
    gridSensor->addLayout(LayoutPeriodo,1,0);
    gridSensor->addLayout(LayoutFecha,2,0);
    gridSensor->addLayout(LayoutBotonesSensor,3,0);
    gridActuador->addWidget(label_Apertura,0,0);
    gridActuador->addWidget(SliderActuacion,0,1);
    gridActuador->addWidget(LCDActuador,1,0,1,2);
    gridActuador->addWidget(botonActuador,2,0,1,2);
    this->setLayout(pantalla);
    dialogoCalendarioInit = nullptr;
    dialogoCalendarioFin = nullptr;
    layoutCalendarioFin = nullptr;
    layoutCalendarioInit = nullptr;
    init = nullptr;
    fin = nullptr;
    casa = nullptr;
    PeriodoMuestreo = "Diario";
    QDialog::resize(600, 600);


    toolbar = new QToolBar;
    tool_inicio=new QToolButton(this);//
    tool_inicio->setText("Inicio");
    tool_inicio->setStyleSheet("QToolButton::menu-indicator{image:none;}");
    tool_sensor=new QToolButton(this);
    tool_sensor->setText("Consumo");
    tool_sensor->setPopupMode(QToolButton::InstantPopup);
    tool_sensor->setStyleSheet("QToolButton::menu-indicator{image:none;}");
    tool_actuador=new QToolButton(this);
    tool_actuador->setText("Limitadores");
    tool_actuador->setPopupMode(QToolButton::InstantPopup);
    tool_actuador->setStyleSheet("QToolButton::menu-indicator{image:none;}");

    sensMenu =new QMenu(tool_sensor);
    actMenu =new QMenu(tool_actuador);

    toolbar->addWidget(tool_inicio);
    toolbar->addWidget(tool_sensor);
    toolbar->addWidget(tool_actuador);
    layout()->setMenuBar(toolbar);
    this->setModal(1);
    tmer = new QTimer();
    connect(tool_inicio,SIGNAL(clicked()),this,SLOT(MostrarInicio()));
    connect(tmer,SIGNAL(timeout()),this,SLOT(tmout()));
    connect(ComboBoxPeriodo,SIGNAL(currentTextChanged(QString)),this,SLOT(EleccionMuestreo(QString)));
    connect(botonActuador,SIGNAL(clicked()),this,SLOT(ActualizarLimitador()));
    connect(boton_acumulado,SIGNAL(clicked()),this,SLOT(ConsumoAcumuladoRecibido()));
    connect(boton_consumo,SIGNAL(clicked()),this,SLOT(ConsumoRecibido()));
    connect(boton_desde,SIGNAL(clicked()),this,SLOT(AbrirCalendarioInit()));
    connect(boton_hasta,SIGNAL(clicked()),this,SLOT(AbrirCalendarioFin()));


}

CasaView::~CasaView(){
    delete tmer;//
    delete label_Muestreo;
    delete ComboBoxPeriodo;
    delete label_Apertura;
    delete LCDActuador;
    delete botonActuador;
    delete boton_desde;
    delete boton_hasta;
    delete actMenu;
    delete sensMenu;
    delete tool_sensor;
    delete tool_actuador;
    delete toolbar;
    delete SliderActuacion;
    delete init;
    delete fin;
    delete boton_acumulado;
    delete boton_consumo;
    delete label_Desde;
    delete label_Hasta;
    delete LayoutPeriodo;
    delete LayoutBotonesSensor;
    delete LayoutFecha;
    delete layoutCalendarioInit;
    delete layoutCalendarioFin;
    delete gridSensor;
    delete gridActuador;
    delete dialogoCalendarioInit;
    delete dialogoCalendarioFin;
    delete widgetSensor;
    delete widgetActuador;
    delete widgetInicio;
    delete stackedWidget;
    delete pantalla;
}

void CasaView::setCasa(Casa *c){
    casa = c;
    QMap<QString, Sensor*> *sensores =casa->getSensors();
    QMap<QString, Actuador*> *actuadores =casa->getActuators();
    QPushButton consumoacumulado;
    QPushButton consumodieferencial;

    for (auto it = sensores->begin(); it != sensores->end();) {
        QAction *q = new QAction(it.key(), this);
        connect(q,SIGNAL(triggered()),
                             this,SLOT(MostrarSensor()));
        accionesSensor.append(q);
        sensMenu->addAction(q);
        ++it;
    }

    for (auto it = actuadores->begin(); it != actuadores->end();) {
        QAction *q = new QAction(it.key(), this);
        connect(q,SIGNAL(triggered()),
                             this,SLOT(MostrarActuador()));
        accionesActuador.append(q);
        actMenu->addAction(q);
        ++it;
    }
    QLabel fechainit;
    QLabel fechafin;
    widgetInicio->SetNombre(casa->getNombre());
    widgetInicio->IniciarCasa();
    tool_sensor->setMenu(sensMenu);
    tool_actuador->setMenu(actMenu);
}

CasaInicioVsta * CasaView::getInicio(){
    return (CasaInicioVsta *)widgetInicio;
}


void CasaView::ConsumoAcumuladoRecibido(){
    QDateTime iniit(fechainit);
    QDateTime fiin(fechafin);
    gridSensor->removeWidget(casa->getNodo()->getGrafico());
    casa->getNodo()->getGrafico()->hide();
    if(PeriodoMuestreo == "Minutal"){
        acum = 1;
        gridSensor->addWidget(casa->getConusmoUltimosDatos(tipoConsumo,acum),0,0);
        casa->getNodo()->getGrafico()->show();
        tmer->start(5000);
    }
    else{
        gridSensor->addWidget(casa->GraficoConsumoAcumulado(iniit,fiin,tipoConsumo,PeriodoMuestreo),0,0);
        casa->getNodo()->getGrafico()->show();
        tmer->stop();
    }
}

void CasaView::tmout(){
    qDebug()<<1;
    gridSensor->removeWidget(casa->getNodo()->getGrafico());
    casa->getNodo()->getGrafico()->hide();
    gridSensor->addWidget(casa->getConusmoUltimosDatos(tipoConsumo,acum),0,0);
    casa->getNodo()->getGrafico()->show();
}




void CasaView::ConsumoRecibido(){
    QDateTime iniit(fechainit);
    QDateTime fiin(fechafin);
    gridSensor->removeWidget(casa->getNodo()->getGrafico());
    casa->getNodo()->getGrafico()->hide();
    if(PeriodoMuestreo == "Minutal"){
        acum = 0;
        gridSensor->addWidget(casa->getConusmoUltimosDatos(tipoConsumo,acum),0,0);
        casa->getNodo()->getGrafico()->show();
        tmer->start(5000);
    }
    else{
        gridSensor->addWidget(casa->GraficoConsumo(iniit,fiin,tipoConsumo,PeriodoMuestreo),0,0);
        casa->getNodo()->getGrafico()->show();
        tmer->stop();
    }
}


void CasaView::MostrarSensor(){
    emit Contador(true);
    QAction *q = qobject_cast<QAction*>(sender());
    tipoConsumo = q->text();
    tmer->stop();
    stackedWidget->setCurrentWidget(widgetSensor);
}

void CasaView::MostrarActuador(){
    emit Contador(false);
    QAction *q = qobject_cast<QAction*>(sender());
    tipoLimitante = q->text();
    tmer->stop();
    stackedWidget->setCurrentWidget(widgetActuador);
    float pos = (*casa->UltimaPosicionLimitador(tipoLimitante))/85.0;
    SliderActuacion->setValue((int)pos);
}

void CasaView::AbrirCalendarioInit(){

    layoutCalendarioInit = new QGridLayout();
    dialogoCalendarioInit = new QDialog(this);
    init = new QCalendarWidget(dialogoCalendarioInit);
    init->setMinimumDate(QDate(2022, 1, 1));
    init->setMaximumDate(QDate(2024, 1, 1));
    init->setGridVisible(true);
    layoutCalendarioInit->addWidget(init);
    dialogoCalendarioInit->setWindowFlag(Qt::WindowMaximizeButtonHint);
    dialogoCalendarioInit->setWindowFlag(Qt::WindowCloseButtonHint);
    dialogoCalendarioInit->setLayout(layoutCalendarioInit);
    connect(init,SIGNAL(activated(QDate)),this,SLOT(SeleccionarFechaInit(QDate)));
    dialogoCalendarioInit->resize(600, 600);
    dialogoCalendarioInit->setModal(1);
    dialogoCalendarioInit->show();
}

void CasaView::AbrirCalendarioFin(){
    layoutCalendarioFin = new QGridLayout();
    dialogoCalendarioFin = new QDialog(this);
    fin = new QCalendarWidget(dialogoCalendarioInit);
    fin->setMinimumDate(QDate(2022, 1, 1));
    fin->setMaximumDate(QDate(2024, 1, 1));
    fin->setGridVisible(true);
    layoutCalendarioFin->addWidget(fin);
    dialogoCalendarioFin->setWindowFlag(Qt::WindowMaximizeButtonHint);
    dialogoCalendarioFin->setWindowFlag(Qt::WindowCloseButtonHint);
    dialogoCalendarioFin->setLayout(layoutCalendarioFin);
    connect(fin,SIGNAL(activated(QDate)),this,SLOT(SeleccionarFechaFin(QDate)));
    dialogoCalendarioFin->resize(600, 600);
    dialogoCalendarioFin->setModal(1);
    dialogoCalendarioFin->show();
}

void CasaView::SeleccionarFechaInit(QDate date){
    fechainit = date;
    qDebug()<<"seleccionado";
    dialogoCalendarioInit->reject();
}

void CasaView::SeleccionarFechaFin(QDate date){
    fechafin = date;
    qDebug()<<"seleccionado2";
    dialogoCalendarioFin->reject();
}


void CasaView::ActualizarLimitador() {
    casa->moverLimitador(SliderActuacion->value(),tipoLimitante);
    qDebug()<<"act";
}

void CasaView::reject()
{
    emit Contador(true);
    gridSensor->removeWidget(casa->getNodo()->getGrafico());
    casa->getNodo()->getGrafico()->hide();
    stackedWidget->setCurrentWidget(widgetInicio);
    qDebug()<<"Cerrado";
    sensMenu->clear();
    actMenu->clear();
    tmer->stop();
    QDialog::reject();
}

void CasaView::EleccionMuestreo(QString muestreo){
    casa->getNodo()->UnidadConsumo(muestreo);
    PeriodoMuestreo = muestreo;
}

void CasaView::setInicio(CasaInicioVsta * wid){
    widgetInicio = wid;
    widgetInicio->resize(stackedWidget->width(),stackedWidget->height());
    stackedWidget->addWidget(widgetInicio);
    stackedWidget->setCurrentWidget(widgetInicio);
}


void CasaView::MostrarInicio(){
    stackedWidget->setCurrentWidget(widgetInicio);
}
