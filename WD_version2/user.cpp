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


/******************************************************************************/

Seller::Seller()
{
}

Seller::Seller(int id, QString userName, QString password, double balance)
    :User(id, userName, password, balance)
{
    curClass = SELLER;
}

