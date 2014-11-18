#ifndef GOODS_H
#define GOODS_H

#include <QString>

class Goods
{
public:
    Goods();
    virtual double calcPrice() = 0;

protected:
    QString id;
    QString name;
    int amount;
    double price;
    QString owner;
};

#endif // GOODS_H
