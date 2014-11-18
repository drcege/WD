#ifndef USER_H
#define USER_H

#include <QString>
#include <QVector>

class User
{
public:
    User();
    User(QString id, QString userName, QString password, double balance = 0.0);
    bool login();
    bool logout();
    //QVector<QString> viewSaleProductList();
    //virtual void viewUserInfo();

protected:
    QString id;
    QString userName;
    QString password;
    double balance;

public:
    QString getId() {return id;}
    QString getUserName() {return userName;}
    QString getPassword() {return password;}
    double getBalance() { return balance;}
};

#endif // USER_H
