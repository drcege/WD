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
}

bool User::login()
{
    return true;
}

bool User::logout()
{
    return true;
}

void User::viewUserInfo()
{

}

/******************************************************************************/

Buyer::Buyer()
{
}

Buyer::Buyer(int id, QString userName, QString password, double balance)
    :User(id, userName, password, balance)
{
    curClass = BUYER_Y;
}

void Buyer::viewUserInfo()
{

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
    curClass = MEMBER_Y;
}

void Member::viewUserInfo()
{

}

/******************************************************************************/

Seller::Seller()
{
}

Seller::Seller(int id, QString userName, QString password, double balance)
    :User(id, userName, password, balance)
{
    curClass = SELLER_Y;
}


void Seller::viewUserInfo()
{

}
