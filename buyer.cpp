#include "buyer.h"

Buyer::Buyer()
{
}

Buyer::Buyer(QString id, QString userName, QString password, double balance)
    :User(id, userName, password, balance)
{

}

void Buyer::recharge(double money)
{
    balance += money;
}
