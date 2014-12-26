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

UserClass Member::getClass()
{
    return MEMBER;
}

int Member::getLevel() const
{
    return this->level;
}

int Member::getToken() const
{
    return this->token;
}

int Member::setLevel(int level)
{
    this->level = level;
    return this->level;
}

int Member::changeToken(int token)
{
    this->token += token;
    return this->token;
}

QDataStream &operator >>(QDataStream &in, Member &m)
{
    in >> m.id >> m.userName >> m.password >> m.balance >> m.level >> m.token >> m.record;
    if(in.status() != QDataStream::Ok)
        throw QString("member.dat 已损坏");
    return in;
}

QDataStream &operator <<(QDataStream &out, const Member &m)
{
    out << m.id << m.userName << m.password << m.balance << m.level << m.token << m.record;
    return out;
}
