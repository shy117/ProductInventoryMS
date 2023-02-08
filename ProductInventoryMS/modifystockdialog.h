#ifndef MODIFYSTOCKDIALOG_H
#define MODIFYSTOCKDIALOG_H


#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>

class modifyStockDialog : public QDialog
{
    Q_OBJECT

public:
    modifyStockDialog(QWidget *parent = nullptr);
    ~modifyStockDialog();

    QLineEdit *nameEdit;
    QComboBox *addrEdit;
    QComboBox *categoryEdit;
    QLineEdit *manuEdit;
    QLineEdit *noteEdit;
    QLineEdit *speciEdit;
    QPushButton *modifyButton;
};

#endif // MODIFYSTOCKDIALOG_H
