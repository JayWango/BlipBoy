#ifndef BULLET_H 
#define BULLET_H

class Bullet {
public:
    float x, y, dirX, dirY;
    // float mouseX, mouseY;
    float bulletSpeed;
    bool isActive = false;

    Bullet(float startX, float startY, float dirX, float dirY, float speed);
    void draw() const;
    void update();
};

#endif