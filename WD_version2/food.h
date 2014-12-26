#ifndef FOOD_H
#define FOOD_H

#include "goods.h"

class Food : public Goods
{
public:
    Food();
    Food(int id, QString goodsName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, QDate reduceDate, double reduceRate);

    GoodsClass getClass();
    double reducedPrice();
    QDate getProduceDate();
    QDate getValidityDate();
    QDate getReduceDate();
    double getReduceRate();
    QStringList toStringList();

    friend QDataStream &operator>>(QDataStream &in, Food &);
    friend QDataStream &operator<<(QDataStream &out, const Food &);

private:
    QDate produceDate;
    QDate validityDate;
    QDate reduceDate;
    double reduceRate;
};

#endif // FOOD_H
