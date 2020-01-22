#include "object.h"



Object::Object(){}

bool Object::read(QString filename){
    v.clear();
    indicies.clear();
    QFile f(filename);
    if (!f.exists()) {
        qDebug() << "Такого файла нет!";
        return false;
    }
    if (!f.open(QIODevice::ReadOnly)){
        qDebug() << "Не могу открыть файл!";
        return false;
    }
    QTextStream istream(&f);

    QVector<QVector3D> _v;
    QVector<QVector2D> _t;
    QVector<QVector3D> _n;
    QString tmp;
    QStringList list, indiciesList;

    while (!istream.atEnd()){
        tmp = istream.readLine();
        list = tmp.split(" ");
        if (list[0] == "v"){
            _v.append(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
            continue;
        }
        if (list[0] == "vt"){
            _t.append(QVector2D(list[1].toFloat(), list[2].toFloat()));
            //qDebug() << list[1].toFloat() << list[2].toFloat();
            continue;
        }
        if (list[0] == "vn"){
            _n.append(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
            continue;
        }
        if (list[0] == "f"){
            for (int i = 1; i <= 3; i++){
                indiciesList = list[i].split("/");
                if (indiciesList[1].size() == 0 && indiciesList[2].size() == 0)
                    v.append(Vertex(_v[indiciesList[0].toLong()-1]));

                if (indiciesList[1].size() == 0 && indiciesList[2].size() != 0)
                    v.append(Vertex(_v[indiciesList[0].toLong()-1], _n[indiciesList[2].toLong()-1]));

                if (indiciesList[1].size() != 0 && indiciesList[2].size() == 0)
                    v.append(Vertex(_v[indiciesList[0].toLong()-1], _t[indiciesList[1].toLong()-1]));

                if (indiciesList[1].size() != 0 && indiciesList[2].size() != 0)
                    v.append(Vertex(_v[indiciesList[0].toLong()-1], _t[indiciesList[1].toLong()-1], _n[indiciesList[2].toLong()-1]));

                indicies.append(indicies.size());
            }
        }
    }
    f.close();
    qDebug() << "reading done, size of v: " << v.size() << ", size of indicies: " << indicies.size();
    return true;
}

QVector3D Object::getCenter(){

}

Object::~Object(){

}
