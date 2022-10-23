#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <iostream>
#include <memory>
#include <string.h>
using namespace std;

class Image
{
public:
  Image()
  {
    // default avatar
    bufLen = 64 * 64;
    buf = new uint8_t[64 * 64]{3};
  }

  Image(uint8_t *data, size_t bufLen)
  {
    this->bufLen = bufLen;
    buf = new uint8_t[bufLen];
    memcpy(buf, data, bufLen);
  }

  Image(const Image &img)
  {
    bufLen = img.bufLen;
    buf = new uint8_t[bufLen];
    memcpy(buf, img.buf, bufLen);
  }

  Image(Image &&img)
  {
    if (this == &img)
    {
      return;
    }
    if (buf != nullptr)
    {
      delete[] buf;
    }
    bufLen = img.bufLen;
    buf = img.buf;
    img.bufLen = 0;
    img.buf = nullptr;
  }

  virtual ~Image()
  {
    cout << "image destroy" << endl;
    delete[] buf;
  }

  Image &operator=(const Image &img)
  {
    if (this == &img)
    {
      return *this;
    }
    if (buf != nullptr)
    {
      delete[] buf;
    }
    bufLen = img.bufLen;
    buf = new uint8_t[img.bufLen];
    memcpy(buf, img.buf, bufLen);
  }

  void show()
  {
    string str((char *)buf);
    cout << "Avatar: " << str << endl;
  }

protected:
  uint8_t *buf;
  size_t bufLen = 0;
};

class Resume
{
public:
  Resume() {}
  Resume(const Image &img) : avatar(img)
  {
  }
  virtual shared_ptr<Resume> clone() = 0;
  virtual void show() = 0;

protected:
  char *name;
  Image avatar;
};

class ResumeA : public Resume
{
public:
  ResumeA() {}
  ResumeA(const char *str)
      : ResumeA(str, Image())
  {
  }

  ResumeA(const char *str, const Image &img)
      : Resume(img)
  {
    if (str == nullptr)
    {
      name = new char[1]{0};
    }
    else
    {
      name = new char[strlen(str) + 1];
      strcpy(name, str);
    }
  }

  ResumeA(const ResumeA &obj)
  {
    name = new char[strlen(obj.name) + 1];
    strcpy(name, obj.name);
    avatar = obj.avatar;
  }

  ResumeA &operator=(const ResumeA &obj)
  {
    if (this == &obj)
    {
      return *this;
    }
    if (name != nullptr)
    {
      delete[] name;
    }
    name = new char[strlen(obj.name) + 1];
    strcpy(name, obj.name);
    avatar = obj.avatar;
  }

  virtual ~ResumeA()
  {
    delete[] name;
  }

  virtual shared_ptr<Resume> clone() override
  {
    cout << "cloned." << endl;
    ResumeA *r2 = new ResumeA(*this);
    return shared_ptr<ResumeA>(r2);
  }

  virtual void show() override
  {
    cout << "ResumeA name = " << name << endl;
    avatar.show();
  }
};

class PrototypeTest
{
public:
  void test()
  {
    char *str = "This is the img of avatar !";
    unique_ptr<Resume> r1 = make_unique<ResumeA>("zhangzewei", Image((uint8_t *)(str), strlen(str) + 1));
    auto r2 = r1->clone();

    r1->show();
    r2->show();
    cout << "delete r1" << endl;
    delete r1.release();
    r2->show();
  }
};

#endif