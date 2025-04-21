#include<iostream>
using namespace std;
#include<GL/glut.h>
#include<math.h>
#define w 1080
#define h 720

void axes(){
    for(int i=-w ; i < w ; i++){
        glBegin(GL_POINTS);
            glVertex2i(i,0);
            glVertex2i(0,i);
        glEnd();
    }
}

void Bresenham(int x1 , int y1 , int x2 , int y2){
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void Translate(int x1 , int y1 , int x2 , int y2 , int tx , int ty){
    int p1 , q1 , p2 , q2;
    p1 = x1+tx;
    q1 = y1+ty;
    p2 = x2 + tx;
    q2 = y2 + ty;
    Bresenham(p1 , q1 , p2 , q2);
}

void Scaling(int x1 , int y1 , int x2 , int y2,float sx , float sy){
    int p1,q1,p2,q2;
    p1 = x1 * sx;
    q1 = y1 * sy;
    p2 = x2 * sx;
    q2 = y2 * sy;
    Bresenham(p1,q1,p2,q2);
}

void Rotation(int x1 , int y1 , int x2 , int y2 , int angle ){
    int p1 , q1 , p2 , q2;
    float angler;
    angler = (3.14*angle)/180;
    p1 = x1*cos(angler) + y1*sin(angler);
    q1 = x1*sin(-angler) + y1*cos(angler);
    p2 = x2*cos(angler) + y2*sin(angler);
    q2 = x2*sin(-angler) + y2*cos(angler);
    Bresenham(p1,q1,p2,q2);
}

void RotationPt(int x1, int y1, int x2, int y2, int X, int Y, int angle) {
    // Step 1: Translate line so that (X,Y) becomes the origin
    int tx1, ty1, tx2, ty2;
    tx1 = x1 - X;
    ty1 = y1 - Y;
    tx2 = x2 - X;
    ty2 = y2 - Y;
    
    // Step 2: Rotate around origin
    float angler = (3.14 * angle) / 180;
    int rx1, ry1, rx2, ry2;
    
    rx1 = tx1 * cos(angler) - ty1 * sin(angler);
    ry1 = tx1 * sin(angler) + ty1 * cos(angler);
    rx2 = tx2 * cos(angler) - ty2 * sin(angler);
    ry2 = tx2 * sin(angler) + ty2 * cos(angler);
    
    // Step 3: Translate back so that origin moves back to (X,Y)
    int fx1, fy1, fx2, fy2;
    fx1 = rx1 + X;
    fy1 = ry1 + Y;
    fx2 = rx2 + X;
    fy2 = ry2 + Y;
    
    // Draw the rotated line
    Bresenham(fx1, fy1, fx2, fy2);
}
void ScalingPt(int x1, int y1, int x2, int y2, int X, int Y, float sx, float sy) {
    // Step 1: Translate line so that (X,Y) becomes the origin
    int tx1, ty1, tx2, ty2;
    tx1 = x1 - X;
    ty1 = y1 - Y;
    tx2 = x2 - X;
    ty2 = y2 - Y;
    
    // Step 2: Apply scaling
    int sx1, sy1, sx2, sy2;
    sx1 = tx1 * sx;
    sy1 = ty1 * sy;
    sx2 = tx2 * sx;
    sy2 = ty2 * sy;
    
    // Step 3: Translate back so that origin moves back to (X,Y)
    int fx1, fy1, fx2, fy2;
    fx1 = sx1 + X;
    fy1 = sy1 + Y;
    fx2 = sx2 + X;
    fy2 = sy2 + Y;
    
    // Draw the scaled line
    Bresenham(fx1, fy1, fx2, fy2);
}

void Reflection(int x1 , int y1 , int x2 , int y2 ,int X , int Y , int wrt){
    int tx1 , ty1 , tx2 , ty2;
    tx1 = x1 - X ;
    ty1 = y1 - Y;
    tx2 = x2 - X;
    ty2 = y2 - Y;
    
    int p1 , q1 , p2 , q2;
    int fx1, fy1, fx2, fy2;

    if(wrt == 1){ // x-axis
        p1 = tx1;
        q1 = -ty1;
        p2 = tx2;
        q2 = -ty2;
    }
    else if(wrt == 2){ // y-axis
        p1 = -tx1;
        q1 = ty1;
        p2 = -tx2;
        q2 = ty2;
    } else {
        return; // Invalid option
    }

    fx1 = p1 + X;
    fy1 = q1 + Y;
    fx2 = p2 + X;
    fy2 = q2 + Y;

    Bresenham(fx1, fy1, fx2, fy2);
}


void Shear(int x1, int y1, int x2, int y2, float shx, float shy) {
    int sx1, sy1, sx2, sy2;

    // Apply shearing
    sx1 = x1 + shx * y1;
    sy1 = y1 + shy * x1;
    sx2 = x2 + shx * y2;
    sy2 = y2 + shy * x2;

    // Draw the sheared line
    Bresenham(sx1, sy1, sx2, sy2);
}


void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    axes();
    glLineWidth(5.0); 
    Bresenham(-100,100,100,100);
    Bresenham(100,100,100,-100);
    Bresenham(100,-100,-100,-100);
    Bresenham(-100,-100,-100,100);
    glFlush();
}

void menu(int item){
    if(item == 1 ){
        int tx ,ty ;
        cout<<"Tx:"; cin>>tx;
        cout<<"Ty:"; cin>>ty;
        Translate(-100,100,100,100,tx , ty);
        Translate(100,100,100,-100,tx , ty);
        Translate(100,-100,-100,-100,tx , ty);
        Translate(-100,-100,-100,100,tx , ty);
    }
    if(item == 2){
        int sx ,sy ;
        cout<<"Sx:"; cin>>sx;
        cout<<"Sy:"; cin>>sy;
        Scaling(-100,100,100,100,sx, sy);
        Scaling(100,100,100,-100,sx, sy);
        Scaling(100,-100,-100,-100,sx, sy);
        Scaling(-100,-100,-100,100,sx, sy);
    }
    if(item == 8){
        int angle;
        cout<<"Angle:"; cin>>angle;
        Rotation(-100,100,100,100,angle);
        Rotation(100,100,100,-100,angle);
        Rotation(100,-100,-100,-100,angle);
        Rotation(-100,-100,-100,100,angle);
    }
    if(item == 3) {
        int X, Y, angle;
        cout << "Enter center of rotation (X Y): ";
        cin >> X >> Y;
        cout << "Enter rotation angle in degrees: ";
        cin >> angle;
        
        // Rotate each side of the square around (X,Y)
        RotationPt(-100, 100, 100, 100, X, Y, angle);  // Top edge
        RotationPt(100, 100, 100, -100, X, Y, angle);  // Right edge
        RotationPt(100, -100, -100, -100, X, Y, angle); // Bottom edge
        RotationPt(-100, -100, -100, 100, X, Y, angle); // Left edge
    }
    if(item == 4){
        int X, Y;
        float sx, sy;
        cout << "Enter fixed point for scaling (X Y): ";
        cin >> X >> Y;
        cout << "Enter scaling factors (sx sy): ";
        cin >> sx >> sy;
        
        // Scale each side of the square with respect to (X,Y)
        ScalingPt(-100, 100, 100, 100, X, Y, sx, sy);   // Top edge
        ScalingPt(100, 100, 100, -100, X, Y, sx, sy);   // Right edge
        ScalingPt(100, -100, -100, -100, X, Y, sx, sy); // Bottom edge
        ScalingPt(-100, -100, -100, 100, X, Y, sx, sy); // Left edge
    }
    if(item == 5){
        int wrt ,X , Y ;
        cout << "Enter fixed point for Reflection (X Y): ";
        cin >> X >> Y;
        cout<<endl;
        cout<<"Reflection wrt to x-axis[1] or y-axis[2]:"; cin>>wrt;
        cout<<endl;
        Reflection(-100,100,100,100,X,Y,wrt);
        Reflection(100,100,100,-100,X,Y,wrt);
        Reflection(100,-100,-100,-100,X,Y,wrt);
        Reflection(-100,-100,-100,100,X,Y,wrt);

    }
    if(item == 6){
        float shx, shy;
        cout << "Enter shearing factors (shx shy): ";
        cin >> shx >> shy;
    
        // Apply shearing to each side of the square
        Shear(-100, 100, 100, 100, shx, shy);    // Top edge
        Shear(100, 100, 100, -100, shx, shy);    // Right edge
        Shear(100, -100, -100, -100, shx, shy);  // Bottom edge
        Shear(-100, -100, -100, 100, shx, shy);  // Left edge
    }
    
    if(item == 7){
        exit(0);
    }
    glFlush();
}

void myinit(){
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPointSize(4.0);
    gluOrtho2D(-w/2,w/2,-h/2,h/2);
}

void menuInit(){
    glutCreateMenu(menu);
    glutAddMenuEntry("Translation",1);
    glutAddMenuEntry("Scaling" , 2);
    glutAddMenuEntry("Rotation",8);
    glutAddMenuEntry("Rotation Pt",3);
    glutAddMenuEntry("Scaling Pt",4);
    glutAddMenuEntry("Reflection",5);
    glutAddMenuEntry("Shear",6);
    glutAddMenuEntry("Exit",7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int v , char** c){
    glutInit(&v , c);
    glutCreateWindow("Transformation");
    glutInitWindowSize(w,h);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutDisplayFunc(Display);
    menuInit();
    myinit();
    glutMainLoop();
    return 0;
}
