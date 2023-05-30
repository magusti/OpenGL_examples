/*
 * 
 * https://math.hws.edu/graphicsbook/source/glut/
 * +
 * http://www.glprogramming.com/red/chapter01.html
 * 
 *  As a first example of using OpenGL in C, this program draws the
 *  classic red/green/blue triangle.  It uses the default OpenGL
 *  coordinate system, in which x, y, and z are limited to the range
 *  -1 to 1, and the positive z-axis points into the screen.  Note
 *  that this coordinate system is hardly ever used in practice.
 *
 *  When compiling this program, you must link it to the OpenGL library
 *  and to the glut library. For example, in Linux using the gcc compiler, 
 *  it can be compiled with the command:
 *
 *          gcc -o first-triangle first-triangle.c -lGL -lglut
 * 
 * gcc -o first-triangle__animat first-triangle__animat.c -lGL -lglut && first-triangle__animat
 */
 
#include <GL/gl.h>
#include <GL/glut.h>   // freeglut.h might be a better alternative, if available.

//
static GLfloat spin = 0.0;
//

void display() {  // Display function will draw the image.
 
    glClearColor( 0, 0, 0, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );
    
    // Originalment
    // glRotatef(spin, 0.0, 0.0, 1.0);
    // Per que siga constant 
    glRotatef(1, 0.0, 0.0, 1.0); 
       
    glBegin(GL_TRIANGLES);
    glColor3f( 1, 0, 0 ); // red
    glVertex2f( -0.8, -0.8 );
    glColor3f( 0, 1, 0 ); // green
    glVertex2f( 0.8, -0.8 );
    glColor3f( 0, 0, 1 ); // blue
    glVertex2f( 0, 0.9 );
    glEnd(); 
    
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
 
}

// Per a fer-lo rodar <-- http://www.glprogramming.com/red/chapter01.html
void spinDisplay(void)
{
   //spin = spin + 2.0;
//    spin = spin + 0.001;
//    if (spin > 360.0)
//       spin = spin - 360.0;
   glutPostRedisplay();
}
void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-50.0, 50.0, -50.0, 50.0, 1.0, 1.0);
   glOrtho(-50.0, 50.0, -50.0, 50.0, 1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
         break;
      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}
//


int main( int argc, char** argv ) {  // Initialize GLUT and 

    glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE);    // Use single color buffer and no depth buffer.
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    
    glutInitWindowSize(500,500);         // Size of display area, in pixels.
    glutInitWindowPosition(100,100);     // Location of window in screen coordinates.
    glutCreateWindow("GL RGB Triangle"); // Parameter is window title.
    glutDisplayFunc(display);            // Called when the window needs to be redrawn.
    
    //
    glutReshapeFunc(reshape); 
    glutMouseFunc(mouse);
    //
    
    glutMainLoop(); // Run the event loop!  This function does not return.
                    // Program ends when user closes the window.
    return 0;

}

