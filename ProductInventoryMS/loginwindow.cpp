#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    sql = new SqlServer;
    if(sql->initSql())
        qDebug()<<"连接成功";
    else
        qDebug()<<"连接失败";

    //注册、登录、退出按钮
    connect(ui->passwordEdit, SIGNAL(returnPressed()), this, SLOT(on_loginButton_clicked()));
    connect(ui->quitButton, &QPushButton::clicked, this, &LoginWindow::on_quitButton_clicked);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}


//注册
void LoginWindow::on_registerButton_clicked()
{
    QString name = ui->nameEdit->text();
    QString password = ui->passwordEdit->text();
    QString role = "CommonAdmin";
    if(name == nullptr || password == nullptr)
    {
        QMessageBox::information(this,"注册","注册失败,账号或密码为空");
    }
    else if(!sql->registerUser(name,password,role))
    {
        qDebug()<<"failed";
        QMessageBox::information(this,"注册","注册失败，账号已存在");
    }
    else
    {
        qDebug()<<"successful";
        QMessageBox::information(this,"注册","注册成功");
    }
}



//登录
void LoginWindow::on_loginButton_clicked()
{
    MainWindow *homepage = new MainWindow;

    QString name = ui->nameEdit->text();
    QString password = ui->passwordEdit->text();

    if(name == nullptr || password == nullptr)
    {
        QMessageBox::information(this, "提示", "账号或密码输入为空\n请继续输入");
    }
    else if(!sql->loginUser(name,password))
    {
        qDebug()<<"failed";
        QMessageBox::information(this, "提示", "账号或密码输入错误\n请重新输入");
    }
    else
    {
        qDebug()<<"successful";
        this->close();
        homepage->show();
        //QMessageBox::information(this,"登录","登录成功");
    }
}

//退出
void LoginWindow::on_quitButton_clicked()
{
    this->close();
}

//密码显示
void LoginWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->passwordEdit->setEchoMode(QLineEdit::Password);
    }
    else
    {
        ui->passwordEdit->setEchoMode(QLineEdit::Normal);
    }
}

