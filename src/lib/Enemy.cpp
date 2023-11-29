#include "Enemy.h"

Enemy::Enemy(GLfloat size, GLfloat x, GLfloat y, GLfloat xMax, GLfloat xMin, GLfloat yMax, GLfloat yMin, GLfloat speedX, GLfloat speedY) {
        enemySize = size;  
        enemyX = x;      
        enemyY = y;
        enemyXMax = xMax;
        enemyXMin = xMin; 
        enemyYMax = yMax;
        enemyYMin = yMin; 
        xSpeed = speedX;      
        ySpeed = speedY; 
}

void Enemy::drawEnemy() {
    // Define shapes enclosed within a pair of glBegin and glEnd
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(-enemySize, enemySize);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f(-enemySize, -enemySize);     //  so that the normal (front-face) is facing you
      glVertex2f(enemySize, -enemySize);
      glVertex2f(enemySize, enemySize);
   glEnd();
}

void Enemy::checkBounds() {
   // Check if the enemy exceeds the edges
   if (enemyX > enemyXMax) {
      enemyX = enemyXMax;
      xSpeed = -xSpeed;
   } 
   else if (enemyX < enemyXMin) {
      enemyX = enemyXMin;
      xSpeed = -xSpeed;
   }

   if (enemyY > enemyYMax) {
      enemyY = enemyYMax;
      ySpeed = -ySpeed;
   } 
   else if (enemyY < enemyYMin) {
      enemyY = enemyYMin;
      ySpeed = -ySpeed;
   }
}