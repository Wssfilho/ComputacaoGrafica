#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Variáveis globais para rastrear as opções selecionadas pelo usuário
int contornoFacial = 1;
int cabelos = 1;
int olhos = 1;
char boca = 1;
char sobrancelha = 1;
char nariz = 1;

void desenharContornoFacial(int opcao);
void desenharCabelos(int opcao);
void desenharOlhos(int opcao);
void desenharBoca(char opcao);
void desenharSobrancelha(char opcao);
void desenharNariz(char opcao);
void display(void);
void keyboard(unsigned char key, int x, int y);
void Special_keyboard(GLint tecla, int x, int y);

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(00, 00);
  glutCreateWindow(argv[0]);
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glOrtho(-1, 1, -1, 1, -1, 1);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(Special_keyboard);
  glutMainLoop();
  return 0;
}

void desenharContornoFacial(int opcao)
{
  switch (opcao)
  {
  case 1:
    glColor3f(0.87, 0.72, 0.63);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.4);  // inferior esquerdo
    glVertex2f(-0.4, -0.2); // inferior direito
    glVertex2f(0.0, -0.4);  // superior esquerdo
    glVertex2f(0.4, -0.2);  // superior direito
    glVertex2f(0.4, 0.4);   // superior esquerdo
    glEnd();
    break;
  case 2:
    glColor3f(0.87, 0.72, 0.63);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.4);  // inferior esquerdo
    glVertex2f(-0.3, -0.3); // inferior direito
    glVertex2f(0.0, -0.4);  // superior esquerdo
    glVertex2f(0.3, -0.3);  // superior direito
    glVertex2f(0.4, 0.4);   // superior esquerdo
    glEnd();
    break;
  case 3:
    glColor3f(0.87, 0.72, 0.63);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.4);  // inferior esquerdo
    glVertex2f(-0.3, 0.3);  // inferior direito
    glVertex2f(-0.2, -0.1); // inferior direito
    glVertex2f(-0.1, -0.3); // inferior direito
    glVertex2f(0.0, -0.4);  // superior esquerdo
    glVertex2f(0.1, -0.3);  // inferior direito
    glVertex2f(0.2, -0.1);  // inferior direito
    glVertex2f(0.4, 0.4);   // inferior direito
    glVertex2f(0.3, 0.3);   // inferior direito
    glEnd();
    break;
  case 4:
    glColor3f(0.87, 0.72, 0.63);
    glBegin(GL_POLYGON);
    glVertex2f(-0.40, 0.40);
    glVertex2f(-0.40, 0.10);
    glVertex2f(-0.30, -0.30);
    glVertex2f(0.30, -0.30);
    glVertex2f(0.40, 0.10);
    glVertex2f(0.40, 0.40);

    glEnd();
    glPushMatrix();
    glTranslatef(0.0, -0.10, 0.0);
    glBegin(GL_POLYGON);
    float comAnglo = 330.0; // Ângulo inicial do arco
    float fimAnglo = 210.0; // Ângulo final do arco
    for (float i = comAnglo; i >= fimAnglo; i -= 1.0)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.35 * cos(angle), 0.40 * sin(angle));
    }
    glEnd();
    glPopMatrix();

    break;
  case 5:
    glColor3f(0.87, 0.72, 0.63);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, -0.4); // inferior esquerdo
    glVertex2f(0.4, -0.4);  // inferior direito
    glVertex2f(0.4, 0.4);   // superior direito
    glVertex2d(-0.4, 0.4);
    glEnd();

    break;
  case 6:
    glColor3f(0.87, 0.72, 0.63);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.4);  // inferior esquerdo
    glVertex2f(-0.4, 0.0);  // inferior direito
    glVertex2f(-0.4, -0.3); // inferior direito
    glVertex2f(-0.2, -0.3); // inferior direito
    glVertex2f(0.0, -0.4);  // superior esquerdo
    glVertex2f(0.0, -0.4);  // superior esquerdo
    glVertex2f(0.2, -0.3);  // superior esquerdo
    glVertex2f(0.4, -0.3);  // superior esquerdo
    glVertex2f(0.4, 0.0);   // superior esquerdo
    glVertex2f(0.4, 0.4);   // superior esquerdo
    glEnd();
    break;
  }
}

void desenharCabelos(int opcao)
{
  switch (opcao)
  {
  case 1:
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.33941);
    glVertex2f(-0.5, 0.3);
    glVertex2f(-0.46184, 0.401); // p
    glVertex2f(-0.6, 0.4);
    glVertex2f(-0.5, 0.5);
    glVertex2f(-0.6, 0.6);
    glVertex2f(-0.5, 0.7);
    glVertex2f(-0.4, 0.6);
    glVertex2f(-0.3, 0.7);
    glVertex2f(-0.2, 0.6);
    glVertex2f(-0.1, 0.7);
    glVertex2f(0, 0.6);
    glVertex2f(0.4, 0.33941);
    glVertex2f(0.5, 0.3);
    glVertex2f(0.46184, 0.401); // p
    glVertex2f(0.6, 0.4);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.6, 0.6);
    glVertex2f(0.5, 0.7);
    glVertex2f(0.4, 0.6);
    glVertex2f(0.3, 0.7);
    glVertex2f(0.2, 0.6);
    glVertex2f(0.1, 0.7);
    glEnd();
    break;
  case 2:
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.4); // inferior direito
    glVertex2f(-0.4, 0.5); // inferior direito
    glVertex2f(-0.3, 0.4); // inferior direito
    glVertex2f(-0.3, 0.5); // inferior direito
    glVertex2f(-0.2, 0.4); // inferior direito
    glVertex2f(-0.2, 0.5); // inferior direito
    glVertex2f(-0.1, 0.4); // inferior direito
    glVertex2f(-0.1, 0.5); // inferior direito
    glVertex2f(0.0, 0.4);  // inferior direito
    glVertex2f(0.4, 0.4);  // inferior direito
    glVertex2f(0.4, 0.5);  // inferior direito
    glVertex2f(0.3, 0.4);  // inferior direito
    glVertex2f(0.3, 0.5);  // inferior direito
    glVertex2f(0.2, 0.4);  // inferior direito
    glVertex2f(0.2, 0.5);  // inferior direito
    glVertex2f(0.1, 0.4);  // inferior direito
    glVertex2f(0.1, 0.5);  // inferior direito

    glEnd();

    break;
  case 3:
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 0.2, 0.0);
    glBegin(GL_POLYGON);
    float comAnglo = 30.0;  // Ângulo inicial do arco
    float fimAnglo = 150.0; // Ângulo final do arco
    for (float i = comAnglo; i <= fimAnglo; i += 1.0)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.47 * cos(angle), 0.40 * sin(angle));
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.6, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.15 * cos(angle), 0.15 * sin(angle));
    }
    glEnd();
    glPopMatrix();
    break;
  case 4:
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.4, 0.4); // base esquerda
    glVertex2f(0.4, 0.5); // base direita

    glVertex2f(0.35, 0.4); // base esquerda
    glVertex2f(0.35, 0.5); // base direita
    glVertex2f(0.30, 0.4); // base esquerda
    glVertex2f(0.30, 0.5); // base direita

    glVertex2f(0.25, 0.4); // base esquerda
    glVertex2f(0.25, 0.5); // base direita

    glVertex2f(0.20, 0.4);  // base esquerda
    glVertex2f(0.20, 0.5);  // base direita
    glVertex2f(0.15, 0.4);  // base esquerda
    glVertex2f(0.15, 0.5);  // base direita
    glVertex2f(0.10, 0.4);  // base esquerda
    glVertex2f(0.10, 0.5);  // base direita
    glVertex2f(0.05, 0.4);  // base esquerda
    glVertex2f(0.05, 0.5);  // base direita
    glVertex2f(0.0, 0.4);   // base esquerda
    glVertex2f(0.0, 0.5);   // base direita
    glVertex2f(-0.4, 0.4);  // base esquerda
    glVertex2f(-0.4, 0.5);  // base direita
    glVertex2f(-0.20, 0.4); // base esquerda
    glVertex2f(-0.20, 0.5); // base direita
    glVertex2f(-0.15, 0.4); // base esquerda
    glVertex2f(-0.15, 0.5); // base direita
    glVertex2f(-0.10, 0.4); // base esquerda
    glVertex2f(-0.10, 0.5); // base direita
    glVertex2f(-0.05, 0.4); // base esquerda
    glVertex2f(-0.05, 0.5); // base direita
    glVertex2f(-0.25, 0.4); // base esquerda
    glVertex2f(-0.25, 0.5); // base direita
    glVertex2f(-0.30, 0.4); // base esquerda
    glVertex2f(-0.30, 0.5); // base direita
    glVertex2f(-0.35, 0.4); // base esquerda
    glVertex2f(-0.35, 0.5); // base direita
    glEnd();
    break;
  case 5:
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.4);
    glVertex2f(0.0, 0.7);
    glVertex2f(0.0, 0.4);
    glVertex2f(-0.25, 0.7);
    glVertex2f(0.0, 0.4);
    glVertex2f(0.25, 0.7);
    glVertex2f(0.0, 0.4);
    glVertex2f(-0.25, 0.5);
    glVertex2f(0.0, 0.4);
    glVertex2f(0.25, 0.5);
    glEnd();
    break;
  case 6:
  glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.0, 0.4);
    glVertex2f(-0.4, 0.4);  // inferior esquerdo
    glVertex2f(-0.4, 0.5);  // inferior direito
    glVertex2f(-0.299114919855,0.5613260412464);
    glVertex2f(-0.2, 0.5);  // inferior direito
    glVertex2f(-0.09904990360866,0.56233139308683);
    glVertex2f(0.0, 0.5);   // inferior direito]
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.0, 0.4);  // inferior esquerdo
    glVertex2f(0.4, 0.4);  // inferior esquerdo
    glVertex2f(0.4, 0.5);  // inferior direito
    glVertex2f(0.299114919855,0.5613260412464);
    glVertex2f(0.2, 0.5);  // inferior direito
    glVertex2f(0.09904990360866,0.56233139308683);
    glVertex2f(0.0, 0.5);   // inferior direito]
    glEnd();
    break;
    // Continue para as outras opções de cabelo
  }
}

void desenharOlhos(int opcao)
{
  // Implemente conforme necessário
  switch (opcao)
  {
  case 1:
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.05, 0.2); // inferior esquerdo
    glVertex2f(-0.1, 0.25); // inferior direito
    glVertex2f(-0.2, 0.25); // inferior direito
    glVertex2f(-0.25, 0.2); // inferior direito
    glVertex2f(-0.2, 0.15); // superior esquerdo
    glVertex2f(-0.1, 0.15); // inferior direito
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.05, 0.2);
    glVertex2f(0.0, 0.2);
    glEnd();
    glPushMatrix();
    glTranslatef(-0.15, 0.20, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.05 * cos(angle), 0.05 * sin(angle));
    }
    glEnd();
    glPopMatrix();
    glBegin(GL_LINES);
    glVertex2f(-0.15, 0.30);
    glVertex2f(-0.15, 0.25);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.15, 0.15);
    glVertex2f(-0.15, 0.10);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.05, 0.2); // inferior esquerdo
    glVertex2f(0.1, 0.25); // inferior direito
    glVertex2f(0.2, 0.25); // inferior direito
    glVertex2f(0.25, 0.2); // inferior direito
    glVertex2f(0.2, 0.15); // superior esquerdo
    glVertex2f(0.1, 0.15); // inferior direito
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.2);
    glVertex2f(0.05, 0.2);
    glEnd();
    glPushMatrix();
    glTranslatef(0.15, 0.20, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.05 * cos(angle), 0.05 * sin(angle));
    }
    glEnd();
    glPopMatrix();
    break;
  case 2:
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-0.05, 0.2); // inferior esquerdo
    glVertex2f(-0.25, 0.2); // inferior direito
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.05, 0.2); // inferior esquerdo
    glVertex2f(0.25, 0.2); // inferior direito
    glEnd();
    break;
  case 3:
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.15, 0.20, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.05 * cos(angle), 0.05 * sin(angle));
    }
    glEnd();
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-0.15, 0.20, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.05 * cos(angle), 0.05 * sin(angle));
    }
    glEnd();
    glPopMatrix();
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  }
}

void desenharBoca(char opcao)
{
  switch (opcao)
  {
  case 1:
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-0.1, -0.2);
    glVertex2f(0.0, -0.2541144);
    glEnd();

    break;
  case 2:
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-0.1, -0.2);
    glVertex2f(0.0, -0.2541144);
    glVertex2f(0.1, -0.2);
    glVertex2f(0.0, -0.2541144);
    glEnd();
    break;
  case 3:
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, -0.0541144, 0.0);
    glBegin(GL_POLYGON);
    float comAnglo = 330.0; // Ângulo inicial do arco
    float fimAnglo = 210.0; // Ângulo final do arco
    for (float i = comAnglo; i >= fimAnglo; i -= 1.0)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.1 * cos(angle), 0.20 * sin(angle));
    }
    glEnd();
    glPopMatrix();
    break;
  case 4:
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, -0.31144, 0.0);
    glBegin(GL_POLYGON);
    comAnglo = 30.0;  // Ângulo inicial do arco
    fimAnglo = 150.0; // Ângulo final do arco
    for (float i = comAnglo; i <= fimAnglo; i += 1.0)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.1 * cos(angle), 0.15 * sin(angle));
    }
    glEnd();
    glPopMatrix();
    break;
  case 5:
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1, -0.2);
    glVertex2f(0.0, -0.2541144);
    glVertex2f(0.1, -0.2);
    glVertex2f(0.0, -0.1437541);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(-0.1, -0.2);
    glVertex2f(0.1, -0.2);
    glEnd();
    break;
  case 6:
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.1409144371604, -0.13804264515157);
    glVertex2f(0.1, -0.2);
    glVertex2f(-0.13860815329518, -0.14215327148179);
    glVertex2f(-0.1, -0.2);
    glVertex2f(0.1, -0.2);
    glVertex2f(-0.1, -0.2);
    glEnd();
    break;
  }
}

void desenharSobrancelha(char opcao)
{
  switch (opcao)
  {
  case 1:
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-0.15, 0.25, 0.0);
    glLineWidth(10.0);
    glBegin(GL_LINES);
    float comAnglo = 30.0;  // Ângulo inicial do arco
    float fimAnglo = 150.0; // Ângulo final do arco
    for (float i = comAnglo; i <= fimAnglo; i += 1.0)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.10 * cos(angle), 0.05 * sin(angle));
    }
    glEnd();
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.15, 0.25, 0.0);
    glBegin(GL_LINES);
    comAnglo = 30.0;  // Ângulo inicial do arco
    fimAnglo = 150.0; // Ângulo final do arco
    for (float i = comAnglo; i <= fimAnglo; i += 1.0)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.10 * cos(angle), 0.05 * sin(angle));
    }
    glEnd();
    glPopMatrix();
    glLineWidth(1.0);
    break;
  case 2:
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(-0.21847716410846, 0.29973905901783);
    glVertex2f(-0.1, 0.3);
    glVertex2f(-0.1, 0.3);
    glVertex2f(-0.03981610049201, 0.26356554731182);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.21847716410846, 0.29973905901783);
    glVertex2f(0.1, 0.3);
    glVertex2f(0.1, 0.3);
    glVertex2f(0.03981610049201, 0.26356554731182);
    glEnd();
    glLineWidth(1.0);
    break;
  case 3:
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(-0.20232866009286, 0.32476924024201);
    glVertex2f(-0.05, 0.25);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.20232866009286, 0.32476924024201);
    glVertex2f(0.05, 0.25);
    glEnd();
    glLineWidth(1.0);
    break;
  case 4:
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(-0.25, 0.3);
    glVertex2f(-0.05, 0.3);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(0.25, 0.3);
    glVertex2f(0.05, 0.3);
    glEnd();
    glLineWidth(1.0);
    break;
  case 5:
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(-0.25, 0.3);
    glVertex2f(-0.0, 0.3);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(0.25, 0.3);
    glVertex2f(0.0, 0.3);
    glEnd();
    glLineWidth(1.0);
    break;
  case 6:
  glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(-0.25, 0.3);
    glVertex2f(-0.05, 0.3);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.04069400221164,0.25871513727581);
    glVertex2f(0.13821313073372,0.33914328451052);
    glVertex2f(0.13821313073372,0.33914328451052);
    glVertex2f(0.26086605526665,0.34115398819139);
    glEnd();
    glLineWidth(1.0);
    break;
  }
  // Implemente conforme necessário
}

void desenharNariz(char opcao)
{
  switch (opcao)
  {
  case 1:
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex2f(0.0, 0.1);
  glVertex2f(0.0, -0.04);
  glEnd();
    break;
  case 2:
   glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex2f(0.0, 0.1);
  glVertex2f(0.0, -0.04);
  glVertex2f(0.05979568717988,-0.1012008215995);
  glVertex2f(0.0, -0.04);
  glVertex2f(0.05979568717988,-0.1012008215995);
  glVertex2f(-0.0,-0.1);
  glEnd();
    break;
  case 3:
   glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex2f(-0.02063246005482,-0.07606702558866);
  glVertex2f(-0.06687864471478,-0.00267634123699);
  glVertex2f(0.02063246005482,-0.07606702558866);
  glVertex2f(0.06687864471478,-0.00267634123699);
  glEnd();
    break;
  case 4:
   glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex2f(0.0, 0.02);
  glVertex2f(0.07688666846726,-0.04087971117347);
  glVertex2f(-0.0,-0.1);
  glVertex2f(0.07688666846726,-0.04087971117347);
  glEnd();
    break;
  case 5:
   glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex2f(-0.020,0.021);
  glVertex2f(-0.05984118183174,-0.03786365565217);
  glVertex2f(-0.04174484870393,-0.05897604430128);
  glVertex2f(0.0,-0.1);
  glVertex2f(0.020,0.021);
  glVertex2f(0.05984118183174,-0.03786365565217);
  glVertex2f(0.04174484870393,-0.05897604430128);
  glVertex2f(0.0,-0.1);
  glEnd();
    break;
  case 6:
   glPushMatrix();
    glTranslatef(-0.05, -0.04, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.01 * cos(angle), 0.01 * sin(angle));
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.05, -0.04, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
      float angle = i * 3.14159 / 180;
      glVertex2f(0.01 * cos(angle), 0.01 * sin(angle));
    }
    glEnd();
    glPopMatrix();
    break;
  }
}
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  // Desenhar contorno facial primeiro
  desenharContornoFacial(contornoFacial);
  // Desenhar cabelos depois do contorno facial
  desenharCabelos(cabelos);
  // Desenhar olhos
  desenharOlhos(olhos);
  // Desenhar boca
  desenharBoca(boca);
  // Desenhar sobrancelha
  desenharSobrancelha(sobrancelha);
  // Desenhar nariz
  desenharNariz(nariz);
  glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  printf("*** Tratamento de teclas comuns\n");
  printf(">>> Tecla pressionada: %c\n", key);

  if (key >= 49 && key <= 54)
  {
    olhos = key - 49 + 1;
  }
  glutPostRedisplay();

  switch (key)
  {
  // sombr:
  case 97:
    sobrancelha = 1;
    glutPostRedisplay();
    break;
  case 115:
    sobrancelha = 2;
    glutPostRedisplay();
    break;
  case 100:
    sobrancelha = 3;
    glutPostRedisplay();
    break;
  case 102:
    sobrancelha = 4;
    glutPostRedisplay();
    break;
  case 103:
    sobrancelha = 5;
    glutPostRedisplay();
    break;
  case 104:
    sobrancelha = 6;
    glutPostRedisplay();
    break;
    // boca
  case 113:
    boca = 1;
    glutPostRedisplay();
    break;
  case 119:
    boca = 2;
    glutPostRedisplay();
    break;
  case 101:
    boca = 3;
    glutPostRedisplay();
    break;
  case 114:
    boca = 4;
    glutPostRedisplay();
    break;
  case 116:
    boca = 5;
    glutPostRedisplay();
    break;
  case 121:
    boca = 6;
    glutPostRedisplay();
    break;
  case 112:
    nariz = 1;
    glutPostRedisplay();
    break;
  case 120:
    nariz = 2;
    glutPostRedisplay();
    break;
  case 99:
    nariz = 3;
    glutPostRedisplay();
    break;
  case 118:
    nariz = 4;
    glutPostRedisplay();
    break;
  case 98:
    nariz = 5;
    glutPostRedisplay();
    break;
  case 110:
    nariz = 6;
    glutPostRedisplay();
    break;
  }
}

void Special_keyboard(GLint tecla, int x, int y)
{
  if (tecla >= GLUT_KEY_F1 && tecla <= GLUT_KEY_F6)
    contornoFacial = tecla - GLUT_KEY_F1 + 1;

  if (tecla >= GLUT_KEY_F7 && tecla <= GLUT_KEY_F12)
    cabelos = tecla - GLUT_KEY_F7 + 1;

  glutPostRedisplay();
}
