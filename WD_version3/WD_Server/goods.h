#ifndef GOODS_H
#define GOODS_H

#include <QString>
#include <QDate>
#include <QFile>
#include <QDataStream>

enum goodsClass {FOOD, ELECTRONICS, DAILYNECESSITIES};

class Goods
{
public:
    Goods();
    virtual ~Goods();
    Goods(int id, QString goodsName, int amount, double price, QString owner);

    int getId() const;
    int getAmount();
    double getPrice();
    QString getOwner();
    QString getGoodsName();

    void changeAmount(int amount);
    virtual goodsClass getClass() = 0;
    virtual double reducedPrice() = 0;

protected:
    int id;
    QString goodsName;
    int amount;
    double price;
    QString owner;
};

#endif // GOODS_H
