#ifndef ADDOUTSTOCKDIALOG_H
#define ADDOUTSTOCKDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class addOutStockDialog : public QDialog
{
    Q_OBJECT

public:
    addOutStockDialog(QWidget *parent = nullptr);
    ~addOutStockDialog();

    QLineEdit *snoEdit;
    QLineEdit *snameEdit;
    QLineEdit *ocountEdit;
    QLineEdit *clientEdit;
    QPushButton *outButton;
};

#endif // ADDOUTSTOCKDIALOG_H
