#include "seller.h"

Seller::Seller()
{
}

Seller::Seller(QString id, QString userName, QString password, double balance)
    :User(id, userName, password, balance)
{

}
