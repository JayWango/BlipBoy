#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <chrono>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <random>

#include "lib/Boy.h"
#include "lib/Bullet.h"
#include "lib/Enemy.h"


bool isGameOver = false;

int screenWidth;
int screenHeight;
int refreshMillis = 30;      // Refresh period in milliseconds
std::chrono::time_point<std::chrono::steady_clock> startTime;

// instantiate a blipboy with (x, y)
Boy BlipBoy(0.0f, 0.0f);
std::unordered_set<char> pressedKeys;

// instatiate enemy (size, xMax, xMin, yMax, yMin, speedX, speedY)
Enemy enemy1(0.1, 1, -1, 1, -1, 0.02, 0.007);
Enemy enemy2(0.1, 1, -1, 1, -1, 0.04, 0.01);
Enemy enemy3(0.1, 1, -1, 1, -1, 0.03, -0.007);

// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

int points = 0;


void initGL() {
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
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

//restart game function
void restartGame() {
   isGameOver = false;
   BlipBoy.maxhealth = 100; // Reset the player's health
   BlipBoy.x = 0.0f; // Reset the player's position
   BlipBoy.y = 0.0f;
   BlipBoy.bullets.clear();
   // Reactivate and reset enemies
   BlipBoy.activate();
   enemy1.generateRandomPos(enemy1.enemyXMax, enemy1.enemyXMin, enemy1.enemyYMax, enemy1.enemyYMin);
   enemy1.activate();
   enemy2.generateRandomPos(enemy1.enemyXMax, enemy1.enemyXMin, enemy1.enemyYMax, enemy1.enemyYMin);
   enemy2.activate();
   enemy3.generateRandomPos(enemy1.enemyXMax, enemy1.enemyXMin, enemy1.enemyYMax, enemy1.enemyYMin);
   enemy3.activate();

   startTime = std::chrono::steady_clock::now();
}

bool checkBoyEnemyCollision(const Boy& boy, const Enemy& enemy) {
   float boySizeHalf = boy.size / 2.0f;
   return (boy.x - boySizeHalf < enemy.enemyX + enemy.enemySize && boy.x + boySizeHalf > enemy.enemyX - enemy.enemySize && boy.y - boySizeHalf < enemy.enemyY + enemy.enemySize && boy.y + boySizeHalf > enemy.enemyY - enemy.enemySize);
}

void display() {
   // Your rendering code goes here
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
   glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
   glLoadIdentity();              // Reset model-view matrix

   // Calculate elapsed time
   auto currentTime = std::chrono::steady_clock::now();
   std::chrono::duration<double> elapsedSeconds = currentTime - startTime;
   int remainingSeconds = 5 - static_cast<int>(elapsedSeconds.count());

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

   BlipBoy.draw();
   for (auto& bullet : BlipBoy.bullets) {
      bullet.update(); // Update bullet positions
      bullet.draw();   // Draw updated bullets
   }
   BlipBoy.updateBullets();

   if (enemy1.isActive && checkBoyEnemyCollision(BlipBoy, enemy1)) {
      BlipBoy.maxhealth -= 25.0;
      enemy1.deactivate();
   }
   if (enemy2.isActive && checkBoyEnemyCollision(BlipBoy, enemy2)) {
      BlipBoy.maxhealth -= 25.0;
      enemy2.deactivate();
   }
   if (enemy3.isActive && checkBoyEnemyCollision(BlipBoy, enemy3)) {
      BlipBoy.maxhealth -= 25.0;
      enemy3.deactivate();
   }
   BlipBoy.drawHealthBar(BlipBoy.x - 0.1, BlipBoy.y + 0.2, BlipBoy.maxhealth / 100);
   enemy1.drawEnemy(1.0f, 1.0f, 0.0f);
   enemy2.drawEnemy(1.0f, 0.0f, 0.0f);
   enemy3.drawEnemy(0.0f, 1.0f, 0.0f);

   //Game over logic
   if ((remainingSeconds == 0 || BlipBoy.maxhealth <= 0) && !isGameOver) {
      isGameOver = true;
      BlipBoy.maxhealth = 0; // Ensure health doesn't go below zero
   }
   if (isGameOver) {
      glColor3f(1.0f, 0.0f, 0.0f); // Red color for game over text
      const char* gameOverText = "Game Over!\nPress 'R' to restart";
      glRasterPos2f(-0.5f, 0.0f); // Centered position for game over text
      for (const char* c = gameOverText; *c != '\0'; c++) {
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
      }
      BlipBoy.deactivate();
   }
 
   glutSwapBuffers(); // Render now

   // Animation Control - compute the location for the next refresh
   enemy1.move();
   enemy2.move();
   enemy3.move();
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
   enemy1.calcBounds(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
   enemy2.calcBounds(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
   enemy3.calcBounds(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);

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

void handleKeyPress(unsigned char key, int x, int y) {
   pressedKeys.insert(key);
   if (key == 'r' || key == 'R') {
      if(isGameOver){
         restartGame();
      }
   }
}
void handleKeyRelease(unsigned char key, int x, int y) {
   pressedKeys.erase(key);
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Use GLUT_DOUBLE for double buffering

   glutInitWindowPosition(200, 100);
   glutInitWindowSize(800, 600);
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