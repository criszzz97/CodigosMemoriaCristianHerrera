#ifndef CASAVIEW_H
#define CASAVIEW_H
#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "casa.h"
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolButton>
#include <QCalendarWidget>
#include <QSignalMapper>
#include <QVector>
#include <QStackedWidget>
#include <QSlider>
#include <QLCDNumber>
#include <QComboBox>

#include "casainiciovsta.h"
class CasaView: public QDialog
{
    Q_OBJECT
public:
    virtual ~CasaView();
    explicit CasaView(QWidget *parent = nullptr);
    void setCasa(Casa *c);
    virtual void reject();
    void setInicio(CasaInicioVsta * wid);
    CasaInicioVsta * getInicio();
private:
    Casa * casa;
    QLabel *label;
    QGridLayout *pantalla;
    QGridLayout *gridSensor;
    QGridLayout *gridActuador;
    QGridLayout *grid;
    QHBoxLayout *hboxS;
    QToolBar *toolbar;
    QToolButton * tool_inicio;
    QToolButton * tool_sensor;
    QToolButton * tool_actuador;
    QMenu *sensMenu;
    QMenu *actMenu;
    QString tipoConsumo;
    QString tipoLimitante;
    QVector<QAction*> accionesSensor;
    QVector<QAction*> accionesActuador;
    QStackedWidget *stackedWidget;
    QWidget* widgetSensor;
    QWidget* widgetActuador;
    CasaInicioVsta *widgetInicio;
    QCalendarWidget *init;
    QCalendarWidget *fin;
    QPushButton * boton_desde;
    QPushButton * boton_hasta;
    Qt::WindowFlags flags;
    QDate fechainit;
    QDate fechafin;
    QGridLayout * layoutCalendarioInit;
    QDialog *dialogoCalendarioInit;
    QGridLayout * layoutCalendarioFin;
    QDialog *dialogoCalendarioFin;
    QSlider * SliderActuacion;
    QLCDNumber * LCDActuador;
    QPushButton * botonActuador;
    QHBoxLayout *LayoutBotonesSensor;
    QHBoxLayout *LayoutFecha;
    QPushButton * boton_acumulado;
    QPushButton * boton_consumo;
    QLabel *label_Desde;
    QLabel *label_Hasta;
    QLabel * label_Muestreo;//
    QComboBox *ComboBoxPeriodo;//
    QHBoxLayout * LayoutPeriodo;//
    QLabel *label_Apertura;//
    QString PeriodoMuestreo;
    QTimer * tmer;//
    QThread *thread;//
    int acum = 0;
signals:
    void Contador(bool);
private slots:
    void ConsumoAcumuladoRecibido();
    void ConsumoRecibido();
    void MostrarSensor();
    void MostrarActuador();
    void AbrirCalendarioInit();
    void AbrirCalendarioFin();
    void SeleccionarFechaInit(QDate date);
    void SeleccionarFechaFin(QDate date);
    void ActualizarLimitador();
    void EleccionMuestreo(QString);
    void tmout();
    void MostrarInicio();
};


#endif // CASAVIEW_H
