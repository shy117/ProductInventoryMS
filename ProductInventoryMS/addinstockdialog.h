#ifndef ADDINSTOCKDIALOG_H
#define ADDINSTOCKDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class addInStockDialog : public QDialog
{
    Q_OBJECT

public:
    addInStockDialog(QWidget *parent = nullptr);
    ~addInStockDialog();

    QLineEdit *snoEdit;
    QLineEdit *snameEdit;
    QLineEdit *icountEdit;
    QLineEdit *agentEdit;
    QPushButton *inButton;
};

#endif // ADDINSTOCKDIALOG_H
