#ifndef MEMBER_H
#define MEMBER_H

#include "buyer.h"

class Member : public Buyer
{
public:
    Member();
    Member(int id, QString userName, QString password, double balance = 0.0, int level = 0, int token = 0);
    Member(Buyer buyer);

    userClass getClass();
    int getLevel();
    int getToken();
    void setLevel(int level);
    void changeToken(int token);

    friend QDataStream &operator>>(QDataStream &in, Member &m);
    friend QDataStream &operator<<(QDataStream &out, const Member &m);

private:
    int level;
    int token;
};


#endif // MEMBER_H
