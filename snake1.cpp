// #include "common_structure.h"
// #include "snake_apple.h"
#include "snake.h"
Snake &getSnake() { return my_snake; }

Snake::Snake(const std::vector<Cell> &cells) : body(cells) {
  length_of_snake = getOccupiedCells(*this).size();
}
void Snake::print_body() {
#ifdef RUN1
  std::cout << "\nBODY ";
  for (const auto &elem : body) std::cout << elem.x << ' ' << elem.y << ' ';
  std::cout << "BODY \n";
#endif
}

void Snake::addVector(Cell new1) {
  std::vector<Cell> copy = {new1};
  copy.insert(copy.end(), body.begin(), body.end());
  body = copy;
}
void Snake::advanceHead(int currentDirection, int previousDirection,
                        Cell &newHead) {
  if (previousDirection != currentDirection)  // добавляем вектор
  {
    addVector(newHead);
  } else {  

    if (currentDirection == 0)
      body[0].x -= 1;

    else if (currentDirection == 1)
      body[0].x += 1;

    else if (currentDirection == 2)
      body[0].y -= 1;

    else if (currentDirection == 3)
      body[0].y += 1;
  }
}
void Snake::updateTail() {
  size_t bodySize = body.size();  // убираем посл клетку или переносим
  if (abs(body[bodySize - 2].x - body[bodySize - 1].x) +
          abs(body[bodySize - 2].y - body[bodySize - 1].y) ==
      1) {
    body.pop_back();
  } else {
    int currentDirection =
        getDirectionBetweenVectors(body[bodySize - 2], body[bodySize - 1]);
    if (currentDirection == 0) {
      body[bodySize - 1].x -= 1;
    } else if (currentDirection == 1) {
      body[bodySize - 1].x += 1;
    } else if (currentDirection == 2) {
      body[bodySize - 1].y -= 1;
    } else if (currentDirection == 3) {
      body[bodySize - 1].y += 1;
    }
  }
}
size_t Snake::get_length_of_snake() const { return length_of_snake; }
void Snake::increase_length_of_snake() { length_of_snake++; }
