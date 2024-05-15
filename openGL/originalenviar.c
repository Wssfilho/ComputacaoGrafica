#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int DDA, PM;
int numVertices = 0;
int vertices[10][2];
void keyboard(unsigned char key, int x, int y);
void displayDDA(void);
void displayPM(void);
void iniciarDDA(void);
void iniciarPM(void);
int obterQtdUsuario();
void coletarVertices();
void desenharPoligonoDDA();
void desenharPoligonoPM();
void rasterizarLinhaDDA(int x1, int y1, int x2, int y2);
void rasterizarLinhaPM(int x1, int y1, int x2, int y2);

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  numVertices = obterQtdUsuario();
  coletarVertices();

  iniciarDDA();
  iniciarPM();
  glutKeyboardFunc(keyboard); // Chamada sempre que uma tecla for precionada
  glutMainLoop();
  return 0;
}

int obterQtdUsuario()
{
  int quantidade;
  do
  {
    printf("Digite a quantidade de vértices (1-10): ");
    scanf("%d", &quantidade);
  } while (quantidade < 1 || quantidade > 10);
  return quantidade;
}
void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27:
    exit(0);
  }
}
void coletarVertices()
{
  for (int i = 0; i < numVertices; i++)
  {
    printf("Digite as coordenadas do vértice %d (x y): ", i + 1);
    scanf("%d %d", &vertices[i][0], &vertices[i][1]);
  }
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

  // Desenhando os eixos e pontas dos eixos (mesmo para "DDA" e "Ponto Médio")
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

  // Desenhando os pontos (cor: vermelha)
  glColor3f(1.0, 0.0, 0.0);
  glPointSize(3.0);
  glBegin(GL_POINTS);
  for (int i = 0; i < numVertices; i++)
  {
    glVertex3i(vertices[i][0], vertices[i][1], 0.0);
  }
  glEnd();
  desenharPoligonoDDA();
  glFlush();
}

void displayPM(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);

  // Desenhando os eixos e pontas dos eixos (mesmo para "DDA" e "Ponto Médio")
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

  // Desenhando os pontos (cor: vermelha)
  glColor3f(1.0, 0.0, 0.0);
  glPointSize(3.0);
  glBegin(GL_POINTS);
  for (int i = 0; i < numVertices; i++)
  {
    glVertex3i(vertices[i][0], vertices[i][1], 0.0);
  }
  glEnd();
  desenharPoligonoPM();
  glFlush();
}

void desenharPoligonoDDA()
{
  glLineWidth(2.0);
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(3.0);
  glBegin(GL_POINTS);
  for (int i = 0; i < numVertices; i++)
  {
    int j = (i + 1) % numVertices;
    rasterizarLinhaDDA(vertices[i][0], vertices[i][1], vertices[j][0], vertices[j][1]);
  }
  glEnd();
}

void desenharPoligonoPM()
{
  glLineWidth(1.0);
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(3.0);
  glBegin(GL_POINTS);
  for (int i = 0; i < numVertices; i++)
  {
    int j = (i + 1) % numVertices;
    rasterizarLinhaPM(vertices[i][0], vertices[i][1], vertices[j][0], vertices[j][1]);
  }
  glEnd();
}
void rasterizarLinhaDDA(int x1, int y1, int x2, int y2)
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

void rasterizarLinhaPM(int x1, int y1, int x2, int y2)
{
  int deltax = abs(x2 - x1);
  int deltay = abs(y2 - y1);
  int x, y;
  if (deltax >= deltay)
  {
    int d = 2 * deltay - deltax;
    int ds = 2 * deltay;
    int dt = 2 * (deltay - deltax);
    if (x1 < x2)
    {
      x = x1;
      y = y1;
    }
    else
    {
      x = x2;
      y = y2;
      x2 = x1;
      y2 = y1;
    }
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    for (int i = 0; x < x2; i++)
    {
      x++;
      if (d < 0)
      {
        d += ds;
      }
      else
      {
        if ((x2 > x1 && y2 > y1) || (x2 < x1 && y2 < y1))
        {
          y++;
        }
        else
        {
          y--;
        }
        d += dt;
      }
      glVertex2i(x, y);
    }
    glEnd();
  }
  else
  {
    int d = 2 * deltax - deltay;
    int ds = 2 * deltax;
    int dt = 2 * (deltax - deltay);
    if (y1 < y2)
    {
      x = x1;
      y = y1;
    }
    else
    {
      x = x2;
      y = y2;
      y2 = y1;
      x2 = x1;
    }
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    for (int i = 0; y < y2; i++)
    {
      y++;
      if (d < 0)
      {
        d += ds;
      }
      else
      {
        if ((x2 > x1 && y2 > y1) || (x2 < x1 && y2 < y1))
        {
          x++;
        }
        else
        {
          x--;
        }
        d += dt;
      }
      glVertex2i(x, y);
    }
    glEnd();
    glFlush();
  }
}
