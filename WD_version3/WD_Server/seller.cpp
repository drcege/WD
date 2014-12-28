#include "seller.h"

Seller::Seller()
{
}

Seller::Seller(int id, QString userName, QString password, double balance)
    : User(id, userName, password, balance)
{
}

UserClass Seller::getClass()
{
    return SELLER;
}

QDataStream &operator >>(QDataStream &in, Seller &s)
{
    in >> s.id >> s.userName >> s.password >> s.balance;
    if(in.status() != QDataStream::Ok)
        throw QString("seller.dat 已损坏");
    return in;
}

QDataStream &operator <<(QDataStream &out, const Seller &s)
{
    out << s.id << s.userName << s.password << s.balance;
    return out;
}
