#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "goods.h"

class Electronics : public Goods
{
public:
    Electronics();
    Electronics(int id, QString electName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, double reduceRate);

    QDate getProduceDate();
    QDate getValidityDate();
    double getRuduceRate();

    double reducedPrice();
    goodsClass getClass();
    QStringList toStringList();
    friend QDataStream &operator>>(QDataStream &in, Electronics &e);
    friend QDataStream &operator<<(QDataStream &out, const Electronics &e);

private:
    QDate produceDate;
    QDate validityDate;
    double reduceRate;
};


#endif // ELECTRONICS_H
