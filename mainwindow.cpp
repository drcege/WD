#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->userLineEdit_0->setFocus();
    ui->loginBtn->setDefault(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginBtn_clicked()
{
    if(ui->userLineEdit_0->text().isEmpty())
    {
        QMessageBox::information(this,tr("请输入用户名！"),tr("请先输入用户名再登录！"),QMessageBox::Ok);
        ui->userLineEdit_0->setFocus();
    }
    else if(ui->pwdLineEdit_0->text().isEmpty())
    {
        QMessageBox::information(this,tr("请输入密码！"),tr("请先输入密码再登录！"),QMessageBox::Ok);
        ui->pwdLineEdit_0->setFocus();
    }
    else
    {
        if(ui->userLineEdit_0->text() == "admin" && ui->pwdLineEdit_0->text() == "123")
        {
            ui->stackedWidget->setCurrentIndex(2);
        }
        else
        {
            QMessageBox::warning(this,tr("登陆失败！"),tr("请输入正确的用户名和密码再登录！"),QMessageBox::Ok);
            ui->userLineEdit_0->clear();
            ui->pwdLineEdit_0->clear();
            ui->userLineEdit_0->setFocus();
        }
    }
}

void MainWindow::on_quitBtn_clicked()
{
    QApplication::quit();
}

void MainWindow::on_registerNowBtn_clicked()
{
    ui->userLineEdit_0->clear();
    ui->pwdLineEdit_0->clear();
    ui->stackedWidget->setCurrentIndex(1);
    ui->userLineEdit_1->setFocus();
    ui->registerBtn->setDefault(true);
}

void MainWindow::on_backBtn_clicked()
{
    ui->userLineEdit_1->clear();
    ui->pwdLineEdit_1->clear();
    ui->repaetPwdLineEdit->clear();
    ui->stackedWidget->setCurrentIndex(0);
    ui->userLineEdit_0->setFocus();
    ui->loginBtn->setDefault(true);
}
