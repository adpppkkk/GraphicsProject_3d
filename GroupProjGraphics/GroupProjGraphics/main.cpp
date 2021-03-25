#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif // use as needed for your system
#include <iostream>
#include <fstream>
using namespace std;

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
   glClearColor(0, 0, 0, 0.0);      // set the bg color to a bright white
   glColor3f(255, 255, 255);           // set the drawing color to black
   glPointSize(8.0);                    //set the point size to 4 by 4 pixels
   glMatrixMode(GL_PROJECTION);// set up appropriate matrices- to be explained
   glLoadIdentity();// to be explained
   gluOrtho2D(0.0, 800.0, 0.0, 600.0);// to be explained
}


double **MatrixMulti(double M1[][3],int r1,int c1,double M2[][1],int r2,int c2)
{
   double **result = new double*[r1];
   for(int i=0;i<r1;i++)
   {
       result[i] = new double[c2];
   }

   for(int i=0;i<r1;i++)
   {
       for (int j=0;j<c2;j++)
           result[i][j]=0;
   }

   for(int i=0;i<r1;i++)
   {
       for (int j=0;j<c2;j++)
       {
           double temp = 0;
           for(int k=0;k<c1;k++)
           {
               temp += M1[i][k] * M2[k][j];
           }
           result[i][j] = temp;
       }
   }
   return result;
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
// the redraw function
void myDisplay(void)
{
   glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
   
   //triangle
   glBegin(GL_LINE_STRIP); // draw an open polyline
       glVertex2i(100, 250);
       glVertex2i(200, 250);
       glVertex2i(150, 350);
       glVertex2i(100, 250);
   glEnd();
   //triangle point
   double tripoint[6]={100,250 ,200,250 ,150,350};

   //scaling
   glColor3f(0,255,0);
   double tripointscale[6] = {0,0,0,0,0,0}; // placeholder of the final points
   double scaleMatrix[3][3] = {
           {0.5,0,0},
           {0,0.5,0},                   //scaling matrix
           {0,0,1}
       };
   for(int i=0;i<3;i++)
   {
       double temp_point[3][1] = {tripoint[i*2],tripoint[i*2+1],1};
       
       double **result = MatrixMulti(scaleMatrix,3,3,temp_point,3,1);
       tripointscale[2*i]=result[0][0];
       tripointscale[2*i+1]=result[1][0];
   }

   glBegin(GL_LINE_STRIP); // draw an open polyline
       for(int i=0;i<3;i++)
           glVertex2i(tripointscale[i*2],tripointscale[2*i+1]);
       glVertex2i(tripointscale[0],tripointscale[1]);
   glEnd();

   //translation
   glColor3f(255,0,0);
   double tripointtrans[6] = {0,0,0,0,0,0};
   double transMatrix[3][3] = {
           {1,0,80},
           {0,1,80},
           {0,0,1}
       };
   for(int i=0;i<3;i++)
   {
       double temp_point[3][1] = {tripoint[i*2],tripoint[i*2+1],1};
       
       double **result = MatrixMulti(transMatrix,3,3,temp_point,3,1);
       tripointtrans[2*i]=result[0][0];
       tripointtrans[2*i+1]=result[1][0];
   }
   glBegin(GL_LINE_STRIP); // draw an open polyline
       for(int i=0;i<3;i++)
           glVertex2i(tripointtrans[i*2],tripointtrans[2*i+1]);
       glVertex2i(tripointtrans[0],tripointtrans[1]);
   glEnd();

   //rotation
   glColor3f(0,0,255);
   double tripointrotation[6] = {0,0,0,0,0,0};
   double rotationMatrix[3][3] = {
           {0.96592,-0.25881,0},
           {0.25881,0.96592,0},
           {0,0,1}
       };
   for(int i=0;i<3;i++)
   {
       double temp_point[3][1] = {tripoint[i*2],tripoint[i*2+1],1};
       
       double **result = MatrixMulti(rotationMatrix,3,3,temp_point,3,1);
       tripointrotation[2*i]=result[0][0];
       tripointrotation[2*i+1]=result[1][0];
   }

   glBegin(GL_LINE_STRIP); // draw an open polyline
       for(int i=0;i<3;i++)
           glVertex2i(tripointrotation[i*2],tripointrotation[2*i+1]);
       glVertex2i(tripointrotation[0],tripointrotation[1]);
   glEnd();
   // //square
   // glBegin(GL_LINE_STRIP); // draw an open polyline
   //     glVertex2i(300, 250);
   //     glVertex2i(400, 250);
   //     glVertex2i(400, 350);
   //     glVertex2i(300, 350);
   //     glVertex2i(300, 250);
   // glEnd();

   // //pentagon
   // glBegin(GL_LINE_STRIP); // draw an open polyline
   //     glVertex2i(500, 250);
   //     glVertex2i(575, 250);
   //     glVertex2i(600, 300);
   //     glVertex2i(537, 345);
   //     glVertex2i(475, 300);
   //     glVertex2i(500, 250);
   // glEnd();
   


   glFlush();                         // send all output to display
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
   glutInit(&argc, argv);          // initialize the toolkit
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
   glutInitWindowSize(800,600);     // set the window size
   glutInitWindowPosition(100, 150); // set the window position on the screen
   glutCreateWindow("2D Rotation"); // open the screen window(with its exciting title)
   glutDisplayFunc(myDisplay);     // register the redraw function
   myInit();
   glutMainLoop();              // go into a perpetual loop
   
   return 0;
}
