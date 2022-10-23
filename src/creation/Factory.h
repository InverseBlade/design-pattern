#pragma once

#include <iostream>
#include <memory>
#include "factory_common.h"

class Factory
{
public:
  virtual shared_ptr<SingleCore> createSingleCore() = 0;
};

class FactoryA : public Factory
{
public:
  shared_ptr<SingleCore> createSingleCore() override
  {
    return make_shared<SingleCoreA>();
  }
};

class FactoryB : public Factory
{
public:
  shared_ptr<SingleCore> createSingleCore() override
  {
    return make_shared<SingleCoreB>();
  }
};

class FactoryTest
{
public:
  void test()
  {
    auto product = factory->createSingleCore();
    product->show();
  }

private:
  shared_ptr<Factory> factory = make_shared<FactoryA>();
};
