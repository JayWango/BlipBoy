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
        GLfloat r,g,b;

        Enemy(GLfloat size, GLfloat enemyXMax, GLfloat enemyXMin, GLfloat enemyYMax, GLfloat enemyYMin, GLfloat speedX, GLfloat speedY, int initialHP, GLfloat r, GLfloat g, GLfloat b);
        bool isActive;
        Enemy() : isActive(true){}
        void deactivate() { isActive = false; }
        void activate() { isActive = true; }
        int getHP();
        void drawEnemy();
        void calcBounds(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
        void move();
        void generateRandomPos(GLfloat xMax, GLfloat xMin, GLfloat yMax, GLfloat yMin);
        void takeDMG(int damage){
            HP -= damage;
            if(HP <= 0){
                deactivate();
            }
        }
        void drawHealthBar() const{
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

};

#endif