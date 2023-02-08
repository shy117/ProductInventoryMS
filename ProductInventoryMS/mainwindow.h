#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QAction>
#include <QToolBar>
#include <QLabel>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QDateEdit>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>
#include "sqlserver.h"
#include "homepage.h"
#include "stockpage.h"
#include "instockpage.h"
#include "outstockpage.h"
#include "userpage.h"
#include "addstockdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void creatTool();
    void creatNaviBar();
    void creatStackWidget();
    void switchPages();

private:
    Ui::MainWindow *ui;

    QStackedWidget *stackWidget;

    QAction *homeAction;
    QAction *stockAction;
    QAction *enterAction;
    QAction *exitAction;
    QAction *userAction;
    QSqlTableModel* StockModel;

    HomePage *homespage;
    StockPage *stockpage;
    InStockPage *instockpage;
    OutStockPage *outstockpage;
    UserPage *userpage;


};

#endif // MAINWINDOW_H
