#include "goods.h"

Goods::Goods()
{
}

Goods::Goods(int id, QString foodName, int amount, double price, QString owner)
{
    this->id = id;
    this->foodName = foodName;
    this->amount = amount;
    this->price = price;
    this->owner = owner;
}

/******************************************************************************/

Food::Food()
{
}

Food::Food(int id, QString foodName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, QDate reduceDate, double reduceRate)
    :Goods(id, foodName, amount, price, owner)
{
    this->produceDate = produceDate;
    this->validityDate = validityDate;
    this->reduceDate = reduceDate;
    this->reduceRate = reduceRate;
}

double Food::reducedPrice()
{
    return price;
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
}

double Electronics::reducedPrice()
{
    return price;
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
}

double DailyNecessities::reducedPrice()
{
    return price;
}
