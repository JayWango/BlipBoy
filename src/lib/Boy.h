#ifndef BOY_H 
#define BOY_H

#include <vector>
#include <GLUT/glut.h>

#include "Bullet.h"


class Boy {
public:
    float x, y;
    float maxhealth = 100.0;
    const float size = 0.2f;
    const int maxBullets = 5; 
    GLdouble minX, maxX, minY, maxY;
    std::vector<Bullet> bullets; 
    bool isActive;

    Boy(float startX, float startY);
    void draw() const;
    void calcBounds(GLdouble l, GLdouble r, GLdouble b, GLdouble t);
    void move(float dx, float dy);

    void addBullet(float x, float y);
    void updateBullets();
    void drawHealthBar(float x, float y, float healthPercent);
    void decreaseHealth(float amount);

    void deactivate() { isActive = false; }
    void activate() { isActive = true; }
  
};

#endif