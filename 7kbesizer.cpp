#include <iostream>
using namespace std;
#include<GL/glut.h>
#include<cmath>


int numpoints = 0;

void init(){
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
};


struct point{
    float x,y ;
};

point p0 , p1 ,p2 ,p3;


void besizer(point p0 , point p1 , point p2 , point p3){
    float dx = (p3.x - p0.x);
    float dy = (p3.y - p0.y);
    if(sqrt(dx*dx + dy*dy) < 0.5){
        glBegin(GL_LINES);
        glVertex2f(p0.x,p0.y);
        glVertex2f(p3.x,p3.y);
        glEnd();
        return;

    }

    point p01 = {(p0.x + p1.x)/2 , (p0.y + p1.y)/2};
    point p12 = {(p1.x + p2.x)/2 , (p1.y + p2.y)/2};
    point p23 = {(p2.x + p3.x)/2 , (p2.y + p3.y)/2};

    point p012 = {(p01.x + p12.x)/2 , (p01.y + p12.y)/2};
    point p123 = {(p12.x + p23.x)/2 , (p12.y + p23.y)/2};

    point p0123 = {(p012.x + p123.x)/2 , (p012.y + p123.y)/2};


    besizer(p0,p01,p012,p0123);//left half
    besizer(p0123,p123,p23,p3);//rigth half


}


void mouse (int button , int state , int x ,int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(numpoints == 0){
            p0 = {(float) x , (float) (500-y)};
        };
        if(numpoints == 1){
            p1= {(float) x , (float) (500-y)};
        };
        if(numpoints == 2){
            p2 = {(float) x, (float) (500-y)};
        };
        if(numpoints == 3){
            p3 = {(float) x , (float) (500 - y)};
        };

        if(numpoints < 4){
            numpoints ++;
            glutPostRedisplay();
        }

    }

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0);
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
    if(numpoints >=1) glVertex2f(p0.x,p0.y);
    if(numpoints >= 2) glVertex2f(p1.x , p1.y);
    if(numpoints >=3) glVertex2f(p2.x,p2.y);
    if(numpoints >= 4) glVertex2f(p3.x , p3.y);
    glEnd();


    if(numpoints >= 2){
        glColor3f(0,1,0);
        glBegin(GL_LINE_STRIP);
    if(numpoints >=1) glVertex2f(p0.x,p0.y);
    if(numpoints >= 2) glVertex2f(p1.x , p1.y);
    if(numpoints >=3) glVertex2f(p2.x,p2.y);
    if(numpoints >= 4) glVertex2f(p3.x , p3.y);
    glEnd();
    }

    if(numpoints == 4){
        glColor3f(0,0,1);
        besizer(p0,p1,p2,p3);
    }
    glutSwapBuffers();
}





int main(int argc, char**argv){
    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("abc");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
