#include "food.h"

Food::Food()
{
}

Food::Food(int id, QString goodsName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, QDate reduceDate, double reduceRate)
    : Goods(id, goodsName, amount, price, owner)
{
    this->produceDate = produceDate;
    this->validityDate = validityDate;
    this->reduceDate = reduceDate;
    this->reduceRate = reduceRate;
}

goodsClass Food::getClass()
{
    return FOOD;
}

double Food::reducedPrice()
{
    if (QDate::currentDate() < reduceDate)
        return price;
    if (QDate::currentDate() > validityDate)
        return -1;
    return price * (1 - reduceRate);
}

QDate Food::getProduceDate()
{
    return produceDate;
}

QDate Food::getValidityDate()
{
    return validityDate;
}

QDate Food::getReduceDate()
{
    return reduceDate;
}

double Food::getReduceRate()
{
    return reduceRate;
}

QStringList Food::toStringList()
{
    QStringList sl;
    QString reduced = (reducedPrice() < 0 ? "已过期" : QString::number(reducedPrice(), 'f', 2));
    sl << "" << getGoodsName() << QString::number(getAmount()) << QString::number(getPrice(), 'f', 2) << reduced << getOwner() << getProduceDate().toString(Qt::ISODate) << getValidityDate().toString(Qt::ISODate) << getReduceDate().toString(Qt::ISODate) << QString::number(getReduceRate(), 'f', 2) << QString::number(getId());
    return sl;
}
