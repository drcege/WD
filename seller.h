#ifndef SELLER_H
#define SELLER_H

#include "user.h"

class Seller : public User
{
public:
    Seller();
    Seller(QString id, QString userName, QString password, double balance = 0.0);
};

#endif // SELLER_H
