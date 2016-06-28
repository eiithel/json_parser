#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QFile>
#include <iostream>
#include <QDebug>
#include <QtGlobal>
#include <QObject>
#include <QStringList>
#include "Mains.h"
#include <qvector.h>
#include <QVectorIterator>
#include <QTextStream>


/* On peut faire les requetes direct au serveur en utilisant les classes
 * QNetworkAccessManager, QNetworkRequest et QUrl
/

/*Dans un fichier montreal.json, on enregistre les données
 * des 5 derniers jours toutes les 3heures, ce qui donne 40 tableaux
 * de valeurs exploitables.
*/


QVector<double> readJson()
{
    QString val;
    QFile file;
    //file.setFileName("/home/ethel/qwt-5.2/test-ethel/json_parser/montreal.json");
    file.setFileName("/home/ethel/qwt-5.2/test-ethel/network/forecast");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    qWarning() << file.exists();//deja le fichier s'ouvre
    file.close();
    qWarning() << val;
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    qWarning() <<d.isObject();//il trouve un object dans montreal.json mais pas dans googlemap.json..

    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("list"));//city,message
    qWarning() << sett2.size();

    qWarning() << value;
    qWarning() << value.isArray();
    QJsonArray array =value.toArray();
    qWarning() << value;

    QJsonArray mains;
    QStringList clouds;
    QStringList weather;
    Mains tab;
    QVector<double> hData;
    QVector<double> tData;

    for(int i=0; i<array.size();i++){

        QJsonObject obj = array.at(i).toObject();
        QJsonObject obj2 =obj["main"].toObject();//on recupere bien les infos du main
        tab.read(obj2);//modifie champs humidity de l'objet Main.
        hData.push_back(tab.gethumidity());//on a récupérer toutes les valeurs d'humidité.
    }
    return hData;

}

int writeFile(QVector<double> &Data, QFile &file){
    //    file.setFileName("/home/ethel/qwt-5.2/test-ethel/json_parser/result1.txt");
    file.setFileName("/home/ethel/qwt-5.2/test-ethel/test3/result.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QVectorIterator<double> i(Data);

    QTextStream out(&file);
    while (i.hasNext()){
        out << i.next();
        out << "\n";
    }
    file.close();

    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << a.applicationFilePath();

    QVector<double> humidity;
    QFile file;

    qDebug() << "debut lecture";
    humidity = readJson();
    qDebug() << "ecriture dans fichier";
    writeFile(humidity, file);//ok ecrit bien dans le fichier du repo test3


    return a.exec();
}
