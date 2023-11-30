#include "Boy.h"
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

#include <cmath>


Boy::Boy(float startX, float startY, float startSize)
    : x(startX), y(startY), size(startSize) {}

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
    // glBegin(GL_POINTS);
    // for (const auto& bullet : bullets) {
    //     bullet.draw();
    // }
    // glEnd();
}

void Boy::move(float dx, float dy) {
    // Calculate the new position
    float newX = x + dx;
    float newY = y + dy;

    float minX = -10.0f; 
    float maxX = 10.0f;  
    float minY = -10.0f; 
    float maxY = 10.0f;  

    // boundaries check
    if (newX - size / 2 > minX && newX + size / 2 < maxX) {
        x = newX;
    }
    if (newY - size / 2 > minY && newY + size / 2 < maxY) {
        y = newY;
    }

}


void Boy::updateBullets() {
    std::vector<Bullet>::iterator it = bullets.begin();
    while (it != bullets.end()) {
        const Bullet& b = *it;
        if (b.x < 0 || b.y < 0 || b.x > 800 || b.y > 600) {
            it = bullets.erase(it); // Remove the bullet outside the screen
        } 
        else {
            ++it;
        }
    }
}

void Boy::addBullet(float mouseX, float mouseY) {
    if (bullets.size() < maxBullets) {
        float bulletSpeed = 0.5f;
        bullets.push_back(Bullet(x, y, mouseX, mouseY, bulletSpeed));
        bullets.back().draw();
        bullets.back().update();
    }

}