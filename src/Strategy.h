#ifndef STRATEGY_H
#define STRATEGY_H

#include <iostream>
#include <memory>
using namespace std;

class ReplaceAlgorithm
{
public:
  virtual void replace() = 0;
};

class LRU : public ReplaceAlgorithm
{
public:
  void replace() override
  {
    cout << "Least Recently Used replace algorithm." << endl;
  }
};

class FIFO : public ReplaceAlgorithm
{
public:
  void replace() override
  {
    cout << "First in First out replace algorithm." << endl;
  }
};

class Random : public ReplaceAlgorithm
{
public:
  void replace() override
  {
    cout << "Random replace algorithm." << endl;
  }
};

enum class RA
{
  LRU,
  FIFO,
  RANDOM
};

class Cache
{
public:
  Cache(RA ra)
  {
    if (ra == RA::LRU)
    {
      m_ra = new LRU();
    }
    else if (ra == RA::FIFO)
    {
      m_ra = new FIFO();
    }
    else
    {
      m_ra = new Random();
    }
  }

  virtual ~Cache()
  {
    delete m_ra;
  }

  void replace()
  {
    m_ra->replace();
  }

private:
  ReplaceAlgorithm *m_ra;
};

class StrategyTest
{
public:
  void test()
  {
    Cache cache(RA::LRU);
    cache.replace();
  }
};

#endif