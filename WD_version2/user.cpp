#include "user.h"

User::User()
{
    this->id = 0;
    this->userName = "";
    this->password = "";
    this->balance = 0.0;
}

User::~User()
{

}

User::User(int id, QString userName, QString password, double balance)
{
    this->id = id;
    this->userName = userName;
    this->password = password;
    this->balance = balance;
    this->curClass = USER;
}

void User::recharge(double money)
{
    balance += money;
}


/******************************************************************************/

Buyer::Buyer()
{
}

Buyer::Buyer(int id, QString userName, QString password, double balance)
    :User(id, userName, password, balance)
{
    curClass = BUYER;
}

int Buyer::recordCount()
{
    return record.count();
}

QStringList Buyer::getRecord(int i)
{
    return record.at(i);
}

int Buyer::appendRecord(QStringList rec)
{
    record.append(rec);
    return record.count();
}

QDataStream &operator>>(QDataStream &in, Buyer &b)
{
    in >> b.id >> b.userName >> b.password >> b.balance >> b.record;
    b.curClass = BUYER;
    return in;
}

QDataStream &operator <<(QDataStream &out, Buyer& b)
{
    out << b.id << b.userName << b.password << b.balance << b.record;
    return out;
}

/******************************************************************************/

Member::Member()
{
}

Member::Member(int id, QString userName, QString password, double balance, int level, int token)
    :Buyer(id, userName, password, balance)
{
    this->level = level;
    this->token = token;
    curClass = MEMBER;
}

Member::Member(Buyer buyer)
{
    curClass = MEMBER;
    this->id = buyer.getId();
    this->userName = buyer.getUserName();
    this->password = buyer.getPassword();
    this->balance = buyer.getBalance();
    this->level = 1;
    this->token = 0;
    for(int r = 0; r < buyer.recordCount(); ++r)
        this->record.push_back(buyer.getRecord(r));
}

void Member::changeToken(int token)
{
    this->token += token;
}

void Member::setLevel(int level)
{
    this->level = level;
}

QDataStream &operator >>(QDataStream& in, Member& m)
{
    in >> m.id >> m.userName >> m.password >> m.balance >> m.level >> m.token >> m.record;
    m.curClass = MEMBER;
    return in;
}

QDataStream &operator <<(QDataStream& out, Member& m)
{
    out << m.id << m.userName << m.password << m.balance << m.level << m.token << m.record;
    return out;
}

/******************************************************************************/

Seller::Seller()
{
}

Seller::Seller(int id, QString userName, QString password, double balance)
    :User(id, userName, password, balance)
{
    curClass = SELLER;
}

QDataStream &operator >>(QDataStream& in, Seller& s)
{
    in >> s.id >> s.userName >> s.password >> s.balance;
    s.curClass = SELLER;
    return in;
}

QDataStream &operator <<(QDataStream& out, Seller& s)
{
    out << s.id << s.userName << s.password << s.balance;
    return out;
}
