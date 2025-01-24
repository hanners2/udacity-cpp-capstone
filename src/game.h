#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "gamesetup.h"
#include "renderer.h"
#include "snake.h"
#include <mutex>
#include <condition_variable>
#include <random>

class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height, GameSetup &game_setup);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  float difficulty; // Defines the starting level of difficulty (0,1]
  int score{0};

  std::mutex game_mtx;
  std::condition_variable game_cond;

  float DifficultyToSpeed(float diff) const;
  void ImplementDifficulty();
  void IncrementDifficulty();
  void PlaceFood();
  void Update(std::unique_lock<std::mutex> &ulock);
};

#endif