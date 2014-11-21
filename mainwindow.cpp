#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    ui->lineEdit_user_login->setFocus();
    ui->pushButton_login->setDefault(true);
    ui->action_user->setDisabled(true);
    ui->action_logout->setDisabled(true);
    ui->treeWidget->expandAll();
    loadData();

    QTreeWidgetItem* treeParent = ui->treeWidget->topLevelItem(0);
    for(int p = 0; p < vecFood.count(); ++p)
    {
        addTreeNode(treeParent, &(vecFood[p]));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loadData()
{
    vecFood.push_back(Food(1, "蛋糕", 20, 3.5, "戈策", QDate::fromString("2014/11/1", "yyyy/M/d"), QDate::fromString("2014/11/20", "yyyy/M/d"), QDate::fromString("2014/11/15", "yyyy/M/d")));
    vecFood.push_back(Food(2, "鸡蛋", 35, 1.5, "戈策", QDate::fromString("2014/11/5", "yyyy/M/d"), QDate::fromString("2014/11/30", "yyyy/M/d"), QDate::fromString("2014/11/28", "yyyy/M/d")));
    return true;
}

int MainWindow::checkUser(QString userName, QString password)
{
    //QString valuePwd = allAccount.value(userName);
    for(QVector<Buyer>::iterator iter = vecBuyer.begin(); iter != vecBuyer.end(); ++iter)
    {
        if(userName == iter->getUserName())
        {
            if(password == iter->getPassword())
                return BUYER_Y;
            else
                return BUYER_N;
        }
    }
    for(QVector<Member>::iterator iter = vecMember.begin(); iter != vecMember.end(); ++iter)
    {
        if(userName == iter->getUserName())
        {
            if(password == iter->getPassword())
                return MEMBER_Y;
            else
                return MEMBER_N;
        }
    }
    for(QVector<Seller>::iterator iter = vecSeller.begin(); iter != vecSeller.end(); ++iter)
    {
        if(userName == iter->getUserName())
        {
            if(password == iter->getPassword())
                return SELLER_Y;
            else
                return SELLER_N;
        }
    }
    return NO_EXIST;
}

void MainWindow::addTreeNode(QTreeWidgetItem *parent, Food* food)
{
    QTreeWidgetItem * item = new QTreeWidgetItem(QStringList() << "" << food->getFoodName() << QString::number(food->getAmount()) << QString::number(food->getPrice()) << food->getOwner() << food->getProduceDate().toString("yyyy/MM/dd") << food->getValidityDate().toString("yyyy/MM/dd") << food->getReduceDate().toString("yyyy/MM/dd"));
    parent->addChild(item);
}

void MainWindow::addTreeNode(QTreeWidgetItem *parent, Electronics * elect)
{
//    QTreeWidgetItem * item = new QTreeWidgetItem(QStringList() << "" << elect->getFoodName() << QString::number(elect->getAmount()) << QString::number(elect->getPrice()) << elect->getOwner() << elect->getProduceDate());
//    parent->addChild(item);
}

void MainWindow::addTreeNode(QTreeWidgetItem *parent, DailyNecessities *daily)
{
//    QTreeWidgetItem * item = new QTreeWidgetItem(QStringList() << "" << daily->getFoodName() << QString::number(daily->getAmount()) << QString::number(daily->getPrice()) << daily->getOwner() << daily->getProduceDate());
//    parent->addChild(item);
}

void MainWindow::on_pushButton_login_clicked()
{
    QString user = ui->lineEdit_user_login->text();
    QString pwd = ui->lineEdit_pwd_login->text();
    ui->lineEdit_user_login->clear();
    ui->lineEdit_pwd_login->clear();
    switch (checkUser(user, pwd))
    {
    case BUYER_Y:
        curUser = new Buyer(++USERID, user, pwd);
        ui->stackedWidget_2->setCurrentWidget(ui->page_buyer);
        ui->action_user->setEnabled(true);
        ui->action_logout->setEnabled(true);
        ui->stackedWidget->setCurrentWidget(ui->mainPage);
        MainWindow::setWindowState(Qt::WindowMaximized);
        break;
    case MEMBER_Y:
        curUser = new Member(++USERID, user, pwd);
        ui->stackedWidget_2->setCurrentWidget(ui->page_buyer);
        ui->action_user->setEnabled(true);
        ui->action_logout->setEnabled(true);
        ui->stackedWidget->setCurrentWidget(ui->mainPage);
        MainWindow::setWindowState(Qt::WindowMaximized);
        break;
    case SELLER_Y:
        curUser = new Seller(++USERID, user, pwd); //登陆成功
        ui->stackedWidget_2->setCurrentWidget(ui->page_seller);
        ui->action_user->setEnabled(true);
        ui->action_logout->setEnabled(true);
        ui->stackedWidget->setCurrentWidget(ui->mainPage);
        MainWindow::setWindowState(Qt::WindowMaximized);
        break;
    case NO_EXIST:
        QMessageBox::warning(this,tr("登陆失败！"),tr("用户名不存在！"),QMessageBox::Ok);
        ui->lineEdit_user_login->setFocus();
        break;
    case BUYER_N: case MEMBER_N: case SELLER_N:
        QMessageBox::warning(this,tr("登陆失败！"),tr("密码错误！"),QMessageBox::Ok);
        ui->lineEdit_user_login->setFocus();
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_quit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_now_clicked()
{
    ui->lineEdit_user_login->clear();
    ui->lineEdit_pwd_login->clear();
    ui->stackedWidget->setCurrentWidget(ui->registerPage);
    ui->lineEdit_user_register->setFocus();
}

void MainWindow::on_pushButton_back_clicked()
{
    ui->lineEdit_user_register->clear();
    ui->lineEdit_pwd_register->clear();
    ui->lineEdit_pwd_repeat->clear();
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    ui->lineEdit_user_login->setFocus();
}

void MainWindow::on_action_logout_triggered()
{
    MainWindow::setWindowState(Qt::WindowNoState);
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    ui->lineEdit_user_login->setFocus();
    ui->pushButton_login->setDefault(true);
}

void MainWindow::on_action_exit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_register_clicked()
{
    QString user = ui->lineEdit_user_register->text();
    if(checkUser(user) != NO_EXIST)
    {
        QMessageBox::information(this,tr("注册失败！"),tr("用户名已存在！"),QMessageBox::Ok);
        ui->lineEdit_user_register->clear();
        ui->lineEdit_user_register->setFocus();
    }
    else
    {
        QString pwd = ui->lineEdit_pwd_register->text();
        QString repeatPwd = ui->lineEdit_pwd_repeat->text();
        if(pwd != repeatPwd)
        {
            QMessageBox::information(this,tr("注册失败！"),tr("两次密码不一致！"),QMessageBox::Ok);
            ui->lineEdit_pwd_register->setFocus();
        }
        else
        {
            if(ui->buttonGroup->checkedButton() == ui->radioButton_buyer)    //买家
            {
                Buyer curBuyer(++USERID, user, pwd);
                vecBuyer.push_back(curBuyer);
            }
            else if(ui->buttonGroup->checkedButton() == ui->radioButton_seller)
            {
                Seller curSeller(++USERID, user, pwd);
                vecSeller.push_back(curSeller);
            }
            //allAccount.insert(user, pwd);
            QMessageBox::information(this,tr("注册成功！"),tr("恭喜你 ^_^ 注册成功！"),QMessageBox::Ok);
            ui->lineEdit_user_register->clear();
            ui->stackedWidget->setCurrentWidget(ui->loginPage);
            ui->lineEdit_user_login->setFocus();
        }
    }
    ui->lineEdit_pwd_register->clear();
    ui->lineEdit_pwd_repeat->clear();
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox::about(this, tr("关于"), tr("作者：戈策 ~^_^~\nQQ：1334527295    "));
}

void MainWindow::on_action_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_lineEdit_user_login_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() || ui->lineEdit_pwd_login->text().isEmpty())
        ui->pushButton_login->setDisabled(true);
    else
        ui->pushButton_login->setEnabled(true);
}

void MainWindow::on_lineEdit_pwd_login_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() || ui->lineEdit_user_login->text().isEmpty())
        ui->pushButton_login->setDisabled(true);
    else
        ui->pushButton_login->setEnabled(true);
}

void MainWindow::on_lineEdit_user_register_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() || ui->lineEdit_pwd_register->text().isEmpty() || ui->lineEdit_pwd_repeat->text().isEmpty() || (ui->buttonGroup->checkedId() == -1))
        ui->pushButton_register->setDisabled(true);
    else
        ui->pushButton_register->setEnabled(true);
}

void MainWindow::on_lineEdit_pwd_register_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() || ui->lineEdit_user_register->text().isEmpty() || ui->lineEdit_pwd_repeat->text().isEmpty() || (ui->buttonGroup->checkedId() == -1))
        ui->pushButton_register->setDisabled(true);
    else
        ui->pushButton_register->setEnabled(true);
}

void MainWindow::on_lineEdit_pwd_repeat_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() || ui->lineEdit_user_register->text().isEmpty() || ui->lineEdit_pwd_register->text().isEmpty() || (ui->buttonGroup->checkedId() == -1))
        ui->pushButton_register->setDisabled(true);
    else
        ui->pushButton_register->setEnabled(true);
}
