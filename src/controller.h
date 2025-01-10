#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "gamesetup.h"
#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;
  void HandleDifficultySelection(bool &waiting, bool &running,
                                 GameSetup *game_setup);

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif