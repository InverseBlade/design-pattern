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
  virtual void subscribe(shared_ptr<Topic> topic) = 0;
  virtual void unsubscribe(shared_ptr<Topic> topic) = 0;
};

class Topic
{
public:
  virtual void attach(shared_ptr<Observer> observer) = 0;
  virtual void detach(shared_ptr<Observer> observer) = 0;
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

  void subscribe(shared_ptr<Topic> topic) override
  {
    shared_ptr<Student> stu(this);
    topic->attach(stu);
    topics.insert(topic);
  }

  void unsubscribe(shared_ptr<Topic> topic) override
  {
    shared_ptr<Student> stu(this);
    topic->detach(stu);
    topics.erase(topic);
  }

private:
  string name;
  set<shared_ptr<Topic>> topics;
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

  void subscribe(shared_ptr<Topic> topic) override
  {
    if (this->topic == nullptr)
    {
      this->topic = topic;
      topic->attach(shared_ptr<Teacher>(this));
    }
    else
    {
      cout << "您只能订阅一个主题！" << endl;
    }
  }

  void unsubscribe(shared_ptr<Topic> topic) override
  {
    topic->detach(shared_ptr<Teacher>(this));
    this->topic = nullptr;
  }

private:
  string name;
  shared_ptr<Topic> topic{nullptr};
};

class MicroBlog : public Topic
{
public:
  virtual void attach(shared_ptr<Observer> observer) override
  {
    listeners.insert(observer);
  }

  virtual void detach(shared_ptr<Observer> observer) override
  {
    listeners.erase(observer);
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
    this->state = state;
    notify();
  }

  virtual int getState() override
  {
    return state;
  }

  virtual void notify() override
  {
    for (auto listener : listeners)
    {
      listener->update();
    }
  }

private:
  int state = 0;
  set<shared_ptr<Observer>> listeners;
};

class IMService : public Topic
{
public:
  virtual void attach(shared_ptr<Observer> observer) override
  {
    listeners.emplace(observer);
  }

  virtual void detach(shared_ptr<Observer> observer) override
  {
    listeners.erase(observer);
  }

  virtual void publish(string msg) override
  {
    for (auto listener : listeners)
    {
      listener->onReceive(msg);
    }
  }

private:
  set<shared_ptr<Observer>> listeners;
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
  stu1->subscribe(qq);
  stu1->subscribe(weibo);

  stu2->subscribe(qq);
  teacher->subscribe(weibo);

  qq->publish("qq发的");
  weibo->publish("微博发的");
  weibo->setState(110);
  weibo->setState(91);
  qq->setState(-1);
}

#endif