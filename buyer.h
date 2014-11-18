#ifndef BUYER_H
#define BUYER_H

#include "user.h"

class Buyer : public User
{
public:
    Buyer();
    Buyer(QString id, QString userName, QString password, double balance = 0.0);
    void recharge(double money);
};

#endif // BUYER_H
