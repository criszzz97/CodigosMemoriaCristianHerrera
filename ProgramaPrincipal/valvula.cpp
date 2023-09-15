#include "valvula.h"

Valvula::Valvula(string deviceID, string condominio)
{
    this->deviceID = QString::fromStdString(deviceID);
    this->condominio = QString::fromStdString(condominio);
    tipo = "ValvulaFlujoAgua";
    connName = "ConexionValvula"+QString::fromStdString(deviceID);
}

double Valvula::ActivarLimitador(float porcentaje){
    JsonClear();
    float tmp = (8.5/100.0)*porcentaje*1000;//En 8 segundos la valvula se mueve de un extremo a otro
    tmp = int(tmp);
    UltimaPosicion();
    int tmpp = tmp-apertura;
    QString path(PathToProyect);
    QFile file(path+"ejadas.json");
    file.resize(0);
    jsonValvula.insert("Type","RELAY_T");
    jsonValvula.insert("Mode","BACK");
    if(tmpp<0) {//Se invierte la direccion de cierre
        jsonValvula.insert("RON1",1);
        jsonValvula.insert("RON2",2);
        jsonValvula.insert("Time",-tmpp);
    }
    else{
        jsonValvula.insert("RON1",2);
        jsonValvula.insert("RON2",1);
        jsonValvula.insert("Time",tmpp);
    }
    jsonData.insert("f_port",30);
    jsonData.insert("priority","HIGHEST");
    jsonData.insert("confirmed",true);
    jsonData.insert("decoded_payload",jsonValvula);
    jsonArrayData.append(jsonData);
    jsonDownlink.insert("downlinks",jsonArrayData);
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
    } else {
        qDebug() <<"JSONTest2 File open!";
    }
    QJsonDocument jsonDoc(jsonDownlink);
    file.write(jsonDoc.toJson());
    file.close();


    QNetworkAccessManager *mgr = new QNetworkAccessManager();
    QString sapp = "https://nam1.cloud.thethings.network/api/v3/as/applications/"+condominio +"/devices/";
    QString sdev = deviceID + "/down/push";
    QString down = sapp+sdev;
    QUrl url(down);
    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Authorization", "Bearer "+Token);
    QByteArray data = jsonDoc.toJson();
    QNetworkReply *reply = mgr->post(request, data);
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        if(reply->error() == QNetworkReply::NoError){
            QString contents = QString::fromUtf8(reply->readAll());
            qDebug() << contents;
            ActualizarPosicionLimitador(tmp);
            CleanBase();
        }
        else{
            QString err = reply->errorString();
            qDebug() << err;
        }
        reply->deleteLater();
    });
    return ((apertura/8000.0)*100.0);
}

void Valvula::JsonClear() {
    jsonValvula.remove("Type");
    jsonValvula.remove("Mode");
    jsonValvula.remove("RON1");
    jsonValvula.remove("RON2");
    jsonValvula.remove("Time");


    jsonData.remove("f_port");
    jsonData.remove("priority");
    jsonData.remove("confirmed");
    jsonData.remove("decoded_payload");

    for (int i = 0; i <jsonArrayData.count();i++){
        jsonArrayData.removeAt(i);
    }

    jsonDownlink.remove("downlinks");

}

void Valvula::CleanBase(){
    {
        db = QSqlDatabase::database();
        db.close();
    }
    QSqlDatabase::removeDatabase(connName);
}

void Valvula::ConfigurarConexion(){
    if(!db.contains(connName)){
        db = QSqlDatabase::addDatabase("QODBC" , connName);
        db.setDatabaseName(DatabaseName);
        db.setUserName(User);
    }
}

int * Valvula::UltimaPosicion(){
    CleanBase();
    ConfigurarConexion();
    try {
        bool flag_conexion = db.open();
        if(!flag_conexion) throw flag_conexion;
        QSqlQuery query(db);
        static int valor[3];
        query.prepare("Select Top(1) AperturaValvula, TiempoRele0, TiempoRele1 from Envios_Dispositivos_Dragino_Lt_22222 with(nolock) where Device_Id = '"+deviceID+"' Order By Fecha Desc;");
        try {
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
            query.next();
            apertura = query.value(0).toInt();
            valor[0] = apertura;
            valor[1] = query.value(1).toInt();
            valor[2] = query.value(2).toInt();
            db.close();
            return valor;
        }
        catch(bool flag_query)
        {
            qDebug() << "No se puedo ejecutar el query";
        }
    }
    catch(bool flag_conexion)
    {
        qDebug() << "No se puede conectar a la base de datos";
    }
    return nullptr;
}

void Valvula::ActualizarPosicionLimitador(int cantidad){
    CleanBase();
    ConfigurarConexion();
    QDateTime fecha = QDateTime::currentDateTime();
    QString fechaa = fecha.toString("yyyy-MM-ddThh:mm:ss");
    int * valores = UltimaPosicion();
    cantidad = cantidad-apertura;
    try {
        bool flag_conexion = db.open();
        if(!flag_conexion) throw flag_conexion;
        QSqlQuery query(db);
        try {
            int tiempoRele0 = *(valores+1);
            int tiempoRele1 = *(valores+2);
            apertura = apertura + cantidad;
            if (cantidad < 0) tiempoRele0 += -cantidad;
            else tiempoRele1 += cantidad;
            apertura = (apertura<0) ? 0: apertura;
            apertura = (apertura>8500) ? 8500: apertura;
            QString ap = QString::number(apertura);
            QString tr0 = QString::number(tiempoRele0);
            QString tr1 = QString::number(tiempoRele1);
            query.clear();

            query.prepare("Insert Into Envios_Dispositivos_Dragino_Lt_22222 (AperturaValvula, TiempoRele0, TiempoRele1,Fecha, Device_Id, Application_Id, Dev_Eui) Select "+ap+", "+ tr0+", "+ tr1+", '"+fechaa+"', '"+deviceID+"', '"+condominio+"', Dev_Eui from Propiedades_Dispositivos_Dragino_Lt_22222_M3 where Device_Id = '"+deviceID+"';");
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
            db.close();
        }
        catch(bool flag_query)
        {
            qDebug() << "No se puedo ejecutar el query";
        }
    }
    catch(bool flag_conexion)
    {
        qDebug() << "No se puede conectar a la base de datos";
    }
}

QString Valvula::getTipo() {
    return tipo;
}
