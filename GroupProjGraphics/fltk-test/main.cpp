#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/Fl_Button.H>
#include <iostream>

using namespace std;

class MyGlWindow : public Fl_Gl_Window {
    public:
        // DRAW METHOD
        // OpenGL window: (w,h) is upper right, (-w,-h) is lower left, (0,0) is center
        //
        void draw() {
            // First time? init viewport, etc.
            if (!valid()) {
                valid(1);
                glLoadIdentity();
                glViewport(0,0,w(),h());
                glOrtho(-w(),w(),-h(),h(),-1,1);
            }
            // Clear screen
            glClear(GL_COLOR_BUFFER_BIT);
            // Draw white 'X'
        
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

            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINE_STRIP); glVertex2f(w(), h()); glVertex2f(-w(),-h()); glEnd();
            glBegin(GL_LINE_STRIP); glVertex2f(w(),-h()); glVertex2f(-w(), h()); glEnd();
        }
    // HANDLE WINDOW RESIZING
    // If window reshaped, need to readjust viewport/ortho
    //

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

        CubeTransform c;

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


        void resize(int X,int Y,int W,int H) {
            Fl_Gl_Window::resize(X,Y,W,H);
            glLoadIdentity();
            glViewport(0,0,W,H);
            glOrtho(-W,W,-H,H,-1,1);
            redraw();
        }

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

        // CONSTRUCTOR
        MyGlWindow(int X,int Y,int W,int H,const char*L=0) : Fl_Gl_Window(X,Y,W,H,L) {
        }
};

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

int main() {
    Fl_Window win(1000, 640);
    MyGlWindow mygl(210, 10, win.w()-220, win.h()-20);
    Fl_Button* translateButton = new Fl_Button(20, 20, 150, 50, "Translate");
    Fl_Button* rotateButton = new Fl_Button(20, 90, 150, 50, "Rotate");
    win.end();
    win.resizable(mygl);
    win.show(); // displays window
    initGL();
    return(Fl::run()); // enter event loop
}