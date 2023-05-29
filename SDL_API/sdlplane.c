/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain.
   
*/
/*
 * SDL OpenGL Tutorial.
 * (c) Michael Vance, 2000
 * briareos@lokigames.com
 *
 * Distributed under terms of the LGPL.  
 */
// gcc sdlplane.c   -o sdlplane `pkg-config sdl2 --cflags --libs` -lGLU -lGL -lm

// SDL Wiki
// Simple DirectMedia Layer 2.0
// https://wiki.libsdl.org/SDL2/
// https://wiki.libsdl.org/wiki/index


// https://www.khronos.org/opengl/wiki/Tutorial1:_Creating_a_Cross_Platform_OpenGL_3.2_Context_in_SDL_(C_/_SDL)
// ???

#include <stdlib.h>
#include <stdio.h>
#ifndef WIN32
#include <unistd.h>
#else
#define random rand
#define srandom srand
#endif
#include <math.h>

//#include <GL/glut.h>
// #include <SDL/SDL.h>
// https://stackoverflow.com/questions/34738439/problems-compiling-with-sdl2-in-c
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>






/* Some <math.h> files do not define M_PI... */
#ifndef M_PI
#define M_PI 3.14159265
#endif
#ifndef M_PI_2
#define M_PI_2 1.57079632
#endif

GLboolean appFuncionant = GL_TRUE;
GLboolean moving = GL_FALSE;

#define MAX_PLANES 150  // 15 inicialmente!!!

struct {
  float speed;          /* zero speed means not flying */
  GLfloat red, green, blue;
  float theta;
  float x, y, z, angle;
} planes[MAX_PLANES];

#define v3f glVertex3f  /* v3f was the short IRIS GL name for
                           glVertex3f */

void
draw(void)
{
  GLfloat red, green, blue;
  int i;

  glClear(GL_DEPTH_BUFFER_BIT);
  /* paint black to blue smooth shaded polygon for background */
  glDisable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 0.0);
  v3f(-20, 20, -19);
  v3f(20, 20, -19);
  glColor3f(0.0, 0.0, 1.0);
  v3f(20, -20, -19);
  v3f(-20, -20, -19);
  glEnd();
  /* paint planes */
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);
  for (i = 0; i < MAX_PLANES; i++)
    if (planes[i].speed != 0.0) {
      glPushMatrix();
      glTranslatef(planes[i].x, planes[i].y, planes[i].z);
      glRotatef(290.0, 1.0, 0.0, 0.0);
      glRotatef(planes[i].angle, 0.0, 0.0, 1.0);
      glScalef(1.0 / 3.0, 1.0 / 4.0, 1.0 / 4.0);
      glTranslatef(0.0, -4.0, -1.5);
      glBegin(GL_TRIANGLE_STRIP);
      /* left wing */
      v3f(-7.0, 0.0, 2.0);
      v3f(-1.0, 0.0, 3.0);
      glColor3f(red = planes[i].red, green = planes[i].green,
        blue = planes[i].blue);
      v3f(-1.0, 7.0, 3.0);
      /* left side */
      glColor3f(0.6 * red, 0.6 * green, 0.6 * blue);
      v3f(0.0, 0.0, 0.0);
      v3f(0.0, 8.0, 0.0);
      /* right side */
      v3f(1.0, 0.0, 3.0);
      v3f(1.0, 7.0, 3.0);
      /* final tip of right wing */
      glColor3f(red, green, blue);
      v3f(7.0, 0.0, 2.0);
      glEnd();
      glPopMatrix();
    }
//   glutSwapBuffers();
  
//   SDL_GL_SwapBuffers( ); --> millor al bucle ppal.

}

void
tick_per_plane(int i)
{
  float theta = planes[i].theta += planes[i].speed;
  planes[i].z = -9 + 4 * cos(theta);
  planes[i].x = 4 * sin(2 * theta);
  planes[i].y = sin(theta / 3.4) * 3;
  planes[i].angle = ((atan(2.0) + M_PI_2) * sin(theta) - M_PI_2) * 180 / M_PI;
  if (planes[i].speed < 0.0)
    planes[i].angle += 180;
}

void
add_plane(void)
{
  int i;

  for (i = 0; i < MAX_PLANES; i++)
    if (planes[i].speed == 0) {

     // Com saps quants n'hi han, el primer que topeta a velocitat 0 li la canvia i eixirà oer el 'return'
     printf(" #avions == %d.\n", i);
         
#define SET_COLOR(r,g,b) \
	planes[i].red=r; planes[i].green=g; planes[i].blue=b;

      switch (random() % 6) {
      case 0:
        SET_COLOR(1.0, 0.0, 0.0);  /* red */
        break;
      case 1:
        SET_COLOR(1.0, 1.0, 1.0);  /* white */
        break;
      case 2:
        SET_COLOR(0.0, 1.0, 0.0);  /* green */
        break;
      case 3:
        SET_COLOR(1.0, 0.0, 1.0);  /* magenta */
        break;
      case 4:
        SET_COLOR(1.0, 1.0, 0.0);  /* yellow */
        break;
      case 5:
        SET_COLOR(0.0, 1.0, 1.0);  /* cyan */
        break;
      }
      planes[i].speed = ((float) (random() % 20)) * 0.001 + 0.02;
      if (random() & 0x1)
        planes[i].speed *= -1;
      planes[i].theta = ((float) (random() % 257)) * 0.1111;
      tick_per_plane(i);
//       if (!moving)
//         glutPostRedisplay();
      return;
    }
}

void
remove_plane(void)
{
  int i;

  for (i = MAX_PLANES - 1; i >= 0; i--)
    if (planes[i].speed != 0) {
      planes[i].speed = 0;
//       if (!moving)
//         glutPostRedisplay();
      return;
    }
}

void
tick(void)
{
  int i;

  for (i = 0; i < MAX_PLANES; i++)
    if (planes[i].speed != 0.0)
      tick_per_plane(i);
}

void
animate(void)
{
  tick();
//   glutPostRedisplay();
}

void
visible(int state)
{
//   if (state == GLUT_VISIBLE) {
//     if (moving)
//       glutIdleFunc(animate);
//   } else {
//     if (moving)
//       glutIdleFunc(NULL);
//   }
}

// /* ARGSUSED1 */
// void
// keyboard(unsigned char ch, int x, int y)
// {
//   switch (ch) {

// //    case 'p':
// // // glutPopWindow, glutPushWindow
// //   break;
// 
//    case 's':
//    glutShowWindow();
//   break;
//    case 'd':
//    glutHideWindow();   // Hide Total!!! A on s'en va???
//   break;
//   case 'w':
//    glutIconifyWindow();
//   break;
// 
//   case 'i':
//     glutSetIconTitle( "Canviant el titol de l'icono"); // ???
//   break;
//   }
// }

int elIDCursor = SDL_SYSTEM_CURSOR_ARROW; //GLUT_CURSOR_RIGHT_ARROW;
int pantallaCompleta = 0;

SDL_Window *sdlFinestra;
    

static void quit_tutorial( int code )
{
    /*
     * Quit SDL so we can release the fullscreen
     * mode and restore the previous video settings,
     * etc.
     */
    SDL_Quit( );

    /* Exit program. */
    exit( code );
}

SDL_Cursor *elCursor;
// static void handle_key_down( SDL_keysym* keysym )
static void handle_key_down( SDL_Keysym* keysym )
{

    /* 
     * We're only interested if 'Esc' has
     * been presssed.
     *
     * EXERCISE: 
     * Handle the arrow keys and have that change the
     * viewing position/angle.
     */
    switch( keysym->sym ) {
    case SDLK_ESCAPE:
        quit_tutorial( 0 );
        break;

//     case SDLK_SPACE:
// //         should_rotate = !should_rotate;
//         break;
 
    case SDLK_a:
        add_plane();
        break;
    case SDLK_r:
        remove_plane();
        break;

    case SDLK_m:
        moving = !moving;
        break;

    case SDLK_SPACE:
        if (!moving) {
         tick();
        }
        break;
        
    case SDLK_f:
        pantallaCompleta = !pantallaCompleta; 
        if ( pantallaCompleta )
           SDL_SetWindowFullscreen( sdlFinestra, SDL_WINDOW_FULLSCREEN_DESKTOP );
        else
           SDL_SetWindowFullscreen( sdlFinestra, 0 );        
        break;

    case SDLK_t:
        SDL_SetWindowTitle(sdlFinestra, "Canviant el títol!");
        break;
//       
        
    case SDLK_h:
      printf("Ajuda\n\
       h\t Esta ajuda\n\
       a\t  add_plane()\n\
       r\t  remove_plane()\n\
       m o SPACE\t MOVING\n\
       f\t  Fullscreen\n\
       c\t  SetCursor\n\
       o\t  ShowCursor\n\
       s\t  ?ShowWindow\n\
       d\t  ?HideWindow   // Hide Total!!! A on s'en va???\n\
       w\t  ?IconifyWindow\n\
       t\t Cambia el título de la ventana\n\
       i\t ?Cambia el título del icono???\n\
       ESC\t finaliza la aplicación \n");
      break;

    case SDLK_c:
       elCursor = SDL_CreateSystemCursor( elIDCursor++ );
       SDL_SetCursor( elCursor );
       if ( elIDCursor > SDL_SYSTEM_CURSOR_HAND )
         elIDCursor = SDL_SYSTEM_CURSOR_ARROW ;
    break;
        
        
        
//     https://wiki.libsdl.org/SDL2/SDL_Keycode    
//    SDLK_RETURN
   

// http://wiki.libsdl.org/SDL2/SDL_SetCursor
    case SDLK_o:
       if ( SDL_ShowCursor( SDL_QUERY ) == SDL_ENABLE )
           SDL_ShowCursor( SDL_DISABLE );
       else
           SDL_ShowCursor( SDL_ENABLE );

    break;

//  SDL_ShowSimpleMessageBox().
//  http://wiki.libsdl.org/SDL2/SDL_ShowSimpleMessageBox
//  int SDL_ShowMessageBox(const SDL_MessageBoxData *messageboxdata, int *buttonid);
//  http://wiki.libsdl.org/SDL2/SDL_ShowMessageBox
    case SDLK_b:
       SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error???", "Mensatge per a l'error.", sdlFinestra );       
       SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_WARNING, "Warning???", "Mensatge per a l'avís.", sdlFinestra );
       SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_INFORMATION, "Informacio???", "Mensatge per a informar.", sdlFinestra );
       
//        SDL_MessageBoxColor
    break;
 
//     https://github.com/mlabbe/nativefiledialog
//     Native File Dialog
//     A tiny, neat C library that portably invokes native file open, folder select and save dialogs. Write dialog code once and have it pop up native dialogs on all supported platforms. Avoid linking large dependencies like wxWidgets and qt.

//     https://github.com/samhocevar/portable-file-dialogs    
//   Portable File Dialogs
// A free C++11 file dialog library.  
    
    default:
        break;
    }

}


// Play a sound with SDL2 (mo SDL_Mixer) <https://gist.github.com/armornick/3447121>
// Using SDL_AudioStream <https://wiki.libsdl.org/SDL2/Tutorials-AudioStream>
// Playing a WAV File Using SDL2 <https://gigi.nullneuron.net/gigilabs/playing-a-wav-file-using-sdl2/>


static void process_events( void )
{
    /* Our SDL event placeholder:: https://wiki.libsdl.org/SDL2/SDL_Event */
    SDL_Event event;

    /* Grab all the events off the queue. */
    while( SDL_PollEvent( &event ) ) {

      switch( event.type ) {
        case SDL_KEYDOWN:
            /* Handle key presses. */
            handle_key_down( &event.key.keysym );
            break;
            
         case SDL_WINDOWEVENT:
          if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
            glViewport(0, 0, event.window.data1, event.window.data2); //windowWidth, windowHeight); 
           }
           break;
           
        // Atres:
//         case SDL_MOUSEBUTTONDOWN:
//             printf("SDL_MOUSEBUTTONDOWN %d button %s state %d click, %d,%d (x,y) \n", 
//                    event.button, event.state, event.clicks, event.x, event.y );
// //             if (event.button.button == SDL_BUTTON_RIGHT)
// // 			{   }
// 			break; 
// SDL_TOUCH_MOUSEID
//     SDL_MouseMotionEvent 
//     SDL_MouseWheelEvent 
//     SDL_GetMouseState 
//     SDL_GetRelativeMouseState       
//         case SDL_MOUSEBUTTONUP:
//             printf("SDL_MOUSEBUTTONUP %d button %s state %d click, %d,%d (x,y) \n", 
//                    event.button, (event.state==SDL_PRESSED? "SDL_PRESSED":"SDL_RELEASED"), 
//                    event.click, event.x, event.y );
// 			break; 
        //    
// SDL_PushEvent(&user_event);    https://wiki.libsdl.org/SDL2/SDL_Event#push        
        case SDL_QUIT:
            /* Handle quit requests (like Ctrl-c). */
            SDL_DestroyWindow( sdlFinestra );
            quit_tutorial( 0 );
//             SDL_Quit();

            break;
      }

    }

}


/*
#define ADD_PLANE	    1
#define REMOVE_PLANE    2
#define MOTION_ON	    3
#define MOTION_OFF	    4
#define QUIT		    5*/

// void
// menu(int item)
// {
//   switch (item) {
//   case ADD_PLANE:
//     add_plane();
//     break;
//   case REMOVE_PLANE:
//     remove_plane();
//     break;
//   case MOTION_ON:
//     moving = GL_TRUE;
//     printf("menu: moving ON %d\n", moving);
// //     glutChangeToMenuEntry(3, "Motion off", MOTION_OFF);
// //     glutIdleFunc(animate);
//     break;
//   case MOTION_OFF:
//     moving = GL_FALSE;
//     printf("menu: moving OFF %d\n", moving);
// //     glutChangeToMenuEntry(3, "Motion", MOTION_ON);
// //     glutIdleFunc(NULL);
//     break;
//   case QUIT:
//     exit(0);
//     break;
//   }
// }


// /*
//  * GLUT_MENU_IN_USE for its value parameter when pop-up menus are in use by the user; and the callback will be called with the value GLUT_MENU_NOT_IN_USE for its status parameter when pop-up menus are no longer in use.
//  * 
//  * https://www.lighthouse3d.com/tutorials/glut-tutorial/modifying-a-menu/
// */
// void menuStatusFunc( int status, int x, int y )  {
//     if ( status == GLUT_MENU_IN_USE )  {
//         printf("menuStatusFunc GLUT_MENU_IN_USE\n");
// //         printf("menuStatusFunc %d\n", moving);
// //         if ( moving )
// //             glutChangeToMenuEntry(3, "Motion off", MOTION_OFF); 
// //         else
// //             glutChangeToMenuEntry(3, "Motion", MOTION_ON);                         
// //         
// //         glutPostRedisplay();
//     }
//      
// 
//     if ( status == GLUT_MENU_NOT_IN_USE ) {
//         printf("menuStatusFunc GLUT_MENU_NOT_IN_USE\n");
//         printf("menuStatusFunc %d\n", moving);
//         if ( moving )
//             glutChangeToMenuEntry(3, "Motion off", MOTION_OFF); 
//         else
//             glutChangeToMenuEntry(3, "Motion", MOTION_ON);                         
//         
// //         glutPostRedisplay();
//     }
// }
 
int
main(int argc, char *argv[])
{
//   glutInit(&argc, argv);
//   /* use multisampling if available */
//   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
//   glutCreateWindow("glutplane");
//   glutDisplayFunc(draw);
//   glutKeyboardFunc(keyboard);
// 
//   glutVisibilityFunc(visible);
//   glutCreateMenu(menu);
//   glutAddMenuEntry("Add plane", ADD_PLANE);
//   glutAddMenuEntry("Remove plane", REMOVE_PLANE);
//   glutAddMenuEntry("Motion", MOTION_ON);
//   glutAddMenuEntry("Quit", QUIT);
//   glutAttachMenu(GLUT_RIGHT_BUTTON);
//   
//   glutMenuStatusFunc( menuStatusFunc );
     /* Information about the current video settings. */
//     const SDL_VideoInfo* info = NULL;

    /* Dimensions of our window. */
    int width = 0;
    int height = 0;
    /* Color depth in bits of our window. */
    int bpp = 0;
    /* Flags we will pass into SDL_SetVideoMode. */
    int flags = 0;

    /* First, initialize SDL's video subsystem. */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        /* Failed, exit. */
        fprintf( stderr, "Video initialization failed: %s\n",
             SDL_GetError( ) );
        quit_tutorial( 1 );
    }

    /*
     * Set our width/height to 640/480 (you would
     * of course let the user decide this in a normal
     * app). We get the bpp we will request from
     * the display. On X11, VidMode can't change
     * resolution, so this is probably being overly
     * safe. Under Win32, ChangeDisplaySettings
     * can change the bpp.
     */
    width = 640;
    height = 480;
//     bpp = info->vfmt->BitsPerPixel;

    /*
     * Now, we want to setup our requested
     * window attributes for our OpenGL window.
     * We want *at least* 5 bits of red, green
     * and blue. We also want at least a 16-bit
     * depth buffer.
     *
     * The last thing we do is request a double
     * buffered window. '1' turns on double
     * buffering, '0' turns it off.
     *
     * Note that we do not use SDL_DOUBLEBUF in
     * the flags to SDL_SetVideoMode. That does
     * not affect the GL attribute state, only
     * the standard 2D blitting setup.
     */
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

//     http://wiki.libsdl.org/SDL2/MigrationGuide
//     http://wiki.libsdl.org/SDL2/SDL_CreateWindow
    sdlFinestra = SDL_CreateWindow("sdl2plane",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          width, height,
                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
//                           SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
//                              SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (sdlFinestra == NULL) {
      fprintf(stderr, "could not create window: %s\n", SDL_GetError());
      return 1;
    }
 
    
    SDL_GL_CreateContext( sdlFinestra );
     
    SDL_Renderer *renderer = SDL_CreateRenderer(sdlFinestra , -1, 0);

    /*
     * At this point, we should have a properly setup
     * double-buffered window for use with OpenGL.
     */
 
  /* setup OpenGL state */
  glClearDepth(1.0);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20);
  glMatrixMode(GL_MODELVIEW);
  /* add three initial random planes */
  srandom(getpid());
  add_plane();
  add_plane();
  add_plane();
  /* start event processing */
//   glutMainLoop();
    /*
     * Now we want to begin our normal app process--
     * an event loop with a lot of redrawing.
     */
    while( 1 ) {
        /* Process incoming events. */
        process_events( );
        /* Draw the screen. */
//         draw_screen( );
        draw();
        if ( moving ) {
           animate();
        }
//      SDL_GL_SwapBuffers( );
     SDL_GL_SwapWindow( sdlFinestra );
     SDL_Delay( 25 ); //ms
     
    }

  
  
  return 0;             /* ANSI C requires main to return int. */
}
