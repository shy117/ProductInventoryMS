#include "userpage.h"
#include "ui_userpage.h"

UserPage::UserPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPage)
{
    ui->setupUi(this);
    creatUserPage();
}

UserPage::~UserPage()
{
    delete ui;
}

void UserPage::creatUserPage()
{
    //连接槽函数
    connect(ui->searchButton,&QPushButton::clicked,this,&UserPage::searchUserData);

    UserModel = new QSqlTableModel;
    UserModel->setTable("Manager");//选择数据表
    UserModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    UserModel->setHeaderData(0,Qt::Horizontal, "用户序号");
    UserModel->setHeaderData(1,Qt::Horizontal, "用户名");
    UserModel->setHeaderData(2,Qt::Horizontal, "账号");
    UserModel->setHeaderData(3,Qt::Horizontal, "密码");
    UserModel->setHeaderData(4,Qt::Horizontal, "职位");
    UserModel->select();

    ui->tableView->setModel(UserModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//使其不可编辑

}

//查询数据
void UserPage::searchUserData()
{
    QString id =  QString("Mno = '%1'").arg(ui->idEdit->text());
    QString name =  QString("Mname = '%1'").arg(ui->nameEdit->text());
    QString account = QString("Maccount = '%1'").arg(ui->accountEdit->text());
    QString role = QString("Mrole = '%1'").arg(ui->roleEdit->text());
    QString filterStr = "";
    if(!ui->idEdit->text().isEmpty())
        filterStr.append(id);
    if(!ui->nameEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(name);
    }
    if(!ui->accountEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(account);
    }
    if(!ui->roleEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(role);
    }


    UserModel->setFilter(filterStr);
    UserModel->select();
}
