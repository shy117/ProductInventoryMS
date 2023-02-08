#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include "sqlserver.h"

namespace Ui {
class UserPage;
}

class UserPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserPage(QWidget *parent = nullptr);
    ~UserPage();
    void creatUserPage();
    void searchUserData();

private:
    Ui::UserPage *ui;
    QSqlTableModel* UserModel;
    SqlServer *mysql;
    SqlServer *sql;
};

#endif // USERPAGE_H
