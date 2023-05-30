/*
 * Versió pasat OpenGL clàsic + GLUT del
 * còdic d'OpenGL modern + GLFW: "GLFW - Getting started" <https://www.glfw.org/docs/3.3/quick_guide.html>

 gcc triangle_animat_clasic_glut.c   -o triangle_animat_clasic_glut  -lglut  -lGL -lm && triangle_animat_clasic_glut
 

 L'original (en GLFW) es compila en)
 gcc simple.c  -o simple  -lglfw  -lGL && simple
 gcc triangle_animat_modern_glfw.c   -o triangle_animat_modern_glfw  -lglfw  -lGL -lm && triangle_animat_modern_glfw

// GLFW 
// Alternativa a toolkits (freeglut, GLUT) i "multimedia libraries" (Allegro, SDL, SFML, ... Qt, wxWidgets, ...) https://www.khronos.org/opengl/wiki/Related_toolkits_and_APIs
// GLFW is a free, Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan application development. It provides a simple, platform-independent API for creating windows, contexts and surfaces, reading input, handling events, etc.
// GLFW is written in C and supports Windows, macOS, X11 and Wayland.
// GLFW is licensed under the zlib/libpng license.

*/

#include <GL/gl.h>
#include <GL/glut.h>   
#include <GL/freeglut_ext.h>   // glutMainLoopEvent

 
#include "linmath.h"
//https://github.com/glfw/glfw/blob/master/deps/linmath.h

#include <stdlib.h>
#include <stdio.h>
 
static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};
 

// https://www.khronos.org/opengl/wiki/OpenGL_Error
void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
} 


// static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
// {
//     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, GLFW_TRUE);
// }
//  
 void key_callback( unsigned char key, int x, int y ) {
   switch ( key )
  {
    case 27: // Escape key
      glutDestroyWindow ( glutGetWindow() );
      printf("Acabant per ESC\n");
      exit (0);
      break;
  }
  glutPostRedisplay();
  
 }

 //
static GLfloat spin = 0.0;
//
// Per a fer-lo rodar <-- http://www.glprogramming.com/red/chapter01.html
void spinDisplay(void)
{
   //spin = spin + 2.0;
   spin = spin + 0.000001;
   if (spin > 360.0)
      spin = 0.0; //spin - 360.0;
   glutPostRedisplay();
}
 
void display() {  // Display function will draw the image.
 
    glClearColor( 0, 0, 0, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );
    
    // Originalment
    glRotatef(spin, 0.0, 0.0, 1.0);
    // Per que siga constant 
//     glRotatef(1, 0.0, 0.0, 1.0); 
       

    glBegin(GL_TRIANGLES);
    glColor3f( vertices[0].r, vertices[0].g, vertices[0].b  ); // glColor3f( 1, 0, 0 ); // red
    glVertex2f( vertices[0].x, vertices[0].y );                // glVertex2f( -0.8, -0.8 );
    glColor3f( vertices[1].r, vertices[1].g, vertices[1].b  ); // glColor3f( 0, 1, 0 ); // green
    glVertex2f( vertices[1].x, vertices[1].y );                // glVertex2f( 0.8, -0.8 );
    glColor3f( vertices[2].r, vertices[2].g, vertices[2].b  ); // glColor3f( 0, 0, 1 ); // blue
    glVertex2f( vertices[2].x, vertices[2].y );                // glVertex2f( 0, 0.9 );
    glEnd(); 
    
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
 
}

void reshape(int w, int h) {
// Estava al prog. ppal.
//         glfwGetFramebufferSize(window, &width, &height);
//         ratio = width / (float) height;
//  
//         glViewport(0, 0, width, height);
//         glClear(GL_COLOR_BUFFER_BIT);
 
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-50.0, 50.0, -50.0, 50.0, 1.0, 1.0);
   glOrtho(-50.0, 50.0, -50.0, 50.0, 1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
} 
 

 
// int main(void) {
int main( int argc, char** argv ) { 
//     GLFWwindow* window;
//     GLuint vertex_buffer, vertex_shader, fragment_shader, program;
//     GLint mvp_location, vpos_location, vcol_location;
//  
    int window;
    
    glutInit(&argc, argv);               // Initialize GLUT and 
    glutInitDisplayMode(GLUT_SINGLE);    // Use single color buffer and no depth buffer.
    //    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);         // Size of display area, in pixels.
    glutInitWindowPosition(100,100);     // Location of window in screen coordinates.
    window = glutCreateWindow("GL RGB Triangle + Simple example (OGL modern) + MainLoopEvent"); // Parameter is window title.

//     glutSetWindow( window ); //No n'hi ha atra, no fa falta.
     
//     glfwSetErrorCallback(error_callback);
// https://www.khronos.org/opengl/wiki/Debug_Output
//     During init, enable debug output
// glEnable              ( GL_DEBUG_OUTPUT );
// glDebugMessageCallback( MessageCallback, 0 );


 
//     if (!glfwInit())
//         exit(EXIT_FAILURE);
//  
    if ( !window )
        exit(EXIT_FAILURE);

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//  
//     window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
//     if (!window)
//     {
//         glfwTerminate();
//         exit(EXIT_FAILURE);
//     }
 
//     glfwSetKeyCallback(window, key_callback);
    glutKeyboardFunc( key_callback );
 
    
    
//     glfwMakeContextCurrent(window);
// //     gladLoadGL(glfwGetProcAddress);
//     glfwSwapInterval(1);
 
    glutDisplayFunc(display);            // Called when the window needs to be redrawn.    
    glutReshapeFunc(reshape);
//     glutMouseFunc(mouse);

    
    

//     while (!glfwWindowShouldClose(window)) {
    while( 1 ) {        
// reshape
//         float ratio;
//         int width, height;
//         mat4x4 m, p, mvp;
//  
//         glfwGetFramebufferSize(window, &width, &height);
//         ratio = width / (float) height;
//  
//         glViewport(0, 0, width, height);
//         glClear(GL_COLOR_BUFFER_BIT);
//  
//         mat4x4_identity(m);
//         mat4x4_rotate_Z(m, m, (float) glfwGetTime());
//         mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//         mat4x4_mul(mvp, p, m);
//  
//         glUseProgram(program);
//         glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
//         glDrawArrays(GL_TRIANGLES, 0, 3);
// 
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//
      glutMainLoopEvent(); 
    
      display();
      spinDisplay();
    
      glutPostRedisplay();      
    }
 
//     glfwDestroyWindow(window);
    glutDestroyWindow( window );
//     glfwTerminate();
    exit(EXIT_SUCCESS);
}
 
