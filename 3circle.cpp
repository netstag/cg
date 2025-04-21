#include<iostream>
using namespace std;
#include<GL/glut.h>

void circle(int r , int h , int k){
    int x = 0 ;
    int y = r;
    int d = 3-2*r;
    
    glBegin(GL_POINTS);
    while(x<=y){
        if(d<=0){
            d = d + 4*x +6;
            x++;
        }else{
            d = d+4*(x-y)+10;
            x++;
            y--;
        }
        glVertex2i(x+h,y+k);
        glVertex2i(-x+h,y+k);
        glVertex2i(x+h,-y+k);
        glVertex2i(-x+h,-y+k);
        glVertex2i(y+h,x+k);
        glVertex2i(-y+h,x+k);
        glVertex2i(y+h,-x+k);
        glVertex2i(-y+h,-x+k);
    }
    glEnd();
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    circle(180,0,0);
    circle(180,390,0);
    circle(180,390,0);
    circle(180,780,0);
    circle(180,180,-180);
    circle(180,570,-180);


    glFlush();

}

void myInit(){
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPointSize(4.0);
    gluOrtho2D(-1000,1000,-1000,1000);
}

int main(int v , char** c){
    glutInit(&v , c);
    glutInitWindowSize(500,500);
    glutCreateWindow("Circle Drawing");
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    myInit();
    glutDisplayFunc(Display);

    glutMainLoop();


}