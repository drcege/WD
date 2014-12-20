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

double Food::reducedPrice()
{
    if (QDate::currentDate() < reduceDate)
        return price;
    if (QDate::currentDate() > validityDate)
        return -1;
    return price * (1 - reduceRate);
}

goodsClass Food::getClass()
{
    return FOOD;
}

QDataStream &operator>>(QDataStream &in, Food &f)
{
    in >> f.id >> f.goodsName >> f.amount >> f.price >> f.owner >> f.produceDate >> f.validityDate >> f.reduceDate >> f.reduceRate;
    return in;
}


QDataStream &operator<<(QDataStream &out, const Food &f)
{
    out << f.id << f.goodsName << f.amount << f.price << f.owner << f.produceDate << f.validityDate << f.reduceDate;
    return out;
}
