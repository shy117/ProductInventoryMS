#ifndef MODIFYINSTOCKDIALOG_H
#define MODIFYINSTOCKDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class modifyInStockDialog : public QDialog
{
    Q_OBJECT

public:
    modifyInStockDialog(QWidget *parent = nullptr);
    ~modifyInStockDialog();

    QLineEdit *snoEdit;
    QLineEdit *snameEdit;
    QLineEdit *icountEdit;
    QLineEdit *agentEdit;
    QPushButton *modifyInButton;
};

#endif // MODIFYINSTOCKDIALOG_H
