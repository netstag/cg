#include<iostream>
using namespace std;
#include<GL/glut.h>

void myinit(){
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glMatrixMode(GL_PROJECTIONS);
    glLoadIdentity();
    glPointSize(4.0);
    gluOrtho2D(0.0, 640 , 0.0, 480);
}
void BresenhamsLine(int x1 , int y1 , int x2 , int y2){
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}


int mx ,  my , choice = 0;
float interiorColor[3] = {1,1,1};
float boundaryColor[3] = {0,0,0};
float fillColor[3] = {1,0,0};//red
float fillColor2[3] ={0,1,0};//green
float readPixel[3];

void getPixel(int x , int y  , int * color){
    glReadPixels(x, y , 1,1,GL_RGB , GL_FLOAT ,color);
}

void setPixel(int x , int y){
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
    glFlush();
}

void foodFill(int x , int y){

}




void Display(){

}

int main(int v , char** c){
    glutInit(&v , c);
    glutCreateWindow("Polygon filling");
    glutInitWindowSize(500,500);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutDisplayFunc(Display);
    myinit();
    glutMainLoop();
    return 0;
}
