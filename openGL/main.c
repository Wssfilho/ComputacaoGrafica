#include <GL/glut.h> //O arquivo glut.h inclui, além dos protótipos das funções GLUT, os arquivos gl.h e glu.h,
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SIGN(x) ((x) < 0 ? (-1) : (1))
#define ABS(x) ((x) < 0 ? (-x) : (x))
#define FLOOR(x) ((x) < 0 ? ((int)(x) - ((x) - (int)(x) != 0 ? 1 : 0)) : (int)(x))
#define FALSE 0
#define TRUE 1
int numVertices;
int vertices[10][2];


void displayDDA(void);
void displayPM(void);
void iniciarDDA(void);
void iniciarPM(void);
void keyboard(unsigned char key, int x, int y);

int DDA, PM, PMC; // Variáveis das janelas gráficas

void setPixel(int x, int y) {
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void A_DDA(int x1, int y1, int x2, int y2) {
    int length = 0;
    float deltax, deltay, x, y;
    int i;

    if (ABS(x2 - x1) >= ABS(y2 - y1)) {
        length = ABS(x2 - x1);
    } else {
        length = ABS(y2 - y1);
    }

    deltax = (float)(x2 - x1) / (float)length;
    deltay = (float)(y2 - y1) / (float)length;
    x = x1 + 0.5 * SIGN(deltax);
    y = y1 + 0.5 * SIGN(deltay);
    glPointSize(3.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <= length; i++) {
        glVertex2i(x, y);
        x += deltax;
        y += deltay;
    }
  glEnd();
  glFlush();
}  

void A_PM(int x1, int y1, int x2, int y2) {
    int deltax = abs(x2 - x1);
    int deltay = abs(y2 - y1);
    int x, y;
    if (deltax >= deltay) {
        int d = 2 * deltay - deltax;
        int ds = 2 * deltay;
        int dt = 2 * (deltay - deltax);
        if (x1 < x2) {
            x = x1;
            y = y1;
        } else {
            x = x2;
            y = y2;
            x2 = x1;
            y2 = y1;
        }
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        for (int i = 0; x < x2; i++) {
            x++;
            if (d < 0) {
                d += ds;
            } else {
                if ((x2 > x1 && y2 > y1) || (x2 < x1 && y2 < y1)) {
                    y++;
                } else {
                    y--;
                }
                d += dt;
            }
            glVertex2i(x, y);
        }
        glEnd();
    } else {
        int d = 2 * deltax - deltay;
        int ds = 2 * deltax;
        int dt = 2 * (deltax - deltay);
        if (y1 < y2) {
            x = x1;
            y = y1;
        } else {
            x = x2;
            y = y2;
            y2 = y1;
            x2 = x1;
        }
        glPointSize(3.0);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        for (int i = 0; y < y2; i++) {
            y++;
            if (d < 0) {
                d += ds;
            } else {
                if ((x2 > x1 && y2 > y1) || (x2 < x1 && y2 < y1)) {
                    x++;
                } else {
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

void iniciarDDA(void){
  glutInitWindowSize (640, 640); //Posição inicial do canto superior esquerdo da janela a ser criada
  glutInitWindowPosition (10, 10); //Estabelece o tamanho (em pixels) da janela a ser criada
  DDA = glutCreateWindow ("DDA");
  glClearColor(1.0, 1.0, 1.0, 0.0); //selecionar cor de fundo (Branco)
  glOrtho (-2, 12, -2, 12, -1 ,1);
  glutDisplayFunc(displayDDA); //Função callback chamada para fazer o desenho
}

void iniciarPM(void){
  glutInitWindowSize (640, 640); //Posição inicial do canto superior esquerdo da janela a ser criada
  glutInitWindowPosition (1000, 10); //Estabelece o tamanho (em pixels) da janela a ser criada
  PM = glutCreateWindow ("Ponto Médio");
  glClearColor(1.0, 1.0, 1.0, 0.0); //selecionar cor de fundo (Branco)
  glOrtho (-2, 12, -2, 12, -1 ,1);
  glutDisplayFunc(displayPM); //Função callback chamada para fazer o desenho
}

void displayDDA(void){
  glClear(GL_COLOR_BUFFER_BIT); ////Limpa a janela de visualização com a cor de fundo especificada
  glColor3f (0.0, 0.0, 0.0);
  // Desenhando os eixos
  // Definindo a espessura da linha
  glLineWidth(2.0);
  glBegin (GL_LINES);
    // Definindo a reta do eixo Y
    glVertex3i(0,0,0.0);
    glVertex3i(0.0,10,0.0);
    // Definindo a reta do eixo X
    glVertex3i(0.0,0,0.0);
    glVertex3i(10,0,0.0);
  glEnd();
  // Desenhando as pontas dos eixos
  glBegin(GL_TRIANGLES);
    // Triangulo do eixo Y
    glVertex3f(-0.2,10,0.0);
    glVertex3f(0.0,10.2,0.0);
    glVertex3f(0.2,10,0.0);
    //Triangulo do eixo X
    glVertex3f(10,0.2,0.0);
    glVertex3f(10,-0.2,0.0);
    glVertex3f(10.2,0.0,0.0);
  glEnd();
  // Desenhando os pontos (cor: vermelha)
  glColor3f(1.0,0.0,0.0);
  glPointSize(3.0);
  glBegin(GL_LINE_LOOP);
   for (int i = 0; i < numVertices - 1; i++) {
        int x1 = vertices[i][0];
        int y1 = vertices[i][1];
        int x2 = vertices[i + 1][0];
        int y2 = vertices[i + 1][1];
        A_DDA(x1, y1, x2, y2);
    }
  glEnd();
  glFlush(); ////Executa os comandos OpenGL para renderização
}

void displayPM(void){
  glClear(GL_COLOR_BUFFER_BIT); ////Limpa a janela de visualização com a cor de fundo especificada
  glColor3f (0.0, 0.0, 0.0);
  // Desenhando os eixos
  // Definindo a espessura da linha
  glLineWidth(2.0);
  glBegin (GL_LINES);
    // Definindo a reta do eixo Y
    glVertex3i(0,0,0.0);
    glVertex3i(0.0,10,0.0);
    // Definindo a reta do eixo X
    glVertex3i(0.0,0,0.0);
    glVertex3i(10,0,0.0);
  glEnd();
   // Desenhando as pontas dos eixos
  glBegin(GL_TRIANGLES);
    // Triangulo do eixo Y
    glVertex3f(-0.2,10,0.0);
    glVertex3f(0.0,10.2,0.0);
    glVertex3f(0.2,10,0.0);
    //Triangulo do eixo X
    glVertex3f(10,0.2,0.0);
    glVertex3f(10,-0.2,0.0);
    glVertex3f(10.2,0.0,0.0);
  glEnd();
   // Desenhando os pontos (cor: vermelha)
  glColor3f(1.0,0.0,0.0);
  glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++) {
        int nextIndex = (i + 1) % numVertices;
        int x1 = vertices[i][0];
        int y1 = vertices[i][1];
        int x2 = vertices[nextIndex][0];
        int y2 = vertices[nextIndex][1];
        A_PM(x1, y1, x2, y2);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
   //int numVertices;
    printf("Quantos vértices o polígono terá? ");
    scanf("%d", &numVertices);

    //int vertices[numVertices][2];

    for (int i = 0; i < numVertices; i++) {
        printf("Digite as coordenadas (x y) do vértice %d: ", i + 1);
        scanf("%d %d", &vertices[i][0], &vertices[i][1]);
    }

  glutInit(&argc, argv); //Estabelece contato com sistema de janelas
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); //Cores dos pixels serão expressos em RGB
  iniciarDDA();
  iniciarPM();
  glutKeyboardFunc(keyboard); //Chamada sempre que uma tecla for precionada
  glutMainLoop(); //Depois de registradas as callbacks, o controle é entregue ao sistema de janelas
  return 0;
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27: exit(0);
  }
}