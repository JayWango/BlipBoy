#ifndef BULLET_H 
#define BULLET_H

class Bullet {
public:
    float x, y;
    float speed;
    bool active;

    Bullet();
    Bullet(float startX, float startY, float startSpeed);
    void draw() const;
    void move(float dirX, float dirY);
    void activate(float startX, float startY);
};

#endif