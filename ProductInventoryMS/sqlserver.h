#ifndef SQLSERVER_H
#define SQLSERVER_H

#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

class SqlServer
{
public:
    SqlServer();
    bool initSql();
    bool registerUser(QString name,QString password,QString role);
    bool loginUser(QString name,QString password);
    bool insertStock(QString name,QString Scategory,QString Scount,QString Saddr,QString Smanu,QString Snote);

    QSqlQuery *query;
    QSqlDatabase db;
};

#endif // SQLSERVER_H
