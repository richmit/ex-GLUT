/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      tformColor.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1997 by Mitch Richling.  All rights reserved.
   @brief     Demonstrate how colors mix in openGL.  @EOL
   @Keywords  color mix opengl glut
   @Std       C99
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
static float angle = 0;
static float angleDelta = 0.3;
static float eangle = 0.0;
static float eangleDelta = 0.1;

/**********************************************************************************************************************************/
void displayCall() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 5.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glRotatef(eangle, 0, 1, 0);
  glRotatef(angle, 0, 0, 1);

  glBegin(GL_POLYGON);
  glColor3f(fabs(sin(angle/60)), fabs(sin(angle/60)), fabs(cos(angle/60)));
  glVertex2f(1.0, 1.0);
  glColor3f(fabs(sin(angle/60)), fabs(cos(angle/60)), fabs(sin(angle/60)));
  glVertex2f(-1.0, 1.0);
  glColor3f(fabs(cos(angle/60)), fabs(sin(angle/60)), fabs(sin(angle/60)));
  glVertex2f(-1.0, -1.0);
  glColor3f(fabs(cos(angle/60)), fabs(sin(angle/60)), fabs(cos(angle/60)));
  glVertex2f(1.0, -1.0);
  glEnd();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glRotatef(eangle, 0, 1, 0);

  glColor3f(1,0,0);
  glutSolidCube(0.5);
  glColor3f(0,0,0);
  glutWireCube(0.5);

  glutSwapBuffers();
} /* end func displayCall */

/**********************************************************************************************************************************/
void idleCall() {
  eangle += eangleDelta;
  if(eangle >= 360.0)
    eangle -= 360.0;
  angle += angleDelta;
  if(angle >= 360.0)
    angle -= 360.0;
  if(angle <= 0)
    angle += 360.0;
  glutPostRedisplay();
} /* end func idleCall */

/**********************************************************************************************************************************/
void processKeyCall(unsigned char key, int x, int y) {
  angleDelta = -angleDelta;
} /* end func processKeyCall */

/**********************************************************************************************************************************/
void reshapeCall(int width, int height) {
} /* end func reshapeCall */

/**********************************************************************************************************************************/
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(300, 200);
  glutCreateWindow("Demo Prog");
  glutDisplayFunc(displayCall);
  glutReshapeFunc(reshapeCall);
  glutIdleFunc(idleCall);
  glutKeyboardFunc(processKeyCall);
  glutMainLoop();
  /*return NSApplicationMain(argc, argv); */
  return 0;
} /* end func main */
