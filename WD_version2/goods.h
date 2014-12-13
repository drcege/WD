#ifndef GOODS_H
#define GOODS_H

#include <QString>
#include <QDate>
#include <QFile>
#include <QDataStream>

enum goodsClass{GOODS, FOOD, ELECTRONICS, DAILYNECESSITIES};
class Goods
{
public:
    Goods();
    virtual ~Goods();
    Goods(int id, QString goodsName, int amount, double price, QString owner);
    int getId() const {return id;}
    int getAmount() {return amount;}
    double getPrice() {return price;}
    QString getOwner() {return owner;}
    QString getGoodsName() {return goodsName;}

    goodsClass getClass() {return curClass;}
    void changeAmount(int amount);
    virtual double reducedPrice() = 0;

protected:
    int id;
    QString goodsName;
    int amount;
    double price;
    QString owner;
    goodsClass curClass;
};

/******************************************************************************/

class Food : public Goods
{
public:
    Food();
    Food(int id, QString goodsName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, QDate reduceDate, double reduceRate);
    QDate getProduceDate() {return produceDate;}
    QDate getValidityDate() {return validityDate;}
    QDate getReduceDate() {return reduceDate;}
    double getReduceRate() {return reduceRate;}
    double reducedPrice();
    friend QDataStream &operator>>(QDataStream& in, Food&);
    friend QDataStream &operator<<(QDataStream& out, Food&);

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
    friend QDataStream &operator>>(QDataStream& in, Electronics& e);
    friend QDataStream &operator<<(QDataStream& out, Electronics& e);

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
    friend QDataStream &operator>>(QDataStream& in, DailyNecessities& d);
    friend QDataStream &operator<<(QDataStream& out, DailyNecessities& d);

private:
    QDate produceDate;
    QDate validityDate;
};

#endif // GOODS_H
