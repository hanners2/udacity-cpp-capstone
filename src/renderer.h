#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL_ttf.h"

#include "snake.h"
#include <unordered_map>
#include <vector>

class Renderer {
public:
  enum class ColorNames {
    kBlack,
    kYellow,
    kWhite,
    kBlue,
    kRed
  };

  // Constructor
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  Renderer(Renderer&& r); // Move constructor
  // Since this class contains const member variables, assignment
  // operators don't make sense.
  Renderer(Renderer& r) = delete; // Copy constructor
  Renderer operator=(Renderer& r) = delete; // Copy assignment operator
  Renderer operator=(Renderer&& r) = delete; // Move assignement operator
  ~Renderer(); // Destructor

  std::size_t GetScreenWidth() const;
  std::size_t GetScreenHeight() const;

  // Render welcome screen
  void RenderWelcomeScreen(const SDL_Rect &button1, const SDL_Rect &button2,
                           const SDL_Rect &button3, const SDL_Rect &info_rect,
                           const char *welcome_text);
  void Render(Snake const &snake,
              SDL_Point const &food); // Render snake game screen
  void UpdateWindowTitle(int score, int fps);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  TTF_Font *button_font;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  const char *font_path = "../resources/FreeMonoBold.ttf";

  std::unordered_map<ColorNames, std::vector<Uint8>> colors = {
      {ColorNames::kBlack, std::vector<Uint8>{0x1E, 0x1E, 0x1E, 0xFF}},
      {ColorNames::kYellow, std::vector<Uint8>{0xFF, 0xCC, 0x00, 0xFF}},
      {ColorNames::kWhite, std::vector<Uint8>{0xFF, 0xFF, 0xFF, 0xFF}},
      {ColorNames::kBlue, std::vector<Uint8>{0x00, 0x7A, 0xCC, 0xFF}},
      {ColorNames::kRed, std::vector<Uint8>{0xFF, 0x00, 0x00, 0xFF}}};

  void CreateTextRect(const SDL_Rect &rect, ColorNames rect_color,
                    const char *text, ColorNames text_color);
};

#endif