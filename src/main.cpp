#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <chrono>
#include <unordered_set>

#include "lib/Boy.h"
#include "lib/Bullet.h"
#include "lib/Enemy.h"


#define SCREEN_WIDTH = 800;
#define SCREEN_HEIGHT = 600;

int refreshMillis = 30;      // Refresh period in milliseconds

// instantiate a blipboy with (x, y)
Boy BlipBoy(0.0f, 0.0f);
std::unordered_set<char> pressedKeys;

// instatiate enemy (size, x, y, xMax, xMin, yMax, yMin, speedX, speedY)
Enemy enemy1(0.1, 10, 0, 0.02, 0.007);
Enemy enemy2(0.1, -10, 0, 0.04, 0.01);
Enemy enemy3(0.1, 0, 10, 0.03, -0.007);

// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;


void mouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      BlipBoy.addBullet(x, y);
   }
}

void initGL() {
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

void display() {
   // Your rendering code goes here
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
   glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
   glLoadIdentity();              // Reset model-view matrix

   BlipBoy.draw();
   BlipBoy.updateBullets();

   enemy1.drawEnemy(1.0f, 1.0f, 0.0f);
   enemy2.drawEnemy(1.0f, 0.0f, 0.0f);
   enemy3.drawEnemy(0.0f, 1.0f, 0.0f);
 
   glutSwapBuffers(); // Render now

   // Animation Control - compute the location for the next refresh
   enemy1.move();
   enemy2.move();
   enemy3.move();
};

void reshape(GLsizei width, GLsizei height) {
   // Compute aspect ratio of the new window
   if (height == 0) height = 1; // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
   // Set up the projection matrix
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix

   if (width >= height) {
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

   BlipBoy.calcBounds(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
   enemy1.calcBounds(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
   enemy2.calcBounds(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
   enemy3.calcBounds(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);

   glMatrixMode(GL_MODELVIEW);
}


void Timer(int value) {
   const float boySpeed = 0.03f;

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
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Use GLUT_DOUBLE for double buffering

   glutInitWindowPosition(200, 100);
   glutInitWindowSize(800, 600);
   glutCreateWindow("BlipBoy");

   glutDisplayFunc(display); // Set the display callback function
   glutReshapeFunc(reshape); //handles window re-sizing
   glutKeyboardFunc(handleKeyPress);
   glutKeyboardUpFunc(handleKeyRelease);
   glutMouseFunc(mouse);

   glutTimerFunc(0, Timer, 0);     // First timer call immediately

   initGL();
   glutMainLoop(); // Enter the GLUT event processing loop

   return 0;
}