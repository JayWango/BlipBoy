#ifndef BOY_H 
#define BOY_H

#include "Bullet.h"

#include <vector>

class Boy {
public:
    float x, y;
    float size;
    std::vector<Bullet> bullets; // Bullets associated with the boy
    const int maxBullets = 5; // Maximum number of bullets

    Boy(float startX, float startY, float startSize);
    void draw() const;
    void move(float dx, float dy);

    void addBullet(float x, float y);
    void updateBullets();
};


#endif