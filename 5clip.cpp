#include <GL/glut.h>
#include <iostream>
using namespace std;

#define MAX 20

// Window dimensions
int xmin = -100, ymin = -100, xmax = 100, ymax = 100;

// Original polygon points
int poly[MAX][2] = {
    {-150, -50},
    {0, 150},
    {150, 50},
    {100, -100},
    {0, -150}
};
int n = 5; // number of polygon vertices

// Clipped polygon points
int clipped[MAX][2];
int clipped_n = 0;

// Add this global variable to track clipping state
bool isClipped = false;

// Function to draw the polygon
void drawPolygon(int p[][2], int n, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++)
        glVertex2i(p[i][0], p[i][1]);
    glEnd();
    glFlush();
}

// Draw clipping window (rectangle)
void drawClippingWindow() {
    glColor3f(0, 0, 1); // Blue window
    glBegin(GL_LINE_LOOP);
        glVertex2i(xmin, ymin);
        glVertex2i(xmin, ymax);
        glVertex2i(xmax, ymax);
        glVertex2i(xmax, ymin);
    glEnd();
    glFlush();
}

// Helper function to check inside
bool inside(int x, int y, int edge) {
    if (edge == 0) return x >= xmin; // Left
    if (edge == 1) return x <= xmax; // Right
    if (edge == 2) return y >= ymin; // Bottom
    if (edge == 3) return y <= ymax; // Top
    return false;
}

// Find intersection point with a boundary
void intersect(int x1, int y1, int x2, int y2, int edge, int& x, int& y) {
    float m = (x2 - x1 != 0) ? float(y2 - y1) / (x2 - x1) : 1e9;
    if (edge == 0) { // Left
        x = xmin;
        y = y1 + (xmin - x1) * m;
    } else if (edge == 1) { // Right
        x = xmax;
        y = y1 + (xmax - x1) * m;
    } else if (edge == 2) { // Bottom
        y = ymin;
        x = x1 + (1.0 / m) * (ymin - y1);
    } else if (edge == 3) { // Top
        y = ymax;
        x = x1 + (1.0 / m) * (ymax - y1);
    }
}

// Sutherland-Hodgman clipping
void suthHodgClip() {
    int input[MAX][2], output[MAX][2];
    int in_n = n, out_n;

    for (int i = 0; i < n; i++) {
        input[i][0] = poly[i][0];
        input[i][1] = poly[i][1];
    }

    for (int edge = 0; edge < 4; edge++) {
        out_n = 0;
        for (int i = 0; i < in_n; i++) {
            int x1 = input[i][0];
            int y1 = input[i][1];
            int x2 = input[(i + 1) % in_n][0];
            int y2 = input[(i + 1) % in_n][1];

            bool in1 = inside(x1, y1, edge);
            bool in2 = inside(x2, y2, edge);

            if (in1 && in2) {
                // both inside
                output[out_n][0] = x2;
                output[out_n][1] = y2;
                out_n++;
            } else if (in1 && !in2) {
                // inside to outside
                int x, y;
                intersect(x1, y1, x2, y2, edge, x, y);
                output[out_n][0] = x;
                output[out_n][1] = y;
                out_n++;
            } else if (!in1 && in2) {
                // outside to inside
                int x, y;
                intersect(x1, y1, x2, y2, edge, x, y);
                output[out_n][0] = x;
                output[out_n][1] = y;
                out_n++;
                output[out_n][0] = x2;
                output[out_n][1] = y2;
                out_n++;
            }
        }

        in_n = out_n;
        for (int i = 0; i < out_n; i++) {
            input[i][0] = output[i][0];
            input[i][1] = output[i][1];
        }
    }

    // Store final result
    clipped_n = in_n;
    for (int i = 0; i < clipped_n; i++) {
        clipped[i][0] = input[i][0];
        clipped[i][1] = input[i][1];
    }
}

// Modify the display function to conditionally draw the appropriate polygon
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawClippingWindow();
    
    if (isClipped) {
        // Draw only the clipped polygon (green)
        drawPolygon(clipped, clipped_n, 0, 1, 0);
    } else {
        // Draw the original polygon (red)
        drawPolygon(poly, n, 1, 0, 0);
    }
    
    glFlush();
}

// Modify the menu function to update the clipping state
void menu(int id) {
    if (id == 1) {
        // Perform clipping and set flag
        suthHodgClip();
        isClipped = true;
    } else if (id == 2) {
        // Reset to show original polygon
        isClipped = false;
    } else if (id == 3) {
        // Exit
        exit(0);
    }
    glutPostRedisplay(); // Refresh the display
}

// Initialization
void init() {
    glClearColor(1, 1, 1, 1); // White background
    glColor3f(1, 0, 0);       // Drawing color
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
}

// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping");

    init();
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Clip Polygon", 1);
    glutAddMenuEntry("Reset Polygon", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
