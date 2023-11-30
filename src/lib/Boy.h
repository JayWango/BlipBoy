#ifndef BOY_H 
#define BOY_H

class Boy {
public:
    float x, y;
    float size;
    float speed;
    int hp;

    Boy(float startX, float startY, float startSize, float startSpeed);
    void draw() const;
    void move(float dx, float dy);
};

#endif