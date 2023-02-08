#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <QProcess>
#include <QMessageBox>
#include "mainwindow.h"
#include "sqlserver.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    QMap<QString, QString> manager_data;

private slots:

    void on_loginButton_clicked();

    void on_quitButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_registerButton_clicked();



private:
    Ui::LoginWindow *ui;
    SqlServer *sql;
};
#endif // LOGINWINDOW_H
