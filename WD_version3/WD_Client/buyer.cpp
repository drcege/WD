#include "buyer.h"

Buyer::Buyer()
{
}

Buyer::Buyer(int id, QString userName, QString password, double balance)
    : User(id, userName, password, balance)
{
}

UserClass Buyer::getClass()
{
    return BUYER;
}

int Buyer::recordCount()
{
    return record.count();
}

QStringList Buyer::getRecord(int i)
{
    return record.at(i);
}

int Buyer::appendRecord(QStringList rec)
{
    record.append(rec);
    return record.count();
}

QDataStream &operator>>(QDataStream &in, Buyer &b)
{
    in >> b.id >> b.userName >> b.password >> b.balance >> b.record;
    return in;
}

QDataStream &operator <<(QDataStream &out, const Buyer &b)
{
    out << b.id << b.userName << b.password << b.balance << b.record;
    return out;
}
