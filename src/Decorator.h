#ifndef DECORATOR_H
#define DECORATOR_H

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Shape
{
public:
  virtual void draw() = 0;
};

class Rectangle : public Shape
{
public:
  void draw() override
  {
    cout << "Shape: Rectangle" << endl;
  }
};

class Circle : public Shape
{
public:
  void draw() override
  {
    cout << "Shape: Circle" << endl;
  }
};

class ShapeDecorator : public Shape
{
public:
  ShapeDecorator(shared_ptr<Shape> shape)
  {
    this->shape = shape;
  }

  void draw() override
  {
    shape->draw();
  }

protected:
  shared_ptr<Shape> shape{nullptr};
};

class RedShapeDecorator : public ShapeDecorator
{
public:
  RedShapeDecorator(shared_ptr<Shape> shape)
      : ShapeDecorator(shape)
  {
  }

  void draw() override
  {
    cout << "Draw RedShape. ";
    setRedBorder(shape);
  }

  void setRedBorder(shared_ptr<Shape> shape)
  {
    cout << "Border Color: Red, content=";
    shape->draw();
  }
};

class DecoratorTest
{
public:
  void test()
  {
    shared_ptr<Circle> circle(new Circle());
    shared_ptr<ShapeDecorator> redCircle(new RedShapeDecorator(make_shared<Circle>()));
    shared_ptr<ShapeDecorator> redRect(new RedShapeDecorator(make_shared<Rectangle>()));

    circle->draw();
    redCircle->draw();
    redRect->draw();
  }
};

#endif