#ifndef GOODS_H
#define GOODS_H

#include <QString>
#include <QStringList>
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
    virtual double reducedPrice() = 0;
    virtual goodsClass getClass() = 0;
    virtual QStringList toStringList() = 0;



protected:
    int id;
    QString goodsName;
    int amount;
    double price;
    QString owner;
};

#endif // GOODS_H
