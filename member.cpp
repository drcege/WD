#include "member.h"

Member::Member()
{
}

Member::Member(QString id, QString userName, QString password, double balance, int level, int token)
    :Buyer(id, userName, password, balance)
{
    this->level = level;
    this->token = token;
}
