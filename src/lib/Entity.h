#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <GLUT/glut.h>

class Entity {
public:
    int hp;
    float speed;
    float radius;
    float x, y;
    std::vector<float> vertices;

    virtual ~Entity() = default;

    virtual void initialize() = 0;
    virtual void draw() = 0;
    virtual int getHP() const = 0;


};

class Boy : public Entity {
    // GLuint VAO, VBO;

public:
    Boy();
    Boy(float startX, float startY, float startRadius, int startHP, float startSpeed);

    void initialize() override;
    void draw() override;
    int getHP() const override;

    void move(float dx, float dy);
    void takeDamage(int damage);

};

class Enemy : public Entity {

};


#endif