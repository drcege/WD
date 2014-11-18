#include "user.h"

User::User()
{
    this->id = "";
    this->userName = "";
    this->password = "";
    this->balance = 0.0;
}

User::User(QString id, QString userName, QString password, double balance)
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
