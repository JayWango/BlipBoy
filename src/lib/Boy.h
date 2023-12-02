#ifndef BOY_H 
#define BOY_H

#include <vector>
#include <GL/glut.h>

#include "Bullet.h"


class Boy {
public:
    float x, y;
    const float size = 0.2f;
    const int maxBullets = 5; 
    GLdouble minX, maxX, minY, maxY;
    std::vector<Bullet> bullets; 

    Boy(float startX, float startY);
    void draw() const;
    void calcBounds(GLdouble l, GLdouble r, GLdouble b, GLdouble t);
    void move(float dx, float dy);

    void addBullet(float x, float y);
    void updateBullets();
};

#endif