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

int User::getId() const
{
    return id;
}

QString User::getUserName() const
{
    return userName;
}

QString User::getPassword() const
{
    return password;
}

double User::getBalance() const
{
    return balance;
}

void User::recharge(double money)
{
    balance += money;
}
