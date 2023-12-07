#ifndef ENEMY_H
#define ENEMY_H

#include <GL/glut.h>
#include <chrono>
#include <random>

class Enemy {
    private:
        int HP;                 // yellow enemies = 2 HP, red = 5 HP, blue = 10 HP
        int maxHP;
        int pts;

    public:
        GLfloat enemySize;      // this defines the "size" of the square  
        GLfloat enemyX;         // enemy's center (x, y) position
        GLfloat enemyY;
        GLfloat enemyXMax, enemyXMin, enemyYMax, enemyYMin; // enemy's center (x, y) bounds
        GLfloat xSpeed;      // enemy's speed in x and y directions
        GLfloat ySpeed;
        bool isActive;
        GLfloat r,g,b;

        Enemy(GLfloat size, GLfloat enemyXMax, GLfloat enemyXMin, GLfloat enemyYMax, GLfloat enemyYMin, GLfloat speedX, GLfloat speedY, int initialHP, int HPMax, GLfloat r, GLfloat g, GLfloat b, int points);
        void deactivate() { isActive = false; }
        void activate() { isActive = true; }
        int getHP();
        void drawEnemy();
        void calcBounds(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
        void move();
        void generateRandomPos(GLfloat xMax, GLfloat xMin, GLfloat yMax, GLfloat yMin);
        void takeDMG(int damage);
        void drawHealthBar() const;
};

#endif