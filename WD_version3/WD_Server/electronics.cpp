#include "electronics.h"

Electronics::Electronics()
{
}

Electronics::Electronics(int id, QString electName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, double reduceRate)
    : Goods(id, electName, amount, price, owner)
{
    this->produceDate = produceDate;
    this->validityDate = validityDate;
    this->reduceRate = reduceRate;
}


QDate Electronics::getProduceDate()
{
    return produceDate;
}

QDate Electronics::getValidityDate()
{
    return validityDate;
}

double Electronics::getRuduceRate()
{
    return reduceRate;
}

double Electronics::reducedPrice()
{
    if (QDate::currentDate() > validityDate)
        return -1;
    int days = produceDate.daysTo(QDate::currentDate());
    double reducedPrice = price * (1 - days / 30 * reduceRate);
    return (reducedPrice < 0 ? 0 : reducedPrice);
}

goodsClass Electronics::getClass()
{
    return ELECTRONICS;
}

QStringList Electronics::toStringList()
{
    QStringList sl;
    QString reduced = (reducedPrice() < 0 ? "已过期" : QString::number(reducedPrice(), 'f', 2));
    sl << "" << getGoodsName() << QString::number(getAmount()) << QString::number(getPrice(), 'f', 2) << reduced << getOwner() << getProduceDate().toString(Qt::ISODate) << getValidityDate().toString(Qt::ISODate)<< "-" << QString::number(getRuduceRate(), 'f', 2) << QString::number(getId());
    return sl;
}

QDataStream &operator>>(QDataStream &in, Electronics &e)
{
    in >> e.id >> e.goodsName >> e.amount >> e.price >> e.owner >> e.produceDate >> e.validityDate >> e.reduceRate;
    return in;
}

QDataStream &operator<<(QDataStream &out, const Electronics &e)
{
    out << e.id << e.goodsName << e.amount << e.price << e.owner << e.produceDate << e.validityDate << e.reduceRate;
    return out;
}
