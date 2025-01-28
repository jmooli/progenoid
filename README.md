
# 🟦 Classic Paddle/Ball Game Clone 🟦
```
██████╗ ██████╗  ██████╗  ██████╗  ███████╗ ███╗   ██╗ ██████╗ ██╗ ██████╗ 
██╔══██╗██╔══██╗██╔═══██ ██╔════╝  ██╔════╝ ████╗  ██║██╔═══██ ██║ ██╔═══██╗
██████╔╝██████╔╝██║   ██╗██║  ███╗ █████╗   ██╔██╗ ██║██║   ██╗██║ ██║   ██║
██╔═══╝ ██╔═══╝ ██║   ██║██║   ██║ ██╔══╝   ██║╚██╗██║██║   ██║██║ ██║   ██║
██║     ██║     ╚██████╔╝╚██████╔╝ ███████╗ ██║ ╚████║╚██████╔╝██║╚██████╔╝
╚═╝     ╚═╝      ╚═════╝  ╚═════╝  ╚══════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═╝ ╚═════╝ 
───────────────────────────────────────────────────────────────
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
───────────────────────────────────────────────────────────────
```
**Classic Paddle/Ball Game Clone**

A classic paddle and ball game inspired by Breakout, developed in C++. This project is a work in progres...

**CURRENTLY BROKEN
-the game doesn't have any winning condition.
-there is no way to restart game or load different levels **

so it is merely a skeleton of a game atm, but will add more functionality alter.

**Creating New Levels
Designing new levels is straightforward thanks to the flexible level file structure. Here's how you can create and integrate new levels into the game:

Understand the Level File Format:

Levels are defined in text files within the Levels folder. Each character represents a block's type or an empty space.

Characters:
. : Empty space (no block)
1-5 : Block types with varying health
Example Level (level1):

Version
.....
.111.
.222.
.333.
.444.
.555.
.....

Create a New Level File:
Currently the game is hardcoded to load level with key "level1". Will add functionality to change levels on the go. **
 
**Resource_manager
Is a handling loading the files from disk, and queried for textures and levels. Currently it is used very little but it should future proof the Extensibility.


**Level editor
Plans to develop a graphical level editor leveraging the current level file structure, allowing for more intuitive level creation.

![License: CC BY-NC-ND 4.0](https://img.shields.io/badge/License-CC%20BY--NC--ND%204.0-lightgrey.svg)
