#include "sqlserver.h"

SqlServer::SqlServer()
{

}

bool SqlServer::initSql()
{
    db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
    qDebug()<<"ODBC driver?"<<db.isValid();
    QString dsn = QString::fromLocal8Bit("QTDSN");          //数据源名称
    db.setHostName("localhost");                            //选择本地主机，127.0.1.1
    db.setDatabaseName(dsn);                                //设置数据源名称
    db.setUserName("sa");                                   //登录用户
    db.setPassword("123");                                  //密码
    if (!db.open())
    {
        qDebug()<<db.lastError().text();
        QMessageBox::critical(nullptr,QObject::tr("Databaseerror"),db.lastError().text());
        return false;
    }
    else
    {
         qDebug()<<"database open success!";
         return true;
    }
}

//注册输入信息
bool SqlServer::registerUser(QString name,QString password,QString role)
{
    query=new QSqlQuery;
    QString str = QString("insert into Manager(Maccount,Mpassword,Mrole) values('%1','%2','%3')").arg(name).arg(password).arg(role);
    if(!query->exec(str))
        return false;
    return true;
}

//登录读取信息
bool SqlServer::loginUser(QString name,QString password)
{
    query=new QSqlQuery;
    QString str=QString("select * from Manager where Maccount= '%1' and Mpassword = '%2' ").arg(name).arg(password);
    query->exec(str);
    return query->next();
}

bool SqlServer::insertStock(QString name,QString category,QString count,QString addr,QString manu,QString note)
{
    query=new QSqlQuery;
    QString str = QString("insert into Stock values('%1', '%2', '%3','%4','%5','%6')").arg(name).arg(category).arg(count).arg(addr).arg(manu).arg(note);
    if(!query->exec(str))
        return false;
    return true;
}
