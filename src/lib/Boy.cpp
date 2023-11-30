#include "Boy.h"
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

Boy::Boy(float startX, float startY, float startSize, float startSpeed)
    : x(startX), y(startY), size(startSize), speed(startSpeed) {}

void Boy::draw() const {
    glPointSize(10.0);
    glBegin(GL_QUADS);
    glVertex2f(x - size, y + size);
    glVertex2f(x - size, y - size);
    glVertex2f(x + size, y - size);
    glVertex2f(x + size, y + size);
    glEnd();
}

void Boy::move(float dx, float dy) {
    x += dx * speed;
    y += dy * speed;
}