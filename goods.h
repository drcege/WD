#ifndef GOODS_H
#define GOODS_H

#include <QString>
#include <QDate>

class Goods
{
public:
    Goods();
    Goods(int id, QString foodName, int amount, double price, QString owner);
    int getId() {return id;}
    int getAmount() {return amount;}
    double getPrice() {return price;}
    QString getOwner() {return owner;}
    QString getFoodName() {return foodName;}
    virtual double reducedPrice() = 0;

protected:
    int id;
    QString foodName;
    int amount;
    double price;
    QString owner;
};

/******************************************************************************/

class Food : public Goods
{
public:
    Food();
    Food(int id, QString foodName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, QDate reduceDate, double reduceRate);
    QDate getProduceDate() {return produceDate;}
    QDate getValidityDate() {return validityDate;}
    QDate getReduceDate() {return reduceDate;}
    double getReduceRate() {return reduceRate;}
    double reducedPrice();

private:
    QDate produceDate;
    QDate validityDate;
    QDate reduceDate;
    double reduceRate;
};

/******************************************************************************/

class Electronics : public Goods
{
public:
    Electronics();
    Electronics(int id, QString electName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, double reduceRate);
    QDate getProduceDate() {return produceDate;}
    QDate getValidityDate() {return validityDate;}
    double getRuduceRate() {return reduceRate;}
    double reducedPrice();

private:
    QDate produceDate;
    QDate validityDate;
    double reduceRate;
};

/******************************************************************************/

class DailyNecessities : public Goods
{
public:
    DailyNecessities();
    DailyNecessities(int id, QString dailyName, int amount, double price, QString owner, QDate produceDate, QDate validityDate);
    QDate getProduceDate() {return produceDate;}
    QDate getValidityDate() {return validityDate;}
    double reducedPrice();

private:
    QDate produceDate;
    QDate validityDate;
};

#endif // GOODS_H
