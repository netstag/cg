#include<GL/glut.h>
#include<iostream>
using namespace std;
#include<cmath>

int iterations=5;

void koch(float x1 ,float y1 , float x2 , float y2 , int iter){
    if(iter == 0){
        glBegin(GL_LINES);
        glVertex2f(x1 , y1);
        glVertex2f(x2 , y2);
        glEnd();
        return;
    }

    float dx = (x2-x1);
    float dy = (y2 - y1);

    float x3 = x1 + dx/3;
    float y3 = y1 + dy/3;

    float x5 = x1 + 2*(dx/3);
    float y5 = y1 + 2*(dy/3);
    
    float angle = M_PI/3;

    float x4 = x3+(cos(angle)*(x5-x3)-sin(angle)*(y5-y3));
    float y4 = y3+(sin(angle)*(x5-x3) + cos(angle)*(y5-y3));

    koch(x1 , y1 , x3 , y3 , iter - 1);
    koch(x3 , y3 , x4 , y4 , iter - 1);
    koch(x4 , y4 , x5 , y5 , iter - 1);
    koch(x5 , y5 , x2 , y2 , iter - 1);

    }


void Display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0,0,0);
  float x1 = 250, y1 = 100;
  float x2 = 100, y2 = 350;
  float x3 = 400, y3 = 350;
 
  koch(x1 , y1 , x2 , y2 , iterations);
  koch(x2 , y2 , x3 , y3, iterations);
  koch(x3 , y3 , x1 , y1, iterations);

  glFlush();

}

void myInit(){
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
}

int main(int v , char**c){
    glutInit(&v , c);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500 , 500);
    glutCreateWindow("Koch");
    glutDisplayFunc(Display);
    myInit();
    glutMainLoop();
    return 0;
}