#ifndef ENEMY_H
#define ENEMY_H

#include <GLUT/glut.h>

class Enemy {
    private:
        int HP;
    
    public:
        GLfloat enemySize;      // this defines the "size" of the square  
        GLfloat enemyX;         // enemy's center (x, y) position
        GLfloat enemyY;
        GLfloat enemyXMax, enemyXMin, enemyYMax, enemyYMin; // enemy's center (x, y) bounds
        GLfloat xSpeed;      // enemy's speed in x and y directions
        GLfloat ySpeed;

        Enemy(GLfloat size, GLfloat x, GLfloat y, GLfloat xMax, GLfloat xMin, GLfloat yMax, GLfloat yMin, GLfloat speedX, GLfloat speedY);

        int getHP();
        void drawEnemy();
        void calcBounds(GLdouble l, GLdouble r, GLdouble b, GLdouble t);
        void move();


};

#endif