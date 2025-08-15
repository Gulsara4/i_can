#include "common_structure.h"
#include "snake_apple.h"

Snake &getSnake() { return my_snake; }
Apple &getApple() { return app; }
Apple::Apple(int x, int y) : x(x), y(y) {}

int Apple::getX() const { return x; }
int Apple::getY() const { return y; }

void Apple::relocate(Snake &my_snake) {
  auto occ = getOccupiedCells(my_snake);
  static std::random_device rd;   // случайное начальное зерно
  static std::mt19937 gen(rd());  // генератор Mersenne Twister
  std::uniform_int_distribution<int> distX(0, width1 - 1);   // ширина поля
  std::uniform_int_distribution<int> distY(0, height1 - 1);  // высота поля
  do {
    x = rand() % height1;
    y = rand() % width1;

  } while (occ.count((static_cast<long long>(x) << 32) | (unsigned int)y));
  #ifdef RUN1
std::cout << "RELOCATE" << app.getX() << " " << app.getY() << "\n";
#endif
}
int getDirectionBetweenVectors(Cell one, Cell two) {
  int result = -1;
  if (one.y == two.y) {
    if (one.x < two.x)
      result = 0;
    else
      result = 1;
  }
  if (one.x == two.x) {
    if (one.y < two.y)
      result = 2;
    else
      result = 3;
  }
  return result;
}
// Определение конструктора вне класса
Snake::Snake(const std::vector<Cell> &cells) : body(cells) {
  length_of_snake = getOccupiedCells(*this).size();
}
inline long long encodeCell(
    int x, int y)  // long long code = encodeCell(newHead.x, newHead.y);
{
  return (static_cast<long long>(x) << 32) | (static_cast<unsigned int>(y));
}
std::unordered_set<long long> getOccupiedCells(Snake &my) {
  std::unordered_set<long long> occupied;
  for (const auto &cell : my.body) {
    occupied.insert(encodeCell(cell.x, cell.y));
  }
  size_t l = my.body.size();
  for (int i = 0; i < l - 1; i++) {
    int currentDirection =
        getDirectionBetweenVectors(my.body[i], my.body[i + 1]);
    Cell one = my.body[i], two = my.body[i + 1];

    if (currentDirection == 1 || currentDirection == 3) std::swap(one, two);

    if (currentDirection == 0 || currentDirection == 1) {
      for (int j = one.x; j <= two.x; j++)
        occupied.insert(encodeCell(j, one.y));
    } else {
      for (int j = one.y; j <= two.y; j++)
        occupied.insert(encodeCell(one.x, j));
    }
  }
  return occupied;
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
Cell getNextHeadPosition(const Cell &currentHead, char direction) {
  Cell newHead = currentHead;
  if (direction == Left) newHead.y -= 1;
  if (direction == Right) newHead.y += 1;
  if (direction == Up) newHead.x -= 1;
  if (direction == Down) newHead.x += 1;
  return newHead;
}

bool isColliding(const Cell &newHead, Snake &my) {
  if (newHead.x < 0 || newHead.x > height1 - 1 || newHead.y < 0 ||
      newHead.y > width1 - 1) {
#ifdef RUN1
    std::cout << "/n FAIL border" << newHead.x << " " << newHead.y;
#endif
    return false;
  }
  long long code = encodeCell(newHead.x, newHead.y);
  auto occupied = getOccupiedCells(my);
  for (long long c : occupied) {
    if (c == code) {
#ifdef RUN1
      std::cout << "/n FAIL body" << newHead.x << " " << newHead.y;
#endif
      return false;  // клетка занята
    }
  }
  return true;
}
bool checkAppleCollision(Snake &snake, Apple &apple, const Cell &newHead) {
  if (newHead.x == apple.getX() && newHead.y == apple.getY()) {
    apple.relocate(snake);

    return true;  // съели яблоко
  }
  return false;
}
void Snake::advanceHead(int currentDirection, int previousDirection,
                        Cell &newHead) {
  if (previousDirection != currentDirection)  // добавляем вектор
  {
    addVector(newHead);
  } else {  // продолжаем двигаться (голова)

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
void processSnakeMove(UserAction_t t) {
  Snake &my = getSnake();
  Apple &app = getApple();
  GameInfo_t *info = updateCurrentState();
  int previousDirection = getDirectionBetweenVectors(my.body[0], my.body[1]);

  Cell newHead = getNextHeadPosition(my.body[0], t);
  size_t bodySize = my.body.size();
  #ifdef RUN1
  std::cout << "\n Head pre " << my.body[0].x << " " << my.body[0].y << "  "
            << my.body.size() << "\n";
  std::cout << "\n Tail" << my.body[bodySize - 1].x << " "
            << my.body[bodySize - 1].y << "\n";
#endif
  if (isColliding(newHead, my) == true) {
    bool appleCollision = checkAppleCollision(my, app, newHead);
    int currentDirection = getDirectionBetweenVectors(newHead, my.body[0]);


    my.print_body();
    my.advanceHead(currentDirection, previousDirection, newHead);
    if (appleCollision == false) {
      my.updateTail();
    }else{
      my.increase_length_of_snake();
      info->score=my.get_length_of_snake();
      info->level=(int) info->score/20+1;
    }

    my.print_body();
    resetField();
    fillField(my, app);
    print_field();
  } else {
    State *st = whichState();
    *st = (State_terminate);
  }
}

size_t Snake::get_length_of_snake() const { return length_of_snake; }
void Snake::increase_length_of_snake() { length_of_snake++; }
