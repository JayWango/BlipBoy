// #include "Entity.h"
// #include <cmath>

// Boy::Boy() {
//     x = 10;
//     y = 10;
//     radius = 5;
//     hp = 5;
//     speed = 1;
// }

// Boy::Boy(float x, float y, float radius, int hp, float speed) {
//     this->x = x;
//     this->y = y;
//     this->radius = radius;
//     this->hp = hp;
//     this->speed = speed;
// }

// int Boy::getHP() const {
//     return hp;
// }

// void Boy::initialize() {
//     const int segments = 100; // Number of segments for the circle

//     for (int i = 0; i <= segments; ++i) {
//         float angle = static_cast<float>(i) * (2 * 3.14159f) / static_cast<float>(segments);
//         vertices.push_back(radius * cosf(angle));
//         vertices.push_back(radius * sinf(angle));
//     }

//     // glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     // glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

//     // Vertex attribute setup
//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
// }

// void Boy::draw() {
//     // glBindVertexArray(VAO);
//     glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 2);
//     glBindVertexArray(0);
// }

// void Boy::move(float dx, float dy) {
//     x += dx * speed;
//     y += dy * speed;
// }

// void Boy::takeDamage(int damage) {
//     hp -= damage;
//     if (hp < 0) {
//         hp = 0; // Ensure HP doesn't go below zero
//     }
// }