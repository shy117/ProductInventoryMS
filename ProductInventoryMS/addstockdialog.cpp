#include "addstockdialog.h"
#include <QGridLayout>

addStockDialog::addStockDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("添加"));
    QLabel *nameLabel = new QLabel("产品名称");
    nameEdit = new QLineEdit;
    QLabel *categoryLabel = new QLabel("所属类目");
    categoryEdit = new QComboBox;
    QStringList categoryList;
    categoryList<<""<<"家电"<<"数码"<<"家具"<<"服饰"<<"食品"<<"其他";
    categoryEdit->addItems(categoryList);
    QLabel *speciLabel = new QLabel("产品数量");
    speciEdit = new QLineEdit;
    QLabel *addrLabel = new QLabel("产地");
    addrEdit = new QComboBox;
    QStringList addrList;
    addrList<<""<<"北京"<<"上海"<<"浙江"<<"安徽"<<"广州"<<"深圳"<<"重庆"<<"其他";
    addrEdit->addItems(addrList);
    QLabel *manuLabel = new QLabel("制造商");
    manuEdit = new QLineEdit;
    QLabel *noteLabel = new QLabel("备注");
    noteEdit = new QLineEdit;
    addButton = new QPushButton("添加");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel,0,0);//产品名称
    layout->addWidget(nameEdit,0,1);
    layout->addWidget(categoryLabel,1,0);//所属类目
    layout->addWidget(categoryEdit,1,1);
    layout->addWidget(speciLabel,2,0);//产品数量
    layout->addWidget(speciEdit,2,1);
    layout->addWidget(addrLabel,3,0);//产地
    layout->addWidget(addrEdit,3,1);
    layout->addWidget(manuLabel,4,0);//制造商
    layout->addWidget(manuEdit,4,1);
    layout->addWidget(noteLabel,5,0);//备注
    layout->addWidget(noteEdit,5,1);
    layout->addWidget(addButton,6,1);

    setLayout(layout);
    setWindowModality(Qt::WindowModal);
}

addStockDialog::~addStockDialog()
{

}
