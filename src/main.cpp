#include <GLUT/glut.h>

void display() {
    // Your rendering code goes here
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Use GLUT_DOUBLE for double buffering

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 600);

    glutCreateWindow("BlipBoy");

    glutDisplayFunc(display); // Set the display callback function

    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}