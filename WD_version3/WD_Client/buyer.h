#ifndef BUYER_H
#define BUYER_H

#include "user.h"

class Buyer : public User
{
public:
    Buyer();
    Buyer(int id, QString userName, QString password, double balance = 0.0);
    UserClass getClass();
    QStringList getRecord(int i);
    int recordCount();
    int appendRecord(QStringList rec);

    friend QDataStream &operator>>(QDataStream &in, Buyer &b);
    friend QDataStream &operator<<(QDataStream &out, const Buyer &b);

protected:
    QVector<QStringList> record;
};

#endif // BUYER_H
