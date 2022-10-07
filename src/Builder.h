#ifndef BUILDER_H
#define BUILDER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// 例子：快餐店不变的有汉堡、可乐、薯条、炸鸡翅，
// 易变的有各种套餐型号如套餐一、套餐二，以及不同的包装形式，打包盒、杯子、堂食、外送等

// 包装接口
class Packing
{
public:
  virtual string pack() = 0;
};

// 物品接口
class Item
{
public:
  virtual string name() = 0;
  virtual shared_ptr<Packing> packing() = 0;
  virtual float price() = 0;
};

// 打包带
class Wrapper : public Packing
{
public:
  string pack() override
  {
    return "Wrapper";
  }
};

// 打包杯子
class Bottle : public Packing
{
public:
  string pack() override
  {
    return "Bottle";
  }
};

// 汉堡类
class Burger : public Item
{
public:
  shared_ptr<Packing> packing() override
  {
    return make_shared<Wrapper>();
  }
};

// 饮料类
class Drink : public Item
{
public:
  shared_ptr<Packing> packing() override
  {
    return make_shared<Bottle>();
  }
};

// 素汉堡
class VegBurger : public Burger
{
public:
  float price() override
  {
    return 25.5f;
  }

  string name()
  {
    return "Veg Burger";
  }
};

// 鸡肉汉堡
class ChickenBurger : public Burger
{
public:
  float price() override
  {
    return 50.7f;
  }

  string name()
  {
    return "Chicken Burger";
  }
};

// 可口可乐
class Coke : public Drink
{
public:
  virtual string name()
  {
    return "Coke";
  }

  virtual float price()
  {
    return 10.1f;
  }
};

// 百事
class Pepsi : public Drink
{
public:
  virtual string name()
  {
    return "Pepsi";
  }

  virtual float price()
  {
    return 7.1f;
  }
};

// 套餐
class Meal
{
public:
  void addItem(shared_ptr<Item> item)
  {
    items.emplace_back(item);
  }

  float getCost()
  {
    float sum = 0.0f;
    for (auto item : items)
    {
      sum += item->price();
    }
    return sum;
  }

  void showItemList()
  {
    for (auto item : items)
    {
      cout << "Item: " << item->name();
      cout << ", Packing: " << item->packing()->pack();
      cout << ", Price=" << item->price() << endl;
    }
  }

private:
  vector<shared_ptr<Item>> items;
};

// 套餐构建者接口
class MealBuilder
{
public:
  virtual void orderDrink() = 0;
  virtual void orderCourse() = 0;
  virtual shared_ptr<Meal> commit() = 0;
};

// 素食套餐构建者
class VegMealBuilder : public MealBuilder
{
public:
  virtual void orderDrink()
  {
    meal->addItem(make_shared<Pepsi>());
  }
  virtual void orderCourse()
  {
    meal->addItem(make_shared<VegBurger>());
  }
  virtual shared_ptr<Meal> commit()
  {
    cout << "VegMealBuilder Created !" << endl;
    return meal;
  }

private:
  shared_ptr<Meal> meal = make_shared<Meal>();
};

// 非素套餐构建者
class NonVegMealBuilder : public MealBuilder
{
public:
  virtual void orderDrink()
  {
    meal->addItem(make_shared<Coke>());
  }
  virtual void orderCourse()
  {
    meal->addItem(make_shared<ChickenBurger>());
  }
  virtual shared_ptr<Meal> commit()
  {
    cout << "NonVegMealBuilder Created !" << endl;
    return meal;
  }

private:
  shared_ptr<Meal> meal = make_shared<Meal>();
};

// 豪华套餐
class BestMealBuilder : public MealBuilder
{
public:
  virtual void orderDrink()
  {
    meal->addItem(make_shared<Coke>());
    meal->addItem(make_shared<Pepsi>());
  }
  virtual void orderCourse()
  {
    meal->addItem(make_shared<ChickenBurger>());
    meal->addItem(make_shared<VegBurger>());
  }
  virtual shared_ptr<Meal> commit()
  {
    cout << "Best meal is created !" << endl;
    return meal;
  }

private:
  shared_ptr<Meal> meal = make_shared<Meal>();
};

// 指导构建者
class Director
{
public:
  Director(shared_ptr<MealBuilder> builder)
  {
    mealBuilder = builder;
  }

  shared_ptr<Meal> createMeal()
  {
    mealBuilder->orderDrink();
    mealBuilder->orderCourse();
    return mealBuilder->commit();
  }

private:
  shared_ptr<MealBuilder> mealBuilder;
};

class BuilderTest
{
public:
  void test()
  {
    shared_ptr<Meal> meal = director.createMeal();
    cout << meal->getCost() << endl;
    meal->showItemList();
  }

private:
  Director director{make_shared<BestMealBuilder>()};
};

#endif