#include <iostream>
#include <GL/glut.h>
#include <cmath>
using namespace std;

#define w 640
#define h 480

// Defining matrices for a square (4 vertices)
const int N = 4;
float A[N][3] = {
    {10, 10, 1},    // Bottom-left
    {100, 10, 1},   // Bottom-right
    {100, 100, 1},  // Top-right
    {10, 100, 1}    // Top-left
};
float B[3][3]; // Transformation matrix remains 3x3 for 2D homogeneous transformations
float C[N][3]; // Result matrix for transformed vertices
float tx, ty, sx, sy, t;

// Initialize OpenGL settings
void myInit() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glColor3f(0.0,0.0,0.0);
    glPointSize(4.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w/2, w/2, -h/2, h/2);
}

// Initialize a 3x3 matrix to identity
void matrixInit(float a[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

// Clear a matrix to zero (Nx3 for vertices, 3x3 for transformation)
void matrixClear(float a[][3], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 3; j++) {
            a[i][j] = 0.0f;
        }
    }
}

// Function to multiply matrices (Nx3 * 3x3 = Nx3)
void multiply(float a[][3], float b[][3], float c[][3]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                c[i][j] += a[i][k] * b[j][k];
            }
        }
    }
}

// Draw X and Y axes
void drawAxes() {
    glColor3f(0.5f, 0.5f, 0.5f); // Gray color for axes
    glBegin(GL_LINES);
    // X-axis
    glVertex2i(-w/2, 0);
    glVertex2i(w/2, 0);
    // Y-axis
    glVertex2i(0, -h/2);
    glVertex2i(0, h/2);
    glEnd();
}

// Plot the figure with object matrix a
void plotFigure(float a[][3], bool isTransformed) {
    glColor3f(0.0f, 0.0f, isTransformed ? 1.0f : 0.0f); // Blue for transformed, green for original
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < N; i++) {
        glVertex2i(a[i][0], a[i][1]);
    }
    glEnd();
}

// Translation transformation
void translate() {
    cout << "Enter translation tx and ty: ";
    cin >> tx >> ty;

    matrixInit(B);
    B[0][2] = tx;
    B[1][2] = ty;

    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    plotFigure(A, false); // Original square in green
    matrixClear(C, N);
    multiply(A, B, C);
    plotFigure(C, true); // Transformed square in blue
    glFlush();
}

// Scaling transformation
void scale() {
    cout << "Enter scaling factors sx and sy: ";
    cin >> sx >> sy;

    matrixInit(B);
    B[0][0] = sx;
    B[1][1] = sy;

    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    plotFigure(A, false); // Original square in green
    matrixClear(C, N);
    multiply(A, B, C);
    plotFigure(C, true); // Transformed square in blue
    glFlush();
}

// Rotation transformation
void rotate() {
    cout << "Enter rotation angle in degrees: ";
    cin >> t;

    t = (3.14159f * t) / 180.0f; // Convert to radians
    matrixInit(B);
    B[0][0] = cos(t);
    B[0][1] = -sin(t);
    B[1][0] = sin(t);
    B[1][1] = cos(t);

    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    plotFigure(A, false); // Original square in green
    matrixClear(C, N);
    multiply(A, B, C);
    plotFigure(C, true); // Transformed square in blue
    glFlush();
}

// Shear transformation
void shear() {
    cout << "Enter shear factors shx (along x) and shy (along y): ";
    float shx, shy;
    cin >> shx >> shy;

    matrixInit(B);
    B[0][1] = shx; // Shear along x
    B[1][0] = shy; // Shear along y

    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    plotFigure(A, false); // Original square in green
    matrixClear(C, N);
    multiply(A, B, C);
    plotFigure(C, true); // Transformed square in blue
    glFlush();
}

// Reflection transformation
void reflect() {
    cout << "Enter reflection type (1: X-axis, 2: Y-axis, 3: Origin): ";
    int type;
    cin >> type;

    matrixInit(B);
    if (type == 1) { // Reflect across X-axis
        B[1][1] = -1;
    } else if (type == 2) { // Reflect across Y-axis
        B[0][0] = -1;
    } else if (type == 3) { // Reflect across origin
        B[0][0] = -1;
        B[1][1] = -1;
    } else {
        cout << "Invalid reflection type. Using X-axis reflection." << endl;
        B[1][1] = -1;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    plotFigure(A, false); // Original square in green
    matrixClear(C, N);
    multiply(A, B, C);
    plotFigure(C, true); // Transformed square in blue
    glFlush();
}

// Display callback
void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    matrixInit(B);
    matrixClear(C, N);
    plotFigure(A, false);
    glFlush();
}

// Keyboard callback to exit on 'Esc'
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { // ASCII code for Esc
        exit(0);
    }
}

// Menu handler
void handleMenu(int option) {
    switch (option) {
        case 1: translate(); break;
        case 2: scale(); break;
        case 3: rotate(); break;
        case 4: rotate(); break; // Placeholder for rotate about point
        case 5: shear(); break;
        case 6: reflect(); break;
        default: cout << "Invalid Option" << endl;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(100, 150);

    // Create window and check for errors
    glutCreateWindow("Square Transformations");
    if (!glutGetWindow()) {
        cerr << "Error: Failed to create GLUT window" << endl;
        return 1;
    }

    myInit();
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(keyboard);

    // Menu setup
    glutCreateMenu(handleMenu);
    glutAddMenuEntry("Translate", 1);
    glutAddMenuEntry("Scale", 2);
    glutAddMenuEntry("Rotate", 3);
    glutAddMenuEntry("Rotate about point", 4);
    glutAddMenuEntry("Shear", 5);
    glutAddMenuEntry("Reflection", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    try {
        glutMainLoop();
    } catch (const std::exception& e) {
        cerr << "Error in GLUT main loop: " << e.what() << endl;
        return 1;
    }

   return 0;
}