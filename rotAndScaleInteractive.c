/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      rotAndScaleInteractive.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1998 by Mitch Richling.  All rights reserved.
   @brief     Rotate interactively in an intuitive way.@EOL
   @Keywords  rotate interact mouse
   @Std       C99

   The act of allowing a user to interactively rotate an object is more complex than it first appears.  When a user moves a mouse
   down they expect the object to rotate around an axis that is parallel to the bottom of the screen, and if they move to the right
   they expect the object to rotate around an axis that is parallel to the side of the screen.  The difficulty is that it is
   non-trivial for beginners to figure out how to figure out what the appropriate rotation vectors are.  This code demonstrates one
   way to do that.  It is possible that roundoff error can throw off this method.  A more robust method is to use quaternion
   rotation interpolation.  A good example is displayed by the SGI GLUT example trackball.c
***********************************************************************************************************************************/

/**********************************************************************************************************************************/
#include <math.h>               /* Math stuff      ISOC  */
#include <stdlib.h>             /* Standard Lib    ISOC  */
#include <stdio.h>              /* I/O lib         ISOC  */

/**********************************************************************************************************************************/
/* Apple puts GLUT into a framework named GLUT, while the rest of the world just sticks GLUT into the GL include directory... */
#ifdef __APPLE__
#include <GLUT/glut.h>          /* Open GL Util    APPLE */
#else
#include <GL/glut.h>            /* Open GL Util    OpenGL*/
#endif

/**********************************************************************************************************************************/
/* MODL 1 ==> a box with axis
        2 ==> a Lorenz strange attractor
        3 ==> a Lighted Surface with shading
*/
#ifndef MODL
#define MODL 1
#endif

#if MODL == 1
#include "boxNaxis.h"
#endif

#if MODL == 2
#include "lorenzC.h"
#endif

#if MODL == 3
#include "surf.h"
#endif

/**********************************************************************************************************************************/
/* Define to 1 for anti-aliasing, 0 for none */
#ifndef ANTIA
#if  MODL != 3
#define ANTIA 1
#endif
#endif

#if MODL == 3
#define ANTIA 0
#endif

/**********************************************************************************************************************************/
/* Global state variables. */
enum interactionModeEnum {IMODE_SCALE, IMODE_ROTATE};
int xMS, yMS;
interactionModeEnum interactMode = IMODE_ROTATE;

/**********************************************************************************************************************************/
/* Upon a mouse click we store the coordinates into the global "last mouse" location.  We do this to help the motion call back know
   what the direction of motion is upon a first call.  This also helps to keep the mouse pointer from getting confused by reseting
   it upon a click.  We also set the interactMode flag so the mouse motion callback can know if it is to rotate or scale. */
void mouseCall(int button, int state, int x, int y) {
  if(button == GLUT_LEFT_BUTTON) {
    if(state == GLUT_DOWN) {
      xMS = x;
      yMS = y;
    } /* end if */
  } /* end if */
} /* end func mouseCall */

/**********************************************************************************************************************************/
/* Quit if we get a 'q' or an escape key. */
void keyboardCall(unsigned char key, int x, int y) {
  if((key=='q') || (key=='\e')) 
    exit(0);
} /* end func keyboardCall */

/**********************************************************************************************************************************/
/* On a mouse drag we rotate or scale (shift click).  We compute the direction of mouse motion, find a vector 90 degrees off of
   that, unproject it back into 3D space, and use that vector as the rotation vector.  We use the delta in mouse motion to determine
   the angle of rotation.  If we are in scale mode, then we use the y-delta to determine the scale factor. */
void motionCall(int x, int y) {
  float rz;
  double x3d, y3d, z3d;
  double x3d2, y3d2, z3d2;
  int tx1, ty1, tx2, ty2;
  GLint viewport[4];    
  GLdouble mvmatrix[16], projmatrix[16];
  GLint yFlip;
  int xdelta, ydelta;
  glGetIntegerv (GL_VIEWPORT, viewport);
  // Set the x/y delta, and pay attention to axis lock modifiers
  xdelta = xMS-x;
  ydelta = yMS-y;
  /* Note that you simply use a z-depth to rotate along a vector orthogonal to the screen. If the delta is too big, or too small,
     then we bail... */
  if( (abs(xdelta)<(viewport[2]/2-5) && abs(ydelta)<(viewport[3]/2-5)) && 
      (abs(xdelta)>=1 || abs(ydelta)>=1)) {
    /* Magnitude of the angle (180 degrees per window width)... */
    rz = -180.0*sqrt((xdelta)*(xdelta)+(ydelta)*(ydelta))/sqrt(viewport[2]*viewport[2]+viewport[3]*viewport[2]);
    /* Figure out what our direction of movement is (90 degrees off) */
    tx1 = viewport[2]/2;
    ty1 = viewport[3]/2;
    tx2 = tx1 + (ydelta);
    ty2 = ty1 + (-xdelta);
    /* Compute the world coordinate vectors corresponding to our rate of motion.. */
    glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);
    glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);
    yFlip = viewport[3] - (GLint) ty1 - 1;
    gluUnProject ((GLdouble) tx1, (GLdouble) yFlip, 0.5, mvmatrix, projmatrix, viewport, &x3d2, &y3d2, &z3d2);
    yFlip = viewport[3] - (GLint) ty2 - 1;
    gluUnProject ((GLdouble) tx2, (GLdouble) yFlip, 0.5, mvmatrix, projmatrix, viewport, &x3d, &y3d, &z3d);
    /* Subtract to compute the rotation vector */
    x3d = x3d-x3d2;
    y3d = y3d-y3d2;
    z3d = z3d-z3d2; // Always zero!
    /* Update the MODELVIEW matrix */
    glMatrixMode(GL_MODELVIEW);
    glRotatef(rz, x3d, y3d, z3d);
    /* At this point we have a new MODELVIEW matrix, so we update the display */
    glutPostRedisplay();
    /* The global position must be updated even if we don't change anything.. */
    xMS = x;
    yMS = y;
  }
} /* end func motionCall */

/**********************************************************************************************************************************/
/* How boring can a display update function be?  This is just about it! */
void displayCall() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCallList(1);
  glutSwapBuffers();
} /* end func displayCall */

/**********************************************************************************************************************************/
/* Kick it off.  Note we generate the geometry in main -- bad form, but this example is intended to illustrate how to interactively
   rotate in an intuitive way...
 */
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Interactive Rotate And Scale Demo Program");
  glutDisplayFunc(displayCall);
  glutMotionFunc(motionCall);
  glutMouseFunc(mouseCall);

  glutKeyboardFunc(keyboardCall);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(40, 1, 2*RADIUS, 10*RADIUS);

#if ANTIA
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
#endif

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 6.0*RADIUS,  // Eye
            0.0, 0.0, 0.0,         // Look at
            0.0, 1.0, 0.0);        // Up

  computeGeometry();

  /* Start it up */
  glutMainLoop();
  return 0;
} /* end func main */
