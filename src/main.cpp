#include "AbstractFactory.h"
#include "Builder.h"
#include "Factory.h"
#include "SimpleFactory.h"
#include "Singleton.h"
#include "Prototype.h"
#include "Proxy.h"
#include "Adapter.h"
#include "Facade.h"
#include "Bridge.h"
#include "Composite.h"
#include "Flyweight.h"
#include "Decorator.h"
#include <iostream>
using namespace std;

int main()
{
    SimpleFactoryTest().test();
    FactoryTest().test();
    AbstractFactoryTest().test();
    SingletonTest().test();
    BuilderTest().test();
    PrototypeTest().test();
    AdapterTest().test();
    ProxyTest().test();
    FacadeTest().test();
    BridgeTest().test();
    CompositeTest().test();
    FlyweightTest().test();
    DecoratorTest().test();

    return 0;
}
