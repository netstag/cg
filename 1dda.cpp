#include <iostream>
#include <GL/glut.h>
#include<cmath>

int Sign(float x ){
    if(x>0){
        return 1;
    }else if(x<0){
        return -1;
    }
    else{
        return 0;
    }
}

void DDA(int x1 , int y1 , int x2 , int y2){
    int length;
    float dx = x2 - x1;
    float dy = y2 - y1;

    if(abs(dx)>= abs(dy)){
        length = abs(dx);//make sure length is always positive
    }else{
        length = abs(dy);
    }

    float Xinc = dx/length;
    float Yinc = dy/length;

    float x = x1 + 0.5*Sign(Xinc);
    float y = y1 + 0.5*Sign(Yinc);
    
    

    glBegin(GL_POINTS);
    for(int i =  0 ; i <= length ; i++ ){
        
        glVertex2i(floor(x) , floor(y));
        
        
        x = x + Xinc;
        y = y + Yinc;
    }
    glEnd();
   



}

void Draw(){
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0, 0 , 0);
   DDA(50 , 50 , -50 , -50);
   glFlush();

}

void myInit(){
   glClearColor(1,1,1,1);
   glColor3f(0, 0 , 0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glPointSize(4.0);
   gluOrtho2D(-100, 100, -100, 100);
}

int  main(int c , char** v){
    
    glutInit(&c , v);
    glutInitWindowSize(500,500);
    glutCreateWindow("DDA");
    glutDisplayFunc(Draw);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    myInit();
    // glutInitWindowPosition(100, 100);
    glutMainLoop();
    return 0;

}