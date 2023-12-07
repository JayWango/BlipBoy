# BlipBoy : CS 32 Arcade Project

## What the project is about:
This project is a part of CS32 Arcade, where we were tasked to build a game using OpenGL. In order to handle the window and user input, we utilize the GLUT library.  

Our game is called "BlipBoy" and it is played by controlling a circle (our main character) using the WASD keys. THe player can also shoot projectiles using their left mouse click button.  

Enemies on the screen will be in the shape of squares and they will move all around the screen and bounce off of the screen edges. The top right of the corner will include a score counter which will increment by one every time a projectile comes into contact with an enemy.  

Enemies will have different colors, each indicating the amount of "HP" that they have. Yellow enemies can take 3 hits, Green can take 6 hits, and blue can take 9 hits. The player is rewarded more points for killing enemies that have greater HP. Also, when you hit an enemy, the speed of the enemy will increase as the health decreases. The goal of the game will be to get as high of a score as possible in a time limit of 1 minute. 

## How to build the project:
Run the following commands to build/run the project:

In order to build the project, run `make` in the terminal. The Makefile will compile all the necessary `*.cpp` files into object files and link those object files together. 

## How to use the executables once they're built:
Then, in order to open the GLUT window, run the following command to play the game: 
`DISPLAY=:0 ./blipboy`

**NOTE: If running on MacOS, ensure that XQuartz is installed and opened on your device before running the command above.**

## An overview of how the code is organized:
All of the game code is located with our `src` folder, and when you open that up, we have our `main.cpp` file which contains all of the game logic and setting up the window that the user plays in. Within `main.cpp`, we include all the important header files from our `lib` folders.  

Within `lib`, we have all of the `*.cpp` and `*.h` files that define the classes of entities in our game, such as the main player, NPCs, and objects such as bullets.  

Separating our code in this way allows us to make our code more modular and helps us easily find where to make changes to each part of the game.