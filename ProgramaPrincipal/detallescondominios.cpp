#include "detallescondominios.h"
#include "ui_detallescondominios.h"

DetallesCondominios::DetallesCondominios(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetallesCondominios)
{
    ui->setupUi(this);
    connName = "conexionDetalles";
    tm = nullptr;
    fecha_inic = "";
    fecha_fin = "";
    casaid = "";
    setWindowTitle("Sobrepasos");
}

DetallesCondominios::~DetallesCondominios()
{
    delete ui;
}

void DetallesCondominios::AgregarDetalle(QString casa, QString fechin, QString fechfin){
        const int newIndex = ui->Tabla->rowCount();
        ui->Tabla->setRowCount(newIndex + 1);
        ui->Tabla->setItem(newIndex,0,new QTableWidgetItem(casa));
        ui->Tabla->setItem(newIndex,1,new QTableWidgetItem(fechin));
        ui->Tabla->setItem(newIndex,2,new QTableWidgetItem(fechfin));
}


void DetallesCondominios::setTimer(TimerReglas * t) {
    tm = t;
    connect(tm,SIGNAL(timer_timeout()),this,SLOT(readData()));
    connect(tm,SIGNAL(pausa()),this,SLOT(deleteData()));
    readData();
}



void DetallesCondominios::readData(){
    CleanBase();
    ConfigurarConexion();
    QDateTime presente;
    QDateTime inicio= tm->getFechaInit();
    qDebug()<<"fechainicio";
    qDebug()<<inicio;
    QString inic = inicio.toString("yyyy-MM-dd");
    if(tm->getFecha()>QDateTime::currentDateTime()) presente = QDateTime::currentDateTime();
    else presente = tm->getFecha();
    ui->fecha->setText(presente.toString("yyyy-MM-dd"));
    emit hoy(inic,presente.toString("yyyy-MM-dd"));
    for(int i =  ui->Tabla->rowCount() - 1; i >= 0; i--){
        QTableWidgetItem* m = ui->Tabla->takeItem(i,0);
        QTableWidgetItem* o = ui->Tabla->takeItem(i,1);
        QTableWidgetItem* p = ui->Tabla->takeItem(i,2);
        ui->Tabla->removeRow(i);
        delete m;
        delete o;
        delete p;

    }
    try {
        bool flag_conexion = db.open();
        if(!flag_conexion) throw flag_conexion;
        QSqlQuery query(db);
        query.prepare("SELECT t2.Descripcion, t1.Fecha_Inicio_Penalizacion, t1.Fecha_Fin_Penalizacion from Sobrepasos_Casas t1 with(nolock), Casas t2 with(nolock) where t2.Id_Casa = t1.Id_Casa");// and t1.Fecha_Inicio_Penalizacion >= '"+inic+"'");
        try {
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
            qDebug() << "Query Executed Successfully !";
            while(query.next())
            {

                fecha_inic = query.value(1).toDateTime().toString("yyyy-MM-dd");
                casaid = query.value(0).toString();
                fecha_fin = query.value(2).toDateTime().toString("yyyy-MM-dd");
                AgregarDetalle(casaid, fecha_inic, fecha_fin);
            }
            db.close();
        }
        catch(bool bandera_query)
        {
            qDebug() << "No se puedo ejecutar el query";
        }
    }
    catch(bool bandera_conexion)
    {
        qDebug() << "No se puede conectar a la base de datos";
    }
}



void DetallesCondominios::ConfigurarConexion(){
    if(!db.contains(connName)){
        db = QSqlDatabase::addDatabase("QODBC" , connName);
        db.setDatabaseName(DatabaseName);
        db.setUserName(User); // Set Login Username
    }
}


void DetallesCondominios::CleanBase(){
    {
        db = QSqlDatabase::database();
        db.close();
    }
    QSqlDatabase::removeDatabase(connName);
}


void DetallesCondominios::DeleteCasa(QString casa_id){
    CleanBase();
    ConfigurarConexion();
    try {
        bool flag_conexion = db.open();
        if(!flag_conexion) throw flag_conexion;
        QSqlQuery query(db);
        query.prepare("delete Sobrepasos_Casas where Id_Casa = "+casa_id);
        try {
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
            db.close();
        }
        catch(bool bandera_query)
        {
            qDebug() << "No se puedo ejecutar el query";
        }
    }
    catch(bool bandera_conexion)
    {
        qDebug() << "No se puede conectar a la base de datos";
    }
}


void DetallesCondominios::deleteData(){
    CleanBase();
    ConfigurarConexion();
    ui->fecha->setText(tm->getFechaInit().toString("yyyy-MM-dd"));
    for(int i =  ui->Tabla->rowCount() - 1; i >= 0; i--){
        QTableWidgetItem* m = ui->Tabla->takeItem(i,0);
        QTableWidgetItem* o = ui->Tabla->takeItem(i,1);
        QTableWidgetItem* p = ui->Tabla->takeItem(i,2);
        ui->Tabla->removeRow(i);
        delete m;
        delete o;
        delete p;

    }
    QString fecha_i = tm->getFechaInit().toString("yyyy-MM-dd");
    emit borrar(fecha_i);
    try {
        bool flag_conexion = db.open();
        if(!flag_conexion) throw flag_conexion;
        QSqlQuery query(db);
        query.prepare("delete Sobrepasos_Casas where Fecha_Inicio_Penalizacion >= '"+fecha_i+"'");
        try {
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
            db.close();
        }
        catch(bool bandera_query)
        {
            qDebug() << "No se puedo ejecutar el query";
        }
    }
    catch(bool bandera_conexion)
    {
        qDebug() << "No se puede conectar a la base de datos";
    }
}

void DetallesCondominios::n_fecha(QDate fech) {
    if(fech<QDate::currentDate()) ui->fecha->setText(fech.toString("yyyy-MM-dd"));
    else ui->fecha->setText(QDate::currentDate().toString("yyyy-MM-dd"));
}
