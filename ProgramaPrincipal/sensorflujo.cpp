#include "sensorflujo.h"

SensorFlujo::SensorFlujo(string deviceID, string condominio)
{
    datos = new vector<DatosConsumo>;
    this->deviceID = QString::fromStdString(deviceID);
    this->condominio = QString::fromStdString(condominio);
    tipo = "SensorFlujoAgua";
    connName = "conexionSensorAgua"+this->deviceID;
    connName2 = "conexionSensorFlujoo"+this->deviceID;
    yValCheck = 0;
}

vector<DatosConsumo>* SensorFlujo::getData(QDateTime init,QDateTime fin,int formato, QString periodo) {
    CleanBase(connName);
    datos->clear();
    readData(init,fin,formato,periodo);
    return datos;
}

void SensorFlujo::ConfigurarConexion(QString conexion){
    if(!db.contains(conexion)){
        db = QSqlDatabase::addDatabase("QODBC" , conexion);
        db.setDatabaseName(DatabaseName);
        db.setUserName(User); // Set Login Username
    }
}

qreal SensorFlujo::DataCheck(QDateTime fecha, QString periodo){
    CleanBase(connName2);
    ConfigurarConexion(connName2);
    QDateTime fecha_sig = fecha.addDays(1);
    QString fechaa = fecha.toString("yyyy-MM-ddThh:mm:ss");
    QString fechaa_sig = fecha_sig.toString("yyyy-MM-ddThh:mm:ss");
    QString Periodo = "";
    bool flag_anual = false;
    bool flag_mensual = false;
    bool flag_diario = false;
    if(periodo == "Anual") {Periodo = "Year(Fecha)";flag_anual = true;}
    else if(periodo == "Mensual") {Periodo = "Year(Fecha), DATEPART(month, Fecha)";flag_mensual = true;}
    else if(periodo == "Diario") {Periodo = "Year(Fecha), DATEPART(month, Fecha), DATEPART(Day, Fecha)"; flag_diario = true;}
    try {
        bool flag_conexion = db.open();
        if(!flag_conexion) throw flag_conexion;
        QSqlQuery query(db);
        query.prepare("SELECT c.Descripcion, d.Id_Casa, "+Periodo+", sum(Cantidad) as Cantidad FROM  Detalles_Consumos_Casa d with(nolock), Casas c with(nolock), Propiedades_Dispositivos_Dragino_Lt_22222_M3 p with(nolock) where fecha >= '"+fechaa+"' and fecha <= '"+fechaa_sig+"' and d.Id_Casa = c.Id_Casa and d.Id_Casa= (select p.Id_Casa where p.Device_Id = '"+deviceID+"') GROUP BY c.Descripcion, d.Id_Casa, "+Periodo+" ORDER BY "+Periodo);
        try {
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
            qDebug() << "Query Executed Successfully !";
            query.next();
            if (flag_anual){
                yValCheck = query.value(3).toDouble();
            }
            else if (flag_mensual){
                yValCheck = query.value(4).toDouble();
            }
            else if (flag_diario) {
                yValCheck = query.value(5).toDouble();
            }
            //query.finish();
        }
        catch(bool bandera_query)
        {
            qDebug() << "No se puedo ejecutar el query";
        }
        db.close();
    }
    catch(bool bandera_conexion)
    {
        qDebug() << "No se puede conectar a la base de datos agua";
    }
    return yValCheck;
}

void SensorFlujo::readData(QDateTime init,QDateTime fin,int formato, QString periodo) {
    CleanBase(connName);
    ConfigurarConexion(connName);
    QString initt = init.toString("yyyy-MM-ddThh:mm:ss");
    QString finn = fin.toString("yyyy-MM-ddThh:mm:ss");
    QString seleccion = "";
    QStringList fechasInit = initt.split("-");
    fechasInit[2] = fechasInit[2].split("T")[0];
    QStringList fechasFin = finn.split("-");
    fechasFin[2] = fechasFin[2].split("T")[0];

    QString Periodo = "";
    bool flag_anual = false;
    bool flag_mensual = false;
    bool flag_diario = false;
    if(periodo == "Anual") {Periodo = "Year(Fecha)";flag_anual = true;}
    else if(periodo == "Mensual") {Periodo = "Year(Fecha), DATEPART(month, Fecha)";flag_mensual = true;}
    else if(periodo == "Diario") {Periodo = "Year(Fecha), DATEPART(month, Fecha), DATEPART(Day, Fecha)"; flag_diario = true;}
    //datos->clear();
    qDebug()<<finn;
    try {
        bool flag_conexion = db.open();
        if(!flag_conexion) throw flag_conexion;
        QSqlQuery query(db);
        QString ej = "SELECT c.Descripcion, d.Id_Casa, "+Periodo+", sum(Cantidad) as Cantidad FROM  Detalles_Consumos_Casa d with(nolock), Casas c with(nolock), Propiedades_Dispositivos_Dragino_Lt_22222_M3 p with(nolock) Where fecha >= '"+initt+"' and fecha <= '"+finn+"' and d.Id_Casa = c.Id_Casa and d.Id_Casa= (select p.Id_Casa where p.Device_Id = '"+deviceID+"') GROUP BY c.Descripcion, d.Id_Casa, "+Periodo+" ORDER BY "+Periodo;
        query.prepare(ej);
        try {
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
            qDebug() << "Query Executed Successfully !";
            int xValAno = 1997;
            int xValMes = 1;
            int xValDia = 1;
            qreal yVal = 0;
            while(query.next())
            {
                if (flag_anual){
                    if (formato ==1) {
                        xValAno = query.value(2).toDouble()+1;
                        yVal = query.value(3).toDouble()+yVal;
                    }else{
                        xValAno = query.value(2).toDouble();
                        yVal = query.value(3).toDouble();
                    }
                }
                else if (flag_mensual){
                    if (formato ==1) {
                        xValAno = query.value(2).toDouble();
                        xValMes = query.value(3).toDouble();
                        QDate aux(xValAno,xValMes,1);
                        QDate auxx(xValAno,xValMes,aux.daysInMonth());
                        if(fin.date() > auxx) xValDia = aux.daysInMonth();
                        else xValDia = fin.date().day();
                        yVal = query.value(4).toDouble()+yVal;
                    }else{
                        xValAno = query.value(2).toDouble();
                        xValMes = query.value(3).toDouble();
                        QDate aux(xValAno,xValMes,1);
                        QDate auxx(xValAno,xValMes,aux.daysInMonth());
                        if(fin.date() > auxx) xValDia = aux.daysInMonth();
                        else xValDia = fin.date().day();
                        yVal = query.value(4).toDouble();
                    }
                }
                else if (flag_diario) {
                    if (formato ==1) {
                        xValAno = query.value(2).toDouble();
                        xValMes = query.value(3).toDouble();
                        xValDia = query.value(4).toDouble();
                        yVal = query.value(5).toDouble()+yVal;
                    }else{
                        xValAno = query.value(2).toDouble();
                        xValMes = query.value(3).toDouble();
                        xValDia = query.value(4).toDouble();
                        yVal = query.value(5).toDouble();
                    }
                }
                qreal val = query.value(5).toDouble();
                qDebug()<<val;
                DatosConsumo data_aux(yVal,xValAno,xValMes,xValDia);
                datos->push_back(data_aux);
            }
            query.finish();
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

void SensorFlujo::CleanBase(QString conexion){
    {
        db = QSqlDatabase::database();
        db.close();
    }
    QSqlDatabase::removeDatabase(conexion);
}

SensorFlujo::~SensorFlujo() {
    delete datos;
}

QString SensorFlujo::getTipo() {
    return tipo;
}



vector<DatosConsumo> * SensorFlujo::getUltimosDatos(int acumulado){
    datos->clear();
    CleanBase(connName);
    ConfigurarConexion(connName);
    QString Periodo;
    QString Periododsc;
    double yVal = 0;
    int ano;
    int mes;
    int dia;
    int hora;
    int minuto;
    Periodo = "Year(Fecha), DATEPART(month, Fecha), DATEPART(Day, Fecha), DATEPART(Hour, Fecha), DATEPART(Minute, Fecha)";
    Periododsc = "Year(Fecha) desc, DATEPART(month, Fecha) desc, DATEPART(Day, Fecha) desc, DATEPART(Hour, Fecha) desc, DATEPART(Minute, Fecha) desc";
    try {
        bool flag_conexion = db.open();
        if(!flag_conexion) throw flag_conexion;
        QSqlQuery query(db);
        query.prepare("SELECT TOP(50) c.Descripcion, d.Id_Casa, "+Periodo+", sum(Cantidad) as Cantidad FROM  Detalles_Consumos_Casa d with(nolock), Casas c with(nolock), Propiedades_Dispositivos_Dragino_Lt_22222_M3 p with(nolock) where d.Id_Casa = c.Id_Casa and d.Id_Casa= (select p.Id_Casa where p.Device_Id = '"+deviceID+"') GROUP BY c.Descripcion, d.Id_Casa, "+Periodo+" ORDER BY "+Periododsc);
        try {
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
            qDebug() << "Query Executed Successfully !";
            while(query.next()){
                if(acumulado == 1){
                    yVal = query.value(7).toDouble()+yVal;
                }
                else {
                    yVal = query.value(7).toDouble();
                }
                ano = query.value(2).toInt();
                mes = query.value(3).toInt();
                dia = query.value(4).toInt();
                hora = query.value(5).toInt();
                minuto = query.value(6).toInt();
                qDebug()<<yVal;
                DatosConsumo data_aux(yVal,ano,mes,dia,hora,minuto);
                datos->push_back(data_aux);
                //datos_u.
            }
            std::reverse(datos->begin(),datos->end());
            //query.finish();
        }
        catch(bool bandera_query)
        {
            qDebug() << "No se puedo ejecutar el query";
        }
        db.close();
    }
    catch(bool bandera_conexion)
    {
        qDebug() << "No se puede conectar a la base de datos";
    }
    return datos;
}

