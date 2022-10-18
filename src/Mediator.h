#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <string>
#include <iostream>
using namespace std;

class User;

class ChatRoom
{
public:
  static void showMessage(User *user, string message);
};

class User
{
public:
  string getname()
  {
    return name;
  }
  void setName(string name)
  {
    this->name = name;
  }
  User(string name)
  {
    this->name = name;
  }
  void sendMessage(string msg)
  {
    ChatRoom::showMessage(this, msg);
  }

private:
  string name;
};

void ChatRoom::showMessage(User *user, string message)
{
  cout << __FUNCTION__ << " [" << user->getname() << "] : " << message << endl;
}

void MediatorTest()
{
  User robert("Robert");
  User john("John");
  robert.sendMessage("Hi! John!");
  john.sendMessage("Hello! Robert!");
}

#endif