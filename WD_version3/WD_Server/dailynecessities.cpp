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

goodsClass DailyNecessities::getClass()
{
    return DAILYNECESSITIES;
}

QStringList DailyNecessities::toStringList()
{
    QStringList sl;
    QString reduced = (reducedPrice() < 0 ? "已过期" : QString::number(reducedPrice(), 'f', 2));
    sl << "" << getGoodsName() << QString::number(getAmount()) << QString::number(getPrice(), 'f', 2) << reduced << getOwner() << QString::number(getId()) << getProduceDate().toString(Qt::ISODate) << getValidityDate().toString(Qt::ISODate) << "-" << "-" ;
    return sl;
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
