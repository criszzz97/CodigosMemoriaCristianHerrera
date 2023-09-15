#include "configuracionescondominioview.h"
#include "ui_configuracionescondominioview.h"

ConfiguracionesCondominioView::ConfiguracionesCondominioView(Condominio *con,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfiguracionesCondominioView)
{
    ui->setupUi(this);
    setWindowTitle("Configuraciones");
    flags = 0;
    flags |= Qt::WindowMaximizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    condominio = con;
    configuraciones = condominio->getConfiguraciones();
    configuraciones->setView(this);
    ui->ConsumoLimite->setText(QString::number(configuraciones->getLimiteConsumo()));
    ui->CapacidadConsumo->setText(QString::number(configuraciones->getCapacidadConfigurada()));
    ui->DiasAccion->setText(QString::number(configuraciones->getDias()));
    configcasas = new ConfiguracionCasas(this);
    ui->FechasEdicion->setDate(configuraciones->getFechaRegla());
    ui->FechasEdicion->date();
    connect(configcasas,SIGNAL(elim(QString)),this,SLOT(em_elim(QString)));
    this->setModal(1);
}

ConfiguracionesCondominioView::~ConfiguracionesCondominioView()
{
    delete ui;
    delete configcasas;
}

void ConfiguracionesCondominioView::on_AplicarReglas_clicked()
{
    configuraciones->ActualizarCondominio(ui->ConsumoLimite->text(),ui->CapacidadConsumo->text(),ui->DiasAccion->text(),ui->FechasEdicion->date());
    condominio->setConfiguraciones();
    QString g = (ui->FechasEdicion->date()).toString("yyyy-MM-dd");
    qDebug()<<g;
}


void ConfiguracionesCondominioView::em_elim(QString c){
    emit eliminacion(c);
}

void ConfiguracionesCondominioView::on_ConfigurarCasas_clicked()
{
    configcasas->LlenarTabla();
    configcasas->exec();
}

Condominio * ConfiguracionesCondominioView::getCondominio(){
    return condominio;
}

void ConfiguracionesCondominioView::on_FechasEdicion_userDateChanged(const QDate &date)
{
    emit cambio_fecha(date);
}

