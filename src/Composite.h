#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <iostream>
#include <memory>
#include <string>
#include <list>
using namespace std;

class Company
{
public:
  Company(string name)
      : name(name)
  {
  }

  virtual ~Company()
  {
  }

  virtual void add(shared_ptr<Company> com){};

  virtual void show(int depth) = 0;

protected:
  string name;
};

class ConcreteCompany : public Company
{
public:
  ConcreteCompany(string name) : Company(name)
  {
  }

  virtual ~ConcreteCompany()
  {
  }

  void add(shared_ptr<Company> com) override
  {
    m_comList.push_back(com);
  }

  void show(int depth)
  {
    for (int i = 0; i < depth; i++)
    {
      cout << "-";
    }
    cout << Company::name << endl;
    for (auto it = m_comList.begin(); it != m_comList.end(); it++)
    {
      (*it)->show(depth + 2);
    }
  }

private:
  list<shared_ptr<Company>> m_comList;
};

class FinDepartment : public Company
{
public:
  FinDepartment(string name)
      : Company(name)
  {
  }

  virtual ~FinDepartment()
  {
  }

  void show(int depth) override
  {
    for (int i = 0; i < depth; i++)
    {
      cout << "-";
    }
    cout << name << endl;
  }
};

class HRDepartment : public Company
{
public:
  HRDepartment(string name) : Company(name)
  {
  }
  virtual ~HRDepartment()
  {
  }

  void show(int depth) override
  {
    for (int i = 0; i < depth; i++)
      cout << "-";
    cout << name << endl;
  }
};

class CompositeTest
{
public:
  void test()
  {
    shared_ptr<Company> root(new ConcreteCompany("母公司"));
    shared_ptr<Company> leaf1(new FinDepartment("财务部"));
    shared_ptr<Company> leaf2(new HRDepartment("人力资源部"));
    root->add(leaf1);
    root->add(leaf2);

    shared_ptr<Company> mid1(new ConcreteCompany("子公司A"));
    shared_ptr<Company> leaf3(new FinDepartment("财务部"));
    shared_ptr<Company> leaf4(new HRDepartment("人力资源部"));
    mid1->add(leaf3);
    mid1->add(leaf4);
    root->add(mid1);

    shared_ptr<Company> mid2(new ConcreteCompany("子公司B"));
    shared_ptr<Company> leaf5(new FinDepartment("财务部"));
    shared_ptr<Company> leaf6(new HRDepartment("人力资源部"));
    mid2->add(leaf5);
    mid2->add(leaf6);
    root->add(mid2);
    root->show(0);
  }
};

#endif