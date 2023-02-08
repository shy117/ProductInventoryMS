#ifndef INSTOCKPAGE_H
#define INSTOCKPAGE_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include "sqlserver.h"
#include "sqlserver.h"
#include "addinstockdialog.h"
#include "modifyinstockdialog.h"

namespace Ui {
class InStockPage;
}

class InStockPage : public QWidget
{
    Q_OBJECT

public:
    explicit InStockPage(QWidget *parent = nullptr);
    ~InStockPage();
    void creatInStockPage();

    void addInStock();
    void insertInStockData();
    void searchInStockData();
    void modifyInStock();
    void modifyInStockData();
    void deleteInStockData();

private:
    Ui::InStockPage *ui;
    QSqlTableModel* inStockModel;
    SqlServer *mysql;
    SqlServer *sql;
    addInStockDialog *inStockDialog;
    modifyInStockDialog *inStockModifyDialog;
};

#endif // INSTOCKPAGE_H
