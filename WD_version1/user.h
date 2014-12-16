#ifndef USER_H
#define USER_H

#include <QString>
#include <QVector>
#include <QStringList>

enum userClass {USER, BUYER, MEMBER, SELLER};

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
    userClass curClass;

public:
    int getId() const {return id;}
    QString getUserName() {return userName;}
    QString getPassword() {return password;}
    double getBalance() { return balance;}
    virtual userClass getClass() {return curClass;}
};

/******************************************************************************/

class Buyer : public User
{
public:
    Buyer();
    Buyer(int id, QString userName, QString password, double balance = 0.0);
    int recordCount();
    QStringList getRecord(int i);
    int appendRecord(QStringList rec);

protected:
    QVector<QStringList> record;
};

/******************************************************************************/

class Member : public Buyer
{
public:
    Member();
    Member(int id, QString userName, QString password, double balance = 0.0, int level = 0, int token = 0);
    Member(Buyer buyer);
    void changeToken(int token);
    void setLevel(int level);
    bool operator < (const Member &rhs)
    {
        return id < rhs.getId();
    }


private:
    int level;
    int token;

public:
    int getLevel() {return level;}
    int getToken() {return token;}
};

/******************************************************************************/

class Seller : public User
{
public:
    Seller();
    Seller(int id, QString userName, QString password, double balance = 0.0);
};

#endif // USER_H
