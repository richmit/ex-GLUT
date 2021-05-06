/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      mandelbrotIncImageGL.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1997 by Mitch Richling.  All rights reserved.
   @brief     Raster 2D drawing with OpenGL and GLUT.@EOL
   @Keywords  opengl 2d raster glut
   @Std       C99

   OpenGL can be used for raster drawing too!  This creates an image and drops it line by line into a window providing feedback
   regarding the computation for the user.  The idle callback is used to actually do the computation.  It unregisters itself when
   the computation is done so that it will no longer be called.  it would b a simple matter to add mouse support to this application
   to let users interactively zoom in on regions of the set...
***********************************************************************************************************************************/

/**********************************************************************************************************************************/
#include <math.h>               /* Math stuff      ISOC  */
#include <stdlib.h> /* Need this for abs, atoi */
#include <stdio.h>  /* Need this for printf */

/**********************************************************************************************************************************/
/* Apple puts GLUT into a framework named GLUT, while the rest of the world just sticks GLUT into the GL include directory... */
#ifdef __APPLE__
#include <GLUT/glut.h>          /* Open GL Util    APPLE */
#else
#include <GL/glut.h>            /* Open GL Util    OpenGL*/
#endif

/**********************************************************************************************************************************/
#define COLORMAG 3
#define XMAX 700
#define YMAX 700
#define MAXCOUNT 6024

/**********************************************************************************************************************************/
GLubyte *image;
int y;

/**********************************************************************************************************************************/
void reshapeCall(int h, int w) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLfloat)XMAX, 0.0, (GLfloat)YMAX);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,h,w);
} /* end func reshapeCall */

/**********************************************************************************************************************************/
void idleCall() {
  int count, x;
  float xscale, yscale, left, top, xside, yside, zx, zy, cx, cy, tempx;

  left   =  -.70;  top    =  -.50;  xside  =  .07;  yside  =  .1;
  left   =  -.67;  top    =  -.4;   xside  =  .04;  yside  =  .03;
  left   =  -.642; top    =  -.394; xside  =  .012; yside  =  .021;
  left   =     -2; top    =     -2; xside  =     4; yside  =     4;
  left   =  -.642; top    =  -.394; xside  =  .012; yside  =  .021;

  xscale = xside / XMAX;
  yscale = yside / YMAX;
  y++;
  if(y>=YMAX) {
    // It is drawn, no need to call me anymore.
    glutIdleFunc(NULL);
    return;
  } /* end if */

  for(x = 0; x < XMAX; x++) {
    cx = x * xscale + left;
    cy = y * yscale + top;
    zx = zy = 0;
    count = 0;
    while(zx * zx + zy * zy < 4 && count < MAXCOUNT) {
      tempx = zx * zx - zy * zy + cx;
      zy = 2 * zx * zy + cy;
      zx = tempx;
      count++;
    } /* end while */
    if(count < MAXCOUNT) {
      image[3*(x+y*XMAX)+0] = 255 - (count*COLORMAG)%255;
      if(count > 250) {
        image[3*(x+y*XMAX)+1] = 255;
      } else {
        image[3*(x+y*XMAX)+1] = 0;
      } /* end if/else */
      image[3*(x+y*XMAX)+2] =       (count*COLORMAG)%255;
    } else {
      image[3*(x+y*XMAX)+0] = 0;
      image[3*(x+y*XMAX)+1] = 0;
      image[3*(x+y*XMAX)+2] = 0;
    } /* end if/else */
  } /* end for */
  glutPostRedisplay();
} /* end func idleCall */

/**********************************************************************************************************************************/
void displayCall() {
  if(y<=1)
    glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2i(0,y-1);
  glDrawPixels(XMAX, 1 /*nrows*/, GL_RGB, GL_UNSIGNED_BYTE, image+(XMAX*y*3));
  glFlush();
} /* end func displayCall */

/**********************************************************************************************************************************/
int main(int argc, char *argv[]) {
  y=-1;
  image = (GLubyte*)malloc(3*sizeof(GLubyte)*XMAX*YMAX);
  if(image == NULL) {
    printf("ERROR: Could not malloc memory for image.\n");
    exit(1);
  } /* end if */

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(XMAX, YMAX);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("MandelbrotImageGL");
  glutReshapeFunc(reshapeCall);
  glutDisplayFunc(displayCall);
  glutIdleFunc(idleCall);
  glutMainLoop();
  return 0;
} /* end func main */
