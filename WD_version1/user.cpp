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


/******************************************************************************/

Buyer::Buyer()
{
}

Buyer::Buyer(int id, QString userName, QString password, double balance)
    :User(id, userName, password, balance)
{
    curClass = BUYER;
}

void Buyer::recharge(double money)
{
    balance += money;
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


/******************************************************************************/

Seller::Seller()
{
}

Seller::Seller(int id, QString userName, QString password, double balance)
    :User(id, userName, password, balance)
{
    curClass = SELLER;
}

