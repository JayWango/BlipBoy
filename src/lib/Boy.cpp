#include "Boy.h"

#include <cmath>


Boy::Boy(float startX, float startY)
    : x(startX), y(startY) {}

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
    
    glBegin(GL_POINTS);
    for (auto& bullet : bullets) {
        bullet.draw();
    }
    glEnd();
}

void Boy::move(float dx, float dy) {
    // Calculate the new position
    float newX = x + dx;
    float newY = y + dy;

    if (newX >= minX && newX <= maxX && newY >= minY && newY <= maxY) {
        x = newX;
        y = newY;
    }

}

void Boy::calcBounds(GLdouble l, GLdouble r, GLdouble b, GLdouble t) {
    minX = l + (size / 2);
    maxX = r - (size / 2);
    minY = b + (size / 2);
    maxY = t - (size / 2);
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
        bullets.back().update();
    }
}