#include "AbstractFactory.h"
#include "Builder.h"
#include "Factory.h"
#include "SimpleFactory.h"
#include "Singleton.h"
#include "Prototype.h"
#include "Adapter.h"
#include <iostream>
using namespace std;

int main()
{
    // SimpleFactoryTest demo;
    // FactoryTest demo;
    // AbstractFactoryTest demo;
    // SingletonTest demo;
    // BuilderTest demo;
    // PrototypeTest demo;
    AdapterTest demo;

    demo.test();
    return 0;
}
