#include<iostream>
using namespace std;
#include<GL/glut.h>
# define H 720
# define W 1080
void axes(){
    glBegin(GL_POINTS);
    for(int i= -W ; i < W ; i++){
        glVertex2i(i,0);
        glVertex2i(0, i);

    } 
    glEnd();
    glFlush();
}

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

void olympicRing(){
    circle(50,90,180);
    circle(50,210,180);
    circle(50,330,180);
    circle(50 , 150 , 130);
    circle(50, 270, 130);  

}
void concentricCircles(int R , int X , int Y , int n){
      
    for(int i = 0 ; i < n ; i++){
        circle(R+ i*20 , X  , Y );
    }

}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    axes();
   
   

    glFlush();

}

void menu(int opt){
  if(opt == 1){
    exit(0);
  }
  else if(opt == 2){
    olympicRing();
  }
  else if(opt == 3){
    concentricCircles(50 , 0 ,0 , 5);
  }
  else{
    return;
  }
}


void myInit(){
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPointSize(4.0);
    gluOrtho2D(-W/2,W/2,-H/2,H/2);
}

int main(int v , char** c){
    glutInit(&v , c);
    glutInitWindowSize(W,H);
    glutCreateWindow("Circle Drawing");
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    myInit();
    glutDisplayFunc(Display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Ring" , 2);
    glutAddMenuEntry("Concentric" , 3);
    glutAddMenuEntry("Exit" , 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();


}