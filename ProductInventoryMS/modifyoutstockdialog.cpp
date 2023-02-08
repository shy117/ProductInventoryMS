#include "modifyoutstockdialog.h"
#include <QGridLayout>

modifyOutStockDialog::modifyOutStockDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("修改"));
    QLabel *snoLabel = new QLabel("产品编号");
    snoEdit = new QLineEdit;
    QLabel *snameLabel = new QLabel("产品名称");
    snameEdit = new QLineEdit;
    QLabel *ocountLabel = new QLabel("出库数量");
    ocountEdit = new QLineEdit;
    QLabel *clientLabel = new QLabel("客户");
    clientEdit = new QLineEdit;
    modifyOutButton = new QPushButton("修改");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(snoLabel,0,0);//产品编号
    layout->addWidget(snoEdit,0,1);
    layout->addWidget(snameLabel,1,0);//产品名称
    layout->addWidget(snameEdit,1,1);
    layout->addWidget(ocountLabel,2,0);//出库数量
    layout->addWidget(ocountEdit,2,1);
    layout->addWidget(clientLabel,3,0);//客户
    layout->addWidget(clientEdit,3,1);
    layout->addWidget(modifyOutButton,4,1);

    setLayout(layout);
    setWindowModality(Qt::WindowModal);
}

modifyOutStockDialog::~modifyOutStockDialog()
{

}
