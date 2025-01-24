# Udacity C++ Nanodegress Capstone

This project extends the Snake game provided as the capstone project for the Udacity C++ Nanodegree. The original code can be found [here](https://github.com/udacity/CppND-Capstone-Snake-Game).

<img src="snake_game.gif"/>

## Added Features
I added a "welcome screen" with three buttons that allows the player to select the desired difficulty level for the game. This will affect the starting speed of the Snake, as well as the rate of speed increases as the game progresses.

I also added multithreading, putting the snake update logic in its own thread. A future feature idea is to add more snakes to the game, which would each do updates in their own thread.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL2_ttf >= 2.0
  * Links to binaries for Mac and Windows systems can be found on the [SDL2_ttf wiki](https://www.libsdl.org/projects/old/SDL_ttf/)
  * For Linux, use your system's package manager, e.g. `apt-get install libsdl2-ttf-dev`

## Basic Build Instructions
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Rubric Points
Below is a tally of the rubric items that were addressed by the added features, and where in the code the criteria is met. The categories in the project rubric are provided below.

### README
1. This README includes instructions for building and running the project, as well as installing the additional library needed (`libsdl2-ttf`).
2. In the "Added Feature" section above, I indicated the new features added.
3. The following sections of the README will talk about which rubric points are addressed.

### Compiling and testing
1. This project does indeed compile and run without errors in the Udacity workspace.

### Loops, Functions, I/O
1. Many new functions and a new class were added to the code. **See the new `gamesetup.cpp` file for several examples.**
3. The project now accepts user input (in the form of button clicks) and processes that input to change the behavior of the game. **See `gamesetup.cpp:16` (`AskForUserInput` function).**
4. Several data structures have been added that are either arrays/loops or constant. **See `renderer.h:55` for an unordered map of vectors that provides easier color references in the code. See `renderer.h:36` (`RenderWelcomeScreen` function) for an example of a function that treats parameters as constant.**

### Object Oriented Programming
1. The `GameSetup` class has been added to the program. It includes private and public data members and methods. `GameSetup` includes an invariant on the `difficulty` member. **See `gamesetup.h` for an overview.**
2. The `GameSetup` constructor uses an initialization list. **See `gamesetup.cpp:11`.**
3. All member functions of the new `GameSetup` class abstract the implementation details and are well documented via comments and descriptive naming. **See `gamesetup.cpp`.**

### Memory Management
1. Two new functions that use pass-by-reference are `Renderer::RenderWelcomeScreen`, and `GameSetup::AskForUserInput`. **See `renderer.h:36` and `gamesetup.h:28`.**
3. The `Renderer::CreateTextRect` acquires resources on the heap via calls to the SDL function `TTF_RenderText_Solid` and `SDL_CreateTextureFromSurface`. RAII was implemented for the resources by storing each resource pointer in a `std::unique_ptr` with a custom destructor. (Thanks to [this](https://stackoverflow.com/questions/39176805/using-raii-to-manage-resources-from-a-c-style-api) StackOverflow article for the idea.) When the pointer goes out of scope, the resouces will be deleted.
4. This project follows the Rule of 5. The only class that manages heap-allocated memory is `Renderer`. Since it had a destructor that released memory (indirectly through the calls to some SDL functions), I needed to handle the other four (copy constructor, move constructor, copy assignment operator, move assignment operator). This class contains `const` member variables, so assignment to the class would contradict its design. Therefore the assignment operators have been explicitly deleted. When considering implementing a copy constructor, I discovered that the SDL library does not support deep copying of most SDL objects, including the ones used by the `Renderer` class. Rather than implementing a partial copy of `Renderer` in its copy constructor, I chose to delete this function as well. The move constructor is implemented. **See `renderer.cpp:53`.**
6. A smart pointer is used in the `Renderer::CreateTextRect` function to automatically handle aquisition and release of resources. **See `renderer.cpp:168` and `renderer.cpp:178`.**

### Concurency
1. This project uses multithreading. A thread handling snake updates is spun off at the beginning of the `Game::Run` routine. **See `game.cpp:32`.** As-is, multithreading doesn't buy us any speed improvements, but perhaps as more features are added, it would. I envision adding more snakes (that are controlled by the game), which could operate in additional threads.
3. A mutex and locks are used to protect the snake data while it is being read/written. **See `game.cpp:31` and `snake.cpp:94`.**
4. A condition variable is also used to allow communication between the parent and child threads, so that the snake only updates once per frame. **See `game.cpp:109` and `snake.cpp:102`.**

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

This project uses the Adobe font "Source Code", which is distributed used the SIL OPEN FONT LICENSE Version 1.1 - 26 February 2007. See [](http://scripts.sil.org/OFL) for the full text.
