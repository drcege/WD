#ifndef MEMBER_H
#define MEMBER_H

#include "buyer.h"

class Member : public Buyer
{
public:
    Member();
    Member(QString id, QString userName, QString password, double balance = 0.0, int level = 0, int token = 0);

private:
    int level;
    int token;
};

#endif // MEMBER_H
