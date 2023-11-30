#include "Bullet.h"
#include <GLUT/glut.h>

Bullet::Bullet() : x(0), y(0), speed(0), active(false) {}

Bullet::Bullet(float startX, float startY, float startSpeed)
    : x(startX), y(startY), speed(startSpeed), active(false) {}

void Bullet::draw() const {
    glColor3f(1.0f, 0.0f, 0.0f);
    
    glBegin(GL_POINTS); // Start drawing points
    glPointSize(3.0f);
    glVertex2f(x, y);
    glEnd(); // End drawing points
}

void Bullet::move(float dirX, float dirY) {
    x += speed * dirX;
    y += speed * dirY;
}

void Bullet::activate(float startX, float startY) {
    x = startX;
    y = startY;
    active = true;
}