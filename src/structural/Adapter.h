#ifndef ADAPTER_H
#define ADAPTER_H

#include <iostream>
#include <memory>
using namespace std;

class Deque
{
public:
  void push_back(int x) { cout << "Deque push_back" << endl; }
  void push_front(int x) { cout << "Deque push_front" << endl; }
  void pop_back() { cout << "Deque pop_back" << endl; }
  void pop_front() { cout << "Deque pop_front" << endl; }
};

class List
{
public:
  virtual void push(int val) = 0;
  virtual int pop() = 0;
};

class Stack : public List
{
public:
  virtual void push(int val) override
  {
    deque->push_back(val);
  }

  virtual int pop() override
  {
    deque->pop_back();
    return -1;
  }

private:
  shared_ptr<Deque> deque = make_shared<Deque>();
};

class Queue : public List
{
public:
  virtual void push(int val) override
  {
    deque->push_back(val);
  }

  virtual int pop() override
  {
    deque->pop_front();
    return -1;
  }

private:
  shared_ptr<Deque> deque = make_shared<Deque>();
};

class AdapterTest
{
public:
  void test()
  {
    List *list1 = new Stack();
    List *list2 = new Queue();

    for (int i = 0; i < 3; i++)
    {
      list1->push(i);
      list2->push(i);
    }
    for (int i = 0; i < 3; i++)
    {
      list1->pop();
      list2->pop();
    }
  }
};

#endif