#include "Bullet.h"
#include <GLUT/glut.h>

#include <cmath>

Bullet::Bullet(float startX, float startY, float targetX, float targetY, float bulletSpeed)
    : x(startX), y(startY), mouseX(targetX), mouseY(targetY), speed(bulletSpeed) {}

void Bullet::draw() const {
    glColor3f(1.0f, 0.0f, 0.0f);
    
    glBegin(GL_POINTS); // Start drawing points
    glPointSize(10.0f);
    glVertex2f(x, y);
    glEnd(); // End drawing points
}

void Bullet::update() {
    // Calculate the direction vector towards the mouse
    float dirX = mouseX - x;
    float dirY = 800 - mouseY - y; // Flip the y-coordinate due to screen orientation

    // Normalize the direction vector
    float length = sqrt(dirX * dirX + dirY * dirY);
    if (length != 0) {
        dirX /= length;
        dirY /= length;
    }

    // Move the bullet towards the mouse position
    x += dirX * speed;
    y += dirY * speed;
}