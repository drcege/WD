#ifndef USER_H
#define USER_H

#include <QString>
#include <QVector>
#include <QStringList>

enum UserClass {BUYER, MEMBER, SELLER};

class User
{
public:
    User();
    virtual ~User();
    User(int id, QString userName, QString password, double balance = 0.0);
    void recharge(double money);

protected:
    int id;
    QString userName;
    QString password;
    double balance;
    UserClass curClass;

public:
    int getId() const;
    QString getUserName();
    QString getPassword();
    double getBalance();
    virtual UserClass getClass() = 0;
};

#endif // USER_H
