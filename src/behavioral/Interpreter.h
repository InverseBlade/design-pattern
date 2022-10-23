#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>
using namespace std;

class Expression
{
public:
  virtual bool interpret(string context) = 0;
};

class TerminalExpression : public Expression
{
public:
  TerminalExpression(string data)
  {
    this->data = data;
  }
  bool interpret(string context) override
  {
    return context.find(data) != context.npos;
  }

private:
  string data;
};

class OrExpression : public Expression
{
public:
  OrExpression(shared_ptr<Expression> expr1,
               shared_ptr<Expression> expr2)
  {
    this->expr1 = expr1;
    this->expr2 = expr2;
  }
  bool interpret(string context) override
  {
    return expr1->interpret(context) || expr2->interpret(context);
  }

private:
  shared_ptr<Expression> expr1 = nullptr;
  shared_ptr<Expression> expr2 = nullptr;
};

class AndExpression : public Expression
{
public:
  AndExpression(shared_ptr<Expression> expr1,
                shared_ptr<Expression> expr2)
  {
    this->expr1 = expr1;
    this->expr2 = expr2;
  }
  bool interpret(string context) override
  {
    return expr1->interpret(context) && expr2->interpret(context);
  }

private:
  shared_ptr<Expression> expr1 = nullptr;
  shared_ptr<Expression> expr2 = nullptr;
};

shared_ptr<Expression> getMaleExpression()
{
  auto robert = make_shared<TerminalExpression>("Robert");
  auto john = make_shared<TerminalExpression>("John");
  return make_shared<OrExpression>(robert, john);
}

shared_ptr<Expression> getMarriedWomanExpression()
{
  auto julie = make_shared<TerminalExpression>("Julie");
  auto married = make_shared<TerminalExpression>("Married");
  return make_shared<AndExpression>(julie, married);
}

void InterpreterTest()
{
  auto isMale = getMaleExpression();
  auto isMarriedWoman = getMarriedWomanExpression();
  string context = "Robert is male?  : ";
  cout << context << endl
       << isMale->interpret(context) << endl;
  context = "Married Julie.";
  cout << context << endl
       << isMarriedWoman->interpret(context) << endl;
}

#endif