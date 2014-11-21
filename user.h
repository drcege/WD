#ifndef USER_H
#define USER_H

#include <QString>
#include <QVector>

enum userClass{NO_EXIST, BUYER_Y, MEMBER_Y, SELLER_Y, BUYER_N, MEMBER_N, SELLER_N};

class User
{
public:
    User();
    User(int id, QString userName, QString password, double balance = 0.0);
    bool login();
    bool logout();
    //QVector<QString> viewSaleProductList();
    virtual void viewUserInfo();

protected:
    int id;
    QString userName;
    QString password;
    double balance;

public:
    int getId() {return id;}
    QString getUserName() {return userName;}
    QString getPassword() {return password;}
    double getBalance() { return balance;}
};

/******************************************************************************/

class Buyer : public User
{
public:
    Buyer();
    Buyer(int id, QString userName, QString password, double balance = 0.0);
    userClass getClass();
    void viewUserInfo();
    void recharge(double money);
};

/******************************************************************************/

class Member : public Buyer
{
public:
    Member();
    Member(int id, QString userName, QString password, double balance = 0.0, int level = 0, int token = 0);
    userClass getClass();
    void viewUserInfo();

private:
    int level;
    int token;
};

/******************************************************************************/

class Seller : public User
{
public:
    Seller();
    Seller(int id, QString userName, QString password, double balance = 0.0);
    userClass getClass();
    void viewUserInfo();
};

#endif // USER_H
