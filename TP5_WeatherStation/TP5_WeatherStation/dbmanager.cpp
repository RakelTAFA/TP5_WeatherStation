#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager(const QString &path)
{
    sqldb = QSqlDatabase::addDatabase("QSQLITE");
    sqldb.setDatabaseName(path);

    if (!sqldb.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (sqldb.isOpen())
    {
        sqldb.close();
    }
}

bool DbManager::isOpen() const
{
    return sqldb.isOpen();
}

bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE pollution(id INTEGER PRIMARY KEY, dt INTEGER, aqi INTEGER);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'pollution': one might already exist.";
        success = false;
    }

    return success;
}

bool DbManager::addData(int dt, int aqi) {

    bool success = false;

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO pollution (dt,aqi) VALUES (:dt,:aqi)");
    queryAdd.bindValue(":dt", dt);
    queryAdd.bindValue(":aqi", aqi);

    if(queryAdd.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "add dt/aqi failed: " << queryAdd.lastError();
    }

    return success;
}

bool DbManager::removeData(int dt)
{
    bool success = false;

    if (entryExists(dt))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM pollution WHERE dt = (:dt)");
        queryDelete.bindValue(":dt", dt);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove data failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove data failed: dt doesnt exist";
    }

    return success;
}

void DbManager::printAllData() const
{
    qDebug() << "Data in db:";
    QSqlQuery query("SELECT * FROM pollution");
    int idDt = query.record().indexOf("dt");
    int idAqi = query.record().indexOf("aqi");
    while (query.next())
    {
        int dt = query.value(idDt).toInt();
        int aqi = query.value(idAqi).toInt();
        qDebug() << "===" << dt << " " << aqi;
    }
}

bool DbManager::entryExists(int dt) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT dt FROM pollution WHERE dt = (:dt)");
    checkQuery.bindValue(":dt", dt);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "data exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::removeAllData()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM pollution");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all data failed: " << removeQuery.lastError();
    }

    return success;
}
