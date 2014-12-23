#ifndef GOODS_H
#define GOODS_H

#include <QString>
#include <QStringList>
#include <QDate>

enum goodsClass {FOOD, ELECTRONICS, DAILYNECESSITIES};

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
