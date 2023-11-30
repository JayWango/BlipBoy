#ifndef BOY_H 
#define BOY_H

#include "Bullet.h"

class Boy {
public:
    float x, y;
    float size;
    static const int maxBullets = 5;
    Bullet bullets[maxBullets];
    int mouseX, mouseY;

    Boy(float startX, float startY, float startSize);
    void draw() const;
    void move(float dx, float dy);
    void shoot();
    void setMousePosition(int x, int y);
};


#endif