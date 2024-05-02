#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Variáveis globais para rastrear as opções selecionadas pelo usuário
int contornoFacial;
int cabelos;
int olhos;
char boca;
char sobrancelha;
char nariz;

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
  printf("\nTestando... \n");
  return 0;
}

void desenharContornoFacial(int opcao)
{
  switch (opcao)
  {
  case 1:
  
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  default:
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.25, -0.25); // inferior esquerdo
    glVertex2f(0.25, -0.25);  // inferior direito
    glVertex2f(0.25, 0.25);   // superior direito
    glVertex2f(-0.25, 0.25);  // superior esquerdo
    glEnd();
    break;
  }
}

void desenharCabelos(int opcao)
{
  switch (opcao)
  {
  case 1:
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    // Linha 1: Ponto inicial (-0.25, 0.25) para o primeiro ponto (-0.15, 0.45)
    glVertex2f(-0.25, 0.25);
    glVertex2f(-0.15, 0.45);

    // Linha 2: Ponto inicial (-0.15, 0.45) para o segundo ponto (0, 0.25)
    glVertex2f(-0.15, 0.45);
    glVertex2f(0, 0.25);

    // Linha 3: Ponto inicial (0, 0.25) para o terceiro ponto (0.15, 0.45)
    glVertex2f(0, 0.25);
    glVertex2f(0.15, 0.45);

    // Linha 4: Ponto inicial (0.15, 0.45) para o último ponto (0.25, 0.25)
    glVertex2f(0.15, 0.45);
    glVertex2f(0.25, 0.25);
    glEnd();
    break;
  case 2:
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.25, 0.25); // base esquerda
    glVertex2f(0.25, 0.25);  // base direita
    glVertex2f(0.0, 0.5);    // topo
    glEnd();
    break;
  case 3:
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-0.25, 0.25); // base esquerda
    glVertex2f(0.0, 0.5);    // topo
    glVertex2f(0.25, 0.25);  // base direita
    glEnd();
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
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
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
                glVertex2f(-0.1, -0.1); // inferior esquerdo
                glVertex2f(0.1, -0.1);  // inferior direito
                glVertex2f(0.1, 0.1);   // superior direito
                glVertex2f(-0.1, 0.1);  // superior esquerdo
            glEnd();
            glBegin(GL_POLYGON);
                glVertex2f(0.15, -0.1); // inferior esquerdo
                glVertex2f(0.35, -0.1);  // inferior direito
                glVertex2f(0.35, 0.1);   // superior direito
                glVertex2f(0.15, 0.1);  // superior esquerdo
            glEnd();
    break;
  }
}

void desenharBoca(char opcao)
{
  // Implemente conforme necessário
}

void desenharSobrancelha(char opcao)
{
  // Implemente conforme necessário
}

void desenharNariz(char opcao)
{
  // Implemente conforme necessário
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
  switch (key)
  {
    case 49:
    olhos = 1;
    glutPostRedisplay();
    break;
    case 50:
    glutPostRedisplay();
    break;
    case 51:
    glutPostRedisplay();
    break;
    case 52:
    glutPostRedisplay();
    break;
    case 53:
    glutPostRedisplay();
    break;
    case 54:
    glutPostRedisplay();
    break;
    // Continue para outras teclas específicas
  }
}
void Special_keyboard(GLint tecla, int x, int y)
{
  switch (tecla)
  {
  case GLUT_KEY_F1:
    glutPostRedisplay();
    break;
  case GLUT_KEY_F2:
    glutPostRedisplay();
    break;
  case GLUT_KEY_F3:
    glutPostRedisplay();
    break;
  case GLUT_KEY_F4:
    glutPostRedisplay();
    break;
  case GLUT_KEY_F5:
    glutPostRedisplay();
    break;
  case GLUT_KEY_F6:
    glutPostRedisplay();
    break;
  case GLUT_KEY_F7:
    cabelos = 1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_F8:
    cabelos = 2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_F9:
    cabelos = 3;
    glutPostRedisplay();
    break;
  case GLUT_KEY_F10:
    cabelos = 4;
    glutPostRedisplay();
    break;
  case GLUT_KEY_F11:
    cabelos = 5;
    glutPostRedisplay();
    break;
  case GLUT_KEY_F12:
    cabelos = 6;
    glutPostRedisplay();
    break;
  }
}
