#include <windows.h>
#include <GL/glut.h>
#ifdef __APPLE__
#else
#endif
#include<stdlib.h>

void display() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glOrtho(-1, 1, -1, 1, -1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

    // Top left rectangle
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-1.0f, 0.5f);
    glVertex2f(-0.1f, 0.5f);
    glVertex2f(-0.1f, 0.1f);
    glVertex2f(-1.0f, 0.1f);
    glEnd();

    // Top right rectangle
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.6f);
    glVertex2f(0.1f, 0.5f);
    glVertex2f(1.0f, 0.5f);
    glVertex2f(1.0f, 0.1f);
    glVertex2f(0.1f, 0.1f);
    glEnd();

    // Bottom left rectangle
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.9f);
    glVertex2f(-1.0f, -0.1f);
    glVertex2f(-0.1f, -0.1f);
    glVertex2f(-0.1f, -0.5f);
    glVertex2f(-1.0f, -0.5f);
    glEnd();

    // Bottom right rectangle
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(1.0f, -0.1f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(0.1f, -0.5f);
    glEnd();
    glFlush();
}
void circle()
    {
      glutSolidSphere(0.3,100,2);
      glColor3f(0.7000, 0.0000, 0.0000);
      glEnd();
      glFlush();
    }

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutCreateWindow("Simple Square");
  glutInitWindowSize(320, 320);
  glutInitWindowPosition(50, 50);
  glutDisplayFunc(display);
  glutIdleFunc(circle);
  glutMainLoop();

  return 0;
}
//Finish the code
