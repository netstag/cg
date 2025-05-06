#include<iostream>
using namespace std;
#include<GL/glut.h>
#include<cmath>
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

int sign(int x){
    if(x>0) return 1;
    else if(x<0)return -1;
    else return 0;
}

void Bresenhams(int x1 , int y1 , int x2 , int y2){
    int x = x1 ;
    int y = y1;

    int Dx = abs(x2-x1);
    int Dy = abs(y2-y1);

    int s1 = sign(x2-x1);
    int s2 = sign(y2-y1);

    bool interchange = false;

    if(Dy>Dx){
       swap(Dx , Dy);
       interchange = true;
    }

    int e = 2*Dy - Dx ;
    
    glBegin(GL_POINTS);
    for(int i = 0 ; i <= Dx ; i++){
       
        glVertex2i(x , y);

        while(e>=0){
            if(interchange){
                x = x + s1;
            }else{
                y = y + s2;
            }

            e =  e - 2*Dx;
        }

        if(interchange){
            y = y + s2;
        }else{
            x = x + s1;
        }

        e =  e + 2*Dy;
 }
 glEnd();
}

void BresenhamsDotted(int x1 , int y1 , int x2 , int y2){
    int x = x1 ;
    int y = y1;

    int Dx = abs(x2-x1);
    int Dy = abs(y2-y1);

    int s1 = sign(x2-x1);
    int s2 = sign(y2-y1);

    bool interchange = false;

    if(Dy>Dx){
       swap(Dx , Dy);
       interchange = true;
    }

    int e = 2*Dy - Dx ;
    
    glBegin(GL_POINTS);
    for(int i = 0 ; i <= Dx ; i++){
       
      if(i%8==0){
        glVertex2i(x , y);
      }

        while(e>=0){
            if(interchange){
                x = x + s1;
            }else{
                y = y + s2;
            }

            e =  e - 2*Dx;
        }

        if(interchange){
            y = y + s2;
        }else{
            x = x + s1;
        }

        e =  e + 2*Dy;
 }
 glEnd();
}

void BresenhamsDashed(int x1 , int y1 , int x2 , int y2){
    int x = x1 ;
    int y = y1;

    int Dx = abs(x2-x1);
    int Dy = abs(y2-y1);

    int s1 = sign(x2-x1);
    int s2 = sign(y2-y1);

    bool interchange = false;

    if(Dy>Dx){
       swap(Dx , Dy);
       interchange = true;
    }

    int e = 2*Dy - Dx ;
    
    int dashsize = 8;
    int gapsize = 12;
    int count = 0 ;

    glBegin(GL_POINTS);
    for(int i = 0 ; i <= Dx ; i++){
       
      if(count < dashsize){
        glVertex2i(x , y);
       
      }
      count ++;

      if(count == dashsize + gapsize){
        count = 0;
      }
       
     

        while(e>=0){
            if(interchange){
                x = x + s1;
            }else{
                y = y + s2;
            }

            e =  e - 2*Dx;
        }

        if(interchange){
            y = y + s2;
        }else{
            x = x + s1;
        }

        e =  e + 2*Dy;
 }
 glEnd();
}

void BresenhamsSquareWave(){
    // Bresenhams(50 , 50 , 50 , 200);
    // Bresenhams(50 , 200 , 150 , 200);
    // Bresenhams(150 , 200 , 150 , 50);
    // Bresenhams(150 , 50 , 250 , 50);
    // Bresenhams(250 , 50 , 250 , 200);
    // Bresenhams(250 , 200 , 350 , 200);
    // Bresenhams(350 , 200 , 350 , 50);
   Bresenhams(50,50 , 100 , 150);
   Bresenhams(100 , 150 , 150 , 50);
   Bresenhams(150 , 50 , 200 , 150);
   Bresenhams(200 , 150 , 250 , 50);
   Bresenhams(250 , 50 , 300 , 150);
   Bresenhams(300 , 150 , 350 , 50);
   
   
}


void Display(){
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0,0,0);
   axes();

   glFlush();

}

void myInit(){
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPointSize(4);
  
    gluOrtho2D(-w/2,w/2,-h/2,h/2);
}
void Menu(int item){
    if(item==5){
        exit(0);
    }
    if(item == 6){ 
        BresenhamsSquareWave();
        glFlush();
       return ;
    };
    int x1 , y1 , x2 , y2;

    cout<<"x1=";
    cin>>x1;
    cout<<endl;

    cout<<"y1=";
    cin>>y1;
    cout<<endl;

    cout<<"x2=";
    cin>>x2;
    cout<<endl;

    cout<<"y2=";
    cin>>y2;
    cout<<endl;

    if(item==1) Bresenhams(x1,y1,x2,y2);
    else if(item==2) BresenhamsDotted(x1,y1,x2,y2);
    else if(item==3) BresenhamsDashed(x1,y1,x2,y2);
    
    else cout<<"Invalid option";
    glFlush();
   
    
}

void menuInit(){
   glutCreateMenu(Menu);
   glutAddMenuEntry("Simple Line",1);
   glutAddMenuEntry("Dotted Line",2);
   glutAddMenuEntry("Dashed Line",3);
   glutAddMenuEntry("Square Wave" , 6);
   glutAddMenuEntry("Exit",5);
   glutAttachMenu(GLUT_RIGHT_BUTTON);

}

int main(int v , char** c){
    glutInit(&v , c);
    glutInitWindowSize(w,h);
    glutCreateWindow("Bresenhams");
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutDisplayFunc(Display);
    menuInit();
    myInit();
    glutMainLoop();

}