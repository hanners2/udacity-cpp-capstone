#include "game.h"

#include "SDL.h"
#include <cmath>
#include <iostream>
#include <mutex>
#include <thread>

Game::Game(std::size_t grid_width, std::size_t grid_height,
           GameSetup &game_setup)
    : snake(grid_width, grid_height), engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      difficulty(game_setup.GetDifficulty()) {
  PlaceFood();
  ImplementDifficulty();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  // Start the snake simulation work in its own thread.
  // Use a lock to prevent the snake from updating its location until
  // user inputs have been processed.
  std::unique_lock<std::mutex> lck(game_mtx);
  std::thread t1 = std::thread(&Snake::Simulate, &snake, std::ref(game_mtx),
                               std::ref(game_cond), std::ref(running));

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update(lck);
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
  t1.join();
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

float Game::DifficultyToSpeed(float diff) const {
  // Snake speed needs to grow logarithmically, or the game can quickly
  // become unplayable. This function implements the logic to convert a
  // unitless difficulty value (starting between 0.1 and 1.0) to a
  // snake speed on a log scale.
  return 0.5 * std::log10(diff + 1.2);
}

// Set any parameters that should be influenced by the difficulty
// level. For now, just snake speed.
void Game::ImplementDifficulty() {
  // Standard difficulty levels are 0.1, 0.5, 1.0 (unitless)
  snake.speed = DifficultyToSpeed(difficulty);
}

void Game::IncrementDifficulty() {
  // Increase the speed along the log scale
  difficulty += 0.02;
  snake.speed = DifficultyToSpeed(difficulty);
}

void Game::Update(std::unique_lock<std::mutex> &ulock) {
  snake.update_done = false;
  game_cond.notify_all();
  // This will unlock only when the update is not done, then lock right
  // after
  game_cond.wait(ulock, [this] { return this->snake.update_done; });

  if (!snake.alive)
    return;

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    IncrementDifficulty();
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }