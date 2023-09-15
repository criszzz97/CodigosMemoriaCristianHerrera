#include "proyectomemoria.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProyectoMemoria w;
    w.show();
    return a.exec();
}
