#ifndef MEMBER_H
#define MEMBER_H

#include "buyer.h"

class Member : public Buyer
{
public:
    Member();
    Member(int id, QString userName, QString password, double balance = 0.0, int level = 0, int token = 0);
    Member(Buyer buyer);

    UserClass getClass();
    int getLevel() const;
    int getToken() const;
    int setLevel(int level);
    int changeToken(int token);

    friend QDataStream &operator>>(QDataStream &in, Member &m);
    friend QDataStream &operator<<(QDataStream &out, const Member &m);

private:
    int level;
    int token;
};


#endif // MEMBER_H
