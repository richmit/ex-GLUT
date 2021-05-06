/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      mandelbrotImageGL.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1997 by Mitch Richling.  All rights reserved.
   @brief     Raster 2D drawing with OpenGL and GLUT.@EOL
   @Keywords  opengl 2d raster glut
   @Std       C99

   OpenGL can be used for raster drawing too!  This creates an image and drops it (upside down) into a window.
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
#define COLORMAG 1
#define XMAX 500
#define YMAX 500
#define MAXCOUNT 1024

/**********************************************************************************************************************************/
GLubyte *image;

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
void displayCall() {
  int count, x, y;
  float xscale, yscale, left, top, xside, yside, zx, zy, cx, cy, tempx;

  left   =  -.70;  top    =  -.50;  xside  =  .07;  yside  =  .1;
  left   =  -.67;  top    =  -.4;   xside  =  .04;  yside  =  .03;
  left   =  -.642; top    =  -.394; xside  =  .012; yside  =  .021;
  left   =     -2; top    =     -2; xside  =     4; yside  =     4;
  left   =  -.642; top    =  -.394; xside  =  .012; yside  =  .021;

  xscale = xside / XMAX;
  yscale = yside / YMAX;
  for(y = 1; y <= YMAX; y++) {
    for(x = 1; x <= XMAX; x++) {
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
		image[3*(x+y*XMAX)+0] = (256 - count*COLORMAG)%255;
		image[3*(x+y*XMAX)+1] = 0;
		image[3*(x+y*XMAX)+2] = 0;
      } else {
		image[3*(x+y*XMAX)+0] = 0;
		image[3*(x+y*XMAX)+1] = 255;
		image[3*(x+y*XMAX)+2] = 0;
      } /* end if/else */
    } /* end for */
	fprintf(stderr, "Line %d done\n", (int)y);
  } /* end for */
  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2i(0,0);
  glDrawPixels(XMAX, YMAX, GL_RGB, GL_UNSIGNED_BYTE, image);
  glFlush();
}  /* end func displayCall */

/**********************************************************************************************************************************/
int main(int argc, char *argv[]) {
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
  glutMainLoop();
  return 0;
} /* end func main */
