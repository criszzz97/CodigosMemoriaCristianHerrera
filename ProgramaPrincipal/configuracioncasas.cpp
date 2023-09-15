#include "configuracioncasas.h"
#include "configuracionescondominioview.h"
#include "ui_configuracioncasas.h"

ConfiguracionCasas::ConfiguracionCasas(QObject * confview,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfiguracionCasas)
{
    ui->setupUi(this);
    confv = confview;
    flags = 0;
    flags |= Qt::WindowMaximizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    setWindowTitle("Casas");
    this->setModal(1);
}

ConfiguracionCasas::~ConfiguracionCasas()
{
    delete ui;
}

void ConfiguracionCasas::LlenarTabla() {
    ConfiguracionesCondominioView* m = (ConfiguracionesCondominioView*)confv;
    Condominio * condominio = m->getCondominio();
    mapa_valores = condominio->mapa();
    for(int i =  ui->Tabla->rowCount() - 1; i >= 0; i--){
        QTableWidgetItem* m = ui->Tabla->takeItem(i,0);
        QTableWidgetItem* o = ui->Tabla->takeItem(i,1);
        ui->Tabla->removeRow(i);
        delete m;
        delete o;

    }
    for (auto it = mapa_valores->begin(); it != mapa_valores->end(); ++it)
    {
        const int newIndex = ui->Tabla->rowCount();
        ui->Tabla->setRowCount(newIndex + 1);
        ui->Tabla->setItem(newIndex,0,new QTableWidgetItem(it.value()[0]));
        ui->Tabla->setItem(newIndex,1,new QTableWidgetItem(it.value()[1]));
    }

    dispositivos_sin_casa = condominio->DispositivosSinCasa();
    casas_en_condominio = condominio->CasasEnCondominio();
    ActualizarComboBox(&dispositivos_sin_casa,ui->ComboDispositivos);
    ActualizarComboBox(&casas_en_condominio,ui->ComboCasas);
}

void ConfiguracionCasas::ActualizarComboBox(QList<QList<QString>> * dsc,QComboBox * combobox){
    combobox->clear();
    for (int i = 0; i< dsc->count();i++) {
        combobox->addItem(((*dsc)[i])[0]);
    }
}

void ConfiguracionCasas::on_boton_agregar_clicked()
{
    ConfiguracionesCondominioView* m = (ConfiguracionesCondominioView*)confv;
    Condominio * condominio = m->getCondominio();
    QString nodo = (ui->ComboDispositivos->currentText());
    QString nombre = ui->casa_nueva->text();
    QString fecha;
    QString casa_id = "";
    for (int i = 0; i< dispositivos_sin_casa.count();i++) {
        if ((dispositivos_sin_casa[i])[0] == nodo){
            fecha = (dispositivos_sin_casa[i])[1];
            casa_id = (dispositivos_sin_casa[i])[2];
            QList<QString> aux;
            aux.clear();
            aux.append(nombre);
            aux.append(nodo);
            aux.append(casa_id);
            aux.append(fecha);
            casas_en_condominio.append(aux);
            dispositivos_sin_casa.removeAt(i);
            break;
        }
    }
    const int newIndex = ui->Tabla->rowCount();
    ui->Tabla->setRowCount(newIndex + 1);
    ui->Tabla->setItem(newIndex,0,new QTableWidgetItem(nombre));
    ui->Tabla->setItem(newIndex,1,new QTableWidgetItem(nodo));
    Casa * casa = new Casa(casa_id.toInt(),condominio->getCondominioId().toStdString(),QDateTime::fromString(fecha,"yyyy-MM-dd hh:mm:ss"),nombre);
    condominio->agregarCasaBase(casa);//condominio se encarga de borrar a cada casa
    ActualizarComboBox(&dispositivos_sin_casa,ui->ComboDispositivos);
    ActualizarComboBox(&casas_en_condominio,ui->ComboCasas);
}

void ConfiguracionCasas::on_Eliminar_clicked()
{
    ConfiguracionesCondominioView* m = (ConfiguracionesCondominioView*)confv;
    Condominio * condominio = m->getCondominio();
    QString id_casa = "";
    QString hogar = (ui->ComboCasas->currentText());
    for (int i = 0; i < casas_en_condominio.count(); i++)
    {
        if ((casas_en_condominio[i])[0] == hogar){
            mapa_valores->remove((casas_en_condominio[i])[2].toInt());
            QList<QString> aux;
            id_casa = (casas_en_condominio[i])[2];
            emit elim(id_casa);
            aux.clear();
            aux.append((casas_en_condominio[i])[1]);
            aux.append((casas_en_condominio[i])[3]);
            aux.append((casas_en_condominio[i])[2]);
            dispositivos_sin_casa.append(aux);
            casas_en_condominio.removeAt(i);
            break;
        }
    }

    for(int i =  ui->Tabla->rowCount() - 1; i >= 0; i--){
        QTableWidgetItem* m = ui->Tabla->takeItem(i,0);
        QTableWidgetItem* o = ui->Tabla->takeItem(i,1);
        ui->Tabla->removeRow(i);
        delete m;
        delete o;

    }
    for (int i = 0; i < casas_en_condominio.count(); i++)
        {
            const int newIndex = ui->Tabla->rowCount();
            ui->Tabla->setRowCount(newIndex + 1);
            ui->Tabla->setItem(newIndex,0,new QTableWidgetItem((casas_en_condominio[i])[0]));
            ui->Tabla->setItem(newIndex,1,new QTableWidgetItem((casas_en_condominio[i])[1]));
        }
    condominio->elminiarCasa(id_casa);
    ActualizarComboBox(&dispositivos_sin_casa,ui->ComboDispositivos);
    ActualizarComboBox(&casas_en_condominio,ui->ComboCasas);
}

