#include "condominio.h"

Condominio::Condominio(QString con)
{
    condominio_id = con;
    Casas = new QMap<QString, Casa*>;
    casavista = new CasaView();
    connName = "ConexionCondominio";
    config = new ConfiguracionesCondominio();
    mapa_valores = new QMap<int, QList<QString>>();
}

ConfiguracionesCondominio * Condominio::getConfiguraciones(){
    return config;
}

void Condominio::agregarCasaLista(Casa* hogar){
    QString idc = QString::number(hogar->getId());
    (*Casas)[idc] = hogar;
}

void Condominio::setConfiguraciones() {
    for (auto it = Casas->begin(); it != Casas->end(); ++it)
    {
        it.value()->getNodo()->setConfiguracion(config);
    }
}


void Condominio::agregarCasaBase(Casa* hogar){
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
        QString idd = QString::number(hogar->getId());
        QString nom = hogar->getNombre();
        query.prepare("UPDATE Casas SET Id_Condominio = (select t1.Id_Condominio from Condominio t1 where t1.Descripcion = 'Condominio1'), Descripcion = '"+nom+"' where Id_Casa = "+idd+"");
        try{
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
        }
        catch(bool flag_query){
            qDebug()<<"No se pudo actualizar Casa";
        }
        if(hogar->getNodo() ==nullptr){
            query.prepare("select t3.Application_Id, t3.Device_Id, t4.Descripcion, t3.Fecha_Instalacion,t4.Id_Casa from Propiedades_Dispositivos_Dragino_Lt_22222_M3 t3 with (nolock), Casas t4 with (nolock) where t3.Id_Casa = t4.Id_Casa and t4.Id_Condominio = (select t2.Id_Condominio from Condominio t2 where t2.Descripcion = 'Condominio1') and t4.Id_Casa = "+idd);
            query.exec();
            query.next();
            devid = query.value(1).toString();
            nombre = query.value(2).toString();
            fech = query.value(3).toString();
            fech = fech.split(".")[0];
            casaid = query.value(4).toString();
            Nodo * node = new Nodo(devid.toStdString(),casaid.toInt(),condominio_id.toStdString());
            node->setConfiguracion(config);
            fecha = QDateTime::fromString(fech,"yyyy-MM-dd hh:mm:ss");
            hogar->setNodo(node);
        }
    }
    agregarCasaLista(hogar);
    db.close();
}

void Condominio::ConfigurarConexion(){
    if(!db.contains(connName)){
        db = QSqlDatabase::addDatabase("QODBC" , connName);
        db.setDatabaseName(DatabaseName); //
        db.setUserName(User); // Set Login Username
    }
}

void Condominio::CleanBase(){
    {
        db = QSqlDatabase::database();
        if(db.isOpen()) db.close();
    }
    if(db.contains(connName))QSqlDatabase::removeDatabase(connName);
}

void Condominio::elminiarCasa(QString idcasa){
    CleanBase();
    ConfigurarConexion();
    for (auto it = Casas->begin(); it != Casas->end();) {
        if(it.key()==idcasa){
            it.value()->getNodo()->BorrarConfiguracion();
            Casas->erase(it);
            delete it.value();
            break;
        }
        ++it;
    }
    if(!db.open())
    {
        qDebug() << "Can't Connect to DB !";
    }
    else
    {
        qDebug() << "Connected Successfully to DB !";
        QSqlQuery query(db);
        query.prepare("UPDATE Casas SET Id_Condominio = -1 where Id_Casa = "+idcasa+"");
        try{
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
        }
        catch(bool flag_query){
            qDebug()<<"No se pudo actualizar Casa";
        }
    }
}

void Condominio::openDialogCasaView(QString id) {
    casavista->setCasa((*Casas)[id]);
    casavista->show();
}


QMap<int, QList<QString>> * Condominio::mapa(){
    CleanBase();
    ConfigurarConexion();
    QList<QString> lista;
    if(!db.open())
    {
        qDebug() << "Can't Connect to DB !";
    }
    else
    {
        qDebug() << "Connected Successfully to DB !";
        QSqlQuery query(db);
        query.prepare("select t3.Device_Id, t3.Fecha_Instalacion, t3.Id_Casa, t3.Dev_Eui ,t4.Descripcion  from  Propiedades_Dispositivos_Dragino_Lt_22222_M3 t3 with(nolock), Casas t4 with(nolock) where t3.Id_Casa = (select t1.Id_Casa from Casas t1 with(nolock) where t1.Id_Casa = t3.Id_Casa  and t1.Id_Condominio = (select t2.Id_Condominio from Condominio t2 with(nolock) where t2.Descripcion = 'Condominio1')  group by t1.Id_Casa) and t3.Id_Casa = t4.Id_Casa");
        if(!query.exec())
        {
            qDebug() << "Can't Execute Query !";
        }
        else
        {
            qDebug() << "Query Executed Successfully !";
            //int i = 0;
            while(query.next())
            {
                lista.clear();
                QString dispositivo =  query.value(0).toString();
                QString nombre = query.value(4).toString();
                QString fech = query.value(1).toString();
                int casaid = query.value(2).toInt();
                QString dev_eui = query.value(3).toString();
                lista.append(nombre);
                lista.append(dispositivo);
                lista.append(fech);
                lista.append(dev_eui);
                (*mapa_valores)[casaid] = lista;
            }
        }
    }
    db.close();
    return mapa_valores;
}


QList<QList<QString>> Condominio::CasasEnCondominio() {
    CleanBase();
    ConfigurarConexion();
    QList<QList<QString>> lista;
    if(!db.open())
    {
        qDebug() << "Can't Connect to DB !";
    }
    else
    {
        qDebug() << "Connected Successfully to DB !";
        QSqlQuery query(db);
        query.prepare("select t4.Descripcion, t3.Device_Id, t4.Id_Casa, t3.Fecha_Instalacion from Propiedades_Dispositivos_Dragino_Lt_22222_M3 t3 with(nolock), Casas t4 with(nolock) where t3.Id_Casa = t4.Id_Casa and t4.Id_Condominio = (select t2.Id_Condominio from Condominio t2 with(nolock) where t2.Descripcion = 'Condominio1')");
        if(!query.exec())
        {
            qDebug() << "Can't Execute Query !";
        }
        else
        {
            qDebug() << "Query Executed Successfully !";
            while(query.next())
            {
                QList<QString> aux;
                aux.clear();
                QString nombre =  query.value(0).toString();
                QString dispositivo =  query.value(1).toString();
                QString casa_id = query.value(2).toString();
                QString fecha = query.value(3).toString();
                aux.append(nombre);
                aux.append(dispositivo);
                aux.append(casa_id);
                aux.append(fecha);
                lista.append(aux);
            }
        }
    }
    db.close();
    return lista;
}


QList<QList<QString>> Condominio::DispositivosSinCasa(){
    CleanBase();
    ConfigurarConexion();
    QList<QList<QString>> lista;
    if(!db.open())
    {
        qDebug() << "Can't Connect to DB !";
    }
    else
    {
        qDebug() << "Connected Successfully to DB !";
        QSqlQuery query(db);
        query.prepare("select t3.Device_Id, t3.Fecha_Instalacion, t3.Id_Casa from Propiedades_Dispositivos_Dragino_Lt_22222_M3 t3 with(nolock), Casas t4 with(nolock) where t3.Id_Casa = t4.Id_Casa and t4.Id_Condominio = -1");
        if(!query.exec())
        {
            qDebug() << "Can't Execute Query !";
        }
        else
        {
            qDebug() << "Query Executed Successfully !";
            //int i = 0;
            while(query.next())
            {
                QList<QString> aux;
                aux.clear();
                QString dispositivo =  query.value(0).toString();
                QString fecha =  query.value(1).toString();
                QString casa_id = query.value(2).toString();
                aux.append(dispositivo);
                aux.append(fecha);
                aux.append(casa_id);
                lista.append(aux);
            }
        }
    }
    db.close();
    return lista;
}

void Condominio::llenarCasas(){
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
        query.prepare("select t3.Application_Id, t3.Device_Id, t4.Descripcion, t3.Fecha_Instalacion,t4.Id_Casa from Propiedades_Dispositivos_Dragino_Lt_22222_M3 t3 with (nolock), Casas t4 with (nolock) where t3.Id_Casa = t4.Id_Casa and t4.Id_Condominio = (select t2.Id_Condominio from Condominio t2 with(nolock) where t2.Descripcion = 'Condominio1') ");
        if(!query.exec())
        {
            qDebug() << "Can't Execute Query !";
        }
        else
        {
            qDebug() << "Query Executed Successfully !";
            //int i = 0;
            while(query.next())
            {
                devid = query.value(1).toString();
                nombre = query.value(2).toString();
                fech = query.value(3).toString();
                fech = fech.split(".")[0];
                casaid = query.value(4).toString();
                qDebug()<<devid;
                Nodo * node = new Nodo(devid.toStdString(),casaid.toInt(),condominio_id.toStdString());
                fecha = QDateTime::fromString(fech,"yyyy-MM-dd hh:mm:ss");
                casa = new Casa(casaid.toInt(),condominio_id.toStdString(),fecha,nombre);
                casa->setNodo(node);
                casa->setConfig(config);
                agregarCasaLista(casa);
            }
        }
    }
    db.close();
    setConfiguraciones();
}


Condominio::~Condominio(){
    delete casavista;
    qDeleteAll(*Casas);
    Casas->clear();
    delete Casas;
}

QMap<QString, Casa*> * Condominio::getCasas(){
    return Casas;
}

QString Condominio::getCondominioId(){
    return condominio_id;
}

CasaView * Condominio::getCasaVista(){
    return casavista;
}

CasaInicioVsta * Condominio::getInicio(){
    return casavista->getInicio();
}
