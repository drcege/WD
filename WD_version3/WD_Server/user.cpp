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
}

void User::recharge(double money)
{
    balance += money;
}

int User::getId() const
{
    return id;
}

QString User::getUserName()
{
    return userName;
}

QString User::getPassword()
{
    return password;
}

double User::getBalance()
{
    return balance;
}
