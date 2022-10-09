#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

enum PieceColor
{
  BLACK,
  WHITE
};

struct Pos
{
  int x;
  int y;
  Pos(int a, int b) : x(a), y(b) {}
};

class Piece
{
protected:
  PieceColor color;

public:
  Piece(PieceColor color) : color(color) {}
  ~Piece() {}
  virtual void draw() = 0;
};

class BlackPiece : public Piece
{
public:
  BlackPiece(PieceColor color) : Piece(color) {}
  ~BlackPiece() {}
  void draw() override
  {
    cout << "绘制一颗黑棋" << endl;
  }
};

class WhitePiece : public Piece
{
public:
  WhitePiece(PieceColor color) : Piece(color) {}
  ~WhitePiece() {}
  void draw() override
  {
    cout << "绘制一颗白棋" << endl;
  }
};

class Board
{
public:
  Board(string black, string white)
      : blackName(black), whiteName(white)
  {
  }

  virtual ~Board() {}

  void setPiece(PieceColor color, const Pos &pos)
  {
    if (color == BLACK)
    {
      if (m_blackPiece == nullptr)
      {
        m_blackPiece = make_unique<BlackPiece>(BLACK);
      }
      cout << blackName << "at the position of(" << pos.x << "," << pos.y << ") ";
      m_blackPiece->draw();
    }
    else
    {
      if (m_whitePiece == nullptr)
      {
        m_whitePiece = make_unique<WhitePiece>(WHITE);
      }
      cout << whiteName << "at the pos of(" << pos.x << "," << pos.y << ") ";
      m_whitePiece->draw();
    }
    m_pos.emplace_back(pos);
  }

private:
  vector<Pos> m_pos;
  unique_ptr<Piece> m_blackPiece{nullptr};
  unique_ptr<Piece> m_whitePiece{nullptr};
  string blackName;
  string whiteName;
};

class FlyweightTest
{
public:
  void test()
  {
    Board board("黑", "白");
    board.setPiece(BLACK, Pos(4, 4));
    board.setPiece(WHITE, Pos(4, 16));
    board.setPiece(BLACK, Pos(16, 4));
    board.setPiece(WHITE, Pos(16, 16));
  }
};

#endif