
🟦 Classic Paddle/Ball Game Clone 🟦
```
██████╗ ██████╗  ██████╗  ██████╗  ███████╗ ███╗   ██╗ ██████╗ ██╗ ██████╗
██╔══██╗██╔══██╗██╔═══██ ██╔════╝  ██╔════╝ ████╗  ██║██╔═══██ ██║ ██╔═══██╗
██████╔╝██████╔╝██║   ██╗██║  ███╗ █████╗   ██╔██╗ ██║██║   ██╗██║ ██║   ██║
██╔═══╝ ██╔═══╝ ██║   ██║██║   ██║ ██╔══╝   ██║╚██╗██║██║   ██║██║ ██║   ██║
██║     ██║     ╚██████╔╝╚██████╔╝ ███████╗ ██║ ╚████║╚██████╔╝██║╚██████╔╝
╚═╝     ╚═╝      ╚═════╝  ╚═════╝  ╚══════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═╝ ╚═════╝
──────────────────────────────────────────────────────────────
███▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███████
███                                                             ███
███   █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ ███
███   █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ ███
███   █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ ███
███                                                             ███
███      o                                                      ███
███                                                             ███
███-------------------------------------------------------------███
███                                                             ███
███               (_________________)                           ███
███                                                             ███
███████████████████████████████████████████████████████████████████
──────────────────────────────────────────────────────────────
```
Classic Paddle/Ball Game Clone

A classic paddle and ball game inspired by Breakout, developed in C++. This project is a work in progress...

⚠️ CURRENTLY BROKEN
The game doesn't have any winning condition.
There is no way to restart the game or load different levels.
So, it is merely a skeleton of a game at the moment, but more functionality will be added later.

🎮 Creating New Levels
Designing new levels is straightforward thanks to the flexible level file structure. Here's how you can create and integrate new levels into the game:

Understand the Level File Format
Levels are defined in text files within the Levels folder. Each character represents a block's type or an empty space.

Characters:

. : Empty space (no block)
1-5 : Block types with varying health
first line has version of the level format, if incase new format is needed later.
Example Level (level1):

```
version#
.....
.111.
.222.
.333.
.444.
.555.
.....
```
Create a New Level File
Currently, the game is hardcoded to load the level with the key "level1". Functionality to change levels on the go will be added in future updates.

📦 Resource Manager
The Resource Manager handles loading files from disk and provides access to textures and levels. Although it's used sparingly at the moment, it is designed to future-proof the extensibility of the game, allowing for the easy addition of numerous textures and other assets.

🛠️ Level Editor
Plans are in place to develop a graphical level editor that leverages the current level file structure. This will allow for more intuitive level creation and management.



📋 Installation Instructions
Prerequisites
Before building the project, ensure you have the following installed on your system:

C++ Compiler: Compatible with C++17 or later.
CMake: Version 3.10 or higher.
SFML Library: Imported from git with cmake
Build Instructions
Follow these steps to build the project using CMake:

Clone the Repository
cmake -B build
cmake --build build
Locate the Executable:
/build/bin
copy assets and levels -> bin directory

run
./progenoid

Explanation:
This ensures that the game can locate and load the necessary resources at runtime.

Directory Structure:

Your build directory should look like this:


build/
├── progenoid
|  # Executable
├── Levels/
│   ├── level1
│   └── ...
└── Assets/
    ├── paddle.png
    └── ...


🚀 Future Work
This project is continually evolving. Here's what's on the roadmap:

Game Mechanics:

Winning Conditions: Implement logic to determine when a player has successfully completed a level.
Losing Conditions: Define scenarios where the player loses a life or the game, such as the ball falling below the paddle.
User Interface:

Score Tracking: Introduce a scoring system that rewards players for breaking blocks.
Lives System: Allow players multiple attempts before the game is over.
Menus: Create start, pause, and game over menus for better navigation.
Level Editor:

Develop a graphical level editor to simplify the creation and modification of game levels.
Enhanced Graphics and Audio:

Add particle effects, animations, and sound effects to enrich the gaming experience.
Power-Ups:

Introduce power-ups that drop from destroyed blocks, providing temporary abilities like paddle expansion or multi-ball.
Responsive Design:

Optimize the game for different screen resolutions and aspect ratios.

📜 License
This project is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.

🎥 Gameplay
(Consider adding a screenshot or GIF of your game here to showcase the gameplay.)

## 🎥 Gameplay

![Gameplay Screenshot](path/to/screenshot.png)
Links to Documentation:
