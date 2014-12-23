#include "buyer.h"

Buyer::Buyer()
{
}

Buyer::Buyer(int id, QString userName, QString password, double balance)
    : User(id, userName, password, balance)
{
}

userClass Buyer::getClass()
{
    return BUYER;
}

int Buyer::recordCount()
{
    return record.count();
}

int Buyer::appendRecord(QStringList rec)
{
    record.append(rec);
    return record.count();
}

QStringList Buyer::getRecord(int i)
{
    return record.at(i);
}
