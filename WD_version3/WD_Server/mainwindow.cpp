#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
#include <QDebug>

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

    QDir dir;
    if(!dir.exists("data"))
        dir.mkdir("data");
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
    pos = -1;
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
    pos = -1;
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

QVector<QVector<QStringList> > MainWindow::getAllGoods()
{
    QVector<QVector<QStringList> > allGoods(3);
    for(int i = 0; i < listFood.count(); ++i) {
        allGoods[0].append(listFood[i].toStringList());
    }
    for(int i = 0; i < listElect.count(); ++i){
        allGoods[1].append(listElect[i].toStringList());
    }
    for(int i = 0; i < listDaily.count(); ++i){
        allGoods[2].append(listDaily[i].toStringList());
    }
    qDebug() << allGoods.size() << allGoods[0].size() << allGoods[1].size() << allGoods[2].size();
    return allGoods;
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
    QDir dir;
    if(!dir.exists("data"))
        dir.mkdir("data");
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
        // 输入
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);
        // 输出
        QByteArray dataout;
        QDataStream out(&dataout, QIODevice::WriteOnly);

        int type = 0, resCode = 0, pos = -1;
        QString reqUser;
        User* curUser;

        in >> type;
        switch (type) {
        case LoginRequest:
        {
            out << LoginResponse;
            QString pwd;
            in >> reqUser >> pwd;
            curUser = findUser(reqUser, pos);
            if (curUser == Q_NULLPTR) {
                resCode = -1;
                out << resCode << reqUser;
            } else if (pwd != curUser->getPassword()) {
                resCode = 1;
                out << resCode << reqUser;
            } else {    // 登陆成功
                resCode = 0;
                UserClass userClass = curUser->getClass();
                double balance = curUser->getBalance();
                int level = 0, token = 0;
                QVector<QStringList> vecRecord;
                QVector<QVector<QStringList> > vec2Goods(3);
                if(curUser->getClass() == MEMBER){    // 会员
                    Member* curMem = dynamic_cast<Member*>(curUser);
                    level = curMem->getLevel();
                    token = curMem->getToken();
                }
                if(curUser->getClass() != SELLER){
                    Buyer *curBuyer = dynamic_cast<Buyer *>(curUser);
                    for (int r = 0; r < curBuyer->recordCount(); ++r)
                        vecRecord.append(curBuyer->getRecord(r));
                }
                vec2Goods = getAllGoods();
                out << resCode << reqUser << userClass << balance << level << token << vecRecord << vec2Goods;
            }    // end of else
            break;
        }
        case RegisterRequest:
        {
            qDebug() << "RegisterRequest";
            out << RegisterResponse;
            QString pwd, repeat;
            int userClass;
            in >> reqUser >> pwd >> repeat >> userClass;
            if (findUser(reqUser, pos) != Q_NULLPTR) {    // 用户已存在
                resCode = 1;
            } else if (pwd != repeat) {    // 密码不一致
                resCode = -1;
            } else {
                resCode = 0;
                if (BUYER == userClass) { // 新建买家
                    Buyer curBuyer(++USERID, reqUser, pwd);
                    listBuyer.push_back(curBuyer);
                } else if (SELLER == userClass) { // 新建卖家
                    Seller curSeller(++USERID, reqUser, pwd);
                    listSeller.push_back(curSeller);
                }
            }
            out << resCode << reqUser;
            qDebug() << "RegisterResponse";
            break;
        }
        case BuyRequest:
        {
            out << BuyResponse;
            int id, amount;
            double pay;
            in >> reqUser >> id >> amount >> pay;
            curUser = findUser(reqUser, pos);
            if (pay > curUser->getBalance()) {
                resCode = -1;
                out << resCode << reqUser;
                qDebug() << "buy false";
            } else {
                resCode = 0;
                // 商品数量减少
                Goods *curGoods = findGoods(id, pos);
                int curAmount = curGoods->changeAmount(-1 * amount);
                if (0 == curAmount) {
                    if(FOOD == curGoods->getClass())
                        listFood.removeAt(pos);
                    else if(ELECTRONICS == curGoods->getClass())
                        listElect.removeAt(pos);
                    else
                        listDaily.removeAt(pos);
                }
                // 买家支付
                double curBalance = curUser->recharge(-1 * pay);
                // 会员获得代币
                int curToken = 0;
                if (MEMBER == curUser->getClass()) {
                    int addTokens = qFloor(pay/10);
                    curToken = dynamic_cast<Member *>(curUser)->changeToken(addTokens);
                }
                // 卖家收入
                User* seller = findUser(curGoods->getOwner(), pos);
                seller->recharge(pay);
                // 购买记录
                QStringList record;
                record << QDate::currentDate().toString(Qt::ISODate) << QString::number(amount) << "￥" + QString::number(pay, 'f', 2) << curGoods->getGoodsName();
                dynamic_cast<Buyer *>(curUser)->appendRecord(record);
                out << resCode << reqUser << id << curAmount << curBalance << curToken << record;
            }
            break;
        }
        case StockRequest:
        {
            out << StockResponse;
            int goodsClass, amount, index;
            double price, rate;
            QString goodsName;
            QStringList newGoods;
            QDate produceDate, validityDate, reduceDate;
            in >> reqUser >> goodsClass >> goodsName >> amount >> price >> produceDate >> validityDate >> reduceDate >> rate;
            if (FOOD == goodsClass) {
                index = 0;
                Food food(++GOODSID, goodsName, amount, price, reqUser, produceDate, validityDate, reduceDate, rate);
                listFood.push_back(food);
                newGoods = food.toStringList();
            } else if (ELECTRONICS == goodsClass) {
                index = 1;
                Electronics elect(++GOODSID, goodsName, amount, price, reqUser, produceDate, validityDate, rate);
                listElect.push_back(elect);
                newGoods = elect.toStringList();
            } else {
                index = 2;
                DailyNecessities daily(++GOODSID, goodsName, amount, price, reqUser, produceDate, validityDate);
                listDaily.push_back(daily);
                newGoods = daily.toStringList();
            }
            resCode = 0;
            out << resCode << reqUser << index << newGoods;
            break;
        }
        case RechargeRequest:
        {
            out << RechargeResponse;
            double money;
            in >> reqUser >> money;
            curUser = findUser(reqUser, pos);
            double balance = curUser->recharge(money);
            out << reqUser << balance;
            break;
        }
        case UpgradeRequest:
        {
            out << UpgradeResponse;
            in >> reqUser;
            int level, token;
            double balance;
            curUser = findUser(reqUser, pos);
            if (BUYER == curUser->getClass()) {    //买家升级
                if (curUser->getBalance() < LIMIT) {
                    resCode = -1;
                    out << resCode << reqUser;
                } else {
                    resCode = 0;
                    balance = curUser->recharge(-1 * LIMIT);
                    Member newMember(*(dynamic_cast<Buyer *>(curUser)));
                    listMember.append(newMember);
                    listBuyer.removeAt(pos);
                    level = 1;
                    token = 0;
                    out << resCode << reqUser << level << token << balance;
                }
            } else {    //会员升级
                level = dynamic_cast<Member *>(curUser)->getLevel();
                token = dynamic_cast<Member *>(curUser)->getToken();
                if (token < level * 1000) {
                    resCode = -1;
                    out << resCode << reqUser;
                } else {
                    resCode = 0;
                    token = dynamic_cast<Member *>(curUser)->changeToken(-1000 * level);
                    level += 1;
                    dynamic_cast<Member *>(curUser)->setLevel(level);
                    balance = curUser->getBalance();
                    out << resCode << reqUser << level << token << balance;
                }
            }
            break;
        }
        case ExchangeRequest:
        {
            out << ExchangeResponse;
            double balance;
            int token;
            in >> reqUser >> token;
            curUser = findUser(reqUser, pos);
            balance = dynamic_cast<Member *>(curUser)->recharge(token / 10.0);
            token = dynamic_cast<Member *>(curUser)->changeToken(-1 * token);
            resCode = 0;
            out << resCode << reqUser << balance << token;
            break;
        }
        default:
            break;
        }
        udpSocket->writeDatagram(dataout, dataout.length(), QHostAddress::Broadcast, clientPort);
    }
}
