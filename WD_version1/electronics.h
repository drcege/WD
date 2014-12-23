#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "goods.h"

class Electronics : public Goods
{
public:
    Electronics();
    Electronics(int id, QString electName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, double reduceRate);

    goodsClass getClass();
    double reducedPrice();
    QDate getProduceDate();
    QDate getValidityDate();
    double getReduceRate();
    QStringList toStringList();

private:
    QDate produceDate;
    QDate validityDate;
    double reduceRate;
};

#endif // ELECTRONICS_H
