#ifndef DAILYNECESSITIES_H
#define DAILYNECESSITIES_H

#include "goods.h"

class DailyNecessities : public Goods
{
public:
    DailyNecessities();
    DailyNecessities(int id, QString dailyName, int amount, double price, QString owner, QDate produceDate, QDate validityDate);

    GoodsClass getClass();
    double reducedPrice();
    QDate getProduceDate() const;
    QDate getValidityDate() const;
    QStringList toStringList();

    friend QDataStream &operator>>(QDataStream &in, DailyNecessities &d);
    friend QDataStream &operator<<(QDataStream &out, const DailyNecessities &d);

private:
    QDate produceDate;
    QDate validityDate;
};

#endif // DAILYNECESSITIES_H
