#include "addinstockdialog.h"
#include <QGridLayout>

addInStockDialog::addInStockDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("入库"));
    QLabel *snoLabel = new QLabel("产品编号");
    snoEdit = new QLineEdit;
    QLabel *snameLabel = new QLabel("产品名称");
    snameEdit = new QLineEdit;
    QLabel *icountLabel = new QLabel("入库数量");
    icountEdit = new QLineEdit;
    QLabel *agentLabel = new QLabel("进货人");
    agentEdit = new QLineEdit;
    inButton = new QPushButton("入库");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(snoLabel,0,0);//产品编号
    layout->addWidget(snoEdit,0,1);
    layout->addWidget(snameLabel,1,0);//产品名称
    layout->addWidget(snameEdit,1,1);
    layout->addWidget(icountLabel,2,0);//入库数量
    layout->addWidget(icountEdit,2,1);
    layout->addWidget(agentLabel,3,0);//进货人
    layout->addWidget(agentEdit,3,1);
    layout->addWidget(inButton,4,1);

    setLayout(layout);
    setWindowModality(Qt::WindowModal);
}

addInStockDialog::~addInStockDialog()
{

}
