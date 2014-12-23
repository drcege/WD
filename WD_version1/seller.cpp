#include "seller.h"

Seller::Seller()
{
}

Seller::Seller(int id, QString userName, QString password, double balance)
    : User(id, userName, password, balance)
{
}

userClass Seller::getClass()
{
    return SELLER;
}
