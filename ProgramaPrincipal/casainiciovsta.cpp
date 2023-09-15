#include "casainiciovsta.h"
#include "ui_casainiciovsta.h"

CasaInicioVsta::CasaInicioVsta(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CasaInicioVsta)
{
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    flag_iniciado = false;
    fecha_conexion_in = "2022-11-11";
    fecha_conexion_hoy = "2022-11-11";
}

CasaInicioVsta::~CasaInicioVsta()
{
    delete ui;
}


void CasaInicioVsta::SetNombre(QString nom){
    nombre = nom;
    ui->groupBox->setTitle(nombre);
}


void CasaInicioVsta::AgregarFecha(QString fechin, QString fechfin){
        const int newIndex = ui->Tabla->rowCount();
        ui->Tabla->setRowCount(newIndex + 1);
        ui->Tabla->setItem(newIndex,0,new QTableWidgetItem(fechin));
        ui->Tabla->setItem(newIndex,1,new QTableWidgetItem(fechfin));
        ui->sobrepasos->setText(QString::number(ui->Tabla->rowCount()));
}


void CasaInicioVsta::IniciarCasa(){
    if(flag_iniciado) readData(fecha_conexion_in,fecha_conexion_hoy);
}

void CasaInicioVsta::readData(QString inicio, QString fecha){
    flag_iniciado = true;
    fecha_conexion_in = inicio;
    fecha_conexion_hoy = fecha;
    CleanBase();
    ConfigurarConexion();
    ui->fecha->setText(fecha);
    qDebug()<<QString::number(ui->Tabla->rowCount());
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
        query.prepare("SELECT t2.Descripcion, t1.Fecha_Inicio_Penalizacion, t1.Fecha_Fin_Penalizacion from Sobrepasos_Casas t1 with(nolock), Casas t2 with(nolock) where t2.Id_Casa = t1.Id_Casa and t2.Descripcion = '"+nombre+"' and t1.Fecha_Inicio_Penalizacion >= '"+inicio+"'");
        try {
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
            qDebug() << "Query Executed Successfully !";
            while(query.next())
            {
                fecha_inic = query.value(1).toDateTime().toString("yyyy-MM-dd");
                fecha_fin = query.value(2).toDateTime().toString("yyyy-MM-dd");
                AgregarFecha(fecha_inic, fecha_fin);
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



void CasaInicioVsta::ConfigurarConexion(){
    if(!db.contains(connName)){
        db = QSqlDatabase::addDatabase("QODBC" , connName);
        db.setDatabaseName(DatabaseName); // "WorkDatabase" is the name of the database we want
        db.setUserName(UserName); // Set Login Username
    }
}


void CasaInicioVsta::CleanBase(){
    {
        db = QSqlDatabase::database();
        db.close();
    }
    QSqlDatabase::removeDatabase(connName);
}


void CasaInicioVsta::deleteData(QString inicio){
    flag_iniciado = false;
    CleanBase();
    ConfigurarConexion();
    ui->fecha->setText(inicio);
    for(int i =  ui->Tabla->rowCount() - 1; i >= 0; i--){
        QTableWidgetItem* m = ui->Tabla->takeItem(i,0);
        QTableWidgetItem* o = ui->Tabla->takeItem(i,1);
        QTableWidgetItem* p = ui->Tabla->takeItem(i,2);
        ui->Tabla->removeRow(i);
        delete m;
        delete o;
        delete p;

    }
    ui->sobrepasos->setText(QString::number(ui->Tabla->rowCount()));
}


void CasaInicioVsta::nu_fecha(QDate f){
    if(f<QDate::currentDate()) ui->fecha->setText(f.toString("yyyy-MM-dd"));
    else ui->fecha->setText(QDate::currentDate().toString("yyyy-MM-dd"));
}
