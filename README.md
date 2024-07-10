# The Maze

# Introduction

Welcome to The Maze Game! I created this project because I'm passionate about retro-style games and fascinated by how real-time graphics work. This game lets you explore mazes using advanced technology that creates a 3D-like environment on your screen, similar to old-school first-person shooter games. It's all about getting that nostalgic feel while diving into a challenging and immersive gaming experience.

Link to Deployed Project => https://github.com/nikikiarie/Maze-Game.git
Project Blog => https://www.linkedin.com/posts/nicholasnganga_maze-game-blog-activity-7216855904904740864-1WnZ?utm_source=share&utm_medium=member_desktop
Author => https://www.linkedin.com/in/nicholasnganga/

# Inspiration

The inspiration for this project came from my desire to delve deep into the fundamentals of game development. I aimed to create a game that not only challenges players with intricate mazes but also pushes the boundaries of what I could achieve technically using C and SDL2.



# Technical Details

1 => Raycasting Technology

The game uses raycasting, a technique seen in classic games like Wolfenstein 3D. Instead of modern 3D rendering, which is complex and realistic, raycasting simulates a 3D environment using a 2D map. Each vertical strip on the screen is calculated based on the player's position and viewing angle, creating the illusion of depth with textured walls and dynamic lighting.

2 => SDL2 Integration

SDL2 (Simple DirectMedia Layer) was chosen for handling graphics, audio, and input. It's a reliable framework that simplifies the implementation of game mechanics and real-time player interaction.

# Game Mechanics

Players explore maze levels, solving puzzles and avoiding obstacles with:

1 => Player Movement: Smooth movement controls (WASD) ensure players navigate seamlessly, with real-time collision detection preventing them from walking through walls.

2 => Interactive Minimap: A live minimap helps players navigate complex mazes by showing their position and surroundings in real-time.

3 => Weapon System: Customizable weapons add depth to gameplay, allowing players to engage enemies and overcome challenges effectively.

# Future Iterations

Future updates to the game will include:

1=> Enhanced Visuals: Implementing advanced shading and detailed textures to enhance the visual appeal and immersion.

2 => Multiplayer Mode: Introducing competitive or cooperative multiplayer modes to engage a wider audience and add replayability.

3 => Level Editor: Allowing players to create and share custom mazes, fostering community involvement and expanding the game's content and longevity.

The Maze is game created using the C programming language, SDL2 and the concept of raycasting. On the map, the player can move in all four directions and rotate his field of view. This game includes collision on the wall and an objectif point in yellow on the minimap.

## Installation

Clone this repo:
```bash
git clone https://github.com/nikikiarie/Maze-Game.git
```

First make sure SDL is installed. Then execute the following command to compile all the files and create the executable of the game 

```bash
make
```

## Usage
After successfully compiling run the program using following command:

```bash
./maze-game
```

## Controls

```W``` - Moving forward

```Left arrow``` - Turn left

```Right arrow``` - Turn right

```S``` - Moving backward

```P``` - Enable and disable minimap view

```Z``` - Enable and disable weapon view


```A``` - Look left

```D``` - Look right



***Have fun!***

# Directories

src

Contains all the source code files written in C.

inc

Contains all the header files.

maps

Contains map data files. This will be used by the program to output the map layout.



## Related

A lot of source provides resources on SDL and Raycasting.
[SDL2 tutorial](https://lazyfoo.net/tutorials/SDL/index.php)
[Raycasting tutorial 2](https://lodev.org/cgtutor/raycasting.html)
[SDL2 Functions](https://wiki.libsdl.org/SDL2/CategoryAPI)
[Raycasting tutorial 1](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)

# Licence
MIT License

# Contributing
=> Read the source files in src folder and the header files in inc folder.
=> Clone the repo and make a new branch: $ git checkout https://github.com/nikikiarie/Maze-Game.git  -b [name_of_new_branch].
=> Add a feature, fix a bug, or refactor some code
=> Write/update tests for the changes you made, if necessary.
=> Update README.md if necessary.
=> Open a Pull Request with a comprehensive description of changes.


