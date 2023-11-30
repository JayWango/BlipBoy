#include "Boy.h"
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

#include <cmath>

Boy::Boy(float startX, float startY, float startSize, float startSpeed)
    : x(startX), y(startY), size(startSize), speed(startSpeed) {}

void Boy::draw() const {
    const int numSegments = 100; 
    const float radius = size / 2.0f; 
    glColor3f(0.1f, 0.3f, 1.0f); 

    glBegin(GL_TRIANGLE_FAN); 
    glVertex2f(x, y);

    for (int i = 0; i <= numSegments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float vertexX = x + radius * cosf(theta);
        float vertexY = y + radius * sinf(theta);
        glVertex2f(vertexX, vertexY);
    }

    glEnd();
}

void Boy::move(float dx, float dy) {
    x += dx * speed;
    y += dy * speed;
}