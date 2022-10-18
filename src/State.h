#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
using namespace std;

class War;

class State
{
public:
  virtual void Prophase() {}
  virtual void Metaphase() {}
  virtual void Anaphase() {}
  virtual void End() {}
  virtual void CurrentState(War *war) {}
};

class War
{
public:
  War(State *state) : m_state(state), m_days(0) {}
  ~War()
  {
    delete m_state;
  }
  int GetDays()
  {
    return m_days;
  }
  void SetDays(int days)
  {
    m_days = days;
  }
  void SetState(State *state)
  {
    delete m_state;
    m_state = state;
  }
  void GetState()
  {
    m_state->CurrentState(this);
  }

private:
  State *m_state;
  int m_days;
};

class EndState : public State
{
public:
  void End(War *war)
  {
    cout << "End Of War." << endl;
  }
  void CurrentState(War *war) override
  {
    End(war);
  }
};

class AnaphaseState : public State
{
public:
  void Anaphase(War *war)
  {
    if (war->GetDays() < 30)
    {
      cout << "第" << war->GetDays() << "天：战争后期，双方拼死一搏" << endl;
    }
    else
    {
      war->SetState(new EndState());
      war->GetState();
    }
  }
  void CurrentState(War *war) override
  {
    Anaphase(war);
  }
};

class MetaphaseState : public State
{
public:
  void Metaphase(War *war)
  {
    if (war->GetDays() < 20)
    {
      cout << "第" << war->GetDays() << "天：战争中期，进入相持阶段，双发各有损耗" << endl;
    }
    else
    {
      war->SetState(new AnaphaseState());
      war->GetState();
    }
  }
  void CurrentState(War *war)
  {
    Metaphase(war);
  }
};

//前期
class ProphaseState : public State
{
public:
  void Prophase(War *war) //前期的具体行为
  {
    if (war->GetDays() < 10)
      cout << "第" << war->GetDays() << "天：战争初期，双方你来我往，互相试探对方" << endl;
    else
    {
      war->SetState(new MetaphaseState());
      war->GetState();
    }
  }
  void CurrentState(War *war) { Prophase(war); }
};

void StateTest()
{
  War *war = new War(new ProphaseState());
  for (int i = 1; i < 50; i += 5)
  {
    war->SetDays(i);
    war->GetState();
  }
  delete war;
};

#endif