#ifndef GOODS_H
#define GOODS_H

#include <QString>
#include <QDate>
#include <QFile>
#include <QDataStream>

enum GoodsClass {FOOD, ELECTRONICS, DAILYNECESSITIES};

class Goods
{
public:
    Goods();
    Goods(int id, QString goodsName, int amount, double price, QString owner);
    virtual ~Goods();

    int getId() const;
    int getAmount() const;
    double getPrice() const;
    QString getOwner() const;
    QString getGoodsName() const;
    int changeAmount(int amount);
    virtual GoodsClass getClass() = 0;
    virtual double reducedPrice() = 0;

protected:
    int id;
    QString goodsName;
    int amount;
    double price;
    QString owner;
};

#endif // GOODS_H
