#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "snake.h"
#include <unordered_map>
#include <vector>

class Renderer {
 public:
  enum class ColorNames {
    kBlack, kYellow, kWhite, kBlue, kRed
  };

  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;


  std::unordered_map<ColorNames, std::vector<Uint8>> colors = {
      {ColorNames::kBlack,  std::vector<Uint8>{0x1E, 0x1E, 0x1E, 0xFF}},
      {ColorNames::kYellow, std::vector<Uint8>{0xFF, 0xCC, 0x00, 0xFF}},
      {ColorNames::kWhite,  std::vector<Uint8>{0xFF, 0xFF, 0xFF, 0xFF}},
      {ColorNames::kBlue,   std::vector<Uint8>{0x00, 0x7A, 0xCC, 0xFF}},
      {ColorNames::kRed,    std::vector<Uint8>{0xFF, 0x00, 0x00, 0xFF}}};
};

#endif