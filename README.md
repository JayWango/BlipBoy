# BlipBoy : CS 32 Arcade Project

## What the project is about:
This project is a part of CS32 Arcade, where we were tasked to build a game using OpenGL. In order to handle the window and user input, we utilize the GLUT library.  

Our game is called "BlipBoy" and it is played by controlling a circle (our main character) using the WASD keys. THe player can also shoot projectiles using their left mouse click button.  

Enemies on the screen will be in the shape of squares and they will move all around the screen and bounce off of the screen edges. The top right of the corner will include a score counter which will increment by one every time an enemy's HP bar decreases to 0 or below. 

Enemies will have different colors, however they all have the same amount of HP (100). Each bullet from the BlipBoy does 20 damage, so each enemy can take a total of 5 hits. The BlipBoy also has 100 HP and takes 20 damage if it collides with an enemy. The player's goal is to get as high as a score as possible within 60 seconds, or until they run out of HP. 

## How to build the project:
Run the following commands to build/run the project:

In order to build the project, run `make` in the terminal. The Makefile will compile all the necessary `*.cpp` files into object files and link those object files together. 

## How to use the executables once they're built:
Then, in order to open the GLUT window, run the following command to play the game: 
`DISPLAY=:0 ./blipboy`

## An overview of how the code is organized:
All of the game code is located with our `src` folder, and when you open that up, we have our `main.cpp` file which contains all of the game logic and setting up the window that the user plays in. Within `main.cpp`, we include all the important header files from our `lib` folders.  

Within `lib`, we have all of the `*.cpp` and `*.h` files that define the classes of entities in our game, such as the main player, NPCs, and objects such as bullets.  

Separating our code in this way allows us to make our code more modular and helps us easily find where to make changes to each part of the game.