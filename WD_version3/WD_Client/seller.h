#ifndef SELLER_H
#define SELLER_H

#include "user.h"

class Seller : public User
{
public:
    Seller();
    Seller(int id, QString userName, QString password, double balance = 0.0);
    UserClass getClass();

    friend QDataStream &operator>>(QDataStream &in, Seller &s);
    friend QDataStream &operator<<(QDataStream &in, const Seller &s);
};

#endif // SELLER_H
