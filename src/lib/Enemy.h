#ifndef ENEMY_H
#define ENEMY_H

#include <GLUT/glut.h>
#include <chrono>
#include <random>

class Enemy {
    private:
        int HP;                 // yellow enemies = 1 HP, green = 2 HP, blue = 3 HP
       

    public:
        GLfloat enemySize;      // this defines the "size" of the square  
        GLfloat enemyX;         // enemy's center (x, y) position
        GLfloat enemyY;
        GLfloat enemyXMax, enemyXMin, enemyYMax, enemyYMin; // enemy's center (x, y) bounds
        GLfloat xSpeed;      // enemy's speed in x and y directions
        GLfloat ySpeed;
        bool isActive;

        Enemy(GLfloat size, GLfloat enemyXMax, GLfloat enemyXMin, GLfloat enemyYMax, GLfloat enemyYMin, GLfloat speedX, GLfloat speedY);
        void deactivate() { isActive = false; }
        void activate() { isActive = true; }
        int getHP();
        void drawEnemy(GLfloat r, GLfloat g, GLfloat b);
        void calcBounds(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
        void move();
        void generateRandomPos(GLfloat xMax, GLfloat xMin, GLfloat yMax, GLfloat yMin);

};

#endif