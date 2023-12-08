#include "Enemy.h"

Enemy::Enemy(GLfloat size, GLfloat xMax, GLfloat xMin, GLfloat yMax, GLfloat yMin, GLfloat speedX, GLfloat speedY, int initialHP, int HPMax, GLfloat r, GLfloat g, GLfloat b, int points): enemySize(size), HP(initialHP), maxHP(HPMax), isActive(true), r(r), g(g), b(b), pts(points) {
        enemySize = size; 
        generateRandomPos(xMax, xMin, yMax, yMin);
        xSpeed = speedX;      
        ySpeed = speedY; 
        calcBounds(xMin , xMax, yMin, yMax);
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
   //checks the hp of the enemy and adjusts color
   if(HP < 3){
      r=255;
      g=255;
      b=0;
   }
   else if(HP < 6){
      r=255;
      g=0;
      b=0;
   }
   else{
      r=0;
      g=0;
      b=255;
   }
   //for enemy color
   glColor3f(r,g,b);
   // Define shapes enclosed within a pair of glBegin and glEnd
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(r, g, b); // Red
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
   enemyYMax = top - enemySize - 0.05;    //the -0.05 is so that the enemy HP bar does not go out of bounds
}

void Enemy::move() {
   if (!isActive) return;
   //checks the hp of the enemy and adjusts speed accordingly
   if(HP < 3){
      xSpeed = xSpeed/abs(xSpeed) * 0.04;
      ySpeed = ySpeed/abs(ySpeed) * 0.014;
   }
   else if(HP < 6){
      xSpeed = xSpeed/abs(xSpeed) * 0.02;
      ySpeed = ySpeed/abs(ySpeed) * 0.007;
   }
   else{
      xSpeed = xSpeed/abs(xSpeed) * 0.01;
      ySpeed = ySpeed/abs(ySpeed) * 0.004;
   }
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

int Enemy::getHP(){
   return HP;
}

void Enemy::drawHealthBar() const {
   if (!isActive) return;

   // Calculate health bar dimensions and position
   float barWidth = enemySize * 1.75;
   float barHeight = 0.01f;
   float healthPercentage = static_cast<float>(HP) / static_cast<float>(maxHP);

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