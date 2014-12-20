#include "seller.h"

Seller::Seller()
{
}

Seller::Seller(int id, QString userName, QString password, double balance)
    : User(id, userName, password, balance)
{
    curClass = SELLER;
}

QDataStream &operator >>(QDataStream &in, Seller &s)
{
    in >> s.id >> s.userName >> s.password >> s.balance;
    s.curClass = SELLER;
    return in;
}

QDataStream &operator <<(QDataStream &out, const Seller &s)
{
    out << s.id << s.userName << s.password << s.balance;
    return out;
}
