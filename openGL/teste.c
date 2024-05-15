#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
int numVertices = 0;
int vertices[10][2];

void displayDDA(void);
void displayPM(void);
void iniciarDDA(void);
void iniciarPM(void);
void keyboard(unsigned char key, int x, int y);

int DDA, PM, PMC; // Variáveis das janelas gráficas

void A_DDA(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int passos = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = (float)dx / (float)passos;
    float yInc = (float)dy / (float)passos;
    float x = (float)x1;
    float y = (float)y1;
    glBegin(GL_POINTS);
    for (int i = 0; i <= passos; i++)
    {
        glVertex2i(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}

void A_PM(int x1, int y1, int x2, int y2)
{
  int dx = x2 - x1;
  int dy = y2 - y1;
  int x = x1;
  int y = y1;

  glBegin(GL_POINTS);
  if (abs(dx) > abs(dy))
  {
    int d = 2 * abs(dy) - abs(dx);
    int incrE = 2 * abs(dy);
    int incrNE = 2 * (abs(dy) - abs(dx));
    glVertex2i(x, y);
    while (x < x2)
    {
      if (d <= 0)
      {
        d += incrE;
      }
      else
      {
        d += incrNE;
        y += (dy >= 0 ? 1 : -1);
      }
      x++;
      glVertex2i(x, y);
    }
  }
  else
  {
    int d = 2 * abs(dx) - abs(dy);
    int incrE = 2 * abs(dx);
    int incrNE = 2 * (abs(dx) - abs(dy));
    glVertex2i(x, y);
    while (y < y2)
    {
      if (d <= 0)
      {
        d += incrE;
      }
      else
      {
        d += incrNE;
        x += (dx >= 0 ? 1 : -1);
      }
      y++;
      glVertex2i(x, y);
    }
  }
  glEnd();
}

void iniciarDDA(void)
{
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(10, 10);
    DDA = glutCreateWindow("DDA");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glOrtho(-2, 12, -2, 12, -1, 1);
    glutDisplayFunc(displayDDA);
}

void iniciarPM(void)
{
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(1000, 10);
    PM = glutCreateWindow("Ponto Médio");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glOrtho(-2, 12, -2, 12, -1, 1);
    glutDisplayFunc(displayPM);
}

void displayDDA(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0.0);
    glVertex3i(0.0, 10, 0.0);
    glVertex3i(0.0, 0, 0.0);
    glVertex3i(10, 0, 0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.2, 10, 0.0);
    glVertex3f(0.0, 10.2, 0.0);
    glVertex3f(0.2, 10, 0.0);
    glVertex3f(10, 0.2, 0.0);
    glVertex3f(10, -0.2, 0.0);
    glVertex3f(10.2, 0.0, 0.0);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < numVertices; i++)
    {
        int j = (i + 1) % numVertices;
        int x1 = vertices[i][0];
        int y1 = vertices[i][1];
        int x2 = vertices[j][0];
        int y2 = vertices[j][1];
        A_DDA(x1, y1, x2, y2);
    }
    glEnd();
    glFlush();
}

void displayPM(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0.0);
    glVertex3i(0.0, 10, 0.0);
    glVertex3i(0.0, 0, 0.0);
    glVertex3i(10, 0, 0.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.2, 10, 0.0);
    glVertex3f(0.0, 10.2, 0.0);
    glVertex3f(0.2, 10, 0.0);
    glVertex3f(10, 0.2, 0.0);
    glVertex3f(10, -0.2, 0.0);
    glVertex3f(10.2, 0.0, 0.0);
    glEnd();
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < numVertices; i++)
    {
        int nextIndex = (i + 1) % numVertices;
        int x1 = vertices[i][0];
        int y1 = vertices[i][1];
        int x2 = vertices[nextIndex][0];
        int y2 = vertices[nextIndex][1];
        A_PM(x1, y1, x2, y2);
    }
    glEnd();
}

int main(int argc, char **argv)
{
    printf("Quantos vértices o polígono terá? ");
    scanf("%d", &numVertices);

    for (int i = 0; i < numVertices; i++)
    {
        printf("Digite as coordenadas (x y) do vértice %d: ", i + 1);
        scanf("%d %d", &vertices[i][0], &vertices[i][1]);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    iniciarDDA();
    iniciarPM();
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
    }
}
