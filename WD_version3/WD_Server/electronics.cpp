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

GoodsClass Electronics::getClass()
{
    return ELECTRONICS;
}

double Electronics::reducedPrice()
{
    if (QDate::currentDate() > validityDate)
        return -1;
    int days = produceDate.daysTo(QDate::currentDate());
    double reducedPrice = price * (1 - days / 30 * reduceRate);
    return (reducedPrice < 0 ? 0 : reducedPrice);
}

QDate Electronics::getProduceDate() const
{
    return this->produceDate;
}

QDate Electronics::getValidityDate() const
{
    return this->validityDate;
}

double Electronics::getReduceRate() const
{
    return this->reduceRate;
}

QStringList Electronics::toStringList()
{
    QStringList sl;
    QString reduced = (reducedPrice() < 0 ? "已过期" : QString::number(reducedPrice(), 'f', 2));
    sl << "" << getGoodsName() << QString::number(getAmount()) << QString::number(getPrice(), 'f', 2) << reduced << getOwner() << getProduceDate().toString(Qt::ISODate) << getValidityDate().toString(Qt::ISODate)<< "-" << QString::number(getReduceRate(), 'f', 2) << QString::number(getId());
    return sl;
}

QDataStream &operator>>(QDataStream &in, Electronics &e)
{
    in >> e.id >> e.goodsName >> e.amount >> e.price >> e.owner >> e.produceDate >> e.validityDate >> e.reduceRate;
    if(in.status() != QDataStream::Ok)
        throw QString("elect.dat 已损坏");
    return in;
}

QDataStream &operator<<(QDataStream &out, const Electronics &e)
{
    out << e.id << e.goodsName << e.amount << e.price << e.owner << e.produceDate << e.validityDate << e.reduceRate;
    return out;
}
