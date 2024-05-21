#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int PM; // Variável da janela gráfica do Ponto Médio
int raio = 200; // Raio inicial

void drawCirclePM(int xc, int yc, int r) {
    int x = r;
    int y = 0;
    int p = 1 - r;

    glBegin(GL_POINTS);
    while (x >= y) {
        // Quadrante 1
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc + y, yc + x);

        // Quadrante 2
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc - y, yc + x);

        // Quadrante 3
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc - y, yc - x);

        // Quadrante 4
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc + y, yc - x);

        y++;
        if (p <= 0) {
            p = p + 2 * y + 1;
        } else {
            x--;
            p = p + 2 * y - 2 * x + 1;
        }
    }
    glEnd();
}

void drawQuadrants(int xc, int yc, int r) {
    glBegin(GL_LINES);
    // Linhas do eixo X e Y
    glVertex2i(xc, yc - r);
    glVertex2i(xc, yc + r);
    glVertex2i(xc - r, yc);
    glVertex2i(xc + r, yc);

    // Linhas diagonais dos quadrantes
   
    glEnd();
}

void displayPM(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);

    // Desenhando o círculo usando o algoritmo do Ponto Médio
    glColor3f(1.0, 0.0, 0.0);
    drawCirclePM(0, 0, raio); // Origem (0, 0)

    // Desenhando os quadrantes
    glColor3f(0.0, 0.0, 1.0);
    drawQuadrants(0, 0, raio);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // Tecla Esc para sair
        exit(0);
        break;
    case 'r': // Tecla 'r' para ler o novo raio do teclado
        printf("Digite o novo raio: ");
        scanf("%d", &raio);
        glutPostRedisplay(); // Redesenha a janela
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
    glOrtho(-640, 640, -640, 640, -1, 1); // Ajuste para cobrir o espaço adequado
    glutDisplayFunc(displayPM);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
