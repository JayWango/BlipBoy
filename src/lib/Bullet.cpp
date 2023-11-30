#include "Bullet.h"
#include <GLUT/glut.h>

#include <cmath>

Bullet::Bullet(float startX, float startY, float dirX, float dirY, float speed)
    : x(startX), y(startY), dirX(dirX), dirY(dirY), bulletSpeed(speed), isActive(true) {}

void Bullet::update() {
    if (isActive) {
        x += dirX * bulletSpeed;
        y += dirY * bulletSpeed;
    }
}

void Bullet::draw() const {
    if (isActive) {
        glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
        glPointSize(5.0f); // Adjust point size as needed

        glBegin(GL_POINTS);
        glVertex2f(x, y); // Draw a point for the bullet at its position
        glEnd();
    }
}

// void Bullet::update() {
//     // Calculate the direction vector towards the mouse
//     float dirX = mouseX - x;
//     float dirY = 800 - mouseY - y; // Flip the y-coordinate due to screen orientation

//     // Normalize the direction vector
//     float length = sqrt(dirX * dirX + dirY * dirY);
//     if (length != 0) {
//         dirX /= length;
//         dirY /= length;
//     }

//     // Move the bullet towards the mouse position
//     x += dirX * speed;
//     y += dirY * speed;
// }