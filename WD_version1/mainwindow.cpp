#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QSizePolicy>
#include <QtAlgorithms>
#include <QtMath>

#define LIMIT 8888

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 禁止表头移动，防止按列获取数据错误
    QHeaderView* head =  ui->treeWidget->header();
    head->setSectionsMovable(false);
    head->setVisible(true);
    QHeaderView*  headRecord = ui->treeWidget_record->header();
    head->setSectionsMovable(false);
    headRecord->setVisible(true);
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

/**************************  Custom Functions ********************************/

bool MainWindow::loadData()
{
    vecSeller.append(Seller(1, "戈策", "1", 10000000));
    vecFood.append(Food(1, "蛋糕", 20, 20.0, "戈策", QDate::fromString("2014-11-01", Qt::ISODate), QDate::fromString("2014-11-20", Qt::ISODate), QDate::fromString("2014-11-15", Qt::ISODate), 0.2));
    vecFood.append(Food(2, "鸡蛋", 35, 1.5, "戈策", QDate::fromString("2014-11-05", Qt::ISODate), QDate::fromString("2014-11-30", Qt::ISODate), QDate::fromString("2014-11-28", Qt::ISODate), 0.2));
    vecFood.append(Food(3, "面包", 10, 3.5, "戈策", QDate::fromString("2014-11-20", Qt::ISODate), QDate::fromString("2014-11-28", Qt::ISODate), QDate::fromString("2014-11-25", Qt::ISODate), 0.2));
    vecFood.append(Food(4, "火腿", 30, 2.0, "戈策", QDate::fromString("2014-11-01", Qt::ISODate), QDate::fromString("2014-11-30", Qt::ISODate), QDate::fromString("2014-11-20", Qt::ISODate), 0.2));

    vecElectronics.push_back(Electronics(5, "iphone4s", 50, 2060.0, "戈策", QDate::fromString("2014-01-01",Qt::ISODate), QDate::fromString("2016-01-01", Qt::ISODate), 0.01));
    vecElectronics.push_back(Electronics(6, "iphone5c", 50, 2788.0, "戈策", QDate::fromString("2014-01-01",Qt::ISODate), QDate::fromString("2016-01-01", Qt::ISODate), 0.01));
    vecElectronics.push_back(Electronics(7, "iphone6", 50, 5288.0, "戈策", QDate::fromString("2014-01-01",Qt::ISODate), QDate::fromString("2016-01-01", Qt::ISODate), 0.01));
    vecElectronics.push_back(Electronics(8, "iphone6 plus", 50, 5600.0, "戈策", QDate::fromString("2014-01-01",Qt::ISODate), QDate::fromString("2016-01-01", Qt::ISODate), 0.01));

    vecDailyNecessities.push_back(DailyNecessities(9, "牙刷", 500, 10.0, "戈策", QDate::fromString("2014-10-01", Qt::ISODate), QDate::fromString("2014-12-31", Qt::ISODate)));
    vecDailyNecessities.push_back(DailyNecessities(10, "牙膏", 200, 15.0, "戈策", QDate::fromString("2014-11-30", Qt::ISODate), QDate::fromString("2015-01-01", Qt::ISODate)));

    // 设置为当前最大值
    USERID = 1;
    GOODSID = 10;
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
    return Q_NULLPTR;
}

void MainWindow::addTreeNode(QTreeWidgetItem *parent, Food* food)
{
    QStringList sl;
    QString reduced = (food->reducedPrice() < 0 ? "已过期" : QString::number(food->reducedPrice(),'f',2));
    sl << "" << food->getFoodName() << QString::number(food->getAmount()) << QString::number(food->getPrice(),'f',2) << reduced << food->getOwner() << food->getProduceDate().toString(Qt::ISODate) << food->getValidityDate().toString(Qt::ISODate) << food->getReduceDate().toString(Qt::ISODate) << QString::number(food->getReduceRate(),'f',2) << QString::number(food->getId());
    QTreeWidgetItem * item = new QTreeWidgetItem(sl);
    parent->addChild(item);
}

void MainWindow::addTreeNode(QTreeWidgetItem *parent, Electronics * elect)
{
    QStringList sl;
    QString reduced = (elect->reducedPrice() < 0 ? "已过期" : QString::number(elect->reducedPrice(), 'f', 2));
    sl << "" << elect->getFoodName() << QString::number(elect->getAmount()) << QString::number(elect->getPrice(),'f',2) << reduced << elect->getOwner() << elect->getProduceDate().toString(Qt::ISODate) << elect->getValidityDate().toString(Qt::ISODate) << "-" << QString::number(elect->getRuduceRate(),'f',2) << QString::number(elect->getId());
    QTreeWidgetItem * item = new QTreeWidgetItem(sl);
    parent->addChild(item);
}

void MainWindow::addTreeNode(QTreeWidgetItem *parent, DailyNecessities *daily)
{
    QStringList sl;
    QString reduced = (daily->reducedPrice() < 0 ? "已过期" : QString::number(daily->reducedPrice(), 'f', 2));
    sl << "" << daily->getFoodName() << QString::number(daily->getAmount()) << QString::number(daily->getPrice(),'f',2) << reduced << daily->getOwner() << daily->getProduceDate().toString(Qt::ISODate) << daily->getValidityDate().toString(Qt::ISODate) << "-" << "-" << QString::number(daily->getId());
    QTreeWidgetItem * item = new QTreeWidgetItem(sl);
    parent->addChild(item);
}

void MainWindow::addTreeRecord(QStringList rec)
{
    QTreeWidgetItem* item = new QTreeWidgetItem(rec);
    ui->treeWidget_record->addTopLevelItem(item);
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
    ui->dateEdit_produce->setDate(QDate::currentDate());
    ui->dateEdit_reduce->setDate(QDate::currentDate());
    ui->dateEdit_validity->setDate(QDate::currentDate());
}

void MainWindow::resetManagePage()
{
    ui->label_Level->setText("会员等级");
    ui->lineEdit_Username->clear();
    ui->lineEdit_Balance->clear();
    ui->lineEdit_Level->clear();
    ui->lineEdit_Token->clear();
    ui->lineEdit_userClass->clear();
    ui->lineEdit_note->clear();
    ui->pushButton_Recharge->setEnabled(true);
    ui->pushButton_Upgrade->setEnabled(true);
    ui->pushButton_Exchange->setEnabled(true);
    ui->doubleSpinBox_Recharge->setValue(0.00);
    ui->doubleSpinBox_Recharge->setMinimum(0);
    ui->doubleSpinBox_Recharge->setMaximum(9999999.99);
    ui->spinBox_Token->setValue(0);
    ui->pushButton_Recharge->setText("充值");
    ui->pushButton_record->setVisible(true);
    // 清空购买记录
    ui->treeWidget_record->clear();
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

    /// 修改菜单栏按钮状态
    ui->action_manage->setEnabled(true);
    ui->action_logout->setEnabled(true);

    /// 选择个人交易面板 stackedWidget_2
    if(BUYER == curUser->getClass())
    {
        ui->stackedWidget_2->setCurrentWidget(ui->page_buyer);
    }
    else if(MEMBER == curUser->getClass())
    {
        ui->lineEdit_discount->setText(QString::number(1 - 0.05 * (dynamic_cast<Member*>(curUser))->getLevel(), 'f', 2));
        ui->stackedWidget_2->setCurrentWidget(ui->page_buyer);
    }
    else    //卖家
    {
        ui->dateEdit_produce->setDate(QDate::currentDate());
        ui->dateEdit_reduce->setDate(QDate::currentDate());
        ui->dateEdit_validity->setDate(QDate::currentDate());
        ui->stackedWidget_2->setCurrentWidget(ui->page_seller);
    }

    /// 初始化个人管理界面
    QString classText;    // 用户类别
    switch(curUser->getClass()) {
    case BUYER:
        classText = "普通买家"; break;
    case MEMBER:
        classText = "会员"; break;
    case SELLER:
        classText = "卖家";break;
    default: break;
    }
    // 用户基本信息
    ui->lineEdit_Username->setText(curUser->getUserName());
    ui->lineEdit_userClass->setText(classText);
    ui->lineEdit_Balance->setText("￥" + QString::number(curUser->getBalance(), 'f', 2));
    // 后两行显示与否
    bool isSeller = (SELLER == curUser->getClass());
    ui->pushButton_record->setVisible(!isSeller);
    ui->label_Level->setVisible(!isSeller);
    ui->lineEdit_Level->setVisible(!isSeller);
    ui->pushButton_Upgrade->setVisible(!isSeller);
    ui->lineEdit_note->setVisible(!isSeller);
    ui->label_Token->setVisible(!isSeller);
    ui->lineEdit_Token->setVisible(!isSeller);
    ui->pushButton_Exchange->setVisible(!isSeller);
    ui->spinBox_Token->setVisible(!isSeller);

    if(SELLER == curUser->getClass())    // 卖家信息
    {
        // 充值 or 提现
        ui->pushButton_Recharge->setText("提现");
        ui->doubleSpinBox_Recharge->setMaximum(0);
        ui->doubleSpinBox_Recharge->setMinimum(-1 * curUser->getBalance());
    }
    else
    {
        // 第四行显示与否
        bool isMember = (MEMBER == curUser->getClass());
        ui->label_Token->setVisible(isMember);
        ui->lineEdit_Token->setVisible(isMember);
        ui->pushButton_Exchange->setVisible(isMember);
        ui->spinBox_Token->setVisible(isMember);
        // 购买记录
        Buyer* curBuyer = dynamic_cast<Buyer*>(curUser);
        for(int r = 0; r < curBuyer->recordCount(); ++r)
        addTreeRecord(curBuyer->getRecord(r));

        if(isMember)    // 会员信息
        {
            int level = dynamic_cast<Member*>(curUser)->getLevel();
            ui->lineEdit_Level->setText(QString::number(level));
            ui->lineEdit_note->setText("需支付 " + QString::number(level * 1000) + " 代币");
            ui->lineEdit_Token->setText(QString::number(dynamic_cast<Member*>(curUser)->getToken()));
        }
        else    // 普通买家信息
        {
            ui->lineEdit_Level->setText("非会员");
            ui->lineEdit_note->setText("需支付 ￥8888");
        }
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
    QTreeWidgetItem* current = ui->treeWidget->currentItem();
    if(current->parent() == Q_NULLPTR)
    {
        ui->pushButton_buy->setDisabled(true);
        return;
    }
    QString strp = current->text(4);
    if(strp == "已过期")
    {
        ui->pushButton_buy->setDisabled(true);
        return;
    }
    int amount = ui->spinBox_buyer->value();
    double price = strp.toDouble();
    ui->lineEdit_price->setText(QString::number(price*amount,'f',2));
    price *= amount;

    if(MEMBER == curUser->getClass())
    {
        QString discount = ui->lineEdit_discount->text();
        price = price * discount.toDouble();
        ui->lineEdit_token->setText(QString::number(qFloor(price/10)));
    }

    ui->lineEdit_real->setText(QString::number(price,'f',2));
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
        QMessageBox::warning(this, "余额不足", "余额不足！余额：￥"+QString::number(curUser->getBalance(),'f', 2));
    }
    else
    {
        int pos = -1;
        curUser->recharge(-1*money);
        ui->lineEdit_Balance->setText("￥" + QString::number(curUser->getBalance(),'f',2));
        if(MEMBER == curUser->getClass())
        {
            int addtokens = ui->lineEdit_token->text().toInt();
            dynamic_cast<Member*>(curUser)->changeToken(addtokens);
            ui->lineEdit_Token->setText(QString::number(dynamic_cast<Member*>(curUser)->getToken()));
        }
        QTreeWidgetItem* curItem =  ui->treeWidget->currentItem();
        Goods* curGoods = findGoods(curItem->text(10).toInt(), pos);
        int buyAmount = ui->spinBox_buyer->value();
        curGoods->changeAmount(-1 * buyAmount);
        int amount = curGoods->getAmount();
        ui->treeWidget->currentItem()->setText(2, QString::number(amount));
        QStringList rec;
        rec << QDate::currentDate().toString(Qt::ISODate) << QString::number(buyAmount) << "￥"+QString::number(money, 'f', 2) << curItem->text(1);
        dynamic_cast<Buyer*>(curUser)->appendRecord(rec);
        addTreeRecord(rec);
        QMessageBox::information(this, "购买成功", "购买成功！余额：￥"+QString::number(curUser->getBalance(),'f', 2));

        if(0 == amount)    // 删除库存为零的商品
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
    bool init = ("请选择商品类别" == arg1);
    ui->lineEdit_name->setDisabled(init);
    ui->spinBox_seller->setDisabled(init);
    ui->doubleSpinBox_price->setDisabled(init);
    ui->dateEdit_produce->setDisabled(init);
    ui->dateEdit_validity->setDisabled(init);
    ui->dateEdit_reduce->setDisabled(init);
    ui->doubleSpinBox_rate->setDisabled(init);
    ui->lineEdit_name->setFocus();
    if("电子产品" == arg1)
    {
        ui->dateEdit_reduce->setDisabled(true);
    }
    else if("生活用品" == arg1)
    {
        ui->dateEdit_reduce->setDisabled(true);
        ui->doubleSpinBox_rate->setDisabled(true);
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
    curUser->recharge(money);
    ui->lineEdit_Balance->setText("￥" + QString::number(curUser->getBalance(),'f',2));
    ui->doubleSpinBox_Recharge->setValue(0.00);
    if(SELLER == curUser->getClass())
        ui->doubleSpinBox_Recharge->setMinimum(-1 * curUser->getBalance());
    QString msg = (SELLER == curUser->getClass() ? "提现成功！" : "充值成功！");
    QMessageBox::information(this, msg, msg);
}

void MainWindow::on_pushButton_Upgrade_clicked()
{
    if(BUYER == curUser->getClass())
    {
        if(curUser->getBalance() < LIMIT)
            QMessageBox::warning(this, "余额不足", "余额不足，无法升级会员！");
        else
        {
            QMessageBox::information(this, "升级成功", "升级成功！初始为1级会员，请重新登陆");
            emit ui->action_logout->trigger();
            int pos = -1;
            findUser(curUser->getUserName(), pos);
            Member newMember(*(dynamic_cast<Buyer*>(curUser)));
            //Member newMember(++USERID, buyer->getUserName(), buyer->getPassword(), buyer->getBalance(), 1);
            ///////////////// 需要查找插入位置！！！！！！！！！！！！
            QList<Member>::iterator newPos =  qLowerBound(vecMember.begin(), vecMember.end(), newMember);
            vecMember.insert(newPos, newMember);
            vecBuyer.removeAt(pos);
        }
    }
    else
    {
        int token = dynamic_cast<Member*>(curUser)->getToken();
        int level = dynamic_cast<Member*>(curUser)->getLevel();
        if(token < level * 1000)
            QMessageBox::warning(this, "升级失败", "剩余代币不足，无法升级！");
        else
        {
            dynamic_cast<Member*>(curUser)->changeToken(-1000 * level);
            level += 1;
            dynamic_cast<Member*>(curUser)->setLevel(level);
            QMessageBox::information(this, "升级成功", "升级成功，升级为" + QString::number(level) + "级会员！");
            /*！更改会员相关项目 */
            ui->lineEdit_discount->setText(QString::number(1 - 0.05 * level, 'f', 2));
            ui->lineEdit_Level->setText(QString::number(level));
            ui->lineEdit_note->setText("需支付 " + QString::number(level * 1000) + " 代币");
            ui->lineEdit_Token->setText(QString::number(dynamic_cast<Member*>(curUser)->getToken()));
        }
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

void MainWindow::on_pushButton_record_clicked()
{
    ui->menuBar->setVisible(false);
    ui->stackedWidget->setCurrentWidget(ui->recordPage);
}

void MainWindow::on_pushButton_back_record_clicked()
{
    ui->menuBar->setVisible(true);
    ui->stackedWidget->setCurrentWidget(ui->managePage);
}

void MainWindow::on_lineEdit_Token_textChanged(const QString &arg1)
{
    ui->spinBox_Token->setMaximum(arg1.toInt());
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
    // write data
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
