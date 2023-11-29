#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

#include "lib/Enemy.h"

GLfloat enemySize = 0.1f;      // this defines the "size" of the square  
GLfloat enemyX = 0.0f;         // enemy's center (x, y) position
GLfloat enemyY = 0.0f;
GLfloat enemyXMax, enemyXMin, enemyYMax, enemyYMin; // enemy's center (x, y) bounds
GLfloat xSpeed = 0.02f;      // enemy's speed in x and y directions
GLfloat ySpeed = 0.007f;
int refreshMillis = 30;      // Refresh period in milliseconds

// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

/* Initialize OpenGL Graphics */
void initGL() {
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

void display() {
    Enemy enemy1(enemySize, enemyX, enemyY, enemyXMax, enemyXMin, enemyYMax, enemyYMin, xSpeed, ySpeed);
    Enemy enemy2(enemySize, 0.5, 0.5, enemyXMax, enemyXMin, enemyYMax, enemyYMin, xSpeed, ySpeed);

    // Your rendering code goes here
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
    glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
    glLoadIdentity();              // Reset model-view matrix

    enemy1.drawEnemy();
    enemy2.drawEnemy();
 
    glutSwapBuffers(); // Render now

    // Animation Control - compute the location for the next refresh
    enemyX += xSpeed;
    enemyY += ySpeed;

   // Check if the enemy exceeds the edges
   if (enemyX > enemyXMax) {
      enemyX = enemyXMax;
      xSpeed = -xSpeed;
   } 
   else if (enemyX < enemyXMin) {
      enemyX = enemyXMin;
      xSpeed = -xSpeed;
   }

   if (enemyY > enemyYMax) {
      enemyY = enemyYMax;
      ySpeed = -ySpeed;
   } 
   else if (enemyY < enemyYMin) {
      enemyY = enemyYMin;
      ySpeed = -ySpeed;
   }
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
   
    enemyXMin = clipAreaXLeft + enemySize;
    enemyXMax = clipAreaXRight - enemySize;
    enemyYMin = clipAreaYBottom + enemySize;
    enemyYMax = clipAreaYTop - enemySize;
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