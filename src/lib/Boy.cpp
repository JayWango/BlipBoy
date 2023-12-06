#include "Boy.h"

#include <cmath>


Boy::Boy(float startX, float startY)
: x(startX), y(startY), isActive(true) {}

void Boy::draw() const {
    if (!isActive) return;
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
        if (b.x <= minX -0.1f || b.y <= minY -0.1f || b.x >= maxX + 0.1f  || b.y >= maxY + 0.1f ) {
            it = bullets.erase(it); // Remove the bullet outside the screen
        } 
        else {
            ++it;
        }
    }
}

void Boy::addBullet(float dirX, float dirY) {
    if (bullets.size() < maxBullets) {
        // Normalize the direction vector
        float length = sqrt(dirX * dirX + dirY * dirY);
        if (length != 0) {
            dirX /= length;
            dirY /= length;
        }

        bullets.push_back(Bullet(x, y, dirX, dirY, 0.06f));
        bullets.back().update();
    }
}


void Boy::drawHealthBar(float x, float y, float healthPercent) {
    float barWidth = size * 1.75;
    float barHeight = 0.01f;
    float healthPercentage = static_cast<float>(maxhealth) / 100.0f;

    glPushMatrix();
    glTranslatef(x + 0.1f, y, 0.0f);

    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-barWidth / 2, barHeight);
        glVertex2f(-barWidth / 2, -barHeight);
        glVertex2f(barWidth / 2, -barHeight);
        glVertex2f(barWidth / 2, barHeight);
    glEnd();

    glColor3f(1.0 - healthPercent, healthPercent, 0.0);
    float healthBarWidth = barWidth * healthPercentage;
    glBegin(GL_QUADS);
        glVertex2f(-barWidth / 2, barHeight);
        glVertex2f(-barWidth / 2 + healthBarWidth, barHeight);
        glVertex2f(-barWidth / 2 + healthBarWidth, -barHeight);
        glVertex2f(-barWidth / 2, -barHeight);
    glEnd();

    glPopMatrix();






    // Set color for the background of the health bar (grey)
    // glColor3f(0.5, 0.5, 0.5);
    // glBegin(GL_QUADS);
    // glVertex2f(x, y);
    // glVertex2f(x + 0.1, y);
    // glVertex2f(x + 0.1, y - 0.025);
    // glVertex2f(x, y - 0.025);
    // glEnd();

    // // Set color for the actual health (green for full health, red for low)
    // glColor3f(1.0 - healthPercent, healthPercent, 0.0);
    //     float width = 0.25 * healthPercent;
    //     glBegin(GL_QUADS);
    //     glVertex2f(x, y);
    //     glVertex2f(x + width, y);
    //     glVertex2f(x + width, y - 0.025);
    //     glVertex2f(x, y - 0.025);
    // glEnd();
}

void Boy::decreaseHealth(float amount) {
    maxhealth = std::max(0.0f, maxhealth - amount);
}