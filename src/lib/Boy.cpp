#include "Boy.h"
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

#include <cmath>


Boy::Boy(float startX, float startY, float startSize)
    : x(startX), y(startY), size(startSize) {
    for (int i = 0; i < maxBullets; ++i) {
        bullets[i] = Bullet(); // Initialize bullets array
    }
}

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
    
    // Draw active Bullets
    glPointSize(7.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < maxBullets; ++i) {
        if (bullets[i].active) {
            bullets[i].draw();
        }
    }
    glEnd();
}

void Boy::move(float dx, float dy) {
    // Calculate the new position
    float newX = x + dx;
    float newY = y + dy;

    // Define screen boundaries
    float minX = -10.0f; 
    float maxX = 10.0f;  
    float minY = -10.0f; 
    float maxY = 10.0f;  

    // Clamp the new position within the screen boundaries
    if (newX - size / 2 > minX && newX + size / 2 < maxX) {
        x = newX;
    }
    if (newY - size / 2 > minY && newY + size / 2 < maxY) {
        y = newY;
    }
}

void Boy::setMousePosition(int x, int y) {
    mouseX = x;
    mouseY = y;
}

void Boy::shoot() {
    // Find an inactive bullet and activate it
    for (int i = 0; i < maxBullets; ++i) {
        if (!bullets[i].active) {
            // Assuming mouse position is captured elsewhere and stored in mouseX, mouseY
            float dirX = mouseX - x; // Calculate direction towards mouse position
            float dirY = mouseY - y;

            float magnitude = sqrt((dirX * dirX) + (dirY * dirY)); // Calculate magnitude
            dirX /= magnitude; // Normalize direction vector
            dirY /= magnitude;

            bullets[i].activate(x, y);
            bullets[i].speed = 5.0f;
            bullets[i].move(dirX, dirY);

            break; // Activate only one bullet per shoot() call
        }
    }
}