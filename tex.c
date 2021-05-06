/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      tex.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1997 by Mitch Richling.  All rights reserved.
   @brief     Texture basics with OpenGL@EOL
   @Keywords  opengl 2d raster glut
   @Std       C99

   Here we illustrate mapping a texture to a square, and how to replace parts of that texture later.
***********************************************************************************************************************************/

/**********************************************************************************************************************************/
#include <math.h>   /* Math stuff      ISOC  */
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
#define    texImageWidth 512
#define    texImageHeight 512

/**********************************************************************************************************************************/
GLubyte *texImage;
static GLuint texName;

/**********************************************************************************************************************************/
#define XMAX 900
#define YMAX 900

/**********************************************************************************************************************************/
void reshapeCall(int h, int w) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0*w/h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.6);
} /* end func reshapeCall */

/**********************************************************************************************************************************/
void displayCall() {
  glBindTexture(GL_TEXTURE_2D, texName);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -2.0, 0.0);
  glTexCoord2f(0.0, 1.0); glVertex3f(-2.0,  2.0, 0.0);
  glTexCoord2f(1.0, 1.0); glVertex3f( 2.0,  2.0, 0.0);
  glTexCoord2f(1.0, 0.0); glVertex3f( 2.0, -2.0, 0.0);
  glEnd();
  glFlush();
}  /* end func displayCall */

/**********************************************************************************************************************************/
void idleCall() {
  static int offset;
  int x, y;
  glBindTexture(GL_TEXTURE_2D, texName);
  for(x=0; x<texImageWidth; x++) {
    for(y=0; y<texImageHeight; y++) {
      texImage[3*(x+y*texImageWidth)+0] = (unsigned char)(offset+x+y);
      texImage[3*(x+y*texImageWidth)+1] = (unsigned char)(offset+abs(x-y));
      texImage[3*(x+y*texImageWidth)+2] = (unsigned char)(offset+x+y);
    }
  }
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texImageWidth,
                  texImageHeight, GL_RGB,
                  GL_UNSIGNED_BYTE, texImage);

  offset+=1;
  glutPostRedisplay();
} /* end func idleCall */

/**********************************************************************************************************************************/
int main(int argc, char *argv[]) {
  int x, y;
  texImage = (GLubyte*)malloc(3*sizeof(GLubyte)*texImageWidth*texImageHeight);
  if(texImage == NULL) {
    printf("ERROR: Could not malloc memory for texImage.\n");
    exit(1);
  } /* end if */
  for(x=0; x<texImageWidth; x++)
    for(y=0; y<texImageHeight; y++) {
      texImage[3*(x+y*texImageWidth)+0] = (unsigned char)(x+y);
      texImage[3*(x+y*texImageWidth)+1] = (unsigned char)(abs(x-y));
      texImage[3*(x+y*texImageWidth)+2] = (unsigned char)(x+y);
    }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(XMAX, YMAX);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Texture");

  glClearColor (0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(1, &texName);
  glBindTexture(GL_TEXTURE_2D, texName);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, texImageWidth, texImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_FLAT);

  glutReshapeFunc(reshapeCall);
  glutDisplayFunc(displayCall);
  glutIdleFunc(idleCall);
  glutMainLoop();
  return 0;
} /* end func main */

