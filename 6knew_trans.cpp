#include<iostream>
#include<GL/glut.h>
#include<math.h>
using namespace std;

#define w 1080
#define h 1080

int X,Y;

void myInit(void)
{
   glClearColor(1.0,1.0,1.0,0.0);
   glColor3f(0.0f,0.0f,0.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(-w/2,w/2,-h/2,h/2);
}

void plot_axes(){
   glColor3f(1.0f,0.0f,0.0f);
   for(int i = -w; i < w; i++){
      glBegin(GL_POINTS);
      glVertex2i(i, 0);
      glVertex2i(0, i);
      glEnd();
   }
}

void plot(float x, float y)
{
   glBegin(GL_POINTS);
   glVertex2f(x, y);
   glEnd();
   glFlush();
}

int sign(float val)
{
   if(val < 0) return -1;
   if(val > 0) return 1;
   return 0;
}

void Bresenham(int x1, int y1, int x2, int y2)
{
   int x, y, dx, dy, temp, e;
   int s1, s2, interchange, i;

   x = x1;
   y = y1;
   dx = abs(x2 - x1);
   dy = abs(y2 - y1);
   s1 = sign(x2 - x1);
   s2 = sign(y2 - y1);

   interchange = (dy > dx);
   if(interchange) swap(dx, dy);

   e = 2 * dy - dx;
   for(i = 1; i <= dx; i++) {
      plot(x, y);
      while(e >= 0) {
         if(interchange) x += s1;
         else y += s2;
         e -= 2 * dx;
      }
      if(interchange) y += s2;
      else x += s1;
      e += 2 * dy;
   }
}

void applyTransform(int x1, int y1, int x2, int y2, float mat[3][3])
{
   float p1 = mat[0][0]*x1 + mat[0][1]*y1 + mat[0][2];
   float q1 = mat[1][0]*x1 + mat[1][1]*y1 + mat[1][2];
   float p2 = mat[0][0]*x2 + mat[0][1]*y2 + mat[0][2];
   float q2 = mat[1][0]*x2 + mat[1][1]*y2 + mat[1][2];

   Bresenham(round(p1), round(q1), round(p2), round(q2));
}

void rotate(int x1, int y1, int x2, int y2, float angle)
{
   float rad = angle * M_PI / 180;
   float mat[3][3] = {
      {cos(rad), -sin(rad), 0},
      {sin(rad), cos(rad), 0},
      {0, 0, 1}
   };
   applyTransform(x1, y1, x2, y2, mat);
}

void scale(int x1, int y1, int x2, int y2, float sx, float sy)
{
   float mat[3][3] = {
      {sx, 0, 0},
      {0, sy, 0},
      {0, 0, 1}
   };
   applyTransform(x1, y1, x2, y2, mat);
}

void translate(int x1, int y1, int x2, int y2, float tx, float ty)
{
   float mat[3][3] = {
      {1, 0, tx},
      {0, 1, ty},
      {0, 0, 1}
   };
   applyTransform(x1, y1, x2, y2, mat);
}

void reflectX(int x1, int y1, int x2, int y2)
{
   float mat[3][3] = {
      {1, 0, 0},
      {0, -1, 0},
      {0, 0, 1}
   };
   applyTransform(x1, y1, x2, y2, mat);
}

void reflectY(int x1, int y1, int x2, int y2)
{
   float mat[3][3] = {
      {-1, 0, 0},
      {0, 1, 0},
      {0, 0, 1}
   };
   applyTransform(x1, y1, x2, y2, mat);
}

void shearX(int x1, int y1, int x2, int y2, float shx)
{
   float mat[3][3] = {
      {1, shx, 0},
      {0, 1, 0},
      {0, 0, 1}
   };
   applyTransform(x1, y1, x2, y2, mat);
}

void create_menu(int item)
{
   if(item == 1)
   {
      Bresenham(100, 200, 200, 200);
      Bresenham(200, 200, 200, 300);
      Bresenham(200, 300, 100, 300);
      Bresenham(100, 300, 100, 200);
   }
   if(item == 2)
   {
      rotate(100, 100, 200, 100, 45);
      rotate(200, 100, 200, 200, 45);
      rotate(200, 200, 100, 200, 45);
      rotate(100, 200, 100, 100, 45);
   }
   if(item == 3)
   {
      int tx, ty;
      cout << "Enter tx and ty: ";
      cin >> tx >> ty;

      translate(100, 100, 200, 100, tx, ty);
      translate(200, 100, 200, 200, tx, ty);
      translate(200, 200, 100, 200, tx, ty);
      translate(100, 200, 100, 100, tx, ty);
   }
   if(item == 4)
   {
      reflectX(100, 100, 200, 100);
      reflectX(200, 100, 200, 200);
      reflectX(200, 200, 100, 200);
      reflectX(100, 200, 100, 100);
   }
   if(item == 5)
   {
      reflectY(100, 100, 200, 100);
      reflectY(200, 100, 200, 200);
      reflectY(200, 200, 100, 200);
      reflectY(100, 200, 100, 100);
   }
   if(item == 6)
   {
      float sx, sy;
      cout << "Enter sx and sy: ";
      cin >> sx >> sy;

      scale(100, 100, 200, 100, sx, sy);
      scale(200, 100, 200, 200, sx, sy);
      scale(200, 200, 100, 200, sx, sy);
      scale(100, 200, 100, 100, sx, sy);
   }
   if(item == 7)
   {
      float shx = 1.5;
      shearX(100, 100, 200, 100, shx);
      shearX(200, 100, 200, 200, shx);
      shearX(200, 200, 100, 200, shx);
      shearX(100, 200, 100, 100, shx);
   }
}

void myDisplay(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   plot_axes();
   glFlush();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(1080, 1080);
   glutInitWindowPosition(100, 150);

   glutCreateWindow("SQUARE with 3x3 TRANSFORMATIONS");
   glutDisplayFunc(myDisplay);

   glutCreateMenu(create_menu);
   glutAddMenuEntry("DRAW SQUARE", 1);
   glutAddMenuEntry("ROTATE SQUARE (45 deg)", 2);
   glutAddMenuEntry("TRANSLATE SQUARE", 3);
   glutAddMenuEntry("REFLECT IN X", 4);
   glutAddMenuEntry("REFLECT IN Y", 5);
   glutAddMenuEntry("SCALE", 6);
   glutAddMenuEntry("SHEAR IN X", 7);

   glutAttachMenu(GLUT_RIGHT_BUTTON);
   myInit();
   glutMainLoop();
   return 0;
}
