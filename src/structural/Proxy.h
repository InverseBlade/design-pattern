#ifndef PROXY_H
#define PROXY_H

#include <iostream>
#include <memory>
#include <mutex>
using namespace std;

class ImageIF
{
public:
  virtual void display() = 0;
};

class BigImage : public ImageIF
{
public:
  BigImage(string name) : name(name) {}
  virtual ~BigImage() {}

  virtual void display() override
  {
    cout << "Show BigImage : " << name << endl;
  }

private:
  string name;
};

class ImageProxy : public ImageIF
{
public:
  ImageProxy(string name)
      : name(name), bigImage(nullptr)
  {
  }

  virtual void display() override
  {
    if (bigImage == nullptr)
    {
      lock_guard<mutex> lock(g_mutex);
      if (bigImage == nullptr)
      {
        bigImage = unique_ptr<BigImage>(new BigImage(ImageProxy::name));
      }
    }
    bigImage->display();
  }

private:
  string name;
  unique_ptr<BigImage> bigImage;
  static mutex g_mutex;
};
mutex ImageProxy::g_mutex;

class ProxyTest
{
public:
  void test()
  {
    unique_ptr<ImageIF> img = make_unique<ImageProxy>("proxy.png");
    img->display();
    delete img.release();
  }
};

#endif