#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QSizePolicy>
#include <QtAlgorithms>

#define UPGRADE 8888

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit_user_login, SIGNAL(textChanged(QString)),this, SLOT(loginPage_textChanged()));
    connect(ui->lineEdit_pwd_login, SIGNAL(textChanged(QString)), this, SLOT(loginPage_textChanged()));
    connect(ui->lineEdit_user_register, SIGNAL(textChanged(QString)), this, SLOT(registerPage_textChanged()));
    connect(ui->lineEdit_pwd_register, SIGNAL(textChanged(QString)), this, SLOT(registerPage_textChanged()));
    connect(ui->lineEdit_pwd_repeat, SIGNAL(textChanged(QString)), this, SLOT(registerPage_textChanged()));

    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    ui->lineEdit_user_login->setFocus();
    ui->pushButton_login->setDefault(true);
    ui->treeWidget->expandAll();

    // 读取数据，初始化内部数据变量
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
    USERID = 0;
    GOODSID = 0;
    vecSeller.append(Seller(1, "戈策", "1", 10000000));
    vecFood.append(Food(1, "蛋糕", 20, 20.0, "戈策", QDate::fromString("2014/11/1", "yyyy/M/d"), QDate::fromString("2014/11/20", "yyyy/M/d"), QDate::fromString("2014/11/15", "yyyy/M/d"), 0.2));
    vecFood.append(Food(2, "鸡蛋", 35, 1.5, "戈策", QDate::fromString("2014/11/5", "yyyy/M/d"), QDate::fromString("2014/11/30", "yyyy/M/d"), QDate::fromString("2014/11/28", "yyyy/M/d"), 0.2));
    vecFood.append(Food(3, "面包", 10, 3.5, "戈策", QDate::fromString("2014/11/20", "yyyy/M/d"), QDate::fromString("2014/11/28", "yyyy/M/d"), QDate::fromString("2014/11/25", "yyyy/M/d"), 0.2));
    vecFood.append(Food(4, "火腿", 30, 2.0, "戈策", QDate::fromString("2014/11/1", "yyyy/M/d"), QDate::fromString("2014/11/30", "yyyy/M/d"), QDate::fromString("2014/11/20", "yyyy/M/d"), 0.2));

    vecElectronics.push_back(Electronics(5, "iphone4s", 50, 2060.0, "戈策", QDate::fromString("2014/1/1","yyyy/M/d"), QDate::fromString("2016/1/1", "yyyy/M/d"), 0.1));
    vecElectronics.push_back(Electronics(6, "iphone5c", 50, 2788.0, "戈策", QDate::fromString("2014/1/1","yyyy/M/d"), QDate::fromString("2016/1/1", "yyyy/M/d"), 0.1));
    vecElectronics.push_back(Electronics(7, "iphone6", 50, 5288.0, "戈策", QDate::fromString("2014/1/1","yyyy/M/d"), QDate::fromString("2016/1/1", "yyyy/M/d"), 0.1));
    vecElectronics.push_back(Electronics(8, "iphone6 plus", 50, 5600.0, "戈策", QDate::fromString("2014/1/1","yyyy/M/d"), QDate::fromString("2016/1/1", "yyyy/M/d"), 0.1));

    vecDailyNecessities.push_back(DailyNecessities(9, "牙刷", 500, 3.5, "戈策", QDate::fromString("2014/10/1", "yyyy/M/d"), QDate::fromString("2014/12/31", "yyyy/M/d")));

    return true;
}

User* MainWindow::findUser(QString userName, int& pos)
{

    for(int i = 0; i < vecBuyer.size(); ++i)
        if(userName == vecBuyer[i].getUserName())
        {
            pos = i;
            return &vecBuyer[i];
        }
    for(int i = 0; i < vecMember.size(); ++i)
        if(userName == vecMember[i].getUserName())
        {
            pos = i;
            return &vecMember[i];
        }
    for(int i = 0; i < vecSeller.size(); ++i)
        if(userName == vecSeller[i].getUserName())
        {
            pos = i;
            return &vecSeller[i];
        }
    return Q_NULLPTR;
}

Goods* MainWindow::findGoods(int id, int &pos)
{
    for(int i = 0; i < vecFood.count(); ++i)
        if(id == vecFood.at(i).getId())
        {
            pos = i;
            return &vecFood[i];
        }
    for(int i = 0; i < vecElectronics.count(); ++i)
        if(id == vecElectronics.at(i).getId())
        {
            pos = i;
            return &vecElectronics[i];
        }
    for(int i = 0; i < vecDailyNecessities.count(); ++i)
        if(id == vecDailyNecessities.at(i).getId())
        {
            pos = i;
            return &vecDailyNecessities[i];
        }
}

void MainWindow::addTreeNode(QTreeWidgetItem *parent, Food* food)
{
    QStringList sl;
    sl << "" << food->getFoodName() << QString::number(food->getAmount()) << QString::number(food->getPrice(),'f',1) << QString::number(food->reducedPrice(),'f',1) << food->getOwner() << food->getProduceDate().toString("yyyy/MM/dd") << food->getValidityDate().toString("yyyy/MM/dd") << food->getReduceDate().toString("yyyy/MM/dd") << QString::number(food->getReduceRate(),'f',1) << QString::number(food->getId());
    QTreeWidgetItem * item = new QTreeWidgetItem(sl);
    parent->addChild(item);
}

void MainWindow::addTreeNode(QTreeWidgetItem *parent, Electronics * elect)
{
    QStringList sl;
    sl << "" << elect->getFoodName() << QString::number(elect->getAmount()) << QString::number(elect->getPrice(),'f',1) << QString::number(elect->reducedPrice(),'f',1) << elect->getOwner() << elect->getProduceDate().toString("yyyy/MM/dd") << elect->getValidityDate().toString("yyyy/MM/dd") << "-" << QString::number(elect->getRuduceRate(),'f',1) << QString::number(elect->getId());
    QTreeWidgetItem * item = new QTreeWidgetItem(sl);
    parent->addChild(item);
}

void MainWindow::addTreeNode(QTreeWidgetItem *parent, DailyNecessities *daily)
{
    QStringList sl;
    sl << "" << daily->getFoodName() << QString::number(daily->getAmount()) << QString::number(daily->getPrice(),'f',1) << QString::number(daily->reducedPrice(),'f',1) << daily->getOwner() << daily->getProduceDate().toString("yyyy/MM/dd") << daily->getValidityDate().toString("yyyy/MM/dd") << "-" << "-" << QString::number(daily->getId());
    QTreeWidgetItem * item = new QTreeWidgetItem(sl);
    parent->addChild(item);
}

/********************************  reset  ************************************/

void MainWindow::resetLoginPage()
{
    ui->lineEdit_user_login->clear();
    ui->lineEdit_pwd_login->clear();
    // 自动触发 loginPage_textChanged()
}

void MainWindow::resetRegisterPage()
{
    ui->lineEdit_user_register->clear();
    ui->lineEdit_pwd_register->clear();
    ui->lineEdit_pwd_repeat->clear();
    ui->radioButton_buyer->setChecked(true);
    // 自动触发 registerPage_textChanged()
}

void MainWindow::resetMainPage()
{
    ///page_buyer
    ui->spinBox_buyer->setValue(0);
    ui->lineEdit_price->clear();
    ui->lineEdit_discount->clear();
    ui->lineEdit_token->clear();
    ui->lineEdit_real->clear();
    ui->pushButton_buy->setDisabled(true);
    ///page_seller
    ui->radioButton_all->setChecked(true);
    ui->comboBox->setCurrentText("请选择商品类别");
    ui->lineEdit_name->clear();
    ui->spinBox_seller->setValue(0);
    ui->doubleSpinBox_price->setValue(0.0);
    ui->doubleSpinBox_rate->setValue(0.0);
    ui->dateEdit_produce->clear();
    ui->dateEdit_reduce->clear();
    ui->dateEdit_validity->clear();
}

void MainWindow::resetManagePage()
{
    ui->lineEdit_Username->clear();
    ui->lineEdit_Balance->clear();
    ui->lineEdit_Level->clear();
    ui->lineEdit_Level->clear();
    ui->lineEdit_userClass->clear();
    ui->pushButton_Recharge->setEnabled(true);
    ui->pushButton_Upgrade->setEnabled(true);
    ui->pushButton_Exchange->setEnabled(true);
    ui->doubleSpinBox_Recharge->clear();
    ui->spinBox_Token->clear();
}

/********************************  loginPage  ********************************/

void MainWindow::loginPage_textChanged()
{
    bool empty = (ui->lineEdit_user_login->text().isEmpty() || ui->lineEdit_pwd_login->text().isEmpty());
    ui->pushButton_login->setDisabled(empty);
}

void MainWindow::on_pushButton_login_clicked()
{
    QString user = ui->lineEdit_user_login->text();
    QString pwd = ui->lineEdit_pwd_login->text();
    int pos = -1;
    curUser = findUser(user, pos);
    if(curUser == Q_NULLPTR)
    {
        QMessageBox::warning(this,tr("登陆失败！"),tr("用户名不存在！"));
        resetLoginPage();
        return;
    }
    // 用户名存在，密码错误
    if(pwd != curUser->getPassword())
    {
        QMessageBox::warning(this,tr("登陆失败！"),tr("密码错误！"));
        ui->lineEdit_pwd_login->clear();
        ui->lineEdit_pwd_login->setFocus();
        return;
    }
    // 登陆成功
    MainWindow::setWindowState(Qt::WindowMaximized);
    resetLoginPage();
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
    // 修改菜单栏按钮状态
    ui->action_manage->setEnabled(true);
    ui->action_logout->setEnabled(true);

    // 选择个人交易面板 stackedWidget_2
    if(BUYER == curUser->getClass())
    {
        ui->stackedWidget_2->setCurrentWidget(ui->page_buyer);
    }
    else if(MEMBER == curUser->getClass())
    {
        ui->lineEdit_discount->setText(QString::number(1 - 0.05 * (dynamic_cast<Member*>(curUser))->getLevel()));
        ui->stackedWidget_2->setCurrentWidget(ui->page_buyer);
    }
    else    //卖家
    {
        ui->stackedWidget_2->setCurrentWidget(ui->page_seller);
    }

    // 初始化个人管理界面，只需一次
    QString classText;
    switch(curUser->getClass()) {
    case BUYER:
        classText = "普通买家"; break;
    case MEMBER:
        classText = "会员"; break;
    case SELLER:
        classText = "卖家";break;
    default: break;
    }
    ui->lineEdit_Username->setText(curUser->getUserName());
    ui->lineEdit_userClass->setText(classText);
    ui->lineEdit_Balance->setText("￥" + QString::number(curUser->getBalance(), 'f', 2));

    bool isSeller = (SELLER == curUser->getClass());
    ui->lineEdit_Level->setDisabled(isSeller);
    ui->lineEdit_Token->setDisabled(isSeller);
    ui->lineEdit_note->setDisabled(isSeller);
    ui->pushButton_Recharge->setDisabled(isSeller);
    ui->pushButton_Upgrade->setDisabled(isSeller);
    ui->pushButton_Exchange->setDisabled(isSeller);
    ui->doubleSpinBox_Recharge->setDisabled(isSeller);
    ui->spinBox_Token->setDisabled(isSeller);
    bool isBuyer = (BUYER == curUser->getClass());
    ui->lineEdit_Level->setDisabled(isBuyer);
    ui->lineEdit_Token->setDisabled(isBuyer);
    ui->spinBox_Token->setDisabled(isBuyer);
    ui->pushButton_Exchange->setDisabled(isBuyer);
    if(MEMBER == curUser->getClass())
    {
        ui->lineEdit_note->setDisabled(true);
        ui->pushButton_Upgrade->setDisabled(true);
        ui->lineEdit_Level->setText(QString::number(dynamic_cast<Member*>(curUser)->getLevel()));
        ui->lineEdit_Token->setText(QString::number(dynamic_cast<Member*>(curUser)->getToken()));
        ui->spinBox_Token->setMaximum(dynamic_cast<Member*>(curUser)->getToken());
    }
}

void MainWindow::on_pushButton_quit_clicked()
{
    QApplication::quit();
}


void MainWindow::on_pushButton_now_clicked()
{
    resetLoginPage();
    ui->stackedWidget->setCurrentWidget(ui->registerPage);
    ui->lineEdit_user_register->setFocus();
    ui->pushButton_register->setDefault(true);
}

/******************************  registerPage  *******************************/

void MainWindow::registerPage_textChanged()
{
    bool empty = (ui->lineEdit_user_register->text().isEmpty() || ui->lineEdit_pwd_register->text().isEmpty() || ui->lineEdit_pwd_repeat->text().isEmpty());
    ui->pushButton_register->setDisabled(empty);
}

void MainWindow::on_pushButton_register_clicked()
{
    QString user = ui->lineEdit_user_register->text();
    int pos = -1;
    if(findUser(user, pos) != Q_NULLPTR)
    {
        QMessageBox::information(this,tr("注册失败！"),tr("用户名已存在！"),QMessageBox::Ok);
        resetRegisterPage();
        return;
    }
    // 用户名可用
    QString pwd = ui->lineEdit_pwd_register->text();
    QString repeatPwd = ui->lineEdit_pwd_repeat->text();
    if(pwd != repeatPwd)
    {
        QMessageBox::information(this,tr("注册失败！"),tr("两次密码不一致！"),QMessageBox::Ok);
        ui->lineEdit_pwd_register->clear();
        ui->lineEdit_pwd_repeat->clear();
        ui->lineEdit_pwd_register->setFocus();
        return;
    }
    // 注册成功，新用户加入容器
    if(ui->buttonGroup->checkedButton() == ui->radioButton_buyer)    // 新建买家
    {
        Buyer curBuyer(++USERID, user, pwd);
        vecBuyer.push_back(curBuyer);
    }
    else if(ui->buttonGroup->checkedButton() == ui->radioButton_seller)   // 新建卖家
    {
        Seller curSeller(++USERID, user, pwd);
        vecSeller.push_back(curSeller);
    }
    QMessageBox::information(this,tr("注册成功！"),tr("恭喜你 ^_^ 注册成功！"),QMessageBox::Ok);
    resetRegisterPage();
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    ui->lineEdit_user_login->setFocus();
    ui->pushButton_login->setDefault(true);
}

void MainWindow::on_pushButton_back_clicked()
{
    resetRegisterPage();
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    ui->lineEdit_user_login->setFocus();
    ui->pushButton_login->setDefault(true);
}

/******************************  mainPage  ************************************/

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(current->parent() == Q_NULLPTR)
        ui->pushButton_buy->setDisabled(true);
    else
    {
        ui->spinBox_buyer->setMaximum(current->text(2).toInt());
        if(curUser->getClass() != SELLER)
            emit ui->spinBox_buyer->valueChanged(-1);
    }
}

void MainWindow::on_spinBox_buyer_valueChanged(int arg1)
{
    if(Q_NULLPTR == curUser)
        return;
    QTreeWidgetItem* current = ui->treeWidget->currentItem();
    if(current->parent() == Q_NULLPTR)
    {
        ui->pushButton_buy->setDisabled(true);
        return;
    }

    int amount = ui->spinBox_buyer->value();
    double price = current->text(4).toDouble();
    ui->lineEdit_price->setText(QString::number(price*amount,'f',2));

    if(MEMBER == curUser->getClass())
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

void MainWindow::on_pushButton_buy_clicked()
{
    double money = ui->lineEdit_real->text().toDouble();
    if(money > curUser->getBalance())
    {
        QMessageBox::warning(this, "余额不足", "余额不足！");
    }
    else
    {
        int pos = -1;
        dynamic_cast<Buyer*>(curUser)->recharge(-1*money);
        ui->lineEdit_Balance->setText("￥" + QString::number(curUser->getBalance(),'f',2));
        Goods* curGoods = findGoods(ui->treeWidget->currentItem()->text(10).toInt(), pos);
        curGoods->changeAmount(-1 * ui->spinBox_buyer->value());
        QMessageBox::information(this, "购买成功", "购买成功！余额："+QString::number(curUser->getBalance(),'f', 2));
        if(0 == curGoods->getAmount())    // 删除库存为零的商品
        {
            switch (curGoods->getClass()) {
            case FOOD:
                vecFood.removeAt(pos);
                break;
            case ELECTRONICS:
                vecElectronics.removeAt(pos);
                break;
            case DAILYNECESSITIES:
                vecDailyNecessities.removeAt(pos);
                break;
            default:
                break;
            }
            QTreeWidgetItem* current = ui->treeWidget->currentItem();
            current->parent()->takeChild(current->parent()->indexOfChild(current));
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
void MainWindow::on_radioButton_all_clicked()
{
    QString name = curUser->getUserName();
    for(int p = 0; p < ui->treeWidget->topLevelItemCount(); ++p)
    {
        QTreeWidgetItem* parent = ui->treeWidget->topLevelItem(p);
        for(int q = 0; q < parent->childCount(); ++q)
        {
            QTreeWidgetItem* child = parent->child(q);
            if(child->text(5) != name)
                child->setHidden(false);
        }
    }
}

void MainWindow::on_radioButton_mine_clicked()
{
    QString name = curUser->getUserName();
    for(int p = 0; p < ui->treeWidget->topLevelItemCount(); ++p)
    {
        QTreeWidgetItem* parent = ui->treeWidget->topLevelItem(p);
        for(int q = 0; q < parent->childCount(); ++q)
        {
            QTreeWidgetItem* child = parent->child(q);
            if(child->text(5) != name)
                child->setHidden(true);
        }
    }
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(Q_NULLPTR == curUser)
        return;
    if("请选择商品类别" == arg1)
    {
        ui->lineEdit_name->setDisabled(true);
        ui->spinBox_seller->setDisabled(true);
        ui->doubleSpinBox_price->setDisabled(true);
        ui->dateEdit_produce->setDisabled(true);
        ui->dateEdit_validity->setDisabled(true);
        ui->dateEdit_reduce->setDisabled(true);
        ui->doubleSpinBox_rate->setDisabled(true);
    }
    else
    {
        ui->lineEdit_name->setEnabled(true);
        ui->spinBox_seller->setEnabled(true);
        ui->doubleSpinBox_price->setEnabled(true);
        ui->dateEdit_produce->setEnabled(true);
        ui->dateEdit_validity->setEnabled(true);
        ui->dateEdit_reduce->setEnabled(true);
        ui->doubleSpinBox_rate->setEnabled(true);
        ui->lineEdit_name->setFocus();
    }
}

void MainWindow::on_lineEdit_name_textChanged(const QString &arg1)
{
    if(arg1.isEmpty() || ui->spinBox_seller->value() <= 0)
        ui->pushButton_in->setDisabled(true);
    else
        ui->pushButton_in->setEnabled(true);
}

void MainWindow::on_spinBox_seller_valueChanged(int arg1)
{
    if(arg1 > 0 && !(ui->lineEdit_name->text().isEmpty()))
        ui->pushButton_in->setEnabled(true);
    else
        ui->pushButton_in->setDisabled(true);
}

void MainWindow::on_pushButton_in_clicked()
{
    QDate produceDate = ui->dateEdit_produce->date();
    QDate validityDate = ui->dateEdit_validity->date();
    QDate reduceDate = ui->dateEdit_reduce->date();

    if(!(produceDate <= reduceDate && reduceDate <= validityDate))
    {
        QMessageBox::warning(this, "日期错误", "日期设置错误！\n要求：生成日期 ≤ 降价期 ≤ 有效期");
        return;
    }
    QString name = ui->lineEdit_name->text();
    QString owner = curUser->getUserName();
    int amount = ui->spinBox_seller->value();
    double price = ui->doubleSpinBox_price->value();
    double rate = ui->doubleSpinBox_rate->value();
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


/****************************  managePage  *********************************/

void MainWindow::on_pushButton_Recharge_clicked()
{
    double money = ui->doubleSpinBox_Recharge->value();
    if(0.0 == money)
        return;
    dynamic_cast<Buyer*>(curUser)->recharge(money);
    ui->lineEdit_Balance->setText("￥" + QString::number(curUser->getBalance(),'f',2));
    QMessageBox::information(this, "充值成功！", "充值成功！账户余额：" + QString::number(curUser->getBalance(),'f',2));
}

void MainWindow::on_pushButton_Upgrade_clicked()
{
    if(curUser->getBalance() < UPGRADE)
        QMessageBox::warning(this, "余额不足", "余额不足！无法升级会员");
    else
    {
        QMessageBox::information(this, "升级成功", "升级成功！初始为1级会员，请重新登陆");
        int pos = -1;
        User* member = findUser(curUser->getUserName(), pos);
        vecMember.append(Member(++USERID, member->getUserName(), member->getPassword(), member->getBalance(), 1));
        vecBuyer.removeAt(pos);
        emit ui->action_logout->trigger();
    }
}

void MainWindow::on_pushButton_Exchange_clicked()
{
    int token = ui->spinBox_Token->value();
    dynamic_cast<Member*>(curUser)->recharge(token/10.0);
    dynamic_cast<Member*>(curUser)->changeToken(-1 * token);
    ui->lineEdit_Balance->setText("￥" + QString::number(curUser->getBalance(), 'f', 2));
    ui->lineEdit_Token->setText(QString::number(dynamic_cast<Member*>(curUser)->getToken()));
}


/*****************************  action  ***********************************/

void MainWindow::on_action_deal_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
    ui->action_deal->setDisabled(true);
    ui->action_manage->setEnabled(true);
}

void MainWindow::on_action_manage_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->managePage);
    ui->action_manage->setDisabled(true);
    ui->action_deal->setEnabled(true);
}

void MainWindow::on_action_logout_triggered()
{
    curUser = Q_NULLPTR;
    resetMainPage();
    resetManagePage();
    MainWindow::setWindowState(Qt::WindowNoState);
    ui->action_manage->setDisabled(true);
    ui->action_logout->setDisabled(true);
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    ui->lineEdit_user_login->setFocus();
    ui->pushButton_login->setDefault(true);

}

void MainWindow::on_action_exit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox::about(this, tr("关于"), tr("作者：戈策 ~^_^~\nQQ：1334527295    "));
}

void MainWindow::on_action_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}
