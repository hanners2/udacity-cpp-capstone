#ifndef GAMESETUP_H
#define GAMESETUP_H

#include "renderer.h"

namespace DifficultyLevels {
constexpr float kEasy = 0.1;
constexpr float kMedium = 0.5;
constexpr float kHard = 1.0;
} // namespace DifficultyLevels

/* Class for recording modifiable variables set by the user upon startup. */
class GameSetup {
public:
  // Constructor
  GameSetup();

  // Getters & setters
  float GetDifficulty() const;
  void SetDifficulty(float diff);

  // Typical behavior methods
  void AskForUserInput(Renderer &renderer); // Sets up a welcome screen that
                                            // gets input from the user.

private:
  float difficulty;       // Defines the starting level of difficulty (0,1]
  void CheckDifficulty(); // Checks the invariant on difficulty
};

#endif