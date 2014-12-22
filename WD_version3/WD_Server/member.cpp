#include "member.h"

Member::Member()
{
}

Member::Member(int id, QString userName, QString password, double balance, int level, int token)
    : Buyer(id, userName, password, balance)
{
    this->level = level;
    this->token = token;
}

Member::Member(Buyer buyer)
{
    this->id = buyer.getId();
    this->userName = buyer.getUserName();
    this->password = buyer.getPassword();
    this->balance = buyer.getBalance();
    this->level = 1;
    this->token = 0;
    for (int r = 0; r < buyer.recordCount(); ++r)
        this->record.push_back(buyer.getRecord(r));
}

userClass Member::getClass()
{
    return MEMBER;
}

int Member::getLevel()
{
    return level;
}

int Member::getToken()
{
    return token;
}

void Member::changeToken(int token)
{
    this->token += token;
}

void Member::setLevel(int level)
{
    this->level = level;
}

bool Member::operator <(const Member &rhs)
{
    return this->id < rhs.getId();
}

QDataStream &operator >>(QDataStream &in, Member &m)
{
    in >> m.id >> m.userName >> m.password >> m.balance >> m.level >> m.token >> m.record;
    return in;
}

QDataStream &operator <<(QDataStream &out, const Member &m)
{
    out << m.id << m.userName << m.password << m.balance << m.level << m.token << m.record;
    return out;
}
