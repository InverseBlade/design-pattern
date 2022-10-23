#ifndef FACTORY_COMMON_H
#define FACTORY_COMMON_H

#include <iostream>
#include <memory>
using namespace std;

enum class CTYPE
{
  COREA,
  COREB
};

// 第一个系列产品
class SingleCore
{
public:
  virtual void show() = 0;
};

// 产品种类一
class SingleCoreA : public SingleCore
{
public:
  void show() override
  {
    cout << "SingleCoreA" << endl;
  }
};

// 产品种类二
class SingleCoreB : public SingleCore
{
public:
  void show() override
  {
    cout << "SingleCoreB" << endl;
  }
};

// 第二个系列产品
class MultiCore
{
public:
  virtual void show() = 0;
};

// 产品种类一
class MultiCoreA : public MultiCore
{
public:
  virtual void show() override
  {
    cout << "MultiCoreA" << endl;
  }
};

// 产品种类二
class MultiCoreB : public MultiCore
{
public:
  virtual void show() override
  {
    cout << "MultiCoreB" << endl;
  }
};

#endif