/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      surf.h
   @author    Mitch Richling <https://www.mitchr.me>
   @Copyright Copyright 2014 by Mitch Richling.  All rights reserved.
   @brief     Function that will generate a lorenz curve, bounding box, and x/y/z-axes.@EOL
   @Keywords  none
   @Std       C99
***********************************************************************************************************************************/

/**********************************************************************************************************************************/
#define RADIUS 10
#define DRAW_MODE 1
#define NUMS 150

/**********************************************************************************************************************************/
void computeGeometry() {
  double x, y, z, Dx, Dy, Dz, lenD;
  int    xi, yi, xNum, yNum;
  double xMin, xMax, yMin, yMax, xDelta, yDelta;
  double zPoints[NUMS][NUMS], xPoints[NUMS], yPoints[NUMS];
  double DzPoints[NUMS][NUMS], DxPoints[NUMS], DyPoints[NUMS];

  GLfloat mat_specular[] = { 1.0, 0.0, 1.0, 0.0 };    
  GLfloat mat_diffuse[] = { 0.7, 0.0, 1.0, 0.0 };    
  GLfloat mat_shininess[] = { 100.0 };    
  //GLfloat light_position[] = { 1.0, 1.0, 15.0, 0.0 };    
  GLfloat light_position[] = { 0.0, 0.0, 6.0*RADIUS, 1.0 };    

  glNewList(1, GL_COMPILE);
  glColor3f(1,1,1);
  glPointSize(2.0);

  xMin = yMin = -15.0;
  xMax = yMax =  15.0;
  xNum = yNum = NUMS;
  xDelta = (xMax - xMin) / xNum;
  yDelta = (yMax - yMin) / yNum;

  for(xi=0;xi<xNum;xi++) {
	x = xMin + xi * xDelta;
	for(yi=0;yi<yNum;yi++) {
	  // Compute the function: sin(x)+cos(y)
	  y = yMin + yi * yDelta;
	  z = sin(x)+cos(y);	
	  z = sin(sqrt(x*x+y*y));
	  zPoints[xi][yi] = z;
	  xPoints[xi]     = x;
	  yPoints[yi]     = y;
	  // Compute the normal: [-dz/dx, -dz/dy, 1]
	  Dx = -sin(x);
	  Dy = -cos(y);

	  Dx = cos(sqrt(x*x+y*y))*2*x/sqrt(x*x+y*y);
	  Dy = cos(sqrt(x*x+y*y))*2*y/sqrt(x*x+y*y);

	  Dz = 1;
	  lenD = sqrt(Dx*Dx+Dy*Dy+Dz*Dz);
	  if(lenD > 0) {
		Dx /= lenD;
		Dy /= lenD;
		Dz /= lenD;
	  } /* end if */
	  //Dx=Dy=0;Dz=1;
	  DzPoints[xi][yi] = Dz;
	  DxPoints[xi]     = Dx;
	  DyPoints[yi]     = Dy;
	} /* end for */
  } /* end for */

  glShadeModel(GL_SMOOTH);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  //glPolygonMode(GL_FRONT, GL_LINE);
  //glPolygonMode(GL_BACK,  GL_LINE);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  for(yi=0;yi<yNum-1;yi++) {
	glBegin(GL_TRIANGLE_STRIP);
	for(xi=0;xi<xNum;xi++) {
	  glColor3f(1, 0, 1);
	  glNormal3f(DxPoints[xi], DyPoints[yi],   DzPoints[xi][yi]);
	  glVertex3f(xPoints[xi],  yPoints[yi],    zPoints[xi][yi]);
	  glNormal3f(DxPoints[xi], DyPoints[yi+1], DzPoints[xi][yi+1]);
	  glVertex3f(xPoints[xi],  yPoints[yi+1],  zPoints[xi][yi+1]);
	} /* end for */
	glEnd();
  } /* end for */

//  glBegin(GL_POINTS);
//  for(xi=0;xi<xNum;xi++) {
//   for(yi=0;yi<yNum;yi++) {
// 	 glColor3f(1, 1, 0);
//	 glVertex3f(xPoints[xi], yPoints[yi], zPoints[xi][yi]);
//   }
//  }
//  glEnd();

  glShadeModel(GL_FLAT);
  glDisable(GL_LIGHTING);


  /* Draw the x/y/z axis */
#if 1
  glBegin(GL_LINE_STRIP);
  glColor3f(1, 0, 0);
  glVertex3f( 0, 0, 0);
  glVertex3f(15, 0, 0);
  glVertex3f( 0, 0, 0);

  glColor3f(0, 1, 0);
  glVertex3f( 0, 0, 0);
  glVertex3f(0, 15, 0);
  glVertex3f( 0, 0, 0);

  glColor3f(0, 0, 1);
  glVertex3f(0, 0,  0);
  glVertex3f(0, 0, 15);
  glEnd();
#endif

  /* Draw the box */
#if 1
  glBegin(GL_LINE_STRIP);

  glColor3f(1, 1, 1);

  glVertex3f( 15, -15, -15);
  glVertex3f( 15,  15, -15);
  glVertex3f(-15,  15, -15);
  glVertex3f(-15, -15, -15);
  glVertex3f( 15, -15, -15);

  glVertex3f( 15, -15,  15);
  glVertex3f( 15,  15,  15);
  glVertex3f(-15,  15,  15);
  glVertex3f(-15, -15,  15);
  glVertex3f( 15, -15,  15);

  glVertex3f( 15,  15,  15);
  glVertex3f( 15,  15, -15);

  glVertex3f(-15,  15, -15);
  glVertex3f(-15,  15,  15);

  glVertex3f(-15, -15,  15);
  glVertex3f(-15, -15, -15);

  glEnd();
#endif

  glEndList();
} /* end func computeGeometry */
