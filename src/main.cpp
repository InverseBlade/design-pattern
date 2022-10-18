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
#include "Strategy.h"
#include "Template.h"
#include "Observer.h"
#include "Chain.h"
#include "Iterator.h"
#include "Command.h"
#include "Memento.h"
#include "State.h"
#include "Mediator.h"
#include <iostream>
using namespace std;

int main()
{
    // SimpleFactoryTest().test();
    // FactoryTest().test();
    // AbstractFactoryTest().test();
    // SingletonTest().test();
    // BuilderTest().test();
    // PrototypeTest().test();
    // AdapterTest().test();
    // ProxyTest().test();
    // FacadeTest().test();
    // BridgeTest().test();
    // CompositeTest().test();
    // FlyweightTest().test();
    // DecoratorTest().test();
    // StrategyTest().test();
    // TemplateTest();
    // ObserverTest();
    // ChainTest();
    // IteratorTest();
    // CommandTest();
    // mementoTest();
    StateTest();
    MediatorTest();

    return 0;
}
