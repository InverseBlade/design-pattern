#ifndef MEMENTO_H
#define MEMENTO_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Memento
{
public:
  Memento(string state)
  {
    this->state = state;
  }
  string getState()
  {
    return state;
  }

private:
  string state;
};

class Originator
{
public:
  void setState(string state)
  {
    this->state = state;
  }
  string getState()
  {
    return state;
  }
  Memento saveState()
  {
    return Memento(state);
  }
  void getStateFromMem(Memento &&mem)
  {
    state = mem.getState();
  }

private:
  string state;
};

class CareTaker
{
public:
  void add(Memento mem)
  {
    memList.push_back(mem);
  }
  Memento get(int index)
  {
    return memList[index];
  }

private:
  vector<Memento> memList;
};

void mementoTest()
{
  Originator originator;
  CareTaker careTaker;
  originator.setState("State #1");
  originator.setState("State #2");
  careTaker.add(originator.saveState());
  originator.setState("State #3");
  careTaker.add(originator.saveState());
  originator.setState("State #4");
  cout << "Current State: " + originator.getState() << endl;
  originator.getStateFromMem(careTaker.get(0));
  cout << "First saved State: " + originator.getState() << endl;
  originator.getStateFromMem(careTaker.get(1));
  cout << "Second saved State: " + originator.getState() << endl;
}

#endif