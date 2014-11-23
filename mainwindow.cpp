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
    treeParent = ui->treeWidget->topLevelItem(1);
    for(int p = 0; p < vecElectronics.count(); ++p)
    {
        addTreeNode(treeParent, &(vecElectronics[p]));
    }
    treeParent = ui->treeWidget->topLevelItem(2);
    for(int p = 0; p < vecDailyNecessities.count(); ++p)
    {
        addTreeNode(treeParent, &(vecDailyNecessities[p]));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loadData()
{
    vecFood.push_back(Food(1, "蛋糕", 20, 20.0, "戈策", QDate::fromString("2014/11/1", "yyyy/M/d"), QDate::fromString("2014/11/20", "yyyy/M/d"), QDate::fromString("2014/11/15", "yyyy/M/d"), 0.2));
    vecFood.push_back(Food(2, "鸡蛋", 35, 1.5, "戈策", QDate::fromString("2014/11/5", "yyyy/M/d"), QDate::fromString("2014/11/30", "yyyy/M/d"), QDate::fromString("2014/11/28", "yyyy/M/d"), 0.2));
    vecFood.push_back(Food(3, "面包", 10, 3.5, "戈策", QDate::fromString("2014/11/20", "yyyy/M/d"), QDate::fromString("2014/11/28", "yyyy/M/d"), QDate::fromString("2014/11/25", "yyyy/M/d"), 0.2));
    vecFood.push_back(Food(4, "火腿", 30, 2.0, "戈策", QDate::fromString("2014/11/1", "yyyy/M/d"), QDate::fromString("2014/11/30", "yyyy/M/d"), QDate::fromString("2014/11/20", "yyyy/M/d"), 0.2));

    vecElectronics.push_back(Electronics(5, "iphone4s", 50, 2060.0, "戈策", QDate::fromString("2014/1/1","yyyy/M/d"), QDate::fromString("2016/1/1", "yyyy/M/d"), 0.1));
    vecElectronics.push_back(Electronics(6, "iphone5c", 50, 2788.0, "戈策", QDate::fromString("2014/1/1","yyyy/M/d"), QDate::fromString("2016/1/1", "yyyy/M/d"), 0.1));
    vecElectronics.push_back(Electronics(7, "iphone6", 50, 5288.0, "戈策", QDate::fromString("2014/1/1","yyyy/M/d"), QDate::fromString("2016/1/1", "yyyy/M/d"), 0.1));
    vecElectronics.push_back(Electronics(8, "iphone6 plus", 50, 5600.0, "戈策", QDate::fromString("2014/1/1","yyyy/M/d"), QDate::fromString("2016/1/1", "yyyy/M/d"), 0.1));

    vecDailyNecessities.push_back(DailyNecessities(9, "牙刷", 500, 3.5, "戈策", QDate::fromString("2014/10/1", "yyyy/M/d"), QDate::fromString("2014/12/31", "yyyy/M/d")));

    return true;
}

User* MainWindow::findUser(QString userName)
{
    for(int i = 0; i < vecBuyer.size(); ++i)
    {
        if(userName == vecBuyer[i].getUserName())
            return &vecBuyer[i];
    }
    for(int i = 0; i < vecMember.size(); ++i)
    {
        if(userName == vecMember[i].getUserName())
            return &vecMember[i];
    }
    for(int i = 0; i < vecSeller.size(); ++i)
    {
        if(userName == vecSeller[i].getUserName())
            return &vecSeller[i];
    }
    return Q_NULLPTR;
}

void MainWindow::addTreeNode(QTreeWidgetItem *parent, Food* food)
{
    QStringList sl;
    sl << "" << food->getFoodName() << QString::number(food->getAmount()) << QString::number(food->getPrice(),'f',1) << QString::number(food->reducedPrice(),'f',1) << food->getOwner() << food->getProduceDate().toString("yyyy/MM/dd") << food->getValidityDate().toString("yyyy/MM/dd") << food->getReduceDate().toString("yyyy/MM/dd") << QString::number(food->getReduceRate(),'f',1);
    QTreeWidgetItem * item = new QTreeWidgetItem(sl);
    parent->addChild(item);
}

void MainWindow::addTreeNode(QTreeWidgetItem *parent, Electronics * elect)
{
    QStringList sl;
    sl << "" << elect->getFoodName() << QString::number(elect->getAmount()) << QString::number(elect->getPrice(),'f',1) << QString::number(elect->reducedPrice(),'f',1) << elect->getOwner() << elect->getProduceDate().toString("yyyy/MM/dd") << elect->getValidityDate().toString("yyyy/MM/dd") << "-" << QString::number(elect->getRuduceRate(),'f',1);
    QTreeWidgetItem * item = new QTreeWidgetItem(sl);
    parent->addChild(item);
}

void MainWindow::addTreeNode(QTreeWidgetItem *parent, DailyNecessities *daily)
{
    QStringList sl;
    sl << "" << daily->getFoodName() << QString::number(daily->getAmount()) << QString::number(daily->getPrice(),'f',1) << QString::number(daily->reducedPrice(),'f',1) << daily->getOwner() << daily->getProduceDate().toString("yyyy/MM/dd") << daily->getValidityDate().toString("yyyy/MM/dd") << "-" << "-";
    QTreeWidgetItem * item = new QTreeWidgetItem(sl);
    parent->addChild(item);
}

void MainWindow::on_pushButton_login_clicked()
{
    QString user = ui->lineEdit_user_login->text();
    QString pwd = ui->lineEdit_pwd_login->text();

    curUser = findUser(user);
    if(curUser == Q_NULLPTR)
    {
        QMessageBox::warning(this,tr("登陆失败！"),tr("用户名不存在！"),QMessageBox::Ok);
        ui->lineEdit_user_login->clear();
        ui->lineEdit_pwd_login->clear();
        ui->lineEdit_user_login->setFocus();
        return;
    }
    else
    {
        if(pwd == curUser->getPassword())    // 登陆成功
        {
            MainWindow::setWindowState(Qt::WindowMaximized);
            ui->action_user->setEnabled(true);
            ui->action_logout->setEnabled(true);
            ui->stackedWidget->setCurrentWidget(ui->mainPage);

            if(BUYER_Y == curUser->getClass())
            {
                ui->stackedWidget_2->setCurrentWidget(ui->page_buyer);
            }
            else if(MEMBER_Y == curUser->getClass())
            {
                ui->lineEdit_discount->setText(QString::number(10 - (dynamic_cast<Member*>(curUser))->getLevel()/10.0));
                ui->stackedWidget_2->setCurrentWidget(ui->page_buyer);
            }
            else    //卖家
            {
                ui->stackedWidget_2->setCurrentWidget(ui->page_seller);
            }
        }
        else
        {
            QMessageBox::warning(this,tr("登陆失败！"),tr("密码错误！"),QMessageBox::Ok);
            ui->lineEdit_pwd_login->clear();
            ui->lineEdit_pwd_login->setFocus();
        }
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
    if(findUser(user) != Q_NULLPTR)
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
    if(ui->lineEdit_user_login->text().isEmpty() || ui->lineEdit_pwd_login->text().isEmpty())
        ui->pushButton_login->setDisabled(true);
    else
        ui->pushButton_login->setEnabled(true);
}

void MainWindow::on_lineEdit_pwd_login_textChanged(const QString &arg1)
{
    emit ui->lineEdit_user_login->textChanged("");
}

void MainWindow::on_lineEdit_user_register_textChanged(const QString &arg1)
{
    if(ui->lineEdit_user_register->text().isEmpty() || ui->lineEdit_pwd_register->text().isEmpty() || ui->lineEdit_pwd_repeat->text().isEmpty())
        ui->pushButton_register->setDisabled(true);
    else
        ui->pushButton_register->setEnabled(true);
}

void MainWindow::on_lineEdit_pwd_register_textChanged(const QString &arg1)
{
    emit ui->lineEdit_user_register->textChanged("");
}

void MainWindow::on_lineEdit_pwd_repeat_textChanged(const QString &arg1)
{
    emit ui->lineEdit_user_register->textChanged("");
}

void MainWindow::on_spinBox_buyer_valueChanged(int arg1)
{
    QTreeWidgetItem* current = ui->treeWidget->currentItem();
    if(current->parent() == Q_NULLPTR)
    {
        ui->pushButton_buy->setDisabled(true);
        return;
    }

    int amount = ui->spinBox_buyer->value();
    double price = current->text(4).toDouble();
    ui->lineEdit_price->setText(QString::number(price*amount,'f',2));

    if(MEMBER_Y == curUser->getClass())
    {
        QString discount = ui->lineEdit_discount->text();
        ui->lineEdit_token->setText(QString::number(int(price)));
        price *= discount.toDouble();
    }

    ui->lineEdit_real->setText(QString::number(price*amount,'f',2));
    if(amount > 0)
        ui->pushButton_buy->setEnabled(true);
    else
        ui->pushButton_buy->setDisabled(true);
}

void MainWindow::on_spinBox_seller_valueChanged(int arg1)
{
    if(arg1 > 0 && !(ui->lineEdit_name->text().isEmpty()))
        ui->pushButton_in->setEnabled(true);
    else
        ui->pushButton_in->setDisabled(true);
}

void MainWindow::on_lineEdit_name_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() || ui->spinBox_seller->value() <= 0)
        ui->pushButton_in->setDisabled(true);
    else
        ui->pushButton_in->setEnabled(true);
}


void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{

    if(BUYER_Y == curUser->getClass() || MEMBER_Y == curUser->getClass())
        emit ui->spinBox_buyer->valueChanged(-1);
}

void MainWindow::on_pushButton_buy_clicked()
{
    double money = ui->lineEdit_real->text().toDouble();
    if(money > curUser->getBalance())
    {
        QMessageBox::warning(this, "余额不足", "余额不足！");
    }
    else
    {
        dynamic_cast<Buyer*>(curUser)->recharge(-1*money);
        QMessageBox::information(this, "购买成功", "购买成功！余额："+QString::number(curUser->getBalance()));
    }
}

void MainWindow::on_pushButton_in_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString owner = curUser->getUserName();
    int amount = ui->spinBox_seller->value();
    double price = ui->doubleSpinBox_price->value();
    QDate produceDate = ui->dateEdit_produce->date();
    QDate validityDate = ui->dateEdit_validity->date();
    QDate reduceDate = ui->dateEdit_reduce->date();
    double rate = ui->doubleSpinBox->value();

    QString goodsClass = ui->comboBox->currentText();

    if("食品" == goodsClass)
    {
        QTreeWidgetItem* current = ui->treeWidget->topLevelItem(0);
        Food* food = new Food(++GOODSID, name, amount, price, owner, produceDate, validityDate, reduceDate, rate);
        vecFood.push_back(*food);
        addTreeNode(current, food);
        delete food;
    }
    else if("电子产品" == goodsClass)
    {
        QTreeWidgetItem* current = ui->treeWidget->topLevelItem(1);
        Electronics* elect = new Electronics(++GOODSID, name, amount, price, owner, produceDate, validityDate, rate);
        vecElectronics.push_back(*elect);
        addTreeNode(current, elect);
        delete elect;
    }
    else
    {
        QTreeWidgetItem* current = ui->treeWidget->topLevelItem(2);
        DailyNecessities* daily = new DailyNecessities(++GOODSID, name, amount, price, owner, produceDate, validityDate);
        vecDailyNecessities.push_back(*daily);
        addTreeNode(current, daily);
        delete daily;
    }
    QMessageBox::information(this, "进货成功", "进货成功！");
    ui->lineEdit_name->clear();
    ui->lineEdit_name->setFocus();
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if("请选择商品类别" == arg1)
    {
        ui->lineEdit_name->setDisabled(true);
        ui->spinBox_seller->setDisabled(true);
        ui->doubleSpinBox_price->setDisabled(true);
        ui->dateEdit_produce->setDisabled(true);
        ui->dateEdit_validity->setDisabled(true);
        ui->dateEdit_reduce->setDisabled(true);
        ui->doubleSpinBox->setDisabled(true);
    }
    else
    {
        ui->lineEdit_name->setEnabled(true);
        ui->spinBox_seller->setEnabled(true);
        ui->doubleSpinBox_price->setEnabled(true);
        ui->dateEdit_produce->setEnabled(true);
        ui->dateEdit_validity->setEnabled(true);
        ui->dateEdit_reduce->setEnabled(true);
        ui->doubleSpinBox->setEnabled(true);
        ui->lineEdit_name->setFocus();
    }
}

