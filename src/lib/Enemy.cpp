#include "Enemy.h"

Enemy::Enemy(GLfloat size, GLfloat xMax, GLfloat xMin, GLfloat yMax, GLfloat yMin, GLfloat speedX, GLfloat speedY, int initialHP, GLfloat r, GLfloat g, GLfloat b): enemySize(size), HP(initialHP), isActive(true), r(r), g(g), b(b) {
        enemySize = size; 
        generateRandomPos(xMax, xMin, yMax, yMin);
        xSpeed = speedX;      
        ySpeed = speedY; 
        calcBounds(xMin, xMax, yMin, yMax);
        isActive = true;
}

void Enemy::generateRandomPos(GLfloat xMax, GLfloat xMin, GLfloat yMax, GLfloat yMin) {
    // Use the current time as a seed for the random number generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // Create a uniform distribution for coordinates
    std::uniform_real_distribution<double> xDistribution(xMin, xMax);
    std::uniform_real_distribution<double> yDistribution(yMin, yMax);

    // Generate random coordinates until a non-zero coordinate pair is obtained
    
    do {
        enemyX = xDistribution(generator);
        enemyY = yDistribution(generator);
    } 
    while (enemyX < enemySize + 0.1 && enemyY < enemySize + 0.1);
}

void Enemy::drawEnemy() {
   if (!isActive) return;
   glPushMatrix();
   glTranslatef(enemyX, enemyY, 0.0f);  // Translate to (xPos, yPos)
   
   // Define shapes enclosed within a pair of glBegin and glEnd
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(r, g, b);
      glVertex2f(-enemySize, enemySize);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f(-enemySize, -enemySize);     //  so that the normal (front-face) is facing you
      glVertex2f(enemySize, -enemySize);
      glVertex2f(enemySize, enemySize);
   glEnd();
   
   glPopMatrix();
}

void Enemy::calcBounds(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) {
   enemyXMin = left + enemySize;
   enemyXMax = right - enemySize;
   enemyYMin = bottom + enemySize;
   enemyYMax = top - enemySize;
}

void Enemy::move() {
    if (!isActive) return;
    // Animation Control - compute the location for the next refresh
    enemyX += xSpeed;
    enemyY += ySpeed;

   //Check if the enemy exceeds the edges
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

void Enemy::takeDMG(int damage) {
   HP -= damage;
}

void Enemy::drawHealthBar() {
      if (!isActive) return;

      // Calculate health bar dimensions and position
      float barWidth = enemySize * 1.75;
      float barHeight = 0.01f;
      float healthPercentage = static_cast<float>(HP) / 100.0f;

      glPushMatrix();
      glTranslatef(enemyX, enemyY + enemySize + 0.05f, 0.0f);  // Position above the enemy

      // grey health background
      glColor3f(0.5f, 0.5f, 0.5f);
      glBegin(GL_QUADS);
      glVertex2f(-barWidth / 2, barHeight);
      glVertex2f(-barWidth / 2, -barHeight);
      glVertex2f(barWidth / 2, -barHeight);
      glVertex2f(barWidth / 2, barHeight);
      glEnd();

      // red health background
      glColor3f(1.0f, 0.0f, 0.0f);
      float healthBarWidth = barWidth * healthPercentage;
      glBegin(GL_QUADS);
      glVertex2f(-barWidth / 2, barHeight);
      glVertex2f(-barWidth / 2 + healthBarWidth, barHeight);
      glVertex2f(-barWidth / 2 + healthBarWidth, -barHeight);
      glVertex2f(-barWidth / 2, -barHeight);
      glEnd();

      glPopMatrix();
}

int Enemy::getHP() {
   return HP;
}