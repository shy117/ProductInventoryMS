#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    creatTool();
    creatStackWidget();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//工具栏设置
void MainWindow::creatTool()
{
    //右上角显示
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->loginToolBar->addWidget(spacer);
    ui->loginToolBar->addAction(ui->loginAct);
    ui->loginToolBar->addAction(ui->ReLogin);

    LoginWindow *myLogin = new LoginWindow;
    //关闭
    connect(ui->ReLogin, &QAction::triggered, [this]()
    {
       this->close();
    });
    //打开登录界面,重新登录
    connect(ui->ReLogin, &QAction::triggered, myLogin, &QDialog::show);
}

void MainWindow::creatStackWidget()
{
    stackWidget = new QStackedWidget;
    homespage = new HomePage;
    stockpage = new StockPage;
    instockpage = new InStockPage;
    outstockpage = new OutStockPage;
    userpage = new UserPage;

    stackWidget->addWidget(homespage);
    stackWidget->addWidget(stockpage);
    stackWidget->addWidget(instockpage);
    stackWidget->addWidget(outstockpage);
    stackWidget->addWidget(userpage);
    setCentralWidget(stackWidget);

    //切换
    connect(ui->homeAction,&QAction::triggered,this,&MainWindow::switchPages);
    connect(ui->stockAction,&QAction::triggered,this,&MainWindow::switchPages);
    connect(ui->inAction,&QAction::triggered,this,&MainWindow::switchPages);
    connect(ui->outAction,&QAction::triggered,this,&MainWindow::switchPages);
    connect(ui->userAction,&QAction::triggered,this,&MainWindow::switchPages);
}

void MainWindow::switchPages()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if(action->text() == "主页")
        stackWidget->setCurrentIndex(0);
    else if(action->text() == "库存管理")
        stackWidget->setCurrentIndex(1);
    else if(action->text() == "入库管理")
        stackWidget->setCurrentIndex(2);
    else if(action->text() == "出库管理")
        stackWidget->setCurrentIndex(3);
    else if(action->text() == "用户管理")
        stackWidget->setCurrentIndex(4);
}



