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

GoodsClass DailyNecessities::getClass()
{
    return DAILYNECESSITIES;
}

double DailyNecessities::reducedPrice()
{
    if (QDate::currentDate() > validityDate)
        return -1;
    return price;
}

QDate DailyNecessities::getProduceDate()
{
    return produceDate;
}

QDate DailyNecessities::getValidityDate()
{
    return validityDate;
}

QStringList DailyNecessities::toStringList()
{
    QStringList sl;
    QString reduced = (reducedPrice() < 0 ? "已过期" : QString::number(reducedPrice(), 'f', 2));
    sl << "" << getGoodsName() << QString::number(getAmount()) << QString::number(getPrice(), 'f', 2) << reduced << getOwner() << getProduceDate().toString(Qt::ISODate) << getValidityDate().toString(Qt::ISODate) << "-" << "-" << QString::number(getId()) ;
    return sl;
}

QDataStream &operator>>(QDataStream &in, DailyNecessities &d)
{
    in >> d.id >> d.goodsName >> d.amount >> d.price >> d.owner >> d.produceDate >> d.validityDate;
    if(in.status() != QDataStream::Ok)
        throw QString("daily.dat 已损坏");
    return in;
}

QDataStream &operator<<(QDataStream &out, const DailyNecessities &d)
{
    out << d.id << d.goodsName << d.amount << d.price << d.owner << d.produceDate << d.validityDate;
    return out;
}
