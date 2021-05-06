/* -*- Mode:C; Coding:us-ascii-unix; fill-column:132 -*- */
/**********************************************************************************************************************************/
/**
   @file      interact.c
   @author    Mitch Richling <https://www.mitchr.me/>
   @Copyright Copyright 1997 by Mitch Richling.  All rights reserved.
   @brief     How to get input and process it with GLUT.@EOL
   @Keywords  input mouse keyboard glut
   @Std       C99

   This little program demonstrates how to get input from the keyboard and detect various mouse events.  Also demonstrated are
   several callbacks: display callback, timer callbacks, and the idle callback.
***********************************************************************************************************************************/

/**********************************************************************************************************************************/
#include <stdio.h>              /* I/O lib         ISOC  */
#include <stdlib.h>             /* Standard Lib    ISOC  */

/**********************************************************************************************************************************/
/* Apple puts GLUT into a framework named GLUT, while the rest of the world just sticks GLUT into the GL include directory... */
#ifdef __APPLE__
#include <GLUT/glut.h>          /* Open GL Util    APPLE */
#else
#include <GL/glut.h>            /* Open GL Util    OpenGL*/
#endif

/**********************************************************************************************************************************/
static float eangle      = 0.0;
static float eangleDelta = 0.5;
static int   mainWindow;

/**********************************************************************************************************************************/
void displayCall() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 500.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glScalef(.005,.005,.005);
  glRotatef(eangle, 0, 1, 0);
  glTranslatef(-300, 0, 0);
    
  glColor3f(1,1,1);
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'H');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'l');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'l');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');

  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'W');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'r');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'l');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'd');
  glutStrokeCharacter(GLUT_STROKE_ROMAN, '!');
        
  glutSwapBuffers();
} /* end func displayCall */

/**********************************************************************************************************************************/
/* Called when a key is released... */
void keyboardUpCall(unsigned char key, int x, int y) {
} /* end func keyboardUpCall */

/**********************************************************************************************************************************/
/* Key presses */
void keyboardCall(unsigned char key, int x, int y) {
  char *m;
  int kbMod;
  /* Can only be called during mouse callback or kbd callback. */
  kbMod = glutGetModifiers();
  if(kbMod == GLUT_ACTIVE_SHIFT) {
    m = "SHIFT";
  } else if(kbMod == GLUT_ACTIVE_CTRL) {
    m = "CTRL";
  } else if(kbMod == GLUT_ACTIVE_ALT) {
    m = "ALR";
  } else {
    m = "NONE";
  } /* end if */
  printf("KEY: %c with mod: %s\n", key, m);
} /* end func keyboardCall */

/**********************************************************************************************************************************/
/* Special Key presses */
void specialCall(int key, int x, int y) {
  if       (key == GLUT_KEY_F1       ) { printf("KEY: F1        ");
  } else if(key == GLUT_KEY_F2       ) { printf("KEY: F2        ");
  } else if(key == GLUT_KEY_F3       ) { printf("KEY: F3        ");
  } else if(key == GLUT_KEY_F4       ) { printf("KEY: F4        ");
  } else if(key == GLUT_KEY_F5       ) { printf("KEY: F5        ");
  } else if(key == GLUT_KEY_F6       ) { printf("KEY: F6        ");
  } else if(key == GLUT_KEY_F7       ) { printf("KEY: F7        ");
  } else if(key == GLUT_KEY_F8       ) { printf("KEY: F8        ");
  } else if(key == GLUT_KEY_F9       ) { printf("KEY: F9        ");
  } else if(key == GLUT_KEY_F10      ) { printf("KEY: F10       ");
  } else if(key == GLUT_KEY_F11      ) { printf("KEY: F11       ");
  } else if(key == GLUT_KEY_F12      ) { printf("KEY: F12       ");
  } else if(key == GLUT_KEY_LEFT     ) { printf("KEY: LEFT      ");
  } else if(key == GLUT_KEY_UP       ) { printf("KEY: UP        ");
  } else if(key == GLUT_KEY_RIGHT    ) { printf("KEY: RIGHT     ");
  } else if(key == GLUT_KEY_DOWN     ) { printf("KEY: DOWN      ");
  } else if(key == GLUT_KEY_PAGE_UP  ) { printf("KEY: PAGE_UP   ");
  } else if(key == GLUT_KEY_PAGE_DOWN) { printf("KEY: PAGE_DOWN ");
  } else if(key == GLUT_KEY_HOME     ) { printf("KEY: HOME      ");
  } else if(key == GLUT_KEY_END      ) { printf("KEY: END       ");
  } else if(key == GLUT_KEY_INSERT   ) { printf("KEY: INSERT    ");
  } else                               { printf("KEY: UNKNOWN   ");
  }
  printf("AT: (%d,%d)\n", x, y);
} /* end func specialCall */

/**********************************************************************************************************************************/
/* Mouse clicks */
void mouseCall(int button, int state, int x, int y) {
  char *b, *m;
  int kbMod;

  if       (button == GLUT_LEFT_BUTTON)   {  /* MacOS X: Ctr-Click */
    b = "left button";
  } else if(button == GLUT_MIDDLE_BUTTON) {  /* MacOS X: Opt-Click */
    b = "middle button";
  } else if(button == GLUT_RIGHT_BUTTON)  {  /* MacOS X: Click */
    b = "right button";
  } else {
    b = "unknown";
  } /* end if/else */

  /* Can only be called during mouse callback or kbd callback.  Note that menu binding will capture clicks before they get here.
     Also note that on some platforms, MacOS X, mouse buttons may be emulated with various combinations of keys and the single mouse
     button -- so ctrl-click and alt-click may not be possible.  Shift-click is almost always possible.*/
  kbMod = glutGetModifiers();
  if(kbMod == GLUT_ACTIVE_SHIFT) {
    m = "SHIFT";
  } else if(kbMod == GLUT_ACTIVE_CTRL) {
    m = "CTRL";
  } else if(kbMod == GLUT_ACTIVE_ALT) {
    m = "ALR";
  } else {
    m = "NONE";
  } /* end if/else */

  if(state == GLUT_DOWN) {
    printf("Mouse Depress: b(%s/%d/%s)@(%d,%d)\n", b, button, m, x, y);
  } else if(state == GLUT_UP) {
    printf("Mouse Release: b(%s/%d/%s)@(%d,%d)\n", b, button, m, x, y);
  } else {
    printf("Unknown Mouse Click Event: b(%d/%s)@(%d,%d)\n", button, m, x, y);
  } /* end if/else */
}  /* end func mouseCall */

/**********************************************************************************************************************************/
/* Mouse move with button press */
void motionCall(int x, int y) {
  static int notInit;
  static int oldX;
  static int oldY;
  if(notInit) {
    printf("MOTION: (%d,%d) -> (%d,%d)\n", oldX, oldY, x, y);  
    oldX = x;
    oldY = y;
  } else {
    printf("MOTION: (%d,%d)\n", x, y);  
    oldX = x;
    oldY = y;
    notInit = 1;
  } /* end if/else */
} /* end func motionCall */

/* Mouse move with button press */
void joystickCall(unsigned int buttonMask, int x, int y, int z) {
  printf("JOYSTICK: %ud @ (%d,%d,%d)\n", buttonMask, x, y, z);
} /* end func joystickCall */

/*  Spaceball translation.. Passive. x, y, and z are normalized to [-1000,1000]*/
void spaceballMotionCall(int x, int y, int z) {
  printf("SPACEBALL TRN: (%d,%d,%d)\n", x, y, z);
} /* end func spaceballMotionCall */

/*  Spaceball translation.. Passive. x, y, and z are normalized to [-1000,1000]*/
void spaceballRotateFunc(int x, int y, int z) {
  printf("SPACEBALL ROT: (%d,%d,%d)\n", x, y, z);
} /* end func spaceballRotateFunc */

/**********************************************************************************************************************************/
/*  What to do for spaceball buttons.. */
void spaceballButtonFunc(int button, int state) {
  printf("SPACEBALL BUTTONS:  Button: %d    State: %d\n", button, state);
} /* end func spaceballButtonFunc */

/**********************************************************************************************************************************/
void menuCall(int value) {
  printf("MENU: %d\n", value);
  if       (value == 20) {
    eangle = 0;
  } else if(value == 21) {
  } else if(value == 10) {
    glutPostRedisplay();
  } else if(value == 11) {
    glutDestroyWindow(mainWindow);
    exit(0);
  } else if(value == 0) {
    printf("Hello to you too!!");
  } /* end if/else */
} /* end func menuCall */

/**********************************************************************************************************************************/
void passiveMotionCall(int x, int y) { 
  printf("PASSIVE MOTION: (%d,%d)\n", x, y);  
} /* end func passiveMotionCall */

/**********************************************************************************************************************************/
void entryCall(int state) {
  if(state == GLUT_LEFT) {
    printf("ENTRY/EXIT EVENT: LEFT\n");
  } else if(state == GLUT_ENTERED) {
    printf("ENTRY/EXIT EVENT: ENTERED\n");
  } else {
    printf("UNKNOWN ERROR: glutEntryFunc\n");
  } /* end if/else */
} /* end func entryCall */

/**********************************************************************************************************************************/
void buildMenu() {
  int subMenu1, subMenu2;
  int mainMenu;

  subMenu1 = glutCreateMenu(menuCall);
  glutAddMenuEntry("Redraw", 10);
  glutAddMenuEntry("Quit",   11);

  subMenu2 = glutCreateMenu(menuCall);
  glutAddMenuEntry("Reset Angle", 20);
  glutAddMenuEntry("Reset Size",  21);

  mainMenu = glutCreateMenu(menuCall);
  glutAddMenuEntry("Hello", 0);
  glutAddSubMenu("Reset", subMenu2);
  glutAddSubMenu("System", subMenu1);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

} /* end func buildMenu */

/**********************************************************************************************************************************/
/* Call when we do nothing...  Don't do too much in this function.  It is best to use the timerFunction to do things like rotate as
 that gives precise control over call rate..*/
void idleCall() {
  /* 
  eangle += eangleDelta;
  if(eangle >= 360.0)
    eangle -= 360.0;
   glutPostRedisplay();
  */
} /* end func idleCall */

/**********************************************************************************************************************************/
/* call periodically called -- can have lots of them, and they must be re-registered each time they are called.  Using a timer for
   animation, instead of glutIdleFunc, makes the animation uniform across platforms and will use MUCH less CPU on higher performance
   platforms... */
void timerCall(int value) {
  eangle += eangleDelta;
  if(eangle >= 360.0)
    eangle -= 360.0;
   glutPostRedisplay();
   /* Note we have to start the timer up again after it fires. */
   glutTimerFunc(50 /*msecs*/, timerCall, 0 /*value to pass*/);
   /*printf("TIMER CALL\n");*/
} /* end func timerCall */

/**********************************************************************************************************************************/
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(300, 200);
  mainWindow = glutCreateWindow("User Interaction Demo");
  glutDisplayFunc(displayCall);
/*  glutIdleFunc(idleCall); */
  glutTimerFunc(50 /*msecs*/, timerCall, 0 /*value to pass*/);
  glutKeyboardFunc(keyboardCall);

/* Use the following to detect key releases
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  glutKeyboardUpFunc(keyboardUpCall);
*/

  glutSpecialFunc(specialCall);
  glutMotionFunc(motionCall);
/*  glutPassiveMotionFunc(passiveMotionCall); */
  glutMouseFunc(mouseCall);
  glutEntryFunc(entryCall);
/*  glutJoystickFunc(joystickCall, 1000); */
  glutSpaceballMotionFunc(spaceballMotionCall);
  glutSpaceballRotateFunc(spaceballRotateFunc);
  glutSpaceballButtonFunc(spaceballButtonFunc);
  buildMenu();
  glutMainLoop();
  return 0;
} /* end func main */
