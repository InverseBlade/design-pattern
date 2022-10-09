#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>
#include <mutex>
using namespace std;

namespace LazySingleton
{
  // 懒汉(双重锁校验)
  class Singleton
  {
  public:
    static Singleton *getInstance()
    {
      if (singleton == nullptr)
      {
        lock_guard<mutex> autoLock(g_mutex);
        if (singleton == nullptr)
        {
          singleton = new Singleton();
        }
      }
      return singleton;
    }

  private:
    Singleton() {}
    static Singleton *singleton;
    static mutex g_mutex;
  };
  mutex Singleton::g_mutex;
  Singleton *Singleton::singleton = nullptr;
};

namespace HungrySingleton
{
  // 饿汉
  class Singleton
  {
  public:
    static Singleton *getInstance()
    {
      return singleton;
    }

  private:
    Singleton() {}
    static Singleton *singleton;
  };

  Singleton *Singleton::singleton = new Singleton();

  // 饿汉二
  class Singleton2
  {
  public:
    static Singleton2 *getInstance()
    {
      static Singleton2 *singleton = new Singleton2();
      return singleton;
    }

    int getObjectId()
    {
      return id;
    }

  private:
    Singleton2()
    {
      id = refCnt++;
    }
    int id;
    static int refCnt;
  };

  int Singleton2::refCnt = 0;

  // 饿汉三
  class Singleton3
  {
  public:
    static Singleton3 &getInstance()
    {
      static Singleton3 instance;
      return instance;
    }

    static Singleton3 *instance()
    {
      return &getInstance();
    }

  private:
    Singleton3() {}
  };

}

class SingletonTest
{
public:
  void test()
  {
    test3();
  }
  void test3()
  {
    using namespace HungrySingleton;
    Singleton2 *obj1 = Singleton2::getInstance();
    Singleton2 *obj2 = Singleton2::getInstance();
    Singleton2 *obj3 = Singleton2::getInstance();

    cout << "obj1: " << obj1->getObjectId() << endl;
    cout << "obj2: " << obj2->getObjectId() << endl;
    cout << "obj3: " << obj3->getObjectId() << endl;

    if (obj1 == obj2 && obj2 == obj3)
    {
      cout << "All refer to same Object." << endl;
    }
    else
    {
      cout << "单例失效." << endl;
    }
  }
  void test2()
  {
    using namespace HungrySingleton;
    Singleton *obj1 = Singleton::getInstance();
    Singleton *obj2 = Singleton::getInstance();
    Singleton *obj3 = Singleton::getInstance();
    if (obj1 == obj2 && obj2 == obj3)
    {
      cout << "All refer to same Object." << endl;
    }
    else
    {
      cout << "单例失效." << endl;
    }
  }
  void test1()
  {
    using namespace LazySingleton;
    //
    Singleton *obj1 = Singleton::getInstance();
    Singleton *obj2 = Singleton::getInstance();
    Singleton *obj3 = Singleton::getInstance();
    if (obj1 == obj2 && obj2 == obj3)
    {
      cout << "All refer to same Object." << endl;
    }
    else
    {
      cout << "单例失效." << endl;
    }
  }
};

#endif