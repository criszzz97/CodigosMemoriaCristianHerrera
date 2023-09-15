QT       += core gui charts sql
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    actuador.cpp \
    casa.cpp \
    casainiciovsta.cpp \
    casaview.cpp \
    condominio.cpp \
    condominioview.cpp \
    configuracioncasas.cpp \
    configuracionescondominio.cpp \
    configuracionescondominioview.cpp \
    datosconsumo.cpp \
    detallescondominios.cpp \
    grafico.cpp \
    main.cpp \
    nodo.cpp \
    proyectomemoria.cpp \
    sensor.cpp \
    sensorflujo.cpp \
    timerreglas.cpp \
    valvula.cpp

HEADERS += \
    FechaAustralianaAChilena.h \
    actuador.h \
    casa.h \
    casainiciovsta.h \
    casaview.h \
    condominio.h \
    condominioview.h \
    configuracioncasas.h \
    configuracionescondominio.h \
    configuracionescondominioview.h \
    datosconsumo.h \
    detallescondominios.h \
    grafico.h \
    nodo.h \
    proyectomemoria.h \
    sensor.h \
    sensorflujo.h \
    timerreglas.h \
    valvula.h

FORMS += \
    casainiciovsta.ui \
    configuracioncasas.ui \
    configuracionescondominioview.ui \
    detallescondominios.ui \
    proyectomemoria.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
