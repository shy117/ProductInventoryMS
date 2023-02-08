#ifndef STOCKPAGE_H
#define STOCKPAGE_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include "sqlserver.h"
#include "addstockdialog.h"
#include "modifystockdialog.h"

namespace Ui {
class StockPage;
}

class StockPage : public QWidget
{
    Q_OBJECT

public:
    explicit StockPage(QWidget *parent = nullptr);
    ~StockPage();
    void creatStockPage();

    void addStock();
    void insertStockData();
    void searchStockData();
    void modifyStock();
    void modifyStockData();
    void deleteStockData();

private:
    Ui::StockPage *ui;
    QSqlTableModel* StockModel;
    SqlServer *mysql;
    addStockDialog *stockDialog;
    SqlServer *sql;
    modifyStockDialog *stockModifyDialog;
};

#endif // STOCKPAGE_H
