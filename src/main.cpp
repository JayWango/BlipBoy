#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

#include "lib/Enemy.h"

GLfloat enemyXMax, enemyXMin, enemyYMax, enemyYMin; // enemy's center (x, y) bounds
int refreshMillis = 30;      // Refresh period in milliseconds

Enemy enemy1(0.1, 0, 0, 1.2, -1.2, 0.9, -0.9, 0.02, 0.007);
Enemy enemy2(0.1, 0.5, 0.5, 0.1, -0.1, 0.1, -0.1, 0.02, 0.007);

// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

/* Initialize OpenGL Graphics */
void initGL() {
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

void display() {

    // Your rendering code goes here
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
    glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
    glLoadIdentity();              // Reset model-view matrix

    enemy1.drawEnemy();
    enemy2.drawEnemy();
 
    glutSwapBuffers(); // Render now

    // Animation Control - compute the location for the next refresh
    enemy1.move();
    //if i comment out enemy2.move(), then both enemy 1 and 2 are still somehow moving together? if i dont comment out i get weird behavior
    enemy2.move();
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
   
    enemyXMin = clipAreaXLeft + enemy1.enemySize;
    enemyXMax = clipAreaXRight - enemy1.enemySize;
    enemyYMin = clipAreaYBottom + enemy1.enemySize;
    enemyYMax = clipAreaYTop - enemy1.enemySize;
}

/* Called back when timer expired */
void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // next Timer call milliseconds later
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Use GLUT_DOUBLE for double buffering

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 600);

    glutCreateWindow("BlipBoy");

    glutDisplayFunc(display); // Set the display callback function
    glutReshapeFunc(reshape); //handles window re-sizing

    glutTimerFunc(0, Timer, 0);     // First timer call immediately

    initGL();
    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}