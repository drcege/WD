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

        User* curUser;
        QString user, pwd, repeat, goodsClass, userClass, name, owner;
        QVector<QStringList> vecRecord;
        QVector<QVector<QStringList> > vecGoods(3);
        double pay, money;
        int id, amount, token, pos;
        double price, rate;
        QDate produceDate, validityDate, reduceDate;

        int type;
        in >> type;
        switch (type) {
        case LoginRequest:
            in >> user >> pwd;
            out << LoginResponse;
            curUser = findUser(user, pos);
            if (curUser == Q_NULLPTR || pwd != curUser->getPassword()){
                out << false;
            }
            else {    // 登陆成功
                out << true;
                out << curUser->getUserName();
                switch(curUser->getClass()){
                case BUYER:
                    userClass = "买家"; break;
                case MEMBER:
                    userClass = "会员"; break;
                case SELLER:
                    userClass = "卖家"; break;
                }
                out << userClass;
                out << QString::number(curUser->getBalance(), 'f', 2);
                vecRecord.clear();
                if(curUser->getClass() == SELLER){    // 卖家
                    out << QString() << QString() << vecRecord;
                }else {
                    Buyer *curBuyer = dynamic_cast<Buyer *>(curUser);
                    for (int r = 0; r < curBuyer->recordCount(); ++r)
                        vecRecord.append(curBuyer->getRecord(r));
                    if(curUser->getClass() == MEMBER){    // 会员
                        Member* curMem = dynamic_cast<Member*>(curUser);
                        out << QString::number(curMem->getLevel()) << QString::number(curMem->getToken()) << vecRecord;
                    }
                    else {    // 买家
                        out << QString() << QString() << vecRecord;
                    }
                }    // end of 非卖家
                vecGoods = getAllGoods();
                out << vecGoods;
            }    // end of 成功
            break;
        case RegisterRequest:
            in >> user >> pwd >> repeat >> userClass;
            out << RegisterResponse;
            if (pwd != repeat) {    // 密码不一致
                out << 0;
                break;
            }
            if (findUser(user, pos) != Q_NULLPTR) {    // 用户已存在
                out << -1;
                break;
            }
            if (userClass == "买家") { // 新建买家
                Buyer curBuyer(++USERID, user, pwd);
                listBuyer.push_back(curBuyer);
            } else if (userClass == "卖家") { // 新建卖家
                Seller curSeller(++USERID, user, pwd);
                listSeller.push_back(curSeller);
            }
            out << 1;
            break;
        case BuyRequest:
            in >> user >> id >> amount >> pay;
            out << BuyResponse;
            curUser = findUser(user, pos);
            if (pay > curUser->getBalance()) {
                out << false;
                qDebug() << "buy false";
            } else {
                out << true;
                // 买家支付
                curUser->recharge(-1 * pay);
                // 获得代币
                if (MEMBER == curUser->getClass()) {
                    int addtokens = qFloor(pay/10);
                    dynamic_cast<Member *>(curUser)->changeToken(addtokens);
                }
                // 商品数量减少
                Goods *curGoods = findGoods(id, pos);
                curGoods->changeAmount(-1 * amount);
                if (0 == curGoods->getAmount()) {
                    if(curGoods->getClass() == FOOD)
                        listFood.removeAt(pos);
                    else if(curGoods->getClass() == ELECTRONICS)
                        listElect.removeAt(pos);
                    else
                        listDaily.removeAt(pos);
                }
                // 卖家收入
                User* seller = findUser(curGoods->getOwner(), pos);
                seller->recharge(pay);
                out << QString::number(id) << QString::number(curGoods->getAmount()) << user << QString::number(curUser->getBalance());
                if(curUser->getClass() == MEMBER)
                    out << QString::number(dynamic_cast<Member *>(curUser)->getToken());
                else
                    out << QString::number(0);
                QStringList rec;
                rec << QDate::currentDate().toString(Qt::ISODate) << QString::number(amount) << "￥" + QString::number(pay, 'f', 2) << curGoods->getGoodsName();
                dynamic_cast<Buyer *>(curUser)->appendRecord(rec);
                out << rec;
            }
            break;
        case StockRequest:
            in >> goodsClass >> name >> amount >> price >> owner >> produceDate >> validityDate >> reduceDate >> rate;
            out << StockResponse;
            if ("食品" == goodsClass) {
                Food food(++GOODSID, name, amount, price, owner, produceDate, validityDate, reduceDate, rate);
                listFood.push_back(food);
                out << 0 << food.toStringList();
            } else if ("电子产品" == goodsClass) {
                Electronics elect(++GOODSID, name, amount, price, owner, produceDate, validityDate, rate);
                listElect.push_back(elect);
                out << 1 << elect.toStringList();
            } else {
                DailyNecessities daily(++GOODSID, name, amount, price, owner, produceDate, validityDate);
                listDaily.push_back(daily);
                out << 2 << daily.toStringList();
            }
            break;
        case RechargeRequest:
            in >> user >> money;
            out << RechargeResponse;
            curUser = findUser(user, pos);
            curUser->recharge(money);
            out << user << QString::number(curUser->getBalance(), 'f', 2);
            break;
        case UpgradeRequest:
            in >> user;
            out << UpgradeResponse << user;
            curUser = findUser(user, pos);
            if (BUYER == curUser->getClass()) {
                if (curUser->getBalance() < LIMIT)
                    out << false << QString() << QString() << QString();
                else {
                    curUser->recharge(-1 * LIMIT);
                    Member newMember(*(dynamic_cast<Buyer *>(curUser)));
                    ///////////////// 查找插入位置！！！！！！！！！！！！
                    QList<Member>::iterator newPos =  qLowerBound(listMember.begin(), listMember.end(), newMember);
                    listMember.insert(newPos, newMember);
                    listBuyer.removeAt(pos);
                    out << true << QString("1") << QString::number(newMember.getBalance(), 'f', 2) << "0";
                }
            } else {
                int token = dynamic_cast<Member *>(curUser)->getToken();
                int level = dynamic_cast<Member *>(curUser)->getLevel();
                if (token < level * 1000)
                    out << false << QString() << QString() << QString();
                else {
                    dynamic_cast<Member *>(curUser)->changeToken(-1000 * level);
                    level += 1;
                    dynamic_cast<Member *>(curUser)->setLevel(level);
                    out << true << QString::number(level) << QString::number(curUser->getBalance(), 'f', 2) << QString::number(token - level * 1000);
                }
            }
            break;
        case ExchangeRequest:
            in >> user >> token;
            out << ExchangeResponse;
            curUser = findUser(user, pos);
            dynamic_cast<Member *>(curUser)->recharge(token / 10.0);
            dynamic_cast<Member *>(curUser)->changeToken(-1 * token);
            out << user << QString::number(curUser->getBalance(), 'f', 2) << QString::number(dynamic_cast<Member *>(curUser)->getToken());
            break;
        default:
            break;
        }
        udpSocket->writeDatagram(dataout, dataout.length(), QHostAddress::Broadcast, clientPort);
    }
}
