/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      mandelbrotGL.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1997 by Mitch Richling.  All rights reserved.
   @brief     Psudo-raster 2D vector drawing with OpenGL and GLUT.@EOL
   @Keywords  opengl 2d raster vector glut
   @Std       C99

   OpenGL can be used for fast 2D drawing by simply drawing everything with z=0 and looking right down on the x-y plane.  The OpenGL
   Utility library (GLU) has a function to help one set things up for this called gluOrtho2D.  Precice control over pixels is not
   provided -- it is a real-like plane.
***********************************************************************************************************************************/

/**********************************************************************************************************************************/
#include <math.h>               /* Math stuff      ISOC  */

/**********************************************************************************************************************************/
/* Apple puts GLUT into a framework named GLUT, while the rest of the world just sticks GLUT into the GL include directory... */
#ifdef __APPLE__
#include <GLUT/glut.h>          /* Open GL Util    APPLE */
#else
#include <GL/glut.h>            /* Open GL Util    OpenGL*/
#endif

/**********************************************************************************************************************************/
#define left  -0.6
#define top   -0.5
#define right -0.5
#define botm  -0.6

/**********************************************************************************************************************************/
/* We don't have "pixel" control, so we fake it by drawing "boxes" of pixSiz wide and seporate them by pixSep.  If pixSep<=pixSiz,
   then we have a space filling image.  Otherwise, we may see gaps between the drawn boxes.  Good values for each case are:
      - Set to 10.0 and 11.0 to get full coverage
      - Set to 10.0 and 5.0 to clearly see gaps between "pixels". 
      - Set to 1.0 and 1.5 for a "high resolution" image*/
#define pixSep 10.0
#define pixSiz 11.0

/**********************************************************************************************************************************/
void displayCall() {
  float x, y;
  float zx, zy, tempx, xdelta, ydelta;
  int count, MAXCOUNT = 150;

  xdelta = pixSep*((right)-(left))/glutGet(GLUT_WINDOW_WIDTH);
  ydelta = pixSep*((top)-(botm))/glutGet(GLUT_WINDOW_HEIGHT);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPointSize(pixSiz);
  glBegin(GL_POINTS);
  for(y=top;y>botm;y-=ydelta) {
    for(x=left;x<right;  x+=xdelta) {
      zx = zy = 0;
      count = 0;
      while(zx * zx + zy * zy < 4 && count < MAXCOUNT) {
        tempx = zx * zx - zy * zy + x;
        zy = 2 * zx * zy + y;
        zx = tempx;
        count++;
      } /* end while */
      if(count < MAXCOUNT) {
        glColor3f(1.0*count/MAXCOUNT, fabs(sin(count/5.0)), 1.0-count/MAXCOUNT);
      } else {
        glColor3f(0.0, 0.0, 0.0);
      } /* end if/else */
      glVertex2f(x, y);
    } /* end for */
  } /* end for */
  glEnd();
  glFlush();
} /* end func displayCall */

/**********************************************************************************************************************************/
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("MandelbrotGL");
  glutDisplayFunc(displayCall);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(left, right, top, botm);
  glutMainLoop();
  /*return NSApplicationMain(argc, argv); */
  return 0;
} /* end func main */
