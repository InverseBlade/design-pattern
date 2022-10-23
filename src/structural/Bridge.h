#ifndef BRIDGE_H
#define BRIDGE_H

#include <iostream>
#include <memory>
using namespace std;

class OS
{
public:
  virtual void InstallOS_Imp() = 0;
};

class Windows : public OS
{
public:
  void InstallOS_Imp() override
  {
    cout << "Install Windows Operate System..." << endl;
  }
};

class Linux : public OS
{
public:
  void InstallOS_Imp() override
  {
    cout << "Install Linux Operate System..." << endl;
  }
};

class Unix : public OS
{
public:
  void InstallOS_Imp() override
  {
    cout << "Install Unix Operate System..." << endl;
  }
};

class Computer
{
public:
  virtual void InstallOS(OS *os) = 0;
};

class DELLComputer : public Computer
{
public:
  void InstallOS(OS *os) override
  {
    os->InstallOS_Imp();
  }
};

class AppleComputer : public Computer
{
public:
  void InstallOS(OS *os) override
  {
    os->InstallOS_Imp();
  }
};

class HPComputer : public Computer
{
public:
  void InstallOS(OS *os) override
  {
    os->InstallOS_Imp();
  }
};

class BridgeTest
{
public:
  void test()
  {
    unique_ptr<OS> os1(new Windows());
    unique_ptr<OS> os2(new Linux());
    unique_ptr<OS> os3(new Unix());
    unique_ptr<Computer> computer(new DELLComputer());
    computer->InstallOS(os3.get());
    computer->InstallOS(os1.get());
    computer->InstallOS(os2.get());
  }
};

#endif