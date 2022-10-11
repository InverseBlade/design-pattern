#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

class Object
{
public:
  Object() {}
  Object(string name) : name(name) {}
  void show()
  {
    cout << name << endl;
  }
  string get()
  {
    return name;
  }

private:
  string name;
};

class Iterator
{
public:
  virtual bool hasNext() = 0;
  virtual shared_ptr<Object> next() = 0;
};

class Container
{
public:
  virtual shared_ptr<Iterator> getIterator() = 0;
};

class ArrayIterator;

class ArrayList : public Container
{
public:
  friend class ArrayIterator;
  shared_ptr<Iterator> getIterator() override;
  int size()
  {
    return strs.size();
  }
  void add(shared_ptr<Object> obj)
  {
    strs.emplace_back(obj);
  }

private:
  vector<shared_ptr<Object>> strs{
      make_shared<Object>("123"),
      make_shared<Object>("23"),
      make_shared<Object>("sdf3")};
};

class ArrayIterator : public Iterator
{
public:
  friend class ArrayList;
  virtual bool hasNext() override
  {
    return index < list->size();
  }
  virtual shared_ptr<Object> next() override
  {
    if (!hasNext())
    {
      return nullptr;
    }
    return list->strs[index++];
  }

private:
  ArrayIterator() {}
  ArrayIterator(shared_ptr<ArrayList> list)
  {
    this->list = list;
  }
  int index = 0;
  shared_ptr<ArrayList> list;
};

shared_ptr<Iterator> ArrayList::getIterator()
{
  shared_ptr<ArrayIterator> ptr(new ArrayIterator(shared_ptr<ArrayList>(this)));
  return ptr;
}

void IteratorTest()
{
  auto container = make_shared<ArrayList>();

  container->add(make_shared<Object>("zhangzw1991"));
  container->add(make_shared<Object>("shab"));

  for (auto iter = container->getIterator(); iter->hasNext();)
  {
    shared_ptr<Object> str = iter->next();
    str->show();
  }
}

#endif