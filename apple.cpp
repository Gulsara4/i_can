// #include "common_structure.h"
// #include "snake_apple.h"
#include "snake.h"
Apple &getApple() { return app; }
Apple::Apple(int x, int y) : x(x), y(y) {}

int Apple::getX() const { return x; }
int Apple::getY() const { return y; }

void Apple::relocate(Snake &my_snake) {
  auto occ = getOccupiedCells(my_snake);
  static std::random_device rd;  
  static std::mt19937 gen(rd());  
  std::uniform_int_distribution<int> distX(0, width1 - 1);  // ширина поля
  std::uniform_int_distribution<int> distY(0, height1 - 1);  // высота поля
  do {
    x = rand() % height1;
    y = rand() % width1;

  } while (occ.count((static_cast<long long>(x) << 32) | (unsigned int)y));
#ifdef RUN1
  std::cout << "RELOCATE" << app.getX() << " " << app.getY() << "\n";
#endif
}