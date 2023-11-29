#include <GLUT/glut.h>

void display() {
    // Your rendering code goes here 
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glPointSize(10.0);

    glBegin(GL_TRIANGLES);

    glVertex2f(0, 5);
    glVertex2f(4, -3);
    glVertex2f(-4, -3);

    glEnd();

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Use GLUT_DOUBLE for double buffering

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 600);

    glutCreateWindow("BlipBoy");

    glutDisplayFunc(display); // Set the display callback function
    glutReshapeFunc(reshape);

    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}