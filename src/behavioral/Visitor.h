#ifndef VISITOR_H
#define VISITOR_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Visitor
{
  using namespace std;
  class ComputerPartVisitor;

  class ComputerPart
  {
  public:
    virtual void accept(ComputerPartVisitor &visitor) = 0;
  };

  class Computer;
  class Mouse;
  class Keyboard;
  class Monitor;

  class ComputerPartVisitor
  {
  public:
    virtual void visit(Computer &computer) = 0;
    virtual void visit(Mouse &mouse) = 0;
    virtual void visit(Keyboard &keyBoard) = 0;
    virtual void visit(Monitor &monitor) = 0;
  };

  class Keyboard : public ComputerPart
  {
  public:
    void accept(ComputerPartVisitor &visitor) override
    {
      visitor.visit(*this);
    }
  };

  class Monitor : public ComputerPart
  {
  public:
    void accept(ComputerPartVisitor &visitor) override
    {
      visitor.visit(*this);
    }
  };

  class Mouse : public ComputerPart
  {
  public:
    void accept(ComputerPartVisitor &visitor) override
    {
      visitor.visit(*this);
    }
  };

  class Computer : public ComputerPart
  {
  public:
    Computer()
    {
      parts = {
          make_shared<Mouse>(),
          make_shared<Keyboard>(),
          make_shared<Monitor>(),
      };
    }
    void accept(ComputerPartVisitor &visitor) override
    {
      for (auto ptr : parts)
      {
        ptr->accept(visitor);
      }
      visitor.visit(*this);
    }

  private:
    vector<shared_ptr<ComputerPart>> parts;
  };

  class ComputerPartDisplayVisitor : public ComputerPartVisitor
  {
  public:
    void visit(Computer &computer) override
    {
      cout << "Display Computer." << endl;
    }
    void visit(Mouse &mouse) override
    {
      cout << "Displaying Mouse." << endl;
    }
    void visit(Keyboard &keyboard) override
    {
      cout << "Displaying keyboard." << endl;
    }
    void visit(Monitor &monitor) override
    {
      cout << "Displaying monitor." << endl;
    }
  };

  void VisitorTest()
  {
    auto computer = make_shared<Computer>();
    ComputerPartDisplayVisitor visitor;
    computer->accept(visitor);
  }
}

#endif