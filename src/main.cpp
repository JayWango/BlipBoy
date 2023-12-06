#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <chrono>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <random>
#include <vector>
#include <cstdlib>

#include "lib/Boy.h"
#include "lib/Bullet.h"
#include "lib/Enemy.h"

bool isGameOver = false;

int screenWidth = 800;
int screenHeight = 600;
int refreshMillis = 30;      // Refresh period in milliseconds
std::chrono::time_point<std::chrono::steady_clock> startTime;
std::chrono::time_point<std::chrono::steady_clock> lastSpawnTime = std::chrono::steady_clock::now();
int spawnIntervalMillis = 3000;
int remainingSeconds;

int points = 0;
// instantiate a blipboy with (x, y)
Boy BlipBoy(0.0f, 0.0f);
std::unordered_set<char> pressedKeys;

// instatiate enemy (size, xMax, xMin, yMax, yMin, speedX, speedY)
std::vector<Enemy> enemies;

// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;


//restart game function
void restartGame() {
   isGameOver = false;
   points = 0;
   BlipBoy.maxhealth = 100; // Reset the player's health
   BlipBoy.x = 0.0f; // Reset the player's position
   BlipBoy.y = 0.0f;
   BlipBoy.bullets.clear();
   // Reactivate and reset enemies
   BlipBoy.activate();
   enemies.clear();
   startTime = std::chrono::steady_clock::now();
   lastSpawnTime = std::chrono::steady_clock::now();
   spawnIntervalMillis = 2000;
}

bool checkBoyEnemyCollision(const Boy& boy, const Enemy& enemy) {
   float boySizeHalf = boy.size / 2.0f;
   return (boy.x - boySizeHalf < enemy.enemyX + enemy.enemySize && boy.x + boySizeHalf > enemy.enemyX - enemy.enemySize && boy.y - boySizeHalf < enemy.enemyY + enemy.enemySize && boy.y + boySizeHalf > enemy.enemyY - enemy.enemySize);
}

bool checkBulletEnemyCollision(const Bullet& bullet, const Enemy& enemy){
   if(!enemy.isActive){
      return false;
   }
   return (bullet.x < enemy.enemyX + enemy.enemySize && bullet.x > enemy.enemyX - enemy.enemySize && bullet.y < enemy.enemyY + enemy.enemySize && bullet.y > enemy.enemyY - enemy.enemySize);
}

void spawnEnemy() {
   auto currentTime = std::chrono::steady_clock::now();
   int elapsedMillis = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastSpawnTime).count();
   if (elapsedMillis >= spawnIntervalMillis) {
      GLfloat r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
      GLfloat g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
      GLfloat b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
      
      //add enemies to vector
      enemies.push_back(Enemy(0.1, 1.33, -1.33, 1, -1, 0.02, 0.007, 100, r, g, b));
      enemies.back().activate();
   
      // Reset the spawn time
      lastSpawnTime = std::chrono::steady_clock::now();
      // faster spawning
      spawnIntervalMillis = std::max(1000, spawnIntervalMillis - 100);
      
   }
}

void renderGameInfo() {
   // Calculate elapsed time
   auto currentTime = std::chrono::steady_clock::now();
   std::chrono::duration<double> elapsedSeconds = currentTime - startTime;
   remainingSeconds = 60 - static_cast<int>(elapsedSeconds.count());

   // Render countdown timer
   glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
   glRasterPos2f(clipAreaXLeft + 0.1, clipAreaYTop - 0.1); // Position of the timer
   std::string timerText = "Time: " + std::to_string(remainingSeconds) + "s";
   for (char character : timerText) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, character);
   }

   //Render points counter
   glColor3f(1.0f, 1.0f, 1.0f); 
   glRasterPos2f(clipAreaXRight - 0.35, clipAreaYTop - 0.1); 
   std::string pointsText = "Points: " + std::to_string(points);
   for (char character : pointsText) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, character);
   }
}

void initGL() {
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
   glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
   glLoadIdentity();              // Reset model-view matrix

   renderGameInfo();

   BlipBoy.draw();
   for (auto& bullet : BlipBoy.bullets) {
      bullet.update(); // Update bullet positions
      bullet.draw();   // Draw updated bullets
   }
   //remove inactive bullets
   auto it = BlipBoy.bullets.begin();
    while (it != BlipBoy.bullets.end()) {
      if (!it->isActive) {
         it = BlipBoy.bullets.erase(it);
      } else {
         ++it;
      }
   }
   BlipBoy.updateBullets();
   BlipBoy.drawHealthBar(BlipBoy.x - 0.1, BlipBoy.y + 0.2, BlipBoy.maxhealth / 100);
   
   for (auto& enemy : enemies) {
      if (enemy.isActive) {
         enemy.drawEnemy(); 
         enemy.drawHealthBar();
         enemy.move(); // Move the enemy
         // Check collisions with bullets
         for (auto& bullet : BlipBoy.bullets) {
            if (bullet.isActive && checkBulletEnemyCollision(bullet, enemy)) {
               enemy.takeDMG(20);
               if (enemy.getHP() <= 0) {
                  enemy.deactivate();
                  points++;
               }
               bullet.isActive = false;
               }
         }
         // Check collision with the boy
         if (checkBoyEnemyCollision(BlipBoy, enemy)) {
            BlipBoy.maxhealth -= 20.0;
            enemy.deactivate();
         }
            
      }
   }
   spawnEnemy();

   //Game over logic
   if ((remainingSeconds == 0 || BlipBoy.maxhealth <= 0) && !isGameOver) {
      isGameOver = true;
      BlipBoy.maxhealth = 0; // Ensure health doesn't go below zero
   }
   if (isGameOver) {
      glColor3f(0.0f, 1.0f, 0.0f); // Red color for game over text
      glRasterPos2f(-0.5, clipAreaYTop / 2); // Centered position for game over text
      std::string restartText = "Game Over!\nPress 'R' to restart";
      for (char character : restartText) {
         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, character);
      }

      glColor3f(1.0f, 0.0f, 0.0f); // Red color for game over text
      glRasterPos2f(-0.5f, -0.1f); // Centered position for game over text
      std::string quitText = "Press 'ESC' to close the window.";
      for (char character : quitText) {
         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, character);
      }
   }

   glutSwapBuffers(); // Render now
};

void reshape(GLsizei width, GLsizei height) {
   screenWidth = width;
   screenHeight = height;
   // Compute aspect ratio of the new window
   if (height == 0) height = 1; // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
   // Set up the projection matrix
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix

   if (width >= height) {
      clipAreaXLeft   = -1.0 * aspect;
      clipAreaXRight  = 1.0 * aspect;
      clipAreaYBottom = -1.0;
      clipAreaYTop    = 1.0;
   } 
   else {
      clipAreaXLeft   = -1.0;
      clipAreaXRight  = 1.0;
      clipAreaYBottom = -1.0 / aspect;
      clipAreaYTop    = 1.0 / aspect;
   }

   glOrtho(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop, -1.0, 1.0);

   BlipBoy.calcBounds(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
   for(auto & enemy: enemies){
      enemy.calcBounds(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
   }

   glMatrixMode(GL_MODELVIEW);
}

void Timer(int value) {
   if (!isGameOver) {
      const float boySpeed = 0.03f;

      if (pressedKeys.find('w') != pressedKeys.end()) {
         BlipBoy.move(0.0f, boySpeed);
      }
      if (pressedKeys.find('s') != pressedKeys.end()) {
         BlipBoy.move(0.0f, -boySpeed);
      }
      if (pressedKeys.find('a') != pressedKeys.end()) {
         BlipBoy.move(-boySpeed, 0.0f);
      }
      if (pressedKeys.find('d') != pressedKeys.end()) {
         BlipBoy.move(boySpeed, 0.0f);
      }
      glutPostRedisplay();
   }
   glutTimerFunc(refreshMillis, Timer, 0);
}

void mouse(int button, int state, int x, int y) {
   float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
   float newX;
   float newY;

   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      newX = (static_cast<float>(x) - (screenWidth / 2)) / (screenWidth / 2) * aspect - BlipBoy.x;
      newY = -((static_cast<float>(y) - (screenHeight / 2)) / (screenHeight / 2)) - BlipBoy.y;
      BlipBoy.addBullet(newX, newY);
   }
}

void handleKeyPress(unsigned char key, int x, int y) {
   pressedKeys.insert(key);
   if (isGameOver) {
      if (key == 'r' || key == 'R') {
         restartGame();
      }
   }
   if (key == 27) {  // ASCII code for the Esc key
      exit(0);
   } 
}
void handleKeyRelease(unsigned char key, int x, int y) {
   pressedKeys.erase(key);
}

int main(int argc, char** argv) {
   // random seed for colors
   srand(static_cast<unsigned int>(time(NULL)));
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Use GLUT_DOUBLE for double buffering

   glutInitWindowPosition(200, 100);
   glutInitWindowSize(screenWidth, screenHeight);
   startTime = std::chrono::steady_clock::now(); // Set the start time for the countdown
   glutCreateWindow("BlipBoy");

   glutDisplayFunc(display); // Set the display callback function
   glutReshapeFunc(reshape); //handles window re-sizing
   glutKeyboardFunc(handleKeyPress);
   glutKeyboardUpFunc(handleKeyRelease);
   glutMouseFunc(mouse);

   glutTimerFunc(0, Timer, 0);     // First timer call immediately

   initGL();
   glutMainLoop(); // Enter the GLUT event processing loop

   return 0;
}