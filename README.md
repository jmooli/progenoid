
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
# Classic Paddle/Ball Game Clone<br/>

![](https://github.com/jmooli/progenoid/blob/master/progenoid.gif)

A classic paddle and ball game inspired by Breakout, developed in C++, written with nvim. This project is a work in progress...
<br/>

# ⚠️ CURRENTLY BROKEN

The game doesn't have any winning condition.
There is no way to restart the game or load different levels.
So, it is merely a skeleton of a game at the moment, but more functionality will be added later.


## 🎮 Creating New Levels<br/>

Designing new levels is straightforward thanks to the flexible level file structure. Here's how you can create and integrate new levels into the game:<br/>


Understand the Level File Format<br/>

Levels are defined in text files within the Levels folder. Each character represents a block's type or an empty space.<br/>


## Characters:


'.' : Empty space (no block)<br/>
'1'-'5' : Block types with varying health<br/>
first line has version of the level format, if incase new format is needed later.<br/>
Example Level (level1):<br/>
<br/>

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

Prerequisites:

Before building the project, ensure you have the following installed on your system:<br/>
C++ Compiler, CMake, SFML Library: Imported from git with cmake <br/>
<br/>
Build Instructions:<br/>

Follow these steps to build the project using CMake:<br/>
```
Clone the Repository
cmake -B build
cmake --build build
Locate the Executable:

./build/bin

copy assets and levels -> bin directory


run
./progenoid

```
Explanation:<br/>

## tested and developed on wsl2

This ensures that the game can locate and load the necessary resources at runtime.<br/>
Directory Structure:<br/>

Your build directory should look like this:

<br/>

```
build/bin/
├── progenoid
|  # Executable
├── Levels/
│   ├── level1
│   └── ...
└── Assets/
    ├── paddle.png
    └── ...
```

# 🚀 Future Work<br/>

This project is continually evolving. Here's what's on the roadmap:<br/>

## Game Mechanics:<br/>

## Winning Conditions: 
Implement logic to determine when a player has successfully completed a level.<br/>
Losing Conditions: Define scenarios where the player loses a life or the game, such as the ball falling below the paddle.<br/>

## User Interface:<br/>
## Score Tracking:
Introduce a scoring system that rewards players for breaking blocks.<br/>

## Lives System: 
Allow players multiple attempts before the game is over.<br/>

## Menus: 
Create start, pause, and game over menus for better navigation.<br/>

## Level Editor:<br/>
Develop a graphical level editor to simplify the creation and modification of game levels.<br/>

## Enhanced Graphics and Audio:
Add particle effects, animations, and sound effects to enrich the gaming experience.<br/>

## Power-Ups:
Introduce power-ups that drop from destroyed blocks, providing temporary abilities like paddle expansion or multi-ball.<br/>

## Responsive Design:<br/>
Optimize the game for different screen resolutions and aspect ratios.<br/>
