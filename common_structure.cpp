#include "common_structure.h"
#include <iostream>
GameInfo_t currentGameState;
State currentMachineState;
GameInfo_t* updateCurrentState() {
  static GameInfo_t params;
  return &params;
}

State* whichState(){
  static State params;
  return &params;
}
