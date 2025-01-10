#include "renderer.h"
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

  //TODO Add text to buttons
  // Place buttons on screen
  CreateButton(button1, ColorNames::kBlue);
  CreateButton(button2, ColorNames::kBlue);
  CreateButton(button3, ColorNames::kBlue);

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

void Renderer::CreateButton(SDL_Rect button, ColorNames color) {
  SDL_SetRenderDrawColor(sdl_renderer, colors[color][0], colors[color][1],
                         colors[color][2], colors[color][3]);
  SDL_RenderFillRect(sdl_renderer, &button);
}
