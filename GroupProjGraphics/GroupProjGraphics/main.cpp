#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif // use as needed for your system

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265
using namespace std;

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
/* Global variables */
char title[] = "3D Shapes";


double *MatrixMulti(double M1[][4],int r1,int c1,double M2[],int r2)
{
    double *result = new double[r2];


    for(int i=0;i<r1;i++)
    {
            result[i]=0;
    }

    for(int i=0;i<r1;i++)
    {
        for (int j=0;j<1;j++)
        {
            double temp = 0;
            for(int k=0;k<c1;k++)
            {
                temp += M1[i][k] * M2[k];
            }
            result[i] = temp;
        }
    }
    return result;
}

//the original cube point
struct Cube {
    double topP1[4] = { .5, .5, -.5, 1};
    double topP2[4] = {-.5, .5, -.5, 1};
    double topP3[4] = {-.5, .5,  .5, 1};
    double topP4[4] = { .5, .5,  .5, 1};
    
    double bottomP1[4] = { .5, -.5,  .5, 1};
    double bottomP2[4] = {-.5, -.5,  .5, 1};
    double bottomP3[4] = {-.5, -.5, -.5, 1};
    double bottomP4[4] = { .5, -.5, -.5, 1};
    
    double frontP1[4] = { .5,  .5, .5, 1};
    double frontP2[4] = {-.5,  .5, .5, 1};
    double frontP3[4] = {-.5, -.5, .5, 1};
    double frontP4[4] = { .5, -.5, .5, 1};
    
    double backP1[4] = { .5, -.5, -.5, 1};
    double backP2[4] = {-.5, -.5, -.5, 1};
    double backP3[4] = {-.5,  .5, -.5, 1};
    double backP4[4] = { .5,  .5, -.5, 1};
    
    double leftP1[4] = {-.5,  .5,  .5, 1};
    double leftP2[4] = {-.5,  .5, -.5, 1};
    double leftP3[4] = {-.5, -.5, -.5, 1};
    double leftP4[4] = {-.5, -.5,  .5, 1};
    
    double rightP1[4] = { .5,  .5, -.5, 1};
    double rightP2[4] = { .5,  .5,  .5, 1};
    double rightP3[4] = { .5, -.5,  .5, 1};
    double rightP4[4] = { .5, -.5, -.5, 1};
    
};

//cube after transform stores here
struct CubeTransform {
    double *topP1 = new double[4];
    double *topP2=new double[4];
    double *topP3=new double[4];
    double *topP4=new double[4];

    double *bottomP1=new double[4];
    double *bottomP2=new double[4];
    double *bottomP3=new double[4];
    double *bottomP4=new double[4];

    double *frontP1=new double[4];
    double *frontP2=new double[4];
    double *frontP3=new double[4];
    double *frontP4=new double[4];

    double *backP1=new double[4];
    double *backP2=new double[4];
    double *backP3=new double[4];
    double *backP4=new double[4];

    double *leftP1=new double[4];
    double *leftP2=new double[4];
    double *leftP3=new double[4];
    double *leftP4=new double[4];

    double *rightP1=new double[4];
    double *rightP2=new double[4];
    double *rightP3=new double[4];
    double *rightP4=new double[4];

};


void setDefault(CubeTransform & ct){
    Cube c;
    for(int i = 0; i < 4; i++)
    {
        ct.topP1[i] = c.topP1[i];
        ct.topP2[i] = c.topP2[i];
        ct.topP3[i] = c.topP3[i];
        ct.topP4[i] = c.topP4[i];
        
        ct.bottomP1[i] = c.bottomP1[i];
        ct.bottomP2[i] = c.bottomP2[i];
        ct.bottomP3[i] = c.bottomP3[i];
        ct.bottomP4[i] = c.bottomP4[i];
        
        ct.frontP1[i] = c.frontP1[i];
        ct.frontP2[i] = c.frontP2[i];
        ct.frontP3[i] = c.frontP3[i];
        ct.frontP4[i] = c.frontP4[i];
        
        ct.backP1[i] = c.backP1[i];
        ct.backP2[i] = c.backP2[i];
        ct.backP3[i] = c.backP3[i];
        ct.backP4[i] = c.backP4[i];
        
        ct.leftP1[i] = c.leftP1[i];
        ct.leftP2[i] = c.leftP2[i];
        ct.leftP3[i] = c.leftP3[i];
        ct.leftP4[i] = c.leftP4[i];
        
        ct.rightP1[i] = c.rightP1[i];
        ct.rightP2[i] = c.rightP2[i];
        ct.rightP3[i] = c.rightP3[i];
        ct.rightP4[i] = c.rightP4[i];
    }
}

void Translation(CubeTransform & c,double x,double y,double z)
{
    double transformMatrix[4][4]={
        {1,0,0,x},
        {0,1,0,y},              // transform by x,y,z
        {0,0,1,z},
        {0,0,0,1}
    };
    
    c.topP1 = MatrixMulti(transformMatrix,4,4,c.topP1,4);
    c.topP2 = MatrixMulti(transformMatrix,4,4,c.topP2,4);
    c.topP3 = MatrixMulti(transformMatrix,4,4,c.topP3,4);
    c.topP4 = MatrixMulti(transformMatrix,4,4,c.topP4,4);
    
    c.bottomP1 = MatrixMulti(transformMatrix, 4, 4, c.bottomP1, 4);
    c.bottomP2 = MatrixMulti(transformMatrix, 4, 4, c.bottomP2, 4);
    c.bottomP3 = MatrixMulti(transformMatrix, 4, 4, c.bottomP3, 4);
    c.bottomP4 = MatrixMulti(transformMatrix, 4, 4, c.bottomP4, 4);
    
    c.frontP1 = MatrixMulti(transformMatrix, 4, 4, c.frontP1, 4);
    c.frontP2 = MatrixMulti(transformMatrix, 4, 4, c.frontP2, 4);
    c.frontP3 = MatrixMulti(transformMatrix, 4, 4, c.frontP3, 4);
    c.frontP4 = MatrixMulti(transformMatrix, 4, 4, c.frontP4, 4);
    
    c.backP1 = MatrixMulti(transformMatrix, 4, 4, c.backP1, 4);
    c.backP2 = MatrixMulti(transformMatrix, 4, 4, c.backP2, 4);
    c.backP3 = MatrixMulti(transformMatrix, 4, 4, c.backP3, 4);
    c.backP4 = MatrixMulti(transformMatrix, 4, 4, c.backP4, 4);
    
    c.leftP1 = MatrixMulti(transformMatrix, 4, 4, c.leftP1, 4);
    c.leftP2 = MatrixMulti(transformMatrix, 4, 4, c.leftP2, 4);
    c.leftP3 = MatrixMulti(transformMatrix, 4, 4, c.leftP3, 4);
    c.leftP4 = MatrixMulti(transformMatrix, 4, 4, c.leftP4, 4);
    
    c.rightP1 = MatrixMulti(transformMatrix, 4, 4, c.rightP1, 4);
    c.rightP2 = MatrixMulti(transformMatrix, 4, 4, c.rightP2, 4);
    c.rightP3 = MatrixMulti(transformMatrix, 4, 4, c.rightP3, 4);
    c.rightP4 = MatrixMulti(transformMatrix, 4, 4, c.rightP4, 4);
    
}


void Scaling(CubeTransform & c,double x,double y,double z)
{
    double scalingMatrix[4][4]={
        {x,0,0,0},
        {0,y,0,0},              // scaling by x,y,z
        {0,0,z,0},
        {0,0,0,1}
    };
    
    c.topP1 = MatrixMulti(scalingMatrix,4,4,c.topP1,4);
    c.topP2 = MatrixMulti(scalingMatrix,4,4,c.topP2,4);
    c.topP3 = MatrixMulti(scalingMatrix,4,4,c.topP3,4);
    c.topP4 = MatrixMulti(scalingMatrix,4,4,c.topP4,4);
    
    c.bottomP1 = MatrixMulti(scalingMatrix, 4, 4, c.bottomP1, 4);
    c.bottomP2 = MatrixMulti(scalingMatrix, 4, 4, c.bottomP2, 4);
    c.bottomP3 = MatrixMulti(scalingMatrix, 4, 4, c.bottomP3, 4);
    c.bottomP4 = MatrixMulti(scalingMatrix, 4, 4, c.bottomP4, 4);
    
    c.frontP1 = MatrixMulti(scalingMatrix, 4, 4, c.frontP1, 4);
    c.frontP2 = MatrixMulti(scalingMatrix, 4, 4, c.frontP2, 4);
    c.frontP3 = MatrixMulti(scalingMatrix, 4, 4, c.frontP3, 4);
    c.frontP4 = MatrixMulti(scalingMatrix, 4, 4, c.frontP4, 4);
    
    c.backP1 = MatrixMulti(scalingMatrix, 4, 4, c.backP1, 4);
    c.backP2 = MatrixMulti(scalingMatrix, 4, 4, c.backP2, 4);
    c.backP3 = MatrixMulti(scalingMatrix, 4, 4, c.backP3, 4);
    c.backP4 = MatrixMulti(scalingMatrix, 4, 4, c.backP4, 4);
    
    c.leftP1 = MatrixMulti(scalingMatrix, 4, 4, c.leftP1, 4);
    c.leftP2 = MatrixMulti(scalingMatrix, 4, 4, c.leftP2, 4);
    c.leftP3 = MatrixMulti(scalingMatrix, 4, 4, c.leftP3, 4);
    c.leftP4 = MatrixMulti(scalingMatrix, 4, 4, c.leftP4, 4);
    
    c.rightP1 = MatrixMulti(scalingMatrix, 4, 4, c.rightP1, 4);
    c.rightP2 = MatrixMulti(scalingMatrix, 4, 4, c.rightP2, 4);
    c.rightP3 = MatrixMulti(scalingMatrix, 4, 4, c.rightP3, 4);
    c.rightP4 = MatrixMulti(scalingMatrix, 4, 4, c.rightP4, 4);
}



void Rotation(CubeTransform & c,int axis,double angle)
{
    double r = angle*PI/180;
    
    double rotationMatrixX[4][4]={
        {1,0,0,0},
        {0,cos(r),-sin(r),0},              // rotate by x axis
        {0,sin(r),cos(r),0},
        {0,0,0,1}
    };
    
    double rotationMatrixY[4][4]={
        {cos(r),0,sin(r),0},
        {0,1,0,0},                         // rotate by x axis
        {-sin(r),0,cos(r),0},
        {0,0,0,1}
    };
    
    double rotationMatrixZ[4][4]={
        {cos(r),-sin(r),0,0},
        {sin(r),cos(r),0,0},                         // rotate by z axis
        {0,0,1,0},
        {0,0,0,1}
    };
    
    if (axis != 0)
    {
        if (axis==1)
        {
            c.topP1 = MatrixMulti(rotationMatrixX,4,4,c.topP1,4);
            c.topP2 = MatrixMulti(rotationMatrixX,4,4,c.topP2,4);
            c.topP3 = MatrixMulti(rotationMatrixX,4,4,c.topP3,4);
            c.topP4 = MatrixMulti(rotationMatrixX,4,4,c.topP4,4);
            
            c.bottomP1 = MatrixMulti(rotationMatrixX, 4, 4, c.bottomP1, 4);
            c.bottomP2 = MatrixMulti(rotationMatrixX, 4, 4, c.bottomP2, 4);
            c.bottomP3 = MatrixMulti(rotationMatrixX, 4, 4, c.bottomP3, 4);
            c.bottomP4 = MatrixMulti(rotationMatrixX, 4, 4, c.bottomP4, 4);
            
            c.frontP1 = MatrixMulti(rotationMatrixX, 4, 4, c.frontP1, 4);
            c.frontP2 = MatrixMulti(rotationMatrixX, 4, 4, c.frontP2, 4);
            c.frontP3 = MatrixMulti(rotationMatrixX, 4, 4, c.frontP3, 4);
            c.frontP4 = MatrixMulti(rotationMatrixX, 4, 4, c.frontP4, 4);
            
            c.backP1 = MatrixMulti(rotationMatrixX, 4, 4, c.backP1, 4);
            c.backP2 = MatrixMulti(rotationMatrixX, 4, 4, c.backP2, 4);
            c.backP3 = MatrixMulti(rotationMatrixX, 4, 4, c.backP3, 4);
            c.backP4 = MatrixMulti(rotationMatrixX, 4, 4, c.backP4, 4);
            
            c.leftP1 = MatrixMulti(rotationMatrixX, 4, 4, c.leftP1, 4);
            c.leftP2 = MatrixMulti(rotationMatrixX, 4, 4, c.leftP2, 4);
            c.leftP3 = MatrixMulti(rotationMatrixX, 4, 4, c.leftP3, 4);
            c.leftP4 = MatrixMulti(rotationMatrixX, 4, 4, c.leftP4, 4);
            
            c.rightP1 = MatrixMulti(rotationMatrixX, 4, 4, c.rightP1, 4);
            c.rightP2 = MatrixMulti(rotationMatrixX, 4, 4, c.rightP2, 4);
            c.rightP3 = MatrixMulti(rotationMatrixX, 4, 4, c.rightP3, 4);
            c.rightP4 = MatrixMulti(rotationMatrixX, 4, 4, c.rightP4, 4);
        }
        if (axis==2)
        {
            c.topP1 = MatrixMulti(rotationMatrixY,4,4,c.topP1,4);
            c.topP2 = MatrixMulti(rotationMatrixY,4,4,c.topP2,4);
            c.topP3 = MatrixMulti(rotationMatrixY,4,4,c.topP3,4);
            c.topP4 = MatrixMulti(rotationMatrixY,4,4,c.topP4,4);
            
            c.bottomP1 = MatrixMulti(rotationMatrixY, 4, 4, c.bottomP1, 4);
            c.bottomP2 = MatrixMulti(rotationMatrixY, 4, 4, c.bottomP2, 4);
            c.bottomP3 = MatrixMulti(rotationMatrixY, 4, 4, c.bottomP3, 4);
            c.bottomP4 = MatrixMulti(rotationMatrixY, 4, 4, c.bottomP4, 4);
            
            c.frontP1 = MatrixMulti(rotationMatrixY, 4, 4, c.frontP1, 4);
            c.frontP2 = MatrixMulti(rotationMatrixY, 4, 4, c.frontP2, 4);
            c.frontP3 = MatrixMulti(rotationMatrixY, 4, 4, c.frontP3, 4);
            c.frontP4 = MatrixMulti(rotationMatrixY, 4, 4, c.frontP4, 4);
            
            c.backP1 = MatrixMulti(rotationMatrixY, 4, 4, c.backP1, 4);
            c.backP2 = MatrixMulti(rotationMatrixY, 4, 4, c.backP2, 4);
            c.backP3 = MatrixMulti(rotationMatrixY, 4, 4, c.backP3, 4);
            c.backP4 = MatrixMulti(rotationMatrixY, 4, 4, c.backP4, 4);
            
            c.leftP1 = MatrixMulti(rotationMatrixY, 4, 4, c.leftP1, 4);
            c.leftP2 = MatrixMulti(rotationMatrixY, 4, 4, c.leftP2, 4);
            c.leftP3 = MatrixMulti(rotationMatrixY, 4, 4, c.leftP3, 4);
            c.leftP4 = MatrixMulti(rotationMatrixY, 4, 4, c.leftP4, 4);
            
            c.rightP1 = MatrixMulti(rotationMatrixY, 4, 4, c.rightP1, 4);
            c.rightP2 = MatrixMulti(rotationMatrixY, 4, 4, c.rightP2, 4);
            c.rightP3 = MatrixMulti(rotationMatrixY, 4, 4, c.rightP3, 4);
            c.rightP4 = MatrixMulti(rotationMatrixY, 4, 4, c.rightP4, 4);
        }
        if (axis==3)
        {
            c.topP1 = MatrixMulti(rotationMatrixZ,4,4,c.topP1,4);
            c.topP2 = MatrixMulti(rotationMatrixZ,4,4,c.topP2,4);
            c.topP3 = MatrixMulti(rotationMatrixZ,4,4,c.topP3,4);
            c.topP4 = MatrixMulti(rotationMatrixZ,4,4,c.topP4,4);
            
            c.bottomP1 = MatrixMulti(rotationMatrixZ, 4, 4, c.bottomP1, 4);
            c.bottomP2 = MatrixMulti(rotationMatrixZ, 4, 4, c.bottomP2, 4);
            c.bottomP3 = MatrixMulti(rotationMatrixZ, 4, 4, c.bottomP3, 4);
            c.bottomP4 = MatrixMulti(rotationMatrixZ, 4, 4, c.bottomP4, 4);
            
            c.frontP1 = MatrixMulti(rotationMatrixZ, 4, 4, c.frontP1, 4);
            c.frontP2 = MatrixMulti(rotationMatrixZ, 4, 4, c.frontP2, 4);
            c.frontP3 = MatrixMulti(rotationMatrixZ, 4, 4, c.frontP3, 4);
            c.frontP4 = MatrixMulti(rotationMatrixZ, 4, 4, c.frontP4, 4);
            
            c.backP1 = MatrixMulti(rotationMatrixZ, 4, 4, c.backP1, 4);
            c.backP2 = MatrixMulti(rotationMatrixZ, 4, 4, c.backP2, 4);
            c.backP3 = MatrixMulti(rotationMatrixZ, 4, 4, c.backP3, 4);
            c.backP4 = MatrixMulti(rotationMatrixZ, 4, 4, c.backP4, 4);
            
            c.leftP1 = MatrixMulti(rotationMatrixZ, 4, 4, c.leftP1, 4);
            c.leftP2 = MatrixMulti(rotationMatrixZ, 4, 4, c.leftP2, 4);
            c.leftP3 = MatrixMulti(rotationMatrixZ, 4, 4, c.leftP3, 4);
            c.leftP4 = MatrixMulti(rotationMatrixZ, 4, 4, c.leftP4, 4);
            
            c.rightP1 = MatrixMulti(rotationMatrixZ, 4, 4, c.rightP1, 4);
            c.rightP2 = MatrixMulti(rotationMatrixZ, 4, 4, c.rightP2, 4);
            c.rightP3 = MatrixMulti(rotationMatrixZ, 4, 4, c.rightP3, 4);
            c.rightP4 = MatrixMulti(rotationMatrixZ, 4, 4, c.rightP4, 4);
        }
    }
    
}
 
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void draw(CubeTransform & c){
    glBegin(GL_QUADS);
    // Top face (y = 1.0f)
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(c.topP1[0], c.topP1[1], c.topP1[2]);
    glVertex3f(c.topP2[0], c.topP2[1], c.topP2[2]);
    glVertex3f(c.topP3[0], c.topP3[1], c.topP3[2]);
    glVertex3f(c.topP4[0], c.topP4[1], c.topP4[2]);
    
    // Bottom face (y = -1.0f)
    glColor3f(1.0f, 0.5f, 0.0f);     // Orange
    glVertex3f(c.bottomP1[0], c.bottomP1[1], c.bottomP1[2]);
    glVertex3f(c.bottomP2[0], c.bottomP2[1], c.bottomP2[2]);
    glVertex3f(c.bottomP3[0], c.bottomP3[1], c.bottomP3[2]);
    glVertex3f(c.bottomP4[0], c.bottomP4[1], c.bottomP4[2]);
    
    // Front face  (z = 1.0f)
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(c.frontP1[0], c.frontP1[1], c.frontP1[2]);
    glVertex3f(c.frontP2[0], c.frontP2[1], c.frontP2[2]);
    glVertex3f(c.frontP3[0], c.frontP3[1], c.frontP3[2]);
    glVertex3f(c.frontP4[0], c.frontP4[1], c.frontP4[2]);
    
    //Back face (z = -1.0f)
    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    glVertex3f(c.backP1[0], c.backP1[1], c.backP1[2]);
    glVertex3f(c.backP2[0], c.backP2[1], c.backP2[2]);
    glVertex3f(c.backP3[0], c.backP3[1], c.backP3[2]);
    glVertex3f(c.backP4[0], c.backP4[1], c.backP4[2]);
    
    // Left face (x = -1.0f)
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(c.leftP1[0], c.leftP1[1], c.leftP1[2]);
    glVertex3f(c.leftP2[0], c.leftP2[1], c.leftP2[2]);
    glVertex3f(c.leftP3[0], c.leftP3[1], c.leftP3[2]);
    glVertex3f(c.leftP4[0], c.leftP4[1], c.leftP4[2]);
    
    // Right face (x = 1.0f)
    glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
    glVertex3f(c.rightP1[0], c.rightP1[1], c.rightP1[2]);
    glVertex3f(c.rightP2[0], c.rightP2[1], c.rightP2[2]);
    glVertex3f(c.rightP3[0], c.rightP3[1], c.rightP3[2]);
    glVertex3f(c.rightP4[0], c.rightP4[1], c.rightP4[2]);
    
    glEnd();
}
 
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
   glTranslatef(0.0f, 0.0f, -12.0f);  // Move right and into the screen

    CubeTransform ct;
    setDefault(ct);
    Rotation(ct, 2, 40);
    draw(ct);
    Rotation(ct, 2, -40);
    
    Translation(ct, 2, 1, 2);
    Rotation(ct, 1, 60);
    draw(ct);
    Rotation(ct, 1, -60);
    Scaling(ct, 0.5, 0.5, 0.5);
    Rotation(ct, 3, 20);
    draw(ct);
   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
