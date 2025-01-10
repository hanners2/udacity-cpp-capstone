#include "controller.h"

#include "gamesetup.h"
#include "snake.h"

#include "SDL.h"

// Helper function to determine if click was on a particular button
bool onButton(const Sint32 x, const Sint32 y, const SDL_Rect button) {
  // True if (x,y) is within the boundaries of button
  bool in_x = x >= button.x && x <= (button.x + button.w);
  bool in_y = y >= button.y && y <= (button.y + button.h);
  return in_x && in_y;
}

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1)
    snake.direction = input;
  return;
}

void Controller::HandleDifficultySelection(bool &waiting, bool &running,
                                           GameSetup *game_setup) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
      // Figure out if this click was on a button and set the appropriate
      // difficulty if so
      if (e.button.button == SDL_BUTTON_LEFT) {
        // See if the click was on any of the buttons
        if (onButton(e.button.x, e.button.y, game_setup->easyButton)) {
          game_setup->SetDifficulty(DifficultyLevels::kEasy);
          waiting = false;
        } else if (onButton(e.button.x, e.button.y, game_setup->medButton)) {
          game_setup->SetDifficulty(DifficultyLevels::kMedium);
          waiting = false;
        } else if (onButton(e.button.x, e.button.y, game_setup->hardButton)) {
          game_setup->SetDifficulty(DifficultyLevels::kHard);
          waiting = false;
        }
      }
    }
  }
}

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
        break;

      case SDLK_DOWN:
        ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
        break;

      case SDLK_LEFT:
        ChangeDirection(snake, Snake::Direction::kLeft,
                        Snake::Direction::kRight);
        break;

      case SDLK_RIGHT:
        ChangeDirection(snake, Snake::Direction::kRight,
                        Snake::Direction::kLeft);
        break;
      }
    }
  }
}