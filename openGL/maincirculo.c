#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int PM; // Variável da janela gráfica do Ponto Médio
int raio = 5; // Raio inicial, limitado a 10

void ponto_circulo(int x, int y) {
    // Função para desenhar os pontos simétricos em todos os octantes do círculo
    glVertex2i(x, y);
    glVertex2i(y, x);
    glVertex2i(y, -x);
    glVertex2i(x, -y);
    glVertex2i(-x, -y);
    glVertex2i(-y, -x);
    glVertex2i(-y, x);
    glVertex2i(-x, y);
}

void desenhaCirculoPM(int raio) {
    int x = 0;
    int y = raio;
    int d = 1 - raio;

    ponto_circulo(x, y); // Desenha o primeiro ponto e seus simétricos

    while (y > x) {
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        ponto_circulo(x, y);
    }
}

void desenhaQuadrantes(int xc, int yc, int r) {
    // Função para desenhar os quadrantes do círculo
    
    glVertex2i(xc + r, yc);
    glVertex2i(xc - r, yc);
    glVertex2i(yc, xc + r);
    glVertex2i(yc, xc - r);
   
}

void displayPM(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Cor vermelha para o círculo
    glPointSize(2.0);
    glBegin(GL_POINTS);
    // Desenhando o círculo usando o algoritmo do Ponto Médio
    desenhaCirculoPM(raio); // Origem (0, 0)
    glEnd();
    glPointSize(1.0);
    glColor3f(0.0, 0.0, 1.0); // Cor azul para os quadrantes
    glBegin(GL_LINES);
    desenhaQuadrantes(0, 0, raio);
    glEnd();
    glFlush();
}

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
    case 27: // Tecla Esc para sair
        exit(0);
        break;
    case 'r': // Tecla 'r' para ler o novo raio do teclado
        printf("Digite o novo raio (limite máximo 10): ");
        int novoRaio;
        scanf("%d", &novoRaio);
        if (novoRaio <= 10 && novoRaio > 0) {
            raio = novoRaio;
            glutPostRedisplay(); // Redesenha a janela
        } else {
            printf("Raio inválido! O raio deve estar entre 1 e 10.\n");
        }
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(10, 10);
    PM = glutCreateWindow("Ponto Médio");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glOrtho(-10, 10, -10, 10, -1, 1); // Ajuste para cobrir o espaço adequado
    glutDisplayFunc(displayPM);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}
