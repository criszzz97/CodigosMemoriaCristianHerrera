#ifndef CONFIGURACIONESCONDOMINIOVIEW_H
#define CONFIGURACIONESCONDOMINIOVIEW_H

#include <QDialog>
#include "configuracionescondominio.h"
#include "configuracioncasas.h"
#include "condominio.h"

namespace Ui {
class ConfiguracionesCondominioView;
}

class ConfiguracionesCondominioView : public QDialog
{
    Q_OBJECT

public:
    explicit ConfiguracionesCondominioView(Condominio *con,QWidget *parent = nullptr);
    ~ConfiguracionesCondominioView();
    Condominio * getCondominio();
private slots:
    void on_AplicarReglas_clicked();

    void on_ConfigurarCasas_clicked();
    void em_elim(QString);

    void on_FechasEdicion_userDateChanged(const QDate &date);

private:
    ConfiguracionesCondominio * configuraciones;
    Qt::WindowFlags flags;
    Ui::ConfiguracionesCondominioView *ui;
    ConfiguracionCasas * configcasas;
    Condominio * condominio;
signals:
    void eliminacion(QString);
    void cambio_fecha(QDate);
};

#endif // CONFIGURACIONESCONDOMINIOVIEW_H
