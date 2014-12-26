#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#define LIMIT 8888

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);
    // 发送地址
    serverAddr = QHostAddress::LocalHost;
    serverPort = 45454;
    // 接收端口
    clientPort = 45455;
    udpSocket->bind(clientPort, QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

    // 禁止表头移动，防止按列获取数据错误
    QHeaderView *head =  ui->treeWidget->header();
    head->setSectionsMovable(false);
    head->setVisible(true);
    QHeaderView *headRecord = ui->treeWidget_record->header();
    head->setSectionsMovable(false);
    headRecord->setVisible(true);
    connect(ui->lineEdit_user_login, SIGNAL(textChanged(QString)), this, SLOT(loginPage_textChanged()));
    connect(ui->lineEdit_pwd_login, SIGNAL(textChanged(QString)), this, SLOT(loginPage_textChanged()));
    connect(ui->lineEdit_user_register, SIGNAL(textChanged(QString)), this, SLOT(registerPage_textChanged()));
    connect(ui->lineEdit_pwd_register, SIGNAL(textChanged(QString)), this, SLOT(registerPage_textChanged()));
    connect(ui->lineEdit_pwd_repeat, SIGNAL(textChanged(QString)), this, SLOT(registerPage_textChanged()));
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    ui->lineEdit_user_login->setFocus();
    ui->pushButton_login->setDefault(true);
    ui->treeWidget->expandAll();
    // 读取数据，初始化内部数据变量
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**************************  Custom Functions ********************************/

void MainWindow::addTreeNode(int index, QStringList newGoods)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(newGoods);
    ui->treeWidget->topLevelItem(index)->addChild(item);
}

void MainWindow::addTreeRecord(QStringList rec)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(rec);
    ui->treeWidget_record->addTopLevelItem(item);
}

void MainWindow::listAllGoods(QString key)
{
    QTreeWidgetItem *treeParent;
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i){
        treeParent = ui->treeWidget->topLevelItem(i);
        for (int p = 0; p < treeParent->childCount(); ++p) {
            bool state = treeParent->child(p)->text(10).contains(key);
            treeParent->child(p)->setHidden(state);
        }
    }
}

void MainWindow::listMyGoods(QString key)
{
    QTreeWidgetItem *treeParent;
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i){
        treeParent = ui->treeWidget->topLevelItem(i);
        for (int p = 0; p < treeParent->childCount(); ++p) {
            QTreeWidgetItem *treeChild = treeParent->child(p);
            QString  user = ui->lineEdit_Username->text();
            bool state = (treeChild->text(5) == user)&&(treeChild->text(10).contains(key));
            treeParent->child(p)->setHidden(state);
        }
    }
}

void MainWindow::setManagePage(QString user, UserClass userClass, double balance, int level, int token, QVector<QStringList> vecRecord)
{
    // 用户基本信息
    ui->lineEdit_Username->setText(user);
    QString strClass;
    switch (userClass) {
    case BUYER:
        strClass = "普通买家";
        break;
    case MEMBER:
        strClass = "会员";
        break;
    case SELLER:
        strClass == "卖家";
        break;
    default:
        strClass = "userClass Error";
        break;
    }
    ui->lineEdit_userClass->setText(strClass);
    ui->lineEdit_Balance->setText("￥" + QString::number(balance, 'f', 2));
    // 后两行显示与否
    bool isSeller = (SELLER == userClass);
    ui->pushButton_record->setVisible(!isSeller);
    ui->label_Level->setVisible(!isSeller);
    ui->lineEdit_Level->setVisible(!isSeller);
    ui->pushButton_Upgrade->setVisible(!isSeller);
    ui->lineEdit_note->setVisible(!isSeller);
    ui->label_Token->setVisible(!isSeller);
    ui->lineEdit_Token->setVisible(!isSeller);
    ui->pushButton_Exchange->setVisible(!isSeller);
    ui->spinBox_Token->setVisible(!isSeller);
    if (SELLER == userClass) { // 卖家信息
        // 充值 or 提现
        ui->pushButton_Recharge->setText("提现");
        ui->doubleSpinBox_Recharge->setMaximum(0);
        ui->doubleSpinBox_Recharge->setMinimum(-1 * balance);
    } else {    //买家和会员
        // 第四行显示与否
        bool isMember = (MEMBER == userClass);
        ui->label_Token->setVisible(isMember);
        ui->lineEdit_Token->setVisible(isMember);
        ui->pushButton_Exchange->setVisible(isMember);
        ui->spinBox_Token->setVisible(isMember);
        if (isMember) { // 会员信息
            ui->lineEdit_Level->setText(QString::number(level));
            ui->lineEdit_note->setText("需支付 " + QString::number(level * 1000) + " 代币");
            ui->lineEdit_Token->setText(QString::number(token));
        } else { // 普通买家信息
            ui->lineEdit_Level->setText("非会员");
            ui->lineEdit_note->setText("需支付 ￥8888");
        }
        // 购买记录
        for (int r = 0; r < vecRecord.size(); ++r)
            addTreeRecord(vecRecord.at(r));
    }
}

///// 错误！！！！！！！！！！！！！！！
void MainWindow::setMainPage(QVector<QVector<QStringList> > vec2Goods, UserClass userClass, int level)
{
    resetLoginPage();
    MainWindow::setWindowState(Qt::WindowMaximized);
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
    /// 修改菜单栏按钮状态
    ui->action_manage->setEnabled(true);
    ui->action_logout->setEnabled(true);
    /// 选择个人交易面板 stackedWidget_2
    if (BUYER == userClass) {
        ui->stackedWidget_2->setCurrentWidget(ui->page_buyer);
    } else if (MEMBER == userClass) {
        ui->lineEdit_discount->setText(QString::number(1 - 0.05 * level, 'f', 2));
        ui->stackedWidget_2->setCurrentWidget(ui->page_buyer);
    } else { //卖家
        ui->dateEdit_produce->setDate(QDate::currentDate());
        ui->dateEdit_reduce->setDate(QDate::currentDate());
        ui->dateEdit_validity->setDate(QDate::currentDate());
        ui->stackedWidget_2->setCurrentWidget(ui->page_seller);
    }
    // 商品列表
    for(int t = 0; t < ui->treeWidget->topLevelItemCount(); ++t){
        for(int p = 0; p < vec2Goods.at(t).size(); ++p)
            addTreeNode(t, vec2Goods.at(t).at(p));
    }

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
    // 清楚商品列表
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
        ui->treeWidget->topLevelItem(i)->takeChildren();
    ///page_buyer
    ui->spinBox_buyer->setValue(0);
    ui->lineEdit_price->clear();
    ui->lineEdit_discount->clear();
    ui->lineEdit_token->clear();
    ui->lineEdit_real->clear();
    ui->pushButton_buy->setDisabled(true);
    ///page_Seller
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
    sendRequest(LoginRequest);
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
    sendRequest(RegisterRequest);
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
    if (current->parent() == Q_NULLPTR){
        ui->lineEdit_price->setText("0.00");
        ui->pushButton_buy->setDisabled(true);
        }
    else {
        ui->spinBox_buyer->setMaximum(current->text(2).toInt());
        if (ui->lineEdit_userClass->text() != "卖家")
            emit ui->spinBox_buyer->valueChanged(ui->spinBox_buyer->value());
    }
}

void MainWindow::on_spinBox_buyer_valueChanged(int arg1)
{
    QTreeWidgetItem *current = ui->treeWidget->currentItem();
    if (current->parent() == Q_NULLPTR) {
        ui->lineEdit_price->setText("0.00");
        ui->pushButton_buy->setDisabled(true);
        return;
    }
    QString strp = current->text(4);
    if (strp == "已过期") {
        ui->lineEdit_price->setText("0.00");
        ui->pushButton_buy->setDisabled(true);
        return;
    }
    int amount = arg1;
    double price = strp.toDouble();
    ui->lineEdit_price->setText(QString::number(price * amount, 'f', 2));
    price *= amount;
    if ("会员" == ui->lineEdit_userClass->text()) {
        QString discount = ui->lineEdit_discount->text();
        price = price * discount.toDouble();
        ui->lineEdit_token->setText(QString::number(qFloor(price / 10)));
    }
    ui->lineEdit_real->setText(QString::number(price, 'f', 2));
    if (amount > 0)
        ui->pushButton_buy->setEnabled(true);
    else
        ui->pushButton_buy->setDisabled(true);
}

void MainWindow::on_pushButton_buy_clicked()
{
    sendRequest(BuyRequest);
}

/////////////////////////////////////////////////////////////////////////////
void MainWindow::on_pushButton_search_clicked()
{
    QString key = ui->lineEdit_search->text();
    if(ui->buttonGroup_2->checkedButton() == ui->radioButton_all)
        listAllGoods(key);
    else
        listMyGoods(key);
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->lineEdit_search->clear();
    if(ui->buttonGroup_2->checkedButton() == ui->radioButton_all)
        listAllGoods();
    else
        listMyGoods();
}

void MainWindow::on_radioButton_all_clicked()
{
    listAllGoods(ui->lineEdit_search->text());
}

void MainWindow::on_radioButton_mine_clicked()
{
    listMyGoods(ui->lineEdit_search->text());
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
    if ("电子产品" == arg1) {
        ui->dateEdit_reduce->setDisabled(true);
    } else if ("生活用品" == arg1) {
        ui->dateEdit_reduce->setDisabled(true);
        ui->doubleSpinBox_rate->setDisabled(true);
    }
}

void MainWindow::on_lineEdit_name_textChanged(const QString &arg1)
{
    if (arg1.isEmpty() || ui->spinBox_seller->value() <= 0)
        ui->pushButton_in->setDisabled(true);
    else
        ui->pushButton_in->setEnabled(true);
}

void MainWindow::on_spinBox_seller_valueChanged(int arg1)
{
    if (arg1 > 0 && !(ui->lineEdit_name->text().isEmpty()))
        ui->pushButton_in->setEnabled(true);
    else
        ui->pushButton_in->setDisabled(true);
}

void MainWindow::on_pushButton_in_clicked()
{
    sendRequest(StockRequest);
}

/****************************  managePage  *********************************/

void MainWindow::on_pushButton_Recharge_clicked()
{
    if(ui->doubleSpinBox_Recharge->value() != 0.0)
        sendRequest(RechargeRequest);
}

void MainWindow::on_pushButton_Upgrade_clicked()
{
    sendRequest(UpgradeRequest);
}

void MainWindow::on_pushButton_Exchange_clicked()
{
    sendRequest(ExchangeRequest);
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

void MainWindow::on_action_about_triggered()
{
    QMessageBox::about(this, "关于", "作者：戈策 ~^_^~\nQQ：1334527295    ");
}

void MainWindow::on_action_help_triggered()
{
    QMessageBox::information(this, "帮助", "说明：\n1.普通买家需支付8888元方可升级为会员\n2.一级会员折扣为0.95，会员等级每升一级，会员折扣减少0.05\n3.会员升级需支付相应数量代币，计算公式：代币数 = 当前等级 * 1000\n4.会员每次购物可获得代币，计算公式：代币数 = （应付金额 / 10）向下取整\n5.会员代币可兑换为余额，兑换比例为10：1\n6.食品在降价期-有效期内降价，计算公式：现价 = 原件 * （1 - 降价因子）\n7.电子产品在生产日期-有效期内降价，计算公式：现价 = 原价 * （1 - 降价因子*（当前日期-生产日期）/30）");
}

void MainWindow::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);

        int type;
        bool resCode;
        QString reqUser;

        in >> type;
        switch (type) {
        case LoginFeedBack:
        {
            in >> resCode >> reqUser;
            if(resCode == 0){    //成功
                int userClass;    //!QDatastream 无法读入枚举
                double balance;
                int level, token;
                QVector<QStringList> vecRecord;
                QVector<QVector<QStringList> > vec2Goods(3);
                in >> userClass >> balance >> level >> token >> vecRecord >> vec2Goods;
                if(ui->lineEdit_Username->text() == reqUser){
                    setMainPage(vec2Goods, UserClass(userClass), level);    //!强制转换枚举
                    setManagePage(reqUser, UserClass(userClass), balance, level, token, vecRecord);
                    resetLoginPage();
                }
            } else {    //失败
                if(ui->lineEdit_Username->text() == reqUser){
                    if(resCode > 0)
                        QMessageBox::warning(this, tr("登陆失败！"), tr("密码错误！"));
                    else
                        QMessageBox::warning(this, tr("登陆失败！"), tr("用户名不存在！"));
                }
            }
            break;
        }
        case RegisterFeedBack:
        {
            in >> resCode >> reqUser;
            if(resCode == 0){
                if(ui->lineEdit_Username->text() == reqUser){
                    QMessageBox::information(this, "注册成功！", "恭喜你 ^_^ 注册成功！");
                    resetRegisterPage();
                    ui->stackedWidget->setCurrentWidget(ui->loginPage);
                    ui->lineEdit_user_login->setFocus();
                    ui->pushButton_login->setDefault(true);
                }
            } else {
                if(ui->lineEdit_Username->text() == reqUser){
                    if(resCode > 0)
                        QMessageBox::information(this, tr("注册失败！"), tr("用户名已存在！"));
                    else
                        QMessageBox::information(this, tr("注册失败！"), tr("两次密码不一致！"));
                }
            }
            break;
        }
        case BuyFeedBack:
        {
            in >> resCode >> reqUser;
            if(resCode == 0) {
                int id, amount, token;
                double balance;
                QStringList record;
                in >> id >> amount >> balance >> token >> record;
                qDebug() << "id" << id << "amount" << amount;
                bool notFound = true;
                for(int i = 0; i < ui->treeWidget->topLevelItemCount() && notFound; ++i)
                {
                    QTreeWidgetItem *treeParent = ui->treeWidget->topLevelItem(i);
                    for(int j = 0; j < treeParent->childCount() && notFound; ++j)
                        if(treeParent->child(j)->text(10).toInt() == id)
                        {
                            if(amount <= 0)
                                treeParent->takeChild(j);
                            else
                                treeParent->child(j)->setText(2, QString::number(amount));
                            notFound = false;
                        }
                }
                if(ui->lineEdit_Username->text() == reqUser){
                    ui->lineEdit_Balance->setText("￥" + QString::number(balance, 'f', 2));
                    ui->lineEdit_Token->setText(QString::number(token));
                    addTreeRecord(record);
                    QMessageBox::information(this, "购买成功", "购买成功！");
                }
            }
            else {
                if(ui->lineEdit_Username->text() == reqUser)
                    QMessageBox::warning(this, "购买失败", "余额不足！");
                qDebug() << "buy false";
            }
            break;
        }
        case StockFeedBack:
        {
            in >> resCode >> reqUser;
            int index;
            QStringList newGoods;
            in >> index >> newGoods;
            addTreeNode(index, newGoods);
            if(ui->lineEdit_Username->text() == reqUser)
                QMessageBox::information(this, "进货成功", "进货成功！");
            break;
        }
        case RechargeFeedBack:
        {
            in >> resCode >> reqUser;
            double balance;
            in >> balance;
            if(ui->lineEdit_Username->text() == reqUser){
                ui->lineEdit_Balance->setText("￥" + QString::number(balance, 'f', 2));
                if (ui->lineEdit_userClass->text() == "卖家")
                    ui->doubleSpinBox_Recharge->setMinimum(-1 * balance);
                QString msg = (balance > 0 ? "充值成功" : "提现成功");
                QMessageBox::information(this, msg, msg+"！");
            }
            break;
        }
        case UpgradeFeedBack:
        {
            in >> resCode >> reqUser;
            if(resCode == 0){
                int level, token;
                double balance;
                in >> level >> token >> balance;
                if(ui->lineEdit_Username->text() == reqUser){
                    ui->lineEdit_discount->setText(QString::number(1-level*0.05,'f', 2));
                    ui->lineEdit_note->setText("需支付 " + QString::number(level * 1000) + " 代币");
                    ui->lineEdit_Level->setText(QString::number(level));
                    if(1 == level){    //普通用户升级会员，支付金额
                        ui->lineEdit_Balance->setText(QString::number(balance, 'f', 2));
                        ui->label_Token->setVisible(true);
                        ui->lineEdit_Token->setVisible(true);
                        ui->pushButton_Exchange->setVisible(true);
                        ui->spinBox_Token->setVisible(true);
                    }else            //会员升级，支付代币
                        ui->lineEdit_Token->setText(QString::number(token));
                }
            }
            else {
                if(ui->lineEdit_Username->text() == reqUser)
                    QMessageBox::warning(this, "升级失败", "升级失败！");
            }
            break;
        }
        case ExchangeFeedBack:
        {
            in >> resCode >> reqUser;
            double balance;
            int token;
            in >> balance >> token;
            if(ui->lineEdit_Username->text() == reqUser){
                ui->lineEdit_Balance->setText("￥" + QString::number(balance, 'f', 2));
                ui->lineEdit_Token->setText(QString::number(token));
            }
            break;
        }
        default:
            break;
        }
    }
}

void MainWindow::sendRequest(UdpType type)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << type;
    QString reqUser;

    switch (type) {
    case LoginRequest:
    {
        reqUser = ui->lineEdit_user_login->text();
        QString pwd = ui->lineEdit_pwd_login->text();
        out << reqUser << pwd;
        break;
    }
    case RegisterRequest:
    {
        reqUser = ui->lineEdit_user_register->text();
        QString pwd = ui->lineEdit_pwd_register->text();
        QString repeat = ui->lineEdit_pwd_repeat->text();
        UserClass userClass = (ui->buttonGroup->checkedButton() == ui->radioButton_buyer ? BUYER : SELLER);
        out << reqUser << pwd << repeat << userClass;
        break;
    }
    case BuyRequest:
    {
        reqUser = ui->lineEdit_Username->text();
        int id = ui->treeWidget->currentItem()->text(10).toInt();
        int amount =  ui->spinBox_buyer->value();
        double pay = ui->lineEdit_real->text().toDouble();
        out << reqUser << id << amount << pay;
        break;
    }
    case StockRequest:
    {
        QDate produceDate = ui->dateEdit_produce->date();
        QDate validityDate = ui->dateEdit_validity->date();
        QDate reduceDate = ui->dateEdit_reduce->date();
        QString strClass = ui->comboBox->currentText();
        GoodsClass goodsClass;
        if ("食品" == strClass) {
            if (!(produceDate <= reduceDate && reduceDate <= validityDate)) {
                QMessageBox::warning(this, "日期错误", "日期设置错误！\n要求：生成日期 ≤ 降价期 ≤ 有效期");
                break;
            }
            goodsClass = FOOD;
        } else if ("电子产品" == strClass) {
            if (!(produceDate <= validityDate)) {
                QMessageBox::warning(this, "日期错误", "日期设置错误！\n要求：生成日期 ≤ 有效期");
                break;
            }
            goodsClass = ELECTRONICS;
        } else {
            if (!(produceDate <= validityDate)) {
                QMessageBox::warning(this, "日期错误", "日期设置错误！\n要求：生成日期 ≤ 有效期");
                break;
            }
            goodsClass = DAILYNECESSITIES;
        }
        reqUser = ui->lineEdit_Username->text();
        QString goodsName = ui->lineEdit_name->text();
        int amount = ui->spinBox_seller->value();
        double price = ui->doubleSpinBox_price->value();
        double rate = ui->doubleSpinBox_rate->value();
        out << reqUser << goodsClass << goodsName << amount << price << produceDate << validityDate << reduceDate << rate;
        break;
    }
    case RechargeRequest:
    {
        reqUser = ui->lineEdit_Username->text();
        double money = ui->doubleSpinBox_Recharge->value();
        out << reqUser << money;
        break;
    }
    case UpgradeRequest:
    {
        reqUser = ui->lineEdit_Username->text();
        out << reqUser;
        break;
    }
    case ExchangeRequest:
    {
        reqUser = ui->lineEdit_Username->text();
        int token = ui->spinBox_Token->value();
        out << reqUser << token;
        break;
    }
    default:
        break;
    }
    udpSocket->writeDatagram(data, data.length(), serverAddr, serverPort);
}
