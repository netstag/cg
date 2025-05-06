#include<GL/glut.h>
#include<iostream>
using namespace std;
#include <cmath>

int points[4][2];
bool curvedrawn = false;

void drawPoints(float x1 , float y1){
    glColor3f(1,0,0);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(x1,y1);
    glEnd();

}

void drawLine(float x1 , float y1 , float x2 , float y2){
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}
void midPtSubDivision(float x1,float y1 ,float x2 ,float y2 ,
                      float x3 ,float y3 ,float x4 ,float y4 ){
            
        
        float xAB = (x1+x2)/2 , yAB = (y1+y2)/2;
        float xBC = (x2+x3)/2 , yBC = (y2+y3)/2;
        float xCD = (x3+x4)/2 , yCD = (y3+y4)/2;

        float xABC = (xAB+xBC)/2 ,yABC = (yAB+yBC)/2;
        float xBCD = (xBC+xCD)/2 ,yBCD = (yBC+yCD)/2;

        float xABCD = (xABC+xBCD)/2 , yABCD = (yABC+yBCD)/2;

        if((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)>4||
           (x3-x2)*(x3-x2) + (y3-y2)*(y3-y2)>4||
           (x4-x3)*(x4-x3)+(y4-y3)*(y4-y3)>4 ){
            midPtSubDivision(x1, y1 , xAB , yAB , xABC , yABC ,xABCD , yABCD );
            midPtSubDivision(xABCD , yABCD ,xBCD , yBCD ,xCD, yCD , x4 , y4);
        }else{
            drawLine(x1 , y1 ,xABCD , yABCD );
            drawLine(xABCD , yABCD , x4 , y4);
        }

}




void myInit(){
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);


}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i = 0 ; i < 4 ; i++){
        drawPoints(points[i][0],points[i][1]);
    }
    drawLine(points[0][0],points[0][1] , points[1][0],points[1][1]);
    drawLine(points[1][0],points[1][1] , points[2][0],points[2][1]);
    drawLine(points[2][0],points[2][1] , points[3][0],points[3][1]);

    midPtSubDivision(points[0][0], points[0][1],
        points[1][0], points[1][1],
        points[2][0], points[2][1],
        points[3][0], points[3][1]);

        glFlush();


}


int main(int v , char ** c){
     
    cout<<"Enter the Points"<<endl;
    for(int i = 0 ; i < 4 ; i++){
        cout<<"Enter : X"<<(i+1)<<"Y"<<(i+1)<<endl;
        cin>>points[i][0]>>points[i][1];
    }
    curvedrawn = true;

    glutInit(&v , c);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bezier Curve");
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutDisplayFunc(Display);
    myInit();
    glutMainLoop();
    return 0;
}