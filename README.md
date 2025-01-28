
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
Classic Paddle/Ball Game Clone<br/>
<br/>

A classic paddle and ball game inspired by Breakout, developed in C++. This project is a work in progress...
<br/>

⚠️ CURRENTLY BROKEN<br/>

The game doesn't have any winning condition.<br/>

There is no way to restart the game or load different levels.<br/>

So, it is merely a skeleton of a game at the moment, but more functionality will be added later.<br/>


🎮 Creating New Levels<br/>

Designing new levels is straightforward thanks to the flexible level file structure. Here's how you can create and integrate new levels into the game:<br/>


Understand the Level File Format<br/>

Levels are defined in text files within the Levels folder. Each character represents a block's type or an empty space.<br/>


Characters:<br/>


. : Empty space (no block)<br/>

1-5 : Block types with varying health<br/>

first line has version of the level format, if incase new format is needed later.<br/>

Example Level (level1):<br/>


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
Create a New Level File<br/>

Currently, the game is hardcoded to load the level with the key "level1". Functionality to change levels on the go will be added in future updates.<br/>


📦 Resource Manager<br/>

The Resource Manager handles loading files from disk and provides access to textures and levels. Although it's used sparingly at the moment, it is designed to future-proof the extensibility of the game, allowing for the easy addition of numerous textures and other assets.
<br/>

🛠️ Level Editor<br/>

Plans are in place to develop a graphical level editor that leverages the current level file structure. This will allow for more intuitive level creation and management.



📋 Installation Instructions<br/>

Prerequisites<br/>

Before building the project, ensure you have the following installed on your system:
<br/>

C++ Compiler: Compatible with C++17 or later.<br/>

CMake: Version 3.10 or higher.<br/>

SFML Library: Imported from git with cmake<br/>

Build Instructions<br/>

Follow these steps to build the project using CMake:
<br/>

Clone the Repository<br/>

cmake -B build<br/>

cmake --build build<br/>

Locate the Executable:<br/>

/build/bin<br/>

copy assets and levels -> bin directory<br/>


run<br/>

./progenoid<br/>


Explanation:<br/>

This ensures that the game can locate and load the necessary resources at runtime.

Directory Structure:

Your build directory should look like this:

<br/>
```
build/
├── progenoid
|  # Executable
├── Levels/
│   ├── level1
│   └── ...
└── Assets/
    ├── paddle.png
    └── ...
```

🚀 Future Work<br/>

This project is continually evolving. Here's what's on the roadmap:

Game Mechanics:<br/>


Winning Conditions: Implement logic to determine when a player has successfully completed a level.
Losing Conditions: Define scenarios where the player loses a life or the game, such as the ball falling below the paddle.
User Interface:<br/>


Score Tracking: Introduce a scoring system that rewards players for breaking blocks.
Lives System: Allow players multiple attempts before the game is over.
Menus: Create start, pause, and game over menus for better navigation.
Level Editor:<br/>


Develop a graphical level editor to simplify the creation and modification of game levels.
Enhanced Graphics and Audio:

Add particle effects, animations, and sound effects to enrich the gaming experience.
Power-Ups:<br/>


Introduce power-ups that drop from destroyed blocks, providing temporary abilities like paddle expansion or multi-ball.
Responsive Design:<br/>


Optimize the game for different screen resolutions and aspect ratios.

📜 License<br/>

This project is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.

🎥 Gameplay<br/>

## 🎥 Gameplay

![Gameplay Screenshot](path/to/screenshot.png)
