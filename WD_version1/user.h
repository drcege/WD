#ifndef USER_H
#define USER_H

#include <QString>
#include <QVector>
#include <QStringList>

enum userClass {BUYER, MEMBER, SELLER};

class User
{
public:
    User();
    User(int id, QString userName, QString password, double balance = 0.0);
    virtual ~User();

    int getId() const;
    QString getUserName() const;
    QString getPassword() const;
    double getBalance() const;
    void recharge(double money);
    bool login();
    bool logout();
    bool isLogin();
    bool isLogout();
    virtual userClass getClass() = 0;

protected:
    int id;
    QString userName;
    QString password;
    double balance;
    bool status;
};

#endif // USER_H
