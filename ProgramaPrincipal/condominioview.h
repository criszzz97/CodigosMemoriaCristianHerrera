#ifndef CONDOMINIOVIEW_H
#define CONDOMINIOVIEW_H
#include "condominio.h"
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include "casaboton.h"
#include "configuracionescondominioview.h"

#include <QWidget>
#include "detallescondominios.h"

class CondominioView : public QWidget
{
    Q_OBJECT
public:
    CondominioView(Condominio *con = nullptr,QWidget *parent = nullptr);
    virtual ~CondominioView();
    Condominio* getCondominio();
    void llenarCuadro(Condominio *con);
    ConfiguracionesCondominioView * getConfiguracionesView();
    void setDetalles(DetallesCondominios * d);

    //signals:
signals:
    void ContadorConf(bool);
    void inicio_t();
    void parar_t();
    void eliminar_casa(QString);
    void nueva_fecha(QDate);

private:
    Condominio *condominio;
    QGridLayout *gridLayout;
    QHBoxLayout * layoutGrupoSeleccion;
    QComboBox * ComboBoxCasas;
    QLabel * label_casa;
    QPushButton * boton_casa;
    QGroupBox  *gridGroupBox;
    QString CasaSeleccionada;
    ConfiguracionesCondominioView * config;
    QPushButton * boton_config;
    QMap<QString, Casa*> * hogares;
    QPushButton * boton_iniciar;
    QPushButton * boton_parar;
    QPushButton * boton_detalles;
    DetallesCondominios * detalle;
private slots:
    void EleccionCasa(QString c);
    void SeleccionConfiguracion();
    void VerCasa();
    void CierreConfiguracion();
    void inicio_timer();
    void parar_timer();
    void eliminar_c(QString);
    void c_fecha(QDate);
};

#endif // CONDOMINIOVIEW_H
