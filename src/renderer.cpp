#include "renderer.h"

#include "SDL.h"
#include "SDL_ttf.h"

#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width), screen_height(screen_height),
      grid_width(grid_width), grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  if (TTF_Init() < 0) {
    std::cerr << "SDL_ttf could not initialize.\n";
    std::cerr << "TTF_Error: " << TTF_GetError() << "\n";
    SDL_Quit();
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Set font
  char* font_path = "../resources/FreeMonoBold.ttf";
  button_font = TTF_OpenFont(font_path, 24);
  if (nullptr == button_font) {
    std::cerr << "Font file at " << font_path << " could not be opened" << "\n";
    std::cerr << "TTF_Error: " << TTF_GetError() << "\n";
    SDL_Quit();
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

  std::size_t Renderer::GetScreenWidth() const { return screen_width; }
  std::size_t Renderer::GetScreenHeight() const { return screen_height; }

void Renderer::RenderWelcomeScreen(SDL_Rect button1, SDL_Rect button2, SDL_Rect button3) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, colors[ColorNames::kBlack][0],
                         colors[ColorNames::kBlack][1],
                         colors[ColorNames::kBlack][2],
                         colors[ColorNames::kBlack][3]);
  SDL_RenderClear(sdl_renderer);

  // TODO: Write some welcome message above the buttons

  // Place buttons on screen
  CreateButton(button1, ColorNames::kBlue, "Easy");
  CreateButton(button2, ColorNames::kBlue, "Medium");
  CreateButton(button3, ColorNames::kBlue, "Hard");

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, colors[ColorNames::kBlack][0],
                         colors[ColorNames::kBlack][1],
                         colors[ColorNames::kBlack][2],
                         colors[ColorNames::kBlack][3]);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, colors[ColorNames::kYellow][0],
                         colors[ColorNames::kYellow][1],
                         colors[ColorNames::kYellow][2],
                         colors[ColorNames::kYellow][3]);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, colors[ColorNames::kWhite][0],
                         colors[ColorNames::kWhite][1],
                         colors[ColorNames::kWhite][2],
                         colors[ColorNames::kWhite][3]);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, colors[ColorNames::kBlue][0],
                           colors[ColorNames::kBlue][1],
                           colors[ColorNames::kBlue][2],
                           colors[ColorNames::kBlue][3]);
  } else {
    SDL_SetRenderDrawColor(
        sdl_renderer, colors[ColorNames::kRed][0], colors[ColorNames::kRed][1],
        colors[ColorNames::kRed][2], colors[ColorNames::kRed][3]);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::CreateButton(SDL_Rect button, ColorNames color,
                            char const *text) {
  // std::cout << "In CreateButton" << "\n";
  //  Create a rectangle of the specified color
  SDL_SetRenderDrawColor(sdl_renderer, colors[color][0], colors[color][1],
                         colors[color][2], colors[color][3]);
  SDL_RenderFillRect(sdl_renderer, &button);

  // Add text centered on the rectangl
  SDL_Color text_color = {0, 0, 0}; // Black
  SDL_Surface *text_surface =
      TTF_RenderText_Solid(button_font, text, text_color);

  // Center text on the button
  SDL_Rect text_rect = button;
  text_rect.w = text_surface->w;
  text_rect.h = text_surface->h;
  text_rect.x = button.x + (button.w - text_rect.w) / 2;
  text_rect.y = button.y + (button.h - text_rect.h) / 2;

  SDL_Texture *text_texture =
      SDL_CreateTextureFromSurface(sdl_renderer, text_surface);
  // Might this create a dangling pointer situation? Is it a problem when
  // text_texture and text_rect go out of scope?
  SDL_RenderCopy(sdl_renderer, text_texture, NULL, &text_rect);
}