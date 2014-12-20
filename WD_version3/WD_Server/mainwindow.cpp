#include "mainwindow.h"
#include "ui_mainwindow.h"

#define LIMIT 8888

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);
    serverAddr = QHostAddress::LocalHost;
    serverPort = 45454;
    clientPort = 45455;
    // 接收
    udpSocket->bind(serverAddr, serverPort, QUdpSocket::DontShareAddress);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    loadData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**************************  Custom Functions ********************************/

bool MainWindow::loadData()
{
    USERID = GOODSID = 0;
    QVector<QString> warn;
    QFile file;

    file.setFileName("data/buyer.dat");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        quint32 magic;
        in >> magic;
        if (magic == 0xa0b0c0d0) {
            Buyer buyer;
            while (!in.atEnd()) {
                in >> buyer;
                listBuyer.append(buyer);
            }
            int lastId = buyer.getId();
            USERID = (lastId > USERID ? lastId : USERID);
        } else
            warn.append("buyer.dat 已损坏");
        file.close();
    }
    file.setFileName("data/member.dat");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        quint32 magic;
        in >> magic;
        if (magic == 0xa0b0c0d0) {
            Member member;
            while (!in.atEnd()) {
                in >> member;
                listMember.append(member);
            }
            int lastId = member.getId();
            USERID = (lastId > USERID ? lastId : USERID);
        } else
            warn.append("member.dat 已损坏");
        file.close();
    }
    file.setFileName("data/seller.dat");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        quint32 magic;
        in >> magic;
        if (magic == 0xa0b0c0d0) {
            Seller seller;
            while (!in.atEnd()) {
                in >> seller;
                listSeller.append(seller);
            }
            int lastId = seller.getId();
            USERID = (lastId > USERID ? lastId : USERID);
        } else
            warn.append("seller.dat 已损坏");
        file.close();
    }
    file.setFileName("data/food.dat");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        quint32 magic;
        in >> magic;
        if (magic == 0xa0b0c0d0) {
            Food food;
            while (!in.atEnd()) {
                in >> food;
                listFood.append(food);
            }
            int lastId = food.getId();
            GOODSID = (lastId > GOODSID ? lastId : GOODSID);
        } else
            warn.append("food.dat 已损坏");
        file.close();
    }
    file.setFileName("data/elect.dat");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        quint32 magic;
        in >> magic;
        if (magic == 0xa0b0c0d0) {
            Electronics elect;
            while (!in.atEnd()) {
                in >> elect;
                listElect.append(elect);
            }
            int lastId = elect.getId();
            GOODSID = (lastId > GOODSID ? lastId : GOODSID);
        } else
            warn.append("elect.dat 已损坏");
        file.close();
    }
    file.setFileName("data/daily.dat");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        quint32 magic;
        in >> magic;
        if (magic == 0xa0b0c0d0) {
            DailyNecessities daily;
            while (!in.atEnd()) {
                in >> daily;
                listDaily.append(daily);
            }
            int lastId = daily.getId();
            GOODSID = (lastId > GOODSID ? lastId : GOODSID);
        } else
            warn.append("daily.dat 已损坏");
        file.close();
    }
    if (!warn.isEmpty()) {
        QFile fileLog("data/log.txt");
        fileLog.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text);
        QTextStream log(&fileLog);
        log << QDateTime::currentDateTime().toString(Qt::ISODate) << endl;
        for (int i = 0; i < warn.size(); ++i) {
            log << warn.at(i) << endl;
        }
        log << endl;
        fileLog.close();
    }
    return true;
}

User *MainWindow::findUser(QString userName, int &pos)
{
    for (int i = 0; i < listBuyer.size(); ++i)
        if (userName == listBuyer[i].getUserName()) {
            pos = i;
            return &listBuyer[i];
        }
    for (int i = 0; i < listMember.size(); ++i)
        if (userName == listMember[i].getUserName()) {
            pos = i;
            return &listMember[i];
        }
    for (int i = 0; i < listSeller.size(); ++i)
        if (userName == listSeller[i].getUserName()) {
            pos = i;
            return &listSeller[i];
        }
    return Q_NULLPTR;
}

Goods *MainWindow::findGoods(int id, int &pos)
{
    for (int i = 0; i < listFood.count(); ++i)
        if (id == listFood.at(i).getId()) {
            pos = i;
            return &listFood[i];
        }
    for (int i = 0; i < listElect.count(); ++i)
        if (id == listElect.at(i).getId()) {
            pos = i;
            return &listElect[i];
        }
    for (int i = 0; i < listDaily.count(); ++i)
        if (id == listDaily.at(i).getId()) {
            pos = i;
            return &listDaily[i];
        }
    return Q_NULLPTR;
}


void MainWindow::on_action_about_triggered()
{
    QMessageBox::about(this, "关于", "作者：戈策 ~^_^~\nQQ：1334527295    ");
}

void MainWindow::on_action_help_triggered()
{
    QMessageBox::information(this, "帮助", "说明：\n1.普通买家需支付8888元方可升级为会员\n2.一级会员折扣为0.95，会员等级每升一级，会员折扣减少0.05\n3.会员升级需支付相应数量代币，计算公式：代币数 = 当前等级 * 1000\n4.会员每次购物可获得代币，计算公式：代币数 = （应付金额 / 10）向下取整\n5.会员代币可兑换为余额，兑换比例为10：1\n6.食品在降价期-有效期内降价，计算公式：现价 = 原件 * （1 - 降价因子）\n7.电子产品在生产日期-有效期内降价，计算公式：现价 = 原价 * （1 - 降价因子*（当前日期-生产日期）/30）");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QFile file;
    file.setFileName("data/buyer.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        quint32 magic = 0xa0b0c0d0;
        out << magic;
        for (int i = 0; i < listBuyer.size(); ++i)
            out << listBuyer.at(i);
        file.close();
    }
    file.setFileName("data/member.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        quint32 magic = 0xa0b0c0d0;
        out << magic;
        for (int i = 0; i < listMember.size(); ++i)
            out << listMember.at(i);
        file.close();
    }
    file.setFileName("data/seller.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        quint32 magic = 0xa0b0c0d0;
        out << magic;
        for (int i = 0; i < listSeller.size(); ++i)
            out << listSeller.at(i);
        file.close();
    }
    file.setFileName("data/food.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        quint32 magic = 0xa0b0c0d0;
        out << magic;
        for (int i = 0; i < listFood.size(); ++i)
            out << listFood.at(i);
        file.close();
    }
    file.setFileName("data/elect.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        quint32 magic = 0xa0b0c0d0;
        out << magic;
        for (int i = 0; i < listElect.size(); ++i)
            out << listElect.at(i);
        file.close();
    }
    file.setFileName("data/daily.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        quint32 magic = 0xa0b0c0d0;
        out << magic;
        for (int i = 0; i < listDaily.size(); ++i)
            out << listDaily.at(i);
        file.close();
    }
    event->accept();
}

void MainWindow::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);

        QString newUser, newClass, newId, newAmount, newLevel, newBalance, newToken;
        QStringList newRecord, newGoods;
        QVector<QStringList> vecRecord;
        QVector<QVector<QStringList> > vecGoods;
        bool loginOK, buyOK, upgradeOK;
        int type, res, treeParent;

        in >> type;
        switch (type) {
        case LoginFeedBack:
            in >> loginOK;
            if(loginOK){
                resetLoginPage();
                in >> newUser >> newClass >> newBalance >> newLevel >> newToken >> newRecord >> vecGoods;
                setManagePage(newUser, newClass, newBalance, newLevel, newToken, vecRecord);
                setMainPage(vecGoods, newClass, newLevel.toInt());
            } else{
                QMessageBox::warning(this, "登陆失败", "用户名或密码错误！");
            }
            break;
        case RegisterFeedBack:
            in >> res;
            if(res > 0){
                QMessageBox::information(this, "注册成功！", "恭喜你 ^_^ 注册成功！");
                resetRegisterPage();
                ui->stackedWidget->setCurrentWidget(ui->loginPage);
                ui->lineEdit_user_login->setFocus();
                ui->pushButton_login->setDefault(true);
            }
            else if(res < 0)
                QMessageBox::information(this, tr("注册失败！"), tr("用户名已存在！"));
            else
                QMessageBox::information(this, tr("注册失败！"), tr("两次密码不一致！"));
            break;
        case BuyFeedBack:
            in >> buyOK;
            if(buyOK){
                in >> newId >> newAmount >> newUser >> newBalance >> newToken >> newRecord;
                bool notFound = true;
                for(int i = 0; i < ui->treeWidget->topLevelItemCount() && notFound; ++i)
                {
                    QTreeWidgetItem *treeParent = ui->treeWidget->topLevelItem(i);
                    for(int j = 0; j < treeParent->childCount() && notFound; ++j)
                        if(treeParent->child(j)->text(10) == newId)
                        {
                            if(newAmount == "0")
                                treeParent->takeChild(j);
                            else
                                treeParent->child(j)->setText(j, newAmount);
                            notFound = false;
                        }
                }
                if(ui->lineEdit_name->text() == newUser){
                    ui->lineEdit_Balance->setText("￥" + newBalance);
                    ui->lineEdit_Token->setText(newToken);
                    addTreeRecord(newRecord);
                }
                QMessageBox::information(this, "购买成功", "购买成功！");
            }
            else
                QMessageBox::warning(this, "购买失败", "余额不足！");
            break;
        case StockFeedBack:
            in >> treeParent >> newGoods;
            addTreeNode(treeParent, newGoods);
            QMessageBox::information(this, "进货成功", "进货成功！");
            break;
        case RechargeFeedBack:
            in >> newUser >> newBalance;
            if(ui->lineEdit_Username->text() == newUser){
                ui->lineEdit_Balance->setText(newBalance);
                QString msg = (newBalance.toDouble() > 0 ? "充值成功" : "提现成功");
                QMessageBox::information(this, msg, msg+"！");
            }
            break;
        case UpgradeFeedBack:
            in >> upgradeOK;
            if(upgradeOK){
                in >> newLevel;
                ui->lineEdit_Level->setText(newLevel);
                ui->lineEdit_discount->setText(QString::number(1-newLevel.toInt()*0.05,'f', 2));
                ui->lineEdit_note->setText("需支付 " + QString::number(newLevel.toInt() * 1000) + " 代币");
                if(newLevel == "1"){
                    in >> newBalance;
                    ui->lineEdit_Balance->setText(newBalance);
                    ui->label_Token->setVisible(true);
                    ui->lineEdit_Token->setVisible(true);
                    ui->pushButton_Exchange->setVisible(true);
                    ui->spinBox_Token->setVisible(true);
                }else{
                    in >> newToken;
                    ui->lineEdit_Token->setText(newToken);
                }
            }
            break;
        case ExchangeFeedBack:
            in >> newBalance >> newToken;
            ui->lineEdit_Balance->setText("￥" + newBalance);
            ui->lineEdit_Token->setText(newToken);
            break;
        default:
            break;
        }
    }
}

void MainWindow::sendRequest(UdpType type)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    QString user, pwd, repeat, id, goodsClass, userClass, name, owner, money;
    double pay;
    int amount, token;
    double price, rate;
    QDate produceDate, validityDate, reduceDate;

    out << type;
    switch (type) {
    case LoginRequest:
        user = ui->lineEdit_user_login->text();
        pwd = ui->lineEdit_pwd_login->text();
        out << user << pwd;
        break;
    case RegisterRequest:
        user = ui->lineEdit_user_register->text();
        pwd = ui->lineEdit_pwd_register->text();
        repeat = ui->lineEdit_pwd_repeat->text();
        userClass = (ui->buttonGroup->checkedButton() == ui->radioButton_buyer ? "买家" : "卖家");
        out << user << pwd << repeat << userClass;
        break;
    case BuyRequest:
        id = ui->treeWidget->currentItem()->text(10);
        user = ui->lineEdit_Username->text();
        pay = ui->lineEdit_real->text().toDouble();
        out << id << user << pay;
        break;
    case StockRequest:
        goodsClass = ui->comboBox->currentText();
        name = ui->lineEdit_name->text();
        amount = ui->spinBox_seller->value();
        price = ui->doubleSpinBox_price->value();
        owner = ui->lineEdit_Username->text();
        produceDate = ui->dateEdit_produce->date();
        validityDate = ui->dateEdit_validity->date();
        reduceDate = ui->dateEdit_reduce->date();
        rate = ui->doubleSpinBox_rate->value();
        out << goodsClass << name << amount << price << owner << produceDate << validityDate << reduceDate << rate;
        break;
    case RechargeRequest:
        user = ui->lineEdit_Username->text();
        money = ui->doubleSpinBox_Recharge->value();
        out << user << money;
        break;
    case UpgradeRequest:
        user = ui->lineEdit_Username->text();
        out << user;
        break;
    case ExchangeRequest:
        user = ui->lineEdit_Username->text();
        token = ui->spinBox_Token->value();
        out << user << token;
        break;
    default:
        break;
    }
    udpSocket->writeDatagram(data, data.length(), serverAddr, serverPort);
}
