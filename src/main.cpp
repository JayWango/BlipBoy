#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <chrono>
#include <unordered_set>

#include "lib/Boy.h"
#include "lib/Bullet.h"
#include "lib/Enemy.h"


Boy BlipBoy(0.0f, 0.0f, 2.0f);
std::unordered_set<char> pressedKeys;

int mouseX = 0;
int mouseY = 0;

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseX = x;
        mouseY = y;
        BlipBoy.setMousePosition(mouseX, mouseY);
        BlipBoy.shoot();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    BlipBoy.draw();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-10, 10, -10, 10, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

void Timer(int value) {
    const float boySpeed = 0.3f;

    if (pressedKeys.find('w') != pressedKeys.end()) {
        BlipBoy.move(0.0f, boySpeed);
    }
    if (pressedKeys.find('s') != pressedKeys.end()) {
        BlipBoy.move(0.0f, -boySpeed);
    }
    if (pressedKeys.find('a') != pressedKeys.end()) {
        BlipBoy.move(-boySpeed, 0.0f);
    }
    if (pressedKeys.find('d') != pressedKeys.end()) {
        BlipBoy.move(boySpeed, 0.0f);
    }
    glutPostRedisplay();
    glutTimerFunc(30, Timer, 0);
}

void handleKeyPress(unsigned char key, int x, int y) {
    pressedKeys.insert(key);
}

void handleKeyRelease(unsigned char key, int x, int y) {
    pressedKeys.erase(key);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("BlipBoy");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyRelease);
    glutMouseFunc(mouse);

    initGL();

    glutTimerFunc(0, Timer, 0);
    glutMainLoop();

    return 0;
}