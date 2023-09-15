#include "configuracionescondominio.h"

ConfiguracionesCondominio::ConfiguracionesCondominio()
{
    connName = "ConexionConfiguracionesCondominio";
    LlamarDatos();
}

void ConfiguracionesCondominio::setView(QObject * vista){
    this->vista = vista;
}

void ConfiguracionesCondominio::LlamarDatos(){
    CleanBase();
    ConfigurarConexion();
    if(!db.open())
    {
        qDebug() << "Can't Connect to DB !";
    }
    else
    {
        qDebug() << "Connected Successfully to DB !";
        QSqlQuery query(db);
        query.prepare("select LimiteMesAgua, AccionCapacidad, AccionDias, Inicio_Restriccion from  Condominio with(nolock) where Descripcion = 'Condominio1'");
        if(!query.exec())
        {
            qDebug() << "Can't Execute Query !";
        }
        else
        {
            qDebug() << "Query Executed Successfully !";
            query.next();
            LimiteConsumo = query.value(0).toInt();
            CapacidadConfigurada = query.value(1).toInt();
            dias = query.value(2).toInt();
            qDebug()<<query.value(3);
            FechaRestriccion = query.value(3).toDate();
        }
    }
    db.close();
}

void ConfiguracionesCondominio::ConfigurarConexion(){
    if(!db.contains(connName)){
        db = QSqlDatabase::addDatabase("QODBC" , connName);
        db.setDatabaseName(DatabaseName); 
        db.setUserName(User); // Set Login Username
    }
}

int ConfiguracionesCondominio::getLimiteConsumo(){
    return LimiteConsumo;
}

int ConfiguracionesCondominio::getCapacidadConfigurada(){
    return CapacidadConfigurada;
}

int ConfiguracionesCondominio::getDias(){
    return dias;
}

QDate ConfiguracionesCondominio::getFechaRegla(){
    return FechaRestriccion;
}

void ConfiguracionesCondominio::CleanBase(){
    {
        db = QSqlDatabase::database();
        if(db.isOpen()) db.close();
    }
    if(db.contains(connName))QSqlDatabase::removeDatabase(connName);
}

void ConfiguracionesCondominio::ActualizarCondominio(QString Limite, QString Capacidad, QString d, QDate initregla) {
    LimiteConsumo = Limite.toInt();
    CapacidadConfigurada = Capacidad.toInt();
    dias = d.toInt();
    FechaRestriccion = initregla;
    QString fr = FechaRestriccion.toString("yyyy-MM-dd");
    CleanBase();
    ConfigurarConexion();
    if(!db.open())
    {
        qDebug() << "Can't Connect to DB !";
    }
    else
    {
        qDebug() << "Connected Successfully to DB !";
        QSqlQuery query(db);
        query.prepare("update Condominio set AccionDias = "+QString::number(dias)+", LimiteMesAgua = "+QString::number(LimiteConsumo) +", AccionCapacidad = "+QString::number(CapacidadConfigurada)+", Inicio_Restriccion = '"+fr+"'");
        if(!query.exec())
        {
            qDebug() << "Can't Execute Query !";
        }
    }
    db.close();

}
