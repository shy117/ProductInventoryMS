#include "stockpage.h"
#include "ui_stockpage.h"

StockPage::StockPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockPage)
{
    ui->setupUi(this);
    creatStockPage();

}

StockPage::~StockPage()
{
    delete ui;
}

void StockPage::creatStockPage()
{
    //连接槽函数
    connect(ui->addButton,&QPushButton::clicked,this,&StockPage::addStock);
    connect(ui->searchButton,&QPushButton::clicked,this,&StockPage::searchStockData);
    connect(ui->modifyButton,&QPushButton::clicked,this,&StockPage::modifyStock);
    connect(ui->deleteButton,&QPushButton::clicked,this,&StockPage::deleteStockData);

    StockModel = new QSqlTableModel;
    StockModel->setTable("stock");//选择数据表
    StockModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置保存策略为手动提交
    StockModel->setHeaderData(0,Qt::Horizontal, "序号");
    StockModel->setHeaderData(1,Qt::Horizontal, "产品名称");
    StockModel->setHeaderData(2,Qt::Horizontal, "所属类别");
    StockModel->setHeaderData(3,Qt::Horizontal, "产品数量");
    StockModel->setHeaderData(4,Qt::Horizontal, "产地");
    StockModel->setHeaderData(5,Qt::Horizontal, "制造商");
    StockModel->setHeaderData(6,Qt::Horizontal, "备注");
    StockModel->select();

    ui->tableView->setModel(StockModel);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//使其不可编辑

}

void StockPage::addStock()
{
    stockDialog = new addStockDialog(this);
    stockDialog->show();
    connect(stockDialog->addButton,&QPushButton::clicked,this,&StockPage::insertStockData);
}

//添加数据
void StockPage::insertStockData()
{
    QString stockName = stockDialog->nameEdit->text();
    QString stockcategory = stockDialog->categoryEdit->currentText();
    QString stockSpeci = stockDialog->speciEdit->text();
    QString stockAddr = stockDialog->addrEdit->currentText();
    QString stockManu = stockDialog->manuEdit->text();
    QString stockNote = stockDialog->noteEdit->text();

    QSqlQuery *query=new QSqlQuery;
    QString str = QString("insert into Stock values('%1', '%2', '%3','%4','%5','%6')").arg(stockName).arg(stockcategory).arg(stockSpeci).arg(stockAddr).arg(stockManu).arg(stockNote);
    if(stockName==nullptr)
    {
        qDebug()<<"failed";
        QMessageBox::information(this,"添加","添加失败");
    }
    else if(query->exec(str))
    {
        qDebug()<<"successful";
        QMessageBox::information(this,"添加","添加成功");
        StockModel->submitAll();
    }
    else
    {
        qDebug()<<"failed";
        QMessageBox::information(this,"添加","添加失败\n"+query->lastError().text());
    }
}

//查询数据
void StockPage::searchStockData()
{
    QString id =  QString("Sno = '%1'").arg(ui->idEdit->text());
    QString name =  QString("Sname = '%1'").arg(ui->nameEdit->text());
    QString cate = QString("Scategory = '%1'").arg(ui->cateEdit->currentText());
    QString addr = QString("Saddr = '%1'").arg(ui->addrEdit->currentText());
    QString count = QString("Scount = '%1'").arg(ui->countEdit->text());
    QString manu = QString("Smanu = '%1'").arg(ui->manuEdit->text());
    QString filterStr = "";
    if(!ui->idEdit->text().isEmpty())
        filterStr.append(id);
    if(!ui->nameEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(name);
    }
    if(!ui->cateEdit->currentText().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(cate);
    }
    if(!ui->addrEdit->currentText().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(addr);
    }
    if(!ui->countEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(count);
    }
    if(!ui->manuEdit->text().isEmpty())
    {
        if(!filterStr.isEmpty())
            filterStr.append(" and ");
        filterStr.append(manu);
    }

    StockModel->setFilter(filterStr);
    StockModel->select();
}

//选中一行的数据
void StockPage::modifyStock()
{
    stockModifyDialog = new modifyStockDialog(this);
    int curRow = ui->tableView->currentIndex().row();
    QSqlRecord record = StockModel->record(curRow);

    QString name = record.value(1).toString();
    stockModifyDialog->nameEdit->setText(name);
    QString category = record.value(2).toString();
    stockModifyDialog->categoryEdit->setCurrentText(category);
    QString speci = record.value(3).toString();
    stockModifyDialog->speciEdit->setText(speci);
    QString address = record.value(4).toString();
    stockModifyDialog->addrEdit->setCurrentText(address);
    QString manu = record.value(5).toString();
    stockModifyDialog->manuEdit->setText(manu);
    QString note = record.value(6).toString();
    stockModifyDialog->noteEdit->setText(note);

    connect(stockModifyDialog->modifyButton,&QPushButton::clicked,this,&StockPage::modifyStockData);
    stockModifyDialog->show();
}

//修改数据
void StockPage::modifyStockData()
{
    QString stockName = stockModifyDialog->nameEdit->text();
    QString stockcategory = stockModifyDialog->categoryEdit->currentText();
    QString stockSpeci = stockModifyDialog->speciEdit->text();
    QString stockAddr = stockModifyDialog->addrEdit->currentText();
    QString stockManu = stockModifyDialog->manuEdit->text();
    QString stockNote = stockModifyDialog->noteEdit->text();

    int curRow = ui->tableView->currentIndex().row();
    QSqlRecord record = StockModel->record(curRow);
    record.setValue(1,stockName);
    record.setValue(2,stockcategory);
    record.setValue(3,stockSpeci);
    record.setValue(4,stockAddr);
    record.setValue(5,stockManu);
    record.setValue(6,stockNote);

    if(StockModel->setRecord(curRow, record))
    {
        stockModifyDialog->close();
        StockModel->submitAll();
        ui->tableView->setEnabled(true);
    }
}

//删除数据
void StockPage::deleteStockData()
{
    int curRow = ui->tableView->currentIndex().row();
    StockModel->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定删除当前行吗？"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No)
        StockModel->revertAll(); //如果不删除，则撤销
    else
        StockModel->submitAll(); //否则提交，在数据库中删除该行
}
