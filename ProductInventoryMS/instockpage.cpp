#include "instockpage.h"
#include "ui_instockpage.h"

InStockPage::InStockPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InStockPage)
{
    ui->setupUi(this);
    creatInStockPage();

}

InStockPage::~InStockPage()
{
    delete ui;
}

void InStockPage::creatInStockPage()
{
    //连接槽函数
    connect(ui->addButton,&QPushButton::clicked,this,&InStockPage::addInStock);
    connect(ui->searchButton,&QPushButton::clicked,this,&InStockPage::searchInStockData);
    connect(ui->modifyButton,&QPushButton::clicked,this,&InStockPage::modifyInStock);
    connect(ui->deleteButton,&QPushButton::clicked,this,&InStockPage::deleteInStockData);

    inStockModel = new QSqlTableModel;
    inStockModel->setTable("InStock");//选择数据表
    inStockModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    inStockModel->setHeaderData(0,Qt::Horizontal, "入库编号");
    inStockModel->setHeaderData(1,Qt::Horizontal, "产品编号");
    inStockModel->setHeaderData(2,Qt::Horizontal, "产品名称");
    inStockModel->setHeaderData(3,Qt::Horizontal, "入库数量");
    inStockModel->setHeaderData(4,Qt::Horizontal, "入库时间");
    inStockModel->setHeaderData(5,Qt::Horizontal, "进货人");
    inStockModel->select();

    ui->tableView->setModel(inStockModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//使其不可编辑

}

void InStockPage::addInStock()
{
    inStockDialog = new addInStockDialog(this);
    inStockDialog->show();
    connect(inStockDialog->inButton,&QPushButton::clicked,this,&InStockPage::insertInStockData);
}

//入库
void InStockPage::insertInStockData()
{
    QString Sno = inStockDialog->snoEdit->text();
    QString Sname = inStockDialog->snameEdit->text();
    QString Icount = inStockDialog->icountEdit->text();
    QString Iagent = inStockDialog->agentEdit->text();

    QSqlQuery *query=new QSqlQuery;
    QString str = QString("insert into InStock values('%1', '%2', '%3',getdate(),'%4')").arg(Sno).arg(Sname).arg(Icount).arg(Iagent);
    if(Sno==nullptr)
    {
        qDebug()<<"failed";
        QMessageBox::information(this,"入库","入库失败");
    }
    else if(query->exec(str))
    {
        qDebug()<<"successful";
        QMessageBox::information(this,"入库","入库成功");
        inStockModel->submitAll();
    }
    else
    {
        qDebug()<<"failed";
        QMessageBox::information(this,"入库","入库失败，该产品编号不存在");
    }
}

//查询数据
void InStockPage::searchInStockData()
{
    QString Ino =  QString("Ino = '%1'").arg(ui->inIdEdit->text());
    QString Sno =  QString("Sno = '%1'").arg(ui->idEdit->text());
    QString name =  QString("Sname = '%1'").arg(ui->nameEdit->text());
    QString count = QString("Icount = '%1'").arg(ui->inCountEdit->text());
    QString time = QString("Itime = '%1'").arg(ui->inTimeEdit->text());
    QString agent = QString("Iagent = '%1'").arg(ui->inAgentEdit->text());
    QString filterStr = "";
    if(!ui->inIdEdit->text().isEmpty())
        filterStr.append(Ino);
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
    if(!ui->inCountEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(count);
    }
    if(!ui->inTimeEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(time);
    }
    if(!ui->inAgentEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(agent);
    }

    inStockModel->setFilter(filterStr);
    inStockModel->select();
}

//选中一行的数据
void InStockPage::modifyInStock()
{
    inStockModifyDialog = new modifyInStockDialog(this);
    int curRow = ui->tableView->currentIndex().row();
    QSqlRecord record = inStockModel->record(curRow);

    QString sno = record.value(1).toString();
    inStockModifyDialog->snoEdit->setText(sno);
    QString sname = record.value(2).toString();
    inStockModifyDialog->snameEdit->setText(sname);
    QString icount = record.value(3).toString();
    inStockModifyDialog->icountEdit->setText(icount);
    QString iagent = record.value(5).toString();
    inStockModifyDialog->agentEdit->setText(iagent);

    connect(inStockModifyDialog->modifyInButton,&QPushButton::clicked,this,&InStockPage::modifyInStockData);
    inStockModifyDialog->show();
}

//修改数据
void InStockPage::modifyInStockData()
{
    QString sno = inStockModifyDialog->snoEdit->text();
    QString sname = inStockModifyDialog->snameEdit->text();
    QString icount = inStockModifyDialog->icountEdit->text();
    QString iagent = inStockModifyDialog->agentEdit->text();

    int curRow = ui->tableView->currentIndex().row();
    QSqlRecord record = inStockModel->record(curRow);
    record.setValue(1,sno);
    record.setValue(2,sname);
    record.setValue(3,icount);
    record.setValue(5,iagent);

    if(inStockModel->setRecord(curRow, record))
    {
        inStockModifyDialog->close();
        inStockModel->submitAll();
        ui->tableView->setEnabled(true);
    }
}

//删除数据
void InStockPage::deleteInStockData()
{
    int curRow = ui->tableView->currentIndex().row();
    inStockModel->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
        inStockModel->revertAll(); //如果不删除，则撤销
    else
        inStockModel->submitAll(); //否则提交，在数据库中删除该行
}
