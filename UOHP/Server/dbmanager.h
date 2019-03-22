#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QDebug>
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "person.h"

class DBManager {
public:
    static DBManager& getInstance() {
        static DBManager instance;
        return instance;
    }

    void insertPerson(Person& person);
    std::vector<Person> getPeople();

private:
    DBManager();
    QSqlDatabase db;
    std::vector<Person> people;

    bool containsPeopleTable();
    void createPersonTable();
    void loadPeople();
};

#endif // DBMANAGER_H
