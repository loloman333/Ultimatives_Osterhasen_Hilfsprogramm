#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QMetaType>

class Person
{

public:
    Person(int id, QString name, double latitude, double longitude) {
        this->id = id;
        this->name = name;
        this->latitude = latitude;
        this->longitude = longitude;
    }

    Person(){}
    ~Person(){}

    // Getter
    int getId() { return this-> id; }
    QString getName() { return this->name; }
    double getLongitude() { return this->longitude; }
    double getLatitude() { return this->latitude; }

    // Setter
    void setId(int id) { this->id = id; }
    void setName(QString name) { this->name = name; }
    void setLatitude(double latitude) { this->latitude = latitude; }
    void setLongitude(double longitude) { this->longitude = longitude; }

private:
    int id;
    QString name;
    double latitude;
    double longitude;
};

Q_DECLARE_METATYPE(Person);

#endif // PERSON_H
