#include "gamesetup.h"

#include "renderer.h"

#include <exception>

/* Class for recording modifiable variables set by the user upon startup. */

// Default constructor sets medium difficulty
GameSetup::GameSetup() : difficulty(DifficultyLevels::kMedium) {
  CheckDifficulty();
}

// Sets up a welcome screen that gets input from the user.
void GameSetup::AskForUserInput(Renderer &renderer) {
  // TODO
  // Set the text (Comes from a data file)
  // Create a screen with text and three buttons (easy, medium, hard)
  bool waiting_for_selection{true};
  bool running{true};

  while (waiting_for_selection && running) {
    // Render
    renderer.UpdateWindowTitle(0, 0);
    renderer.RenderWelcomeScreen();
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
