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

Food::Food(int id, QString foodName, int amount, double price, QString owner, QDate produceDate, QDate validityDate, QDate reduceDate)
    :Goods(id, foodName, amount, price, owner)
{
    this->produceDate = produceDate;
    this->validityDate = validityDate;
    this->reduceDate = reduceDate;
}

double Food::calcPrice()
{
    return 0.0;
}

/******************************************************************************/

Electronics::Electronics()
{
}

double Electronics::calcPrice()
{
    return 0.0;
}

/******************************************************************************/

DailyNecessities::DailyNecessities()
{
}

double DailyNecessities::calcPrice()
{
    return 0.0;
}
