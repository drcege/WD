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
    return id;
}

int Goods::getAmount()
{
    return amount;
}

double Goods::getPrice()
{
    return price;
}

QString Goods::getOwner()
{
    return owner;
}

QString Goods::getGoodsName()
{
    return goodsName;
}

void Goods::changeAmount(int amount)
{
    this->amount += amount;
}

