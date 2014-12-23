#ifndef FOOD_H
#define FOOD_H

#include "goods.h"

class Food : public Goods
{
public:
    Food();
    Food(int id, QString goodsName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, QDate reduceDate, double reduceRate);

    goodsClass getClass();
    double reducedPrice();
    QDate getProduceDate();
    QDate getValidityDate();
    QDate getReduceDate();
    double getReduceRate();
    QStringList toStringList();

private:
    QDate produceDate;
    QDate validityDate;
    QDate reduceDate;
    double reduceRate;
};

#endif // FOODS_H
