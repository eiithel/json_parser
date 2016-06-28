#ifndef MAINS_H
#define MAINS_H

#include <QObject>
#include <QString>
#include <QJsonObject>


class Mains
{
public:
    Mains();
    void read(QJsonObject &obj);
    double gethumidity();
private:
    double _humidity;
    double _temp_max;
    double _temp_min;
    //QString _m;
};

#endif // MAINS_H
