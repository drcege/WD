#include "user.h"

User::User()
{
    this->id = 0;
    this->userName = "";
    this->password = "";
    this->balance = 0.0;
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

