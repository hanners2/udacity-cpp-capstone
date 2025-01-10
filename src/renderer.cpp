#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
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

void Renderer::RenderWelcomeScreen() {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, colors[ColorNames::kBlack][0],
                         colors[ColorNames::kBlack][1],
                         colors[ColorNames::kBlack][2],
                         colors[ColorNames::kBlack][3]);
  SDL_RenderClear(sdl_renderer);

  // Set difficulty button size/position parameters
  std::size_t num_buttons = 3;
  std::size_t diff_button_w = screen_width / (num_buttons + 1);
  std::size_t diff_button_h = screen_height / (num_buttons + 1);
  std::size_t diff_button_x; // Set later for each button
  std::size_t diff_button_y = static_cast<int>(
      screen_height * 0.7); // All buttons are 70% down the screen

  std::size_t x_spacing = diff_button_w / 4;

  // Easy button
  diff_button_x = x_spacing;
  CreateButton(diff_button_w, diff_button_h, diff_button_x, diff_button_y,
               ColorNames::kBlue);

  // Medium button
  diff_button_x = 2 * x_spacing + diff_button_w;
  CreateButton(diff_button_w, diff_button_h, diff_button_x, diff_button_y,
               ColorNames::kBlue);

  // Hard button
  diff_button_x = 3 * x_spacing + 2 * diff_button_w;
  CreateButton(diff_button_w, diff_button_h, diff_button_x, diff_button_y,
               ColorNames::kBlue);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);

  // For testing:: Hold 5 sec to see if anything happens
  // SDL_Delay(5000);
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
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::CreateButton(std::size_t width, std::size_t height,
                            std::size_t x, std::size_t y, ColorNames color) {
  // Make some buttons
  SDL_Rect button;
  button.w = width;
  button.h = height;
  button.x = x;
  button.y = y;

  SDL_SetRenderDrawColor(sdl_renderer, colors[color][0], colors[color][1],
                         colors[color][2], colors[color][3]);
  SDL_RenderFillRect(sdl_renderer, &button);
}
