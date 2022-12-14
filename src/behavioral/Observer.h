#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <memory>
#include <set>
#include <string>
using namespace std;

class Topic;

class Observer
{
public:
  virtual void update() = 0;
  virtual void onReceive(string msg) {}
  virtual void subscribe(Topic *topic) = 0;
  virtual void unsubscribe(Topic *topic) = 0;
};

class Topic
{
public:
  virtual void attach(Observer *observer) = 0;
  virtual void detach(Observer *observer) = 0;
  virtual void publish(string msg) {}
  virtual void setState(int state) {}
  virtual int getState() { return 0; }
  virtual void notify() {}
};

class Student : public Observer
{
public:
  Student(string name) : name(name)
  {
  }
  void update() override
  {
    cout << "亲爱的" << name << ",订阅的主题有更新！各个主题状态如下：" << endl;
    for (auto topic : topics)
    {
      cout << topic->getState() << " ";
    }
    cout << endl;
  }

  void onReceive(string msg) override
  {
    cout << "亲爱的" << name << ",您收到一条消息：" << msg << endl;
  }

  void subscribe(Topic *topic) override
  {
    topic->attach(this);
    topics.insert(topic);
  }

  void unsubscribe(Topic *topic) override
  {
    topic->detach(this);
    auto it = topics.find(topic);
    if (it != topics.end())
    {
      topics.erase(it);
    }
  }

private:
  string name;
  set<Topic *> topics;
};

class Teacher : public Observer
{
public:
  Teacher(string name) : name(name) {}
  void update() override
  {
    cout << "亲爱的" << name << ",订阅的主题有更新！各个主题状态如下：" << endl;
    if (topic == nullptr)
    {
      cout << "没有订阅" << endl;
      return;
    }
    cout << topic->getState() << endl;
  }

  void onReceive(string msg) override
  {
    cout << "亲爱的" << name << ", 您收到一条消息：" << msg << endl;
  }

  void subscribe(Topic *topic) override
  {
    if (this->topic == nullptr)
    {
      this->topic = topic;
      topic->attach(this);
    }
    else
    {
      cout << "您只能订阅一个主题！" << endl;
    }
  }

  void unsubscribe(Topic *topic) override
  {
    topic->detach(this);
    this->topic = nullptr;
  }

private:
  string name;
  Topic *topic{nullptr};
};

class MicroBlog : public Topic
{
public:
  virtual void attach(Observer *observer) override
  {
    listeners.insert(observer);
  }

  virtual void detach(Observer *observer) override
  {
    auto it = listeners.find(observer);
    if (it != listeners.end())
    {
      listeners.erase(it);
    }
  }

  virtual void publish(string msg) override
  {
    for (auto listener : listeners)
    {
      listener->onReceive(msg);
    }
  }

  virtual void setState(int state) override
  {
    cout << "set State: " << state << endl;
    this->state = state;
    notify();
  }

  virtual int getState() override
  {
    return state;
  }

  virtual void notify() override
  {
    cout << listeners.size() << endl;
    for (auto it = listeners.begin(); it != listeners.end(); it++)
    {
      cout << "before update" << endl;
      (*it)->update();
      cout << "after update" << endl;
    }
  }

private:
  int state = 0;
  set<Observer *> listeners;
};

class IMService : public Topic
{
public:
  virtual void attach(Observer *observer) override
  {
    listeners.emplace(observer);
  }

  virtual void detach(Observer *observer) override
  {
    auto it = listeners.find(observer);
    if (it != listeners.end())
    {
      listeners.erase(it);
    }
  }

  virtual void publish(string msg) override
  {
    for (auto listener : listeners)
    {
      listener->onReceive(msg);
    }
  }

private:
  set<Observer *> listeners;
};

void ObserverTest()
{
  // 主题
  shared_ptr<Topic> qq(new IMService());
  shared_ptr<Topic> weibo(new MicroBlog());

  // 订阅者
  shared_ptr<Observer> stu1(new Student("zhangzewei"));
  shared_ptr<Observer> stu2(new Student("ShaB"));
  shared_ptr<Observer> teacher(new Teacher("Tech"));

  // 订阅
  stu1->subscribe(qq.get());
  stu1->subscribe(weibo.get());

  stu2->subscribe(qq.get());
  teacher->subscribe(weibo.get());

  qq->publish("qq发的");
  weibo->publish("微博发的");
  weibo->setState(110);
  weibo->setState(91);
  stu1->unsubscribe(qq.get());
  stu1->unsubscribe(weibo.get());
  qq->setState(-1);
}

#endif