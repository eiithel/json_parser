#include "Mains.h"

Mains::Mains()
{

}

void Mains::read(QJsonObject &obj){

    this->_humidity= obj["humidity"].toDouble();
}

double Mains::gethumidity(){
    return _humidity;
}
