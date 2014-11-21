#ifndef GOODS_H
#define GOODS_H

#include <QString>
#include <QDate>

class Goods
{
public:
    Goods();
    Goods(int id, QString foodName, int amount, double price, QString owner);
    virtual double calcPrice() = 0;

protected:
    int id;
    QString foodName;
    int amount;
    double price;
    QString owner;

public:
    int getId() {return id;}
    QString getFoodName() {return foodName;}
    int getAmount() {return amount;}
    double getPrice() {return price;}
    QString getOwner() {return owner;}
};

/******************************************************************************/

class Food : public Goods
{
public:
    Food();
    Food(int id, QString foodName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, QDate reduceDate);
    double calcPrice();

private:
    QDate produceDate;
    QDate validityDate;
    QDate reduceDate;

public:
    QDate getProduceDate() {return produceDate;}
    QDate getValidityDate() {return validityDate;}
    QDate getReduceDate() {return reduceDate;}
};

/******************************************************************************/

class Electronics : public Goods
{
public:
    Electronics();
    double calcPrice();
};

/******************************************************************************/

class DailyNecessities : public Goods
{
public:
    DailyNecessities();
    double calcPrice();
};

#endif // GOODS_H
