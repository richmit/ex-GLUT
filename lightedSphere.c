/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      lightedSphere.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1997 by Mitch Richling.  All rights reserved.
   @brief     lighted poly shadeing   @EOL
   @Keywords  none
   @Std       C99

   Demonstrates how to draw filled polygons and how to place a light.
***********************************************************************************************************************************/

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
  GLfloat specMat[] = {1,1,1,1};
  GLfloat shnyMat[] = { 50 };
  GLfloat lightPos[] = {2, 2, 2, 0};
  GLfloat whiteLight[] = { 1, 1, 1, 1};
  GLfloat ambLight[] = { 0.51, 0.51, 0.51, 1.0};

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glMaterialfv(GL_FRONT, GL_SPECULAR, specMat);
  glMaterialfv(GL_FRONT, GL_SHININESS, shnyMat);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambLight);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 5.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glRotatef(eangle, 0, 1, 0);
  glRotatef(angle, 0, 0, 1);

  glColor3f(1,0,0);
  glutSolidSphere(1.0, 20, 20);
    
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
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(300, 200);
  glutCreateWindow("Demo Prog");
  glutDisplayFunc(displayCall);
  glutIdleFunc(idleCall);
  glutKeyboardFunc(processKeyCall);
  glutMainLoop();
  return 0;
} /* end func main */
