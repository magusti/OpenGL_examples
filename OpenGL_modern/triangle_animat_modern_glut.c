/*
 * Sobre el OpenGL modern en "GLFW - Getting started" <https://www.glfw.org/docs/3.3/quick_guide.html>
 * Versió: pasat a GLLUT

  gcc triangle_animat_modern_glut.c  -o triangle_animat_modern_glut  `pkg-config glesv2 --cflags --libs` -lglut  -lGL -lm && triangle_animat_modern_glut
 * 
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

// https://registry.khronos.org/OpenGL/index_es.php / 
// OpenGL ES
// https://en.wikipedia.org/wiki/OpenGL_ES
#include <GLES3/gl3.h>
/*
 *Sense esta eixien un montó de 
 * simple.c:106:5: warning: implicit declaration of function ‘glGenBuffers’; did you mean ‘glReadBuffer’? [-Wimplicit-function-declaration]
  106 |     glGenBuffers(1, &vertex_buffer);
      |     ^~~~~~~~~~~~
      |     glReadBuffer
 
 * i no funciona en estes
 #include <GL/glx.h>
 #include <GL/glext.h>*/
 
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
 
static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";
 
static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";
 

// https://www.khronos.org/opengl/wiki/OpenGL_Error
void GLAPIENTRY
MessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity,
                 GLsizei length, const GLchar* message, const void* userParam ) {
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
} 


# define KEY_ESCAPE 27
 void key_callback( unsigned char key, int x, int y ) {
  switch ( key )
  {
    case KEY_ESCAPE: // tecla ESC 
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
   spin = spin + 0.0001; // 0.000001;
   if (spin > 360.0)
      spin = 0.0; //spin - 360.0;
//    glutPostRedisplay();
}

// float ratio;
// int width, height;
//  mat4x4 m, p, mvp;
//  GLuint vertex_buffer, vertex_shader, fragment_shader, program;
//  GLint mvp_location, vpos_location, vcol_location;
//  
//  
// void display() {  // Display function will draw the image.
//         glClear(GL_COLOR_BUFFER_BIT);
// //  
//         mat4x4_identity(m); // No fa falta fer animació <-- iddle
// //         mat4x4_rotate_Z(m, m, (float) glfwGetTime());
//         spinDisplay( );
// //         mat4x4_rotate_Z(m, m, (float) spin ); //glutGet( GLUT_ELAPSED_TIME ) );
//         mat4x4_rotate_Z(m, m, spin); //1.0);
//         mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//         mat4x4_mul(mvp, p, m);
//  
//         glUseProgram(program);
//         glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
//         glDrawArrays(GL_TRIANGLES, 0, 3);
// 
// //     glutSwapBuffers(); // Required to copy color buffer onto the screen.
// //     glutPostRedisplay();    //???    
// }


// void reshape(int w, int h) {
// // Estava al prog. ppal.
// //         glfwGetFramebufferSize(window, &width, &height);
// //         ratio = width / (float) height;
// //  
// //         glViewport(0, 0, width, height);
// //         glClear(GL_COLOR_BUFFER_BIT);
//  
//     ratio = (float)w / (float)h;
//     glViewport(0, 0, width, height); //--> reshape
//     mat4x4_identity(m);
// //     mat4x4_rotate_Z(m, m, (float) glfwGetTime());
// //     mat4x4_rotate_Z(m, m, (float) glutGet( GLUT_ELAPSED_TIME ) );
//     spinDisplay( );
//     mat4x4_rotate_Z(m, m, (float) spin ); //glutGet( GLUT_ELAPSED_TIME ) );
//     
//     mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//     mat4x4_mul(mvp, p, m);
//     
// //    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
// //    glMatrixMode(GL_PROJECTION);
// //    glLoadIdentity();
// //    glOrtho(-50.0, 50.0, -50.0, 50.0, 1.0, 1.0);
// //    glOrtho(-50.0, 50.0, -50.0, 50.0, 1.0, 1.0);
// //    glMatrixMode(GL_MODELVIEW);
// //    glLoadIdentity();
//    
//    glutPostRedisplay();      //???
// } 
 

 
// int main(void) {
int main( int argc, char** argv ) { 
//     GLFWwindow* window;
    int window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
   
    glutInit(&argc, argv);               // Initialize GLUT and 
    //glutInitDisplayMode(GLUT_SINGLE);    // Use single color buffer and no depth buffer.
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);         // Size of display area, in pixels.
//     glutInitWindowPosition(100,100);     // Location of window in screen coordinates.
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
 
// Si les deixe ho he de llevar del bucle ppal. Ho deixe en el bucle per comparar en la versió GLFW
//     glutDisplayFunc(display);            // Called when the window needs to be redrawn.    
//     glutReshapeFunc(reshape);
//     glutMouseFunc(mouse);

    
    
    // NOTE: OpenGL error checks have been omitted for brevity
 
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
 
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
 
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
 
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
 
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) (sizeof(float) * 2));
    
//     while (!glfwWindowShouldClose(window)) {
    while( 1 ) {        
// reshape
       float ratio;
        int width, height;
        mat4x4 m, p, mvp;

    width = glutGet(  GLUT_WINDOW_WIDTH );
    height= glutGet(  GLUT_WINDOW_HEIGHT );
    ratio = (float)width / (float)height;
    glViewport(0, 0, width, height); //--> reshape
    mat4x4_identity(m);
//     mat4x4_rotate_Z(m, m, (float) glfwGetTime());
//     mat4x4_rotate_Z(m, m, (float) glutGet( GLUT_ELAPSED_TIME ) );
    spinDisplay( );
    mat4x4_rotate_Z(m, m, (float) spin ); //glutGet( GLUT_ELAPSED_TIME ) );
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);
// fi reshape
    
// Ara està la callback display
    glClear(GL_COLOR_BUFFER_BIT);

     glUseProgram(program);
     glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
     glDrawArrays(GL_TRIANGLES, 0, 3);
        // 
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//
        glutSwapBuffers(); // Required to copy color buffer onto the screen.        
//         glutPostRedisplay();      
        glutMainLoopEvent(); 
        
    }
 
//     glfwDestroyWindow(window);
    glutDestroyWindow( window );
//     glfwTerminate();
    exit(EXIT_SUCCESS);
}
 
