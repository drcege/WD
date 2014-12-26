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

User::~User()
{
}

int User::getId() const
{
    return this->id;
}

QString User::getUserName() const
{
    return this->userName;
}

QString User::getPassword() const
{
    return this->password;
}

double User::getBalance() const
{
    return this->balance;
}

double User::recharge(double money)
{
    balance += money;
    return this->balance;
}
