#include "user.h"

User::User()
{
    this->id = 0;
    this->userName = "";
    this->password = "";
    this->balance = 0.0;
    this->status = false;
}

User::User(int id, QString userName, QString password, double balance)
{
    this->id = id;
    this->userName = userName;
    this->password = password;
    this->balance = balance;
    this->status = false;
}

User::~User()
{
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

double User::recharge(double money)
{
    balance += money;
    return this->balance;
}

bool User::login()
{
    status = true;
    return status;
}

bool User::logout()
{
    status = false;
    return status;
}

bool User::isLogin()
{
    return status;
}

bool User::isLogout()
{
    return status;
}
