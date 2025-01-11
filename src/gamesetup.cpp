#include "gamesetup.h"

#include "controller.h"
#include "renderer.h"

#include <exception>

/* Class for recording modifiable variables set by the user upon startup. */

// Default constructor sets medium difficulty
GameSetup::GameSetup() : difficulty(DifficultyLevels::kMedium) {
  CheckDifficulty();
}

// Sets up a welcome screen that gets input from the user.
bool GameSetup::AskForUserInput(Renderer &renderer, Controller &controller) {
  // TODO
  // Set the text (Comes from a data file)
  // Create a screen with text and three buttons (easy, medium, hard)
  SetButtonLocations(renderer);

  bool waiting_for_selection{true};
  bool running{true};

  renderer.UpdateWindowTitle(0, 0);
  while (waiting_for_selection && running) {
    // Handle inputs
    controller.HandleDifficultySelection(waiting_for_selection, running, this);

    // Render (this must be in the loop to rerender in case the user drags it or puts another screen in front of it)
    renderer.RenderWelcomeScreen(easyButton, medButton, hardButton);
    SDL_Delay(1);
  }

  return running;
  // Wait for user input
  // Close and return
}

float GameSetup::GetDifficulty() const { return difficulty; }

void GameSetup::SetDifficulty(float diff) {
  difficulty = diff;
  CheckDifficulty();
}

void GameSetup::CheckDifficulty() {
  // Difficulty must be greater than 0 and less than or equal to 1
  if (difficulty <= 0 || difficulty > 1)
    throw std::runtime_error(
        "Invalid difficulty level. Difficulty level must be in (0,1]");
}

void GameSetup::SetButtonLocations(Renderer &renderer) {
  // Set the button width, height, x, and y given window size known by renderer

  // Set difficulty button size/position parameters
  std::size_t diff_button_w = renderer.GetScreenWidth() / 4;
  std::size_t diff_button_h = renderer.GetScreenHeight() / 4;
  std::size_t diff_button_y = static_cast<int>(
      renderer.GetScreenHeight() * 0.7); // All buttons are 70% down the screen

  std::size_t x_spacing = diff_button_w / 4;

  // Easy button
  easyButton.w = diff_button_w;
  easyButton.h = diff_button_h;
  easyButton.x = x_spacing;
  easyButton.y = diff_button_y;

  // Medium button
  medButton.w = diff_button_w;
  medButton.h = diff_button_h;
  medButton.x = 2 * x_spacing + diff_button_w;
  medButton.y = diff_button_y;

  // Hard button
  hardButton.w = diff_button_w;
  hardButton.h = diff_button_h;
  hardButton.x = 3 * x_spacing + 2 * diff_button_w;
  hardButton.y = diff_button_y;
}
