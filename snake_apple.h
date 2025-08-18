#ifndef HEADER_3_H
#define HEADER_3_H
#include <ncurses/ncurses.h>

#include <cmath>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>
#include <fstream>
#include "common_structure.h"

extern GameInfo_t currentGameState;
extern State currentMachineState;
int play_w_file(const char* opt, int score);
void print_field(State* st, WINDOW* win1, WINDOW* win2);
void resetField();
void resetDynamicField(int a);

struct Cell {
  int x;
  int y;
};

class Apple;

class Snake {
 private:
  size_t length_of_snake;

 public:
  std::vector<Cell> body;
  size_t get_length_of_snake() const;
  void increase_length_of_snake();
  Snake(const std::vector<Cell>& cells);

  void addVector(Cell new1);
  void print_body();
  void advanceHead(int des, int des_copy, Cell& newHead);
  void updateTail();
};
class Apple {
 private:
  int x, y;

 public:
  Apple(int x, int y);
  int getX() const;
  int getY() const;
  void relocate(Snake& my_snake);
};
void processSnakeMove(UserAction_t t);
void fillField(Snake& snake, const Apple& app);
inline long long encodeCell(int x, int y);
bool isColliding(const Cell& newHead, Snake& my);
std::unordered_set<long long> getOccupiedCells(Snake& my);
bool checkAppleCollision(Snake& snake, Apple& apple, const Cell& newHead);

int getDirectionBetweenVectors(Cell one, Cell two);
static Snake my_snake({{5, 5}, {8, 5}});
static Apple app(0, 0);
Snake& getSnake();
Apple& getApple();
#endif  // HEADER_3_H
