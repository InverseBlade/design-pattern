#include <iostream>
#include <memory>
#include <factory_common.h>
using namespace std;

class SimpleFactory
{
public:
  shared_ptr<SingleCore> CreateSingleCore(CTYPE ctype)
  {
    switch (ctype)
    {
    case CTYPE::COREA:
      return make_shared<SingleCoreA>();
      break;
    case CTYPE::COREB:
      return make_shared<SingleCoreB>();
      break;
    default:
      cout << "Fatal Error: Unknown CTYPE !" << endl;
      break;
    }
    return nullptr;
  }
};

class SimpleFactoryTest
{
public:
  void test()
  {
    auto product = factory->CreateSingleCore(CTYPE::COREB);
    product->show();
  }

private:
  unique_ptr<SimpleFactory> factory = make_unique<SimpleFactory>();
};
