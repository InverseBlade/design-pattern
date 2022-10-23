#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <iostream>
#include <memory>
using namespace std;

class Game
{
public:
  virtual void play() final
  {
    initialize();
    startPlay();
    endPlay();
  }

protected:
  virtual void initialize() = 0;
  virtual void startPlay() = 0;
  virtual void endPlay() = 0;
};

class Cricket : public Game
{
public:
  void initialize() override
  {
    cout << "Cricket Game Initialized! Start playing." << endl;
  }

  void startPlay() override
  {
    cout << "Cricket Game Started. Enjoy the game!" << endl;
  }

  void endPlay() override
  {
    cout << "Cricket Game Finished!" << endl;
  }
};

class Football : public Game
{
public:
  void initialize() override
  {
    cout << "Football Game Initialized! Start playing." << endl;
  }

  void startPlay() override
  {
    cout << "Football Game Started. Enjoy the game!" << endl;
  }

  void endPlay() override
  {
    cout << "Football Game Finished!" << endl;
  }
};

void TemplateTest()
{
  unique_ptr<Game> game(new Cricket());
  game->play();

  game = make_unique<Football>();
  game->play();
}

#endif