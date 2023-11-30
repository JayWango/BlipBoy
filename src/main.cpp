#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <chrono>
#include <unordered_set>


#include "lib/Boy.h"
#include "lib/Enemy.h"


Boy BlipBoy(0.0f, 0.0f, 0.05f, 0.1f);
std::unordered_set<char> pressedKeys;

int refreshMillis = 30;      // Refresh period in milliseconds
// instatiate enemy (size, x, y, xMax, xMin, yMax, yMin, speedX, speedY)
Enemy enemy1(0.1, 0, 0, 0.02, 0.007);
Enemy enemy2(0.1, 0, 0, 0.04, 0.01);
Enemy enemy3(0.1, 0, 0, 0.03, -0.007);

// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

// GLuint loadingscreen;
// void loadLoadingscreen(){
//     loadingscreen = loadImage("blipboy1.png");
// }

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
    glLoadIdentity();

    BlipBoy.draw();
    enemy1.drawEnemy(1.0f, 1.0f, 0.0f);
    enemy2.drawEnemy(1.0f, 0.0f, 0.0f);
    enemy3.drawEnemy(0.0f, 1.0f, 0.0f);
    glutSwapBuffers(); // Render now
}
void update(int value){
    // Animation Control - compute the location for the next refresh
    enemy1.move();
    enemy2.move();
    enemy3.move();

    glutPostRedisplay();
    glutTimerFunc(refreshMillis, update, 0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -1, 1);
    glMatrixMode(GL_MODELVIEW);


    // Compute aspect ratio of the new window
    if (h == 0) h = 1; // To prevent divide by 0
    GLfloat aspect = (GLfloat)w / (GLfloat)h;

    // Set the viewport to cover the new window
    glViewport(0, 0, w, h);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix

   if (w >= h) {
      clipAreaXLeft   = -1.0 * aspect;
      clipAreaXRight  = 1.0 * aspect;
      clipAreaYBottom = -1.0;
      clipAreaYTop    = 1.0;
   } 
   else {
      clipAreaXLeft   = -1.0;
      clipAreaXRight  = 1.0;
      clipAreaYBottom = -1.0 / aspect;
      clipAreaYTop    = 1.0 / aspect;
   }
   glOrtho(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop, -1.0, 1.0);
   
   enemy1.calcBounds(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
   enemy2.calcBounds(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
   enemy3.calcBounds(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

void Timer(int value) {
    if (pressedKeys.find('w') != pressedKeys.end()) {
        BlipBoy.move(0.0f, 1.0f);
    }
    if (pressedKeys.find('s') != pressedKeys.end()) {
        BlipBoy.move(0.0f, -1.0f);
    }
    if (pressedKeys.find('a') != pressedKeys.end()) {
        BlipBoy.move(-1.0f, 0.0f);
    }
    if (pressedKeys.find('d') != pressedKeys.end()) {
        BlipBoy.move(1.0f, 0.0f);
    }
    glutPostRedisplay();
    glutTimerFunc(refreshMillis, Timer, 0);
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
    glutInitWindowSize(800, 600);

    glutCreateWindow("Moving Quad Blip boy");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyRelease);

    initGL();

    glutTimerFunc(0, update, 0);
    glutTimerFunc(0, Timer, 1);

    glutMainLoop();

    return 0;
}