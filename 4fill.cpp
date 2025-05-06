#include <iostream>
#include <GL/glut.h>
using namespace std;

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int mx, my, choice = 0;
float boundaryColor[3] = {0, 0, 0};
float interiorColor[3] = {1, 1, 1};
float fillColor[3] = {1, 0, 0};    // Red for flood fillx`
float fillColor2[3] = {0, 1, 0};   // Green for boundary fill
float readpixel[3];

void getpixel(int x, int y, float *color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

void setpixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void floodfill(int x, int y) {
    if (x < 0 || x >= 640 || y < 0 || y >= 480) {
        return;
    }
    getpixel(x, y, readpixel);
    if (readpixel[0] == interiorColor[0] && readpixel[1] == interiorColor[1] && readpixel[2] == interiorColor[2]) {
        glColor3fv(fillColor);
        setpixel(x, y);
        floodfill(x + 1, y);
        floodfill(x, y + 1);
        floodfill(x - 1, y);
        floodfill(x, y - 1);
    }
}

void boundaryfill(int x, int y) {
    if (x > 640 || x < 0 || y > 480 || y < 0) {
        return;
    }
    getpixel(x, y, readpixel);
    if (
        (readpixel[0] != boundaryColor[0] || readpixel[1] != boundaryColor[1] || readpixel[2] != boundaryColor[2]) &&
        (readpixel[0] != fillColor2[0] || readpixel[1] != fillColor2[1] || readpixel[2] != fillColor2[2])
    ) {
        glColor3fv(fillColor2);
        setpixel(x, y);
        boundaryfill(x + 1, y);
        boundaryfill(x, y + 1);
        boundaryfill(x, y - 1);
        boundaryfill(x - 1, y);
    }
}

void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mx = x;
        my = 480 - y;
        switch (choice) {
        case 1:
            floodfill(mx, my);
            break;
        case 2:
            boundaryfill(mx, my);
            break;
        }
    }
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'e':
        exit(0);
    }
}

void BresenhamLine(int x1, int y1, int x2, int y2) {
   glBegin(GL_LINE_LOOP);
   glVertex2i(x1 , y1);
   glVertex2i(x2 , y2);
   glEnd();
  glFlush();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw a hexagon polygon
    BresenhamLine(200, 300, 300, 300); // Bottom
    BresenhamLine(300, 300, 350, 200); // Bottom-right
    BresenhamLine(350, 200, 300, 100); // Top-right
    BresenhamLine(300, 100, 200, 100); // Top
    BresenhamLine(200, 100, 150, 200); // Top-left
    BresenhamLine(150, 200, 200, 300); // Bottom-left
    glFlush();
}

void menuOptions(int option) {
    switch (option) {
    case 1:
        choice = option;
        break;
    case 2:
        choice = option;
        break;
    case 3:
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Polygon Fill Assignment");
    glutDisplayFunc(display);
     glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    glutCreateMenu(menuOptions);
    glutAddMenuEntry("Flood Fill (Red)", 1);
    glutAddMenuEntry("Boundary Fill (Green)", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    myInit();
    glutMainLoop();
    return 0;
}