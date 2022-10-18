#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Order
{
public:
  virtual void execute() = 0;
};

class Stock
{
public:
  void buy()
  {
    cout << "Stock [ Name: "
         << ",Quantity: " << quantity << " ] bought";
  }
  void sell()
  {
    cout << "Stock [ Name: " << name << ",Quantity: " << quantity << " ] sold";
  }

private:
  string name = "ABC";
  int quantity = 10;
};

class BuyStock : public Order
{
public:
  BuyStock(Stock *abcStock)
  {
    this->abcStock = abcStock;
  }
  void execute() override
  {
    abcStock->buy();
  }

private:
  Stock *abcStock;
};

class SellStock : public Order
{
public:
  SellStock(Stock *abcStock)
  {
    this->abcStock = abcStock;
  }
  void execute() override
  {
    abcStock->sell();
  }

private:
  Stock *abcStock;
};

class Broker
{
public:
  void takeOrder(Order *order)
  {
    orderList.push_back(order);
  }
  void placeOrders()
  {
    for (Order *order : orderList)
    {
      order->execute();
    }
    orderList.clear();
  }

private:
  vector<Order *> orderList;
};

void CommandTest()
{
  Stock *abcStock = new Stock();
  BuyStock *buyStockOrder = new BuyStock(abcStock);
  SellStock *sellStockOrder = new SellStock(abcStock);
  Broker *broker = new Broker();
  broker->takeOrder(buyStockOrder);
  broker->takeOrder(sellStockOrder);
  broker->placeOrders();
}

#endif