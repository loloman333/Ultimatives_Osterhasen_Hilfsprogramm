#include "dbmanager.h"

DBManager::DBManager() {

    QString path{
       QFileInfo(
            QCoreApplication::applicationDirPath()
        ).filePath() + "/People.db"
    };

    QFile::copy(":/res/res/People.db" , path);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";

        if (!containsPeopleTable()) {
            createPersonTable();
        } else {
            loadPeople();
        }
    }
}

bool DBManager::containsPeopleTable(){

    if(this->db.tables(QSql::AllTables).contains("people")) {
        qDebug() << "Database has a people table";
        return true;
    }

    qDebug() << "Database has no people table";
    return false;
}

void DBManager::loadPeople(){
    QSqlQuery query;
    query.prepare("select * from people order by id");
    query.exec();

    auto idCol = query.record().indexOf("id");
    auto nameCol = query.record().indexOf("name");
    auto latCol = query.record().indexOf("latitude");
    auto longCol = query.record().indexOf("longitude");

    while (query.next())
    {
        int id{query.value(idCol).toInt()};
        QString name{query.value(nameCol).toString()};
        double latitude{query.value(latCol).toDouble()};
        double longitude{query.value(longCol).toDouble()};

        people.push_back(Person{id, name, latitude, longitude});

        /*
        qDebug() << "Added new person: "
                 << "id: " + QString::number(id)
                 << "name: " + name
                 << "latitude: " + QString::number(latitude)
                 << "longitude: " + QString::number(longitude);
        */
    }

}

void DBManager::createPersonTable(){
    QSqlQuery query;
    query.prepare("create table people "
                  "(id integer primary key, "
                  "name text,"
                  "latitude float,"
                  "longitude float)");

    if (query.exec()) {
        qDebug() << "People table created";
    } else {
        qDebug() << "Error: People table not created: "
                 << query.lastError();
    }
}

void DBManager::insertPerson(Person &person){

    // First new id
    QSqlQuery idQuery;
    idQuery.exec("select max(id) from people");

    if (idQuery.next()) { person.setId(idQuery.value(0).toInt() + 1); }

    people.push_back(person);

    QSqlQuery query;
    query.prepare("insert into people (id, name, latitude, longitude) "
                  "values(:id, :name, :latitude, :longitude)");

    query.bindValue(":id", person.getId());
    query.bindValue(":name", person.getName());
    query.bindValue(":latitude", person.getLatitude());
    query.bindValue(":longitude", person.getLongitude());

    if (query.exec()) {
        qDebug() << "Inserted";

        QString path{
           QFileInfo(
                QCoreApplication::applicationDirPath()
            ).filePath() + "/People.db"
        };

        QFile::copy(":/res/res/People.db" , path);

    } else {
        qDebug() << "Insert failed";
    }
}

std::vector<Person> DBManager::getPeople(){
    return people;
}

