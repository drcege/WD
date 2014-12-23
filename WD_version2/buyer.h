#ifndef BUYER_H
#define BUYER_H

#include "user.h"

class Buyer : public User
{
public:
    Buyer();
    Buyer(int id, QString userName, QString password, double balance = 0.0);

    userClass getClass();
    int recordCount();
    int appendRecord(QStringList rec);
    QStringList getRecord(int i);

    friend QDataStream &operator>>(QDataStream &in, Buyer &b);
    friend QDataStream &operator<<(QDataStream &out, const Buyer &b);

protected:
    QVector<QStringList> record;
};

#endif // BUYER_H
