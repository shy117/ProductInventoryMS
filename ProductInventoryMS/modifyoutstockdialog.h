#ifndef MODIFYOUTSTOCKDIALOG_H
#define MODIFYOUTSTOCKDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class modifyOutStockDialog : public QDialog
{
    Q_OBJECT

public:
    modifyOutStockDialog(QWidget *parent = nullptr);
    ~modifyOutStockDialog();

    QLineEdit *snoEdit;
    QLineEdit *snameEdit;
    QLineEdit *ocountEdit;
    QLineEdit *clientEdit;
    QPushButton *modifyOutButton;
};


#endif // MODIFYOUTSTOCKDIALOG_H
