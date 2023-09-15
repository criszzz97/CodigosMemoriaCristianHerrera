#ifndef CONFIGURACIONCASAS_H
#define CONFIGURACIONCASAS_H

#include <QDialog>
#include "condominio.h"

namespace Ui {
class ConfiguracionCasas;
}

class ConfiguracionCasas : public QDialog
{
    Q_OBJECT

public:
    explicit ConfiguracionCasas(QObject * confview,QWidget *parent = nullptr);
    ~ConfiguracionCasas();
    void ActualizarComboBox(QList<QList<QString>> * dsc,QComboBox * combobox);
    void LlenarTabla();
signals:
    void elim(QString);

private slots:
    void on_boton_agregar_clicked();

    void on_Eliminar_clicked();

private:
    Ui::ConfiguracionCasas *ui;
    Qt::WindowFlags flags;
    QMap<int, QList<QString>> * mapa_valores;
    QList<QList<QString>> dispositivos_sin_casa;
    QList<QList<QString>> casas_en_condominio;
    QObject * confv;
};

#endif // CONFIGURACIONCASAS_H
