#ifndef FECHAAUSTRALIANAACHILENA_H
#define FECHAAUSTRALIANAACHILENA_H
#include <QDateTime>
QDateTime AutoCl(QDateTime au){
    QDateTime cl = au.addSecs(-50400);//entre australia y chile hay 14 horas de diferencia.
    return cl;
}

QDateTime CltoAu(QDateTime cl){
    QDateTime au = cl.addSecs(50400);//entre australia y chile hay 14 horas de diferencia.
    return au;
}



#endif // FECHAAUSTRALIANAACHILENA_H
