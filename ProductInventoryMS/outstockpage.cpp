#include "outstockpage.h"
#include "ui_outstockpage.h"

OutStockPage::OutStockPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutStockPage)
{
    ui->setupUi(this);
    creatOutStockPage();

}

OutStockPage::~OutStockPage()
{
    delete ui;
}

void OutStockPage::creatOutStockPage()
{
    //连接槽函数
    connect(ui->addButton,&QPushButton::clicked,this,&OutStockPage::addOutStock);
    connect(ui->searchButton,&QPushButton::clicked,this,&OutStockPage::searchOutStockData);
    connect(ui->modifyButton,&QPushButton::clicked,this,&OutStockPage::modifyOutStock);
    connect(ui->deleteButton,&QPushButton::clicked,this,&OutStockPage::deleteOutStockData);

    outStockModel = new QSqlTableModel;
    outStockModel->setTable("OutStock");//选择数据表
    outStockModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    outStockModel->setHeaderData(0,Qt::Horizontal, "出库编号");
    outStockModel->setHeaderData(1,Qt::Horizontal, "产品编号");
    outStockModel->setHeaderData(2,Qt::Horizontal, "产品名称");
    outStockModel->setHeaderData(3,Qt::Horizontal, "出库数量");
    outStockModel->setHeaderData(4,Qt::Horizontal, "出库时间");
    outStockModel->setHeaderData(5,Qt::Horizontal, "客户");
    outStockModel->select();

    ui->tableView->setModel(outStockModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//使其不可编辑

}

void OutStockPage::addOutStock()
{
    outStockDialog = new addOutStockDialog(this);
    outStockDialog->show();
    connect(outStockDialog->outButton,&QPushButton::clicked,this,&OutStockPage::insertOutStockData);
}

//出库
void OutStockPage::insertOutStockData()
{
    QString Sno = outStockDialog->snoEdit->text();
    QString Sname = outStockDialog->snameEdit->text();
    QString Ocount = outStockDialog->ocountEdit->text();
    QString Oagent = outStockDialog->clientEdit->text();

    QSqlQuery *query=new QSqlQuery;
    QString str = QString("insert into OutStock values('%1', '%2', '%3',getdate(),'%4')").arg(Sno).arg(Sname).arg(Ocount).arg(Oagent);
    if(Sno==nullptr)
    {
        qDebug()<<"failed";
        QMessageBox::information(this,"出库","出库失败");
    }
    else if(query->exec(str))
    {
        qDebug()<<"successful";
        QMessageBox::information(this,"出库","出库成功");
        outStockModel->submitAll();
    }
    else
    {
        qDebug()<<"failed";
        QMessageBox::information(this,"出库","出库失败，产品库存不足");
    }
}

//查询数据
void OutStockPage::searchOutStockData()
{
    QString Ono =  QString("Ono = '%1'").arg(ui->outIdEdit->text());
    QString Sno =  QString("Sno = '%1'").arg(ui->idEdit->text());
    QString name =  QString("Sname = '%1'").arg(ui->nameEdit->text());
    QString count = QString("Ocount = '%1'").arg(ui->outCountEdit->text());
    QString time = QString("Otime = '%1'").arg(ui->outTimeEdit->text());
    QString client = QString("Oclient = '%1'").arg(ui->clientEdit->text());
    QString filterStr = "";
    if(!ui->outIdEdit->text().isEmpty())
        filterStr.append(Ono);
    if(!ui->idEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(Sno);
    }
    if(!ui->nameEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(name);
    }
    if(!ui->outCountEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(count);
    }
    if(!ui->outTimeEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(time);
    }
    if(!ui->clientEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(client);
    }

    outStockModel->setFilter(filterStr);
    outStockModel->select();
}

//选中一行的数据
void OutStockPage::modifyOutStock()
{
    outStockModifyDialog = new modifyOutStockDialog(this);
    int curRow = ui->tableView->currentIndex().row();
    QSqlRecord record = outStockModel->record(curRow);

    QString ono = record.value(1).toString();
    outStockModifyDialog->snoEdit->setText(ono);
    QString sname = record.value(2).toString();
    outStockModifyDialog->snameEdit->setText(sname);
    QString ocount = record.value(3).toString();
    outStockModifyDialog->ocountEdit->setText(ocount);
    QString oclient = record.value(5).toString();
    outStockModifyDialog->clientEdit->setText(oclient);

    connect(outStockModifyDialog->modifyOutButton,&QPushButton::clicked,this,&OutStockPage::modifyOutStockData);
    outStockModifyDialog->show();
}

//修改数据
void OutStockPage::modifyOutStockData()
{
    QString ono = outStockModifyDialog->snoEdit->text();
    QString sname = outStockModifyDialog->snameEdit->text();
    QString ocount = outStockModifyDialog->ocountEdit->text();
    QString oclient = outStockModifyDialog->clientEdit->text();

    int curRow = ui->tableView->currentIndex().row();
    QSqlRecord record = outStockModel->record(curRow);
    record.setValue(1,ono);
    record.setValue(2,sname);
    record.setValue(3,ocount);
    record.setValue(5,oclient);

    if(outStockModel->setRecord(curRow, record))
    {
        outStockModifyDialog->close();
        outStockModel->submitAll();
        ui->tableView->setEnabled(true);
    }
}

//删除数据
void OutStockPage::deleteOutStockData()
{
    int curRow = ui->tableView->currentIndex().row();
    outStockModel->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
        outStockModel->revertAll(); //如果不删除，则撤销
    else
        outStockModel->submitAll(); //否则提交，在数据库中删除该行
}
