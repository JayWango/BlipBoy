#ifndef BULLET_H 
#define BULLET_H

class Bullet {
public:
    float x, y;
    float mouseX, mouseY;
    float speed;

    Bullet(float startX, float startY, float mouseX, float mouseY,  float bulletSpeed);

    void draw() const;
    void update();
};

#endif