#ifndef OUTSTOCKPAGE_H
#define OUTSTOCKPAGE_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include "sqlserver.h"
#include "sqlserver.h"
#include "addoutstockdialog.h"
#include "modifyoutstockdialog.h"

namespace Ui {
class OutStockPage;
}

class OutStockPage : public QWidget
{
    Q_OBJECT

public:
    explicit OutStockPage(QWidget *parent = nullptr);
    ~OutStockPage();

    void creatOutStockPage();
    void addOutStock();
    void insertOutStockData();
    void searchOutStockData();
    void modifyOutStock();
    void modifyOutStockData();
    void deleteOutStockData();

private:
    Ui::OutStockPage *ui;
    QSqlTableModel* outStockModel;
    SqlServer *mysql;
    SqlServer *sql;
    addOutStockDialog *outStockDialog;
    modifyOutStockDialog *outStockModifyDialog;
};
#endif // OUTSTOCKPAGE_H
