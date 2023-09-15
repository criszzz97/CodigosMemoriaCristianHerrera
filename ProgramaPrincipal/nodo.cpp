#include "nodo.h"

Nodo::Nodo(string devID,int casaid,string con)
{
    deviceID = devID;
    casa_id = casaid;
    condominio = con;
    grafico = new Grafico();
    sensors = new QMap<QString, Sensor*>;
    actuators = new QMap<QString, Actuador*>;
    config = nullptr;
    flag_consumo_maximo = false;
    connName = "Nodo"+QString::fromStdString(devID);
    checkeo_penalizacion = false; cuenta = 0;
    addSensor(new SensorFlujo(devID,con));
    addActuator(new Valvula(devID,con));
}

void Nodo::addSensor(Sensor* sens) {
    (*sensors)[sens->getTipo()] = sens; //mapea al puntero de derivado de la clase sensor con su string tipo
}

void Nodo::addActuator(Actuador* act) {
    (*actuators)[act->getTipo()] = act; //mapea al puntero de derivado de la clase sensor con su string tipo
}


QMap<QString, Sensor*> * Nodo::getSensors() {
    return sensors;
}


QMap<QString, Actuador*> * Nodo::getActuators() {
    return actuators;
}

int * Nodo::UltimaPosicionLimitador(QString tipo){
    return (*actuators)[tipo]->UltimaPosicion();
}

void Nodo::mLimitador(float cantidad,QString tipo) {
    (*actuators)[tipo]->ActivarLimitador(cantidad);
}

Nodo::~Nodo(){
    qDebug()<<"hol";
    qDeleteAll(*sensors);
    sensors->clear();
    delete sensors;
    qDeleteAll(*actuators);
    actuators->clear();
    delete actuators;
}

vector<DatosConsumo> * Nodo::getConsumo(QDateTime init,QDateTime fin,QString tipo,int formato,QString periodo){
    try {
        if (sensors->contains(tipo)) {
            Sensor *val = (*sensors)[tipo];
            return val->getData(init,fin,formato,periodo);
        }
        else throw tipo;
    } catch (QString tip) {
        qDebug() << "El nodo no tiene ningun sensor del tipo  " << tip;
        return NULL;
    }
}

vector<DatosConsumo> * Nodo::getUltimosDatos(QString tipo, int acumulado){
    try {
        if (sensors->contains(tipo)) {
            Sensor *val = (*sensors)[tipo];
            return val->getUltimosDatos(acumulado);
        }
        else throw tipo;
    } catch (QString tip) {
        qDebug() << "El nodo no tiene ningun sensor del tipo  " << tip;
        return NULL;
    }
}

Grafico * Nodo::GraficoConsumoMinutal(QString tipo,int acumulado) {
    vector<DatosConsumo> * datos = getUltimosDatos(tipo,acumulado);
    grafico->setValues(datos,"Consumo Casa",true);
    grafico = grafico->viewGraph();
    return grafico;
}

Grafico * Nodo::GraficoConsumoAcumulado(QDateTime init,QDateTime fin,QString tipo, QString periodo) {
    vector<DatosConsumo> *datos = getConsumo(init,fin,tipo,1,periodo);
    grafico->setValues(datos,"Consumo Acumulado Casa",false);
    grafico = grafico->viewGraph();
    return grafico;
}


Grafico * Nodo::GraficoConsumo(QDateTime init,QDateTime fin,QString tipo, QString periodo) {
    vector<DatosConsumo> *datos = getConsumo(init,fin,tipo,0,periodo);
    grafico->setValues(datos,"Consumo Casa",false);
    grafico = grafico->viewGraph();
    return grafico;
}


void Nodo::setConfiguracion(ConfiguracionesCondominio * configuracion){
    config = configuracion;
    limite_Agua = config->getLimiteConsumo();
}

void Nodo::ConfigurarConexion(){
    if(!db.contains(connName)){
        db = QSqlDatabase::addDatabase("QODBC" , connName);
        db.setDatabaseName(DatabaseName);
        db.setUserName(User); // Set Login Username
    }
}

void Nodo::CleanBase(){
    {
        db = QSqlDatabase::database();
        db.close();
    }
    QSqlDatabase::removeDatabase(connName);
}

void Nodo::AgregarSobrePaso(QDateTime fecha) {
    ConfigurarConexion();
    int Limite = config->getLimiteConsumo();
    int Dias = config->getDias();
    int Capacidad = config->getCapacidadConfigurada();
    QString sLimite = QString::number(Limite);
    QString sDias = QString::number(Dias);
    QString sCapacidad = QString::number(Capacidad);
    QString idcasa = QString::number(casa_id);

    QString fecha_init = fecha.toString("yyyy-MM-dd");
    QDateTime f = fecha.addDays(Dias);
    QString fecha_fin = f.toString("yyyy-MM-dd");

    try {
        bool flag_conexion = db.open();
        if(!flag_conexion) throw flag_conexion;
        QSqlQuery query(db);
        query.prepare("IF Not EXISTS (SELECT * FROM Sobrepasos_Casas with(nolock) WHERE Fecha_Inicio_Penalizacion = '"+fecha_init+"' and Id_Casa = "+idcasa+") BEGIN   Insert Into Sobrepasos_Casas (Fecha_Inicio_Penalizacion, Id_Casa, Fecha_Fin_Penalizacion,Limite, Capacidad, Dias) Values ('"+fecha_init+"', "+idcasa+", '"+fecha_fin+"', "+sLimite+", "+sCapacidad+", "+sDias+") END");
        try {
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
            qDebug() << "Query Executed Successfully !";
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
    CleanBase();
}


void Nodo::UnidadConsumo(QString unidad){
    grafico->setUnidadConsumo(unidad);
}


bool Nodo::UltimoMesMarcado(QDateTime fecha_actual){
    ConfigurarConexion();
    QDateTime fecha_init_penalizacion;
    QString fecha_in_mm = "";
    QString fecha_in_yy = "";
    QString anoactual = fecha_actual.toString("yyyy-MM-ddThh:mm:ss").split("-")[0];
    QString mesactual = fecha_actual.toString("yyyy-MM-ddThh:mm:ss").split("-")[1];
    bool c = true;
    try {
        bool flag_conexion = db.open();
        if(!flag_conexion) throw flag_conexion;
        QSqlQuery query(db);
        QString idcasa = QString::number(casa_id);
        query.prepare("SELECT MAX (t.Fecha_Inicio_Penalizacion) FROM Sobrepasos_Casas t with(nolock) where t.Id_Casa = "+idcasa);
        try {
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
            qDebug() << "Query Executed Successfully !";
            query.next();
            c = query.isValid();
            if(!c) return false;
            fecha_init_penalizacion = query.value(0).toDateTime();
            if(!fecha_init_penalizacion.isValid()) return false;
            fecha_in_yy = fecha_init_penalizacion.toString("yyyy-MM-ddThh:mm:ss").split("-")[0];
            fecha_in_mm = fecha_init_penalizacion.toString("yyyy-MM-ddThh:mm:ss").split("-")[1];
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
    CleanBase();
    if(mesactual == fecha_in_mm && anoactual == fecha_in_yy){
        return true;
    }
    else{
        return false;
    }
}


bool Nodo::Penalizado(QDateTime fecha_actual){
    ConfigurarConexion();
    QDateTime fecha_fin_penalizacion;
    bool c = true;
    try {
        bool flag_conexion = db.open();
        if(!flag_conexion) throw flag_conexion;
        QSqlQuery query(db);
        QString idcasa = QString::number(casa_id);
        query.prepare("SELECT MAX (t.Fecha_Fin_Penalizacion) FROM Sobrepasos_Casas t with(nolock) where t.Id_Casa = "+idcasa);
        try {
            bool flag_query = query.exec();
            if(!flag_query) throw flag_query;
            query.next();
            c = query.isValid();
            if(!c) return false;
            fecha_fin_penalizacion = query.value(0).toDateTime();
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
    CleanBase();
    if(fecha_fin_penalizacion>fecha_actual){
        return true;
    }
    else{
        return false;
    }
}

void Nodo::ChequearRegla(QDateTime fecha_actual) {//la fecha de inicio corresponde a la primera fecha que se elige en el timer
    QString f = fecha_actual.toString("yyyy-MM-ddThh:mm:ss");
    QStringList fechasactual = f.split("-");
    QString dia = fechasactual[2].split("T")[0];
    if(UltimoMesMarcado(fecha_actual)) flag_consumo_maximo = true;
    Sensor* sensorFlujoAgua = (*sensors)["SensorFlujoAgua"];
    if(dia.toInt() == 1){
        cuenta = sensorFlujoAgua->DataCheck(fecha_actual,"Diario");
        flag_consumo_maximo = false;
    }
    else{
        cuenta = cuenta + sensorFlujoAgua->DataCheck(fecha_actual,"Diario");
    }
    qDebug()<<fecha_actual;
    qDebug()<<cuenta;
    qDebug()<< QString::fromStdString(deviceID);
    if((cuenta>limite_Agua) && (flag_consumo_maximo == false)){
        //accion a realizar
        AgregarSobrePaso(fecha_actual);
        qDebug()<<"El dispositivo "+QString::fromStdString(deviceID)+"supero el consumo maximo";
        flag_consumo_maximo = true;
        mLimitador(config->getCapacidadConfigurada(),"ValvulaFlujoAgua");
        checkeo_penalizacion = false;
    }
    if(!Penalizado(fecha_actual) && (*UltimaPosicionLimitador("ValvulaFlujoAgua")!=8500) && !checkeo_penalizacion){//hacer chequeo penalizado a false cuando se para con el boton parar
        mLimitador(100,"ValvulaFlujoAgua");
        checkeo_penalizacion = true;
        qDebug()<<QString::number(casa_id)+"Noooo";
    }
}

void Nodo::Chequeoa0(){
    checkeo_penalizacion = false;
    cuenta = 0;
    flag_consumo_maximo = false;
}

void Nodo::BorrarConfiguracion(){
    config = nullptr;
}
