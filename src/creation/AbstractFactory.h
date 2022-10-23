#include "factory_common.h"

// 抽象工厂
class AbstractFactory
{
public:
  virtual shared_ptr<SingleCore> createSingleCore() = 0;
  virtual shared_ptr<MultiCore> createMultiCore() = 0;
};

// 工厂一
class FactoryImplA : public AbstractFactory
{
public:
  virtual shared_ptr<SingleCore> createSingleCore() override
  {
    return make_shared<SingleCoreA>();
  }

  virtual shared_ptr<MultiCore> createMultiCore() override
  {
    return make_shared<MultiCoreA>();
  }
};

// 工厂二
class FactoryImplB : public AbstractFactory
{
public:
  virtual shared_ptr<SingleCore> createSingleCore() override
  {
    return make_shared<SingleCoreB>();
  }

  virtual shared_ptr<MultiCore> createMultiCore() override
  {
    return make_shared<MultiCoreB>();
  }
};

class AbstractFactoryTest
{
public:
  void test()
  {
    auto singleCoreProduct = factory->createSingleCore();
    auto multiCoreProduct = factory->createMultiCore();

    singleCoreProduct->show();
    multiCoreProduct->show();
  }

private:
  AbstractFactory *factory = new FactoryImplB();
};
