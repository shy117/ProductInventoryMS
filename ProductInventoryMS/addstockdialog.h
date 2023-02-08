#ifndef ADDSTOCKDIALOG_H
#define ADDSTOCKDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class addStockDialog : public QDialog
{
    Q_OBJECT

public:
    addStockDialog(QWidget *parent = nullptr);
    ~addStockDialog();

    QLineEdit *nameEdit;
    QComboBox *addrEdit;
    QComboBox *categoryEdit;
    QLineEdit *manuEdit;
    QLineEdit *noteEdit;
    QLineEdit *speciEdit;
    QPushButton *addButton;
};

#endif // ADDSTOCKDIALOG_H
