#include "creation/AbstractFactory.h"
#include "creation/Builder.h"
#include "creation/Factory.h"
#include "creation/SimpleFactory.h"
#include "creation/Singleton.h"
#include "creation/Prototype.h"
#include "structural/Proxy.h"
#include "structural/Adapter.h"
#include "structural/Facade.h"
#include "structural/Bridge.h"
#include "structural/Composite.h"
#include "structural/Flyweight.h"
#include "structural/Decorator.h"
#include "behavioral/Strategy.h"
#include "behavioral/Template.h"
#include "behavioral/Observer.h"
#include "behavioral/Chain.h"
#include "behavioral/Iterator.h"
#include "behavioral/Command.h"
#include "behavioral/Memento.h"
#include "behavioral/State.h"
#include "behavioral/Mediator.h"
#include "behavioral/Interpreter.h"
#include "behavioral/Visitor.h"
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
    StrategyTest().test();
    TemplateTest();
    ObserverTest();
    ChainTest();
    IteratorTest();
    CommandTest();
    mementoTest();
    StateTest();
    MediatorTest();
    InterpreterTest();
    Visitor::VisitorTest();

    return 0;
}
