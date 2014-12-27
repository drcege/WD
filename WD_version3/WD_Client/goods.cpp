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

int Goods::getId() const
{
    return this->id;
}

int Goods::getAmount() const
{
    return this->amount;
}

double Goods::getPrice() const
{
    return this->price;
}

QString Goods::getOwner() const
{
    return this->owner;
}

QString Goods::getGoodsName() const
{
    return this->goodsName;
}

int Goods::changeAmount(int amount)
{
    this->amount += amount;
    return this->amount;
}

