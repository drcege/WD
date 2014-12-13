#include "goods.h"

Goods::Goods()
{
}

Goods::~Goods()
{

}

Goods::Goods(int id, QString foodName, int amount, double price, QString owner)
{
    this->id = id;
    this->goodsName = foodName;
    this->amount = amount;
    this->price = price;
    this->owner = owner;
}

void Goods::changeAmount(int amount)
{
    this->amount += amount;
}

/******************************************************************************/

Food::Food()
{
}

Food::Food(int id, QString goodsName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, QDate reduceDate, double reduceRate)
    :Goods(id, goodsName, amount, price, owner)
{
    this->produceDate = produceDate;
    this->validityDate = validityDate;
    this->reduceDate = reduceDate;
    this->reduceRate = reduceRate;
    curClass = FOOD;
}

double Food::reducedPrice()
{
    if(QDate::currentDate() < reduceDate)
        return price;
    if(QDate::currentDate() > validityDate)
        return -1;
    return price * (1-reduceRate);
}

QDataStream &operator>>(QDataStream &in, Food &f)
{
    in >> f.id >> f.goodsName >> f.amount >> f.price >> f.owner >> f.produceDate >> f.validityDate >> f.reduceDate >> f.reduceRate;
    f.curClass = FOOD;
    return in;
}


QDataStream &operator<<(QDataStream &out, Food &f)
{
    out << f.id << f.goodsName << f.amount << f.price << f.owner << f.produceDate << f.validityDate << f.reduceDate;
    return out;
}

/******************************************************************************/

Electronics::Electronics()
{
}

Electronics::Electronics(int id, QString electName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, double reduceRate)
    :Goods(id, electName, amount, price, owner)
{
    this->produceDate = produceDate;
    this->validityDate = validityDate;
    this->reduceRate = reduceRate;
    curClass = ELECTRONICS;
}

double Electronics::reducedPrice()
{
    if(QDate::currentDate() > validityDate)
        return -1;
    int days = produceDate.daysTo(QDate::currentDate());
    double reducedPrice = price * (1 - days / 30 * reduceRate);
    return (reducedPrice < 0 ? 0 : reducedPrice);
}

QDataStream &operator>>(QDataStream& in, Electronics& e)
{
    in >> e.id >> e.goodsName >> e.amount >> e.price >> e.owner >> e.produceDate >> e.validityDate >> e.reduceRate;
    e.curClass = ELECTRONICS;
    return in;
}

QDataStream &operator<<(QDataStream& out, Electronics& e)
{
    out << e.id << e.goodsName << e.amount << e.price << e.owner << e.produceDate << e.validityDate << e.reduceRate;
    return out;
}

/******************************************************************************/

DailyNecessities::DailyNecessities()
{
}

DailyNecessities::DailyNecessities(int id, QString dailyName, int amount, double price, QString owner, QDate produceDate, QDate validityDate)
    :Goods(id, dailyName, amount, price, owner)
{
    this->produceDate = produceDate;
    this->validityDate = validityDate;
    curClass = DAILYNECESSITIES;
}

double DailyNecessities::reducedPrice()
{
    if(QDate::currentDate() > validityDate)
        return -1;
    return price;
}

QDataStream &operator>>(QDataStream& in, DailyNecessities& d)
{
    in >> d.id >> d.goodsName >> d.amount >> d.price >> d.owner >> d.produceDate >> d.validityDate;
    d.curClass = DAILYNECESSITIES;
    return in;
}

QDataStream &operator<<(QDataStream& out, DailyNecessities& d)
{
    out << d.id << d.goodsName << d.amount << d.price << d.owner << d.produceDate << d.validityDate;
    return out;
}
