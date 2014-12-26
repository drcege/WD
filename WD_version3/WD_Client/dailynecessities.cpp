#include "dailynecessities.h"

DailyNecessities::DailyNecessities()
{
}

DailyNecessities::DailyNecessities(int id, QString dailyName, int amount, double price, QString owner, QDate produceDate, QDate validityDate)
    : Goods(id, dailyName, amount, price, owner)
{
    this->produceDate = produceDate;
    this->validityDate = validityDate;
}

QDate DailyNecessities::getProduceDate()
{
    return produceDate;
}

QDate DailyNecessities::getValidityDate()
{
    return validityDate;
}

double DailyNecessities::reducedPrice()
{
    if (QDate::currentDate() > validityDate)
        return -1;
    return price;
}

GoodsClass DailyNecessities::getClass()
{
    return DAILYNECESSITIES;
}

QDataStream &operator>>(QDataStream &in, DailyNecessities &d)
{
    in >> d.id >> d.goodsName >> d.amount >> d.price >> d.owner >> d.produceDate >> d.validityDate;
    return in;
}

QDataStream &operator<<(QDataStream &out, const DailyNecessities &d)
{
    out << d.id << d.goodsName << d.amount << d.price << d.owner << d.produceDate << d.validityDate;
    return out;
}
