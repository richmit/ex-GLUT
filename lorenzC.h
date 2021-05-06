/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      lorenzC.h
   @author    Mitch Richling <https://www.mitchr.me>
   @Copyright Copyright 1997 by Mitch Richling.  All rights reserved.
   @Revision  $Revision$ 
   @SCMdate   $Date$
   @brief     Function that will generate a lorenz curve, bounding box, and x/y/z-axes.@EOL
   @Keywords  none
   @Std       C89
***********************************************************************************************************************************/

/**********************************************************************************************************************************/
#define RADIUS 40
#define DRAW_MODE 2

/**********************************************************************************************************************************/
void computeGeometry() {
  int maxBalls    = 5000;
  double tDelta   = 0.01;
  double x = 0.11;
  double y = 0.0;
  double z = 0;
  double a = 10;
  double b = 28;
  double c = 8.0 / 3.0;
  int numBalls;
  double xNew, yNew, zNew;

  glNewList(1, GL_COMPILE);
  glColor3f(1,1,1);
  glPointSize(2.0);
#if DRAW_MODE == 3
  glBegin(GL_POINTS);
#endif
#if DRAW_MODE == 2
  glBegin(GL_LINE_STRIP);
#endif
#if DRAW_MODE == 3
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(50,0,0);
#endif
#if DRAW_MODE == 4
  glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(0,0,0);
#endif
  
  for(numBalls=0;numBalls<maxBalls;numBalls++) {
    xNew = x + a*(y-x)*tDelta;
    yNew = y + (x*(b-z)-y)*tDelta;
    zNew = z + (x*y-c*z)*tDelta;
    glColor3f(1.0*numBalls/maxBalls, 0.2, 1.0-numBalls/maxBalls);

#if (DRAW_MODE == 5)
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(xNew, yNew, zNew);
    glutSolidSphere(0.5, 5, 5);
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-xNew, -yNew, -zNew);
#endif
#if (DRAW_MODE < 5)
    glVertex3f(xNew, yNew, zNew);
#endif
#if (DRAW_MODE == 4)
    glVertex3f(xNew, yNew, zNew+1);
#endif
    
    x=xNew;
    y=yNew;
    z=zNew;
  } /* end for */
#if (DRAW_MODE < 5)
  glEnd();
#endif

// Draw the x/y/z axis
#if 1
  glBegin(GL_LINE_STRIP);
  glColor3f(1, 0, 0);
  glVertex3f( 0, 0, 0);
  glVertex3f(40, 0, 0);
  glVertex3f( 0, 0, 0);

  glColor3f(0, 1, 0);
  glVertex3f( 0, 0, 0);
  glVertex3f(0, 40, 0);
  glVertex3f( 0, 0, 0);

  glColor3f(0, 0, 1);
  glVertex3f(0, 0,  0);
  glVertex3f(0, 0, 40);
  glEnd();
#endif

// Draw the box
#if 1
  glBegin(GL_LINE_STRIP);

  glColor3f(1, 1, 1);

  glVertex3f( 40, -40, -40);
  glVertex3f( 40,  40, -40);
  glVertex3f(-40,  40, -40);
  glVertex3f(-40, -40, -40);
  glVertex3f( 40, -40, -40);

  glVertex3f( 40, -40,  40);
  glVertex3f( 40,  40,  40);
  glVertex3f(-40,  40,  40);
  glVertex3f(-40, -40,  40);
  glVertex3f( 40, -40,  40);

  glVertex3f( 40,  40,  40);
  glVertex3f( 40,  40, -40);

  glVertex3f(-40,  40, -40);
  glVertex3f(-40,  40,  40);

  glVertex3f(-40, -40,  40);
  glVertex3f(-40, -40, -40);

  glEnd();
#endif

  glEndList();
} /* end func computeGeometry */
