#ifndef DAILYNECESSITIES_H
#define DAILYNECESSITIES_H

#include "goods.h"

class DailyNecessities : public Goods
{
public:
    DailyNecessities();
    DailyNecessities(int id, QString dailyName, int amount, double price, QString owner, QDate produceDate, QDate validityDate);

    goodsClass getClass();
    double reducedPrice();
    QDate getProduceDate();
    QDate getValidityDate();
    QStringList toStringList();

private:
    QDate produceDate;
    QDate validityDate;
};

#endif // DAILYNECESSITIES_H
