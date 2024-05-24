#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int PM;       // Variável da janela gráfica do Ponto Médio
int raio = 0; // Raio inicial, limitado a 0, para não ficar uma variável sem valor

void ponto_circulo(int x, int y)
{
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

void desenhaCirculoPM(int raio)
{
    int x = 0;
    int y = raio;
    int d = 1 - raio;


    while (y > x) // Enquanto o y for maior que x, desenha os pontos simétricos
    {
        ponto_circulo(x, y); // Desenha os pontos simétricos
        if (d < 0) // Se d for menor que 0, escolhe E
        {
            d += 2 * x + 3; // Atualiza d
        }
        else // Se d for maior ou igual a 0, escolhe SE
        {
            d += 2 * (x - y) + 5; // Atualiza d
            y--; // Decrementa y
        }
        x++; // Incrementa x
    }
}

void desenhaQuadrantes(int xc, int yc, int r)
{
    // Função para desenhar os quadrantes do círculo, as linhas azuis
    glVertex2i(xc + r, yc);
    glVertex2i(xc - r, yc);
    glVertex2i(yc, xc + r);
    glVertex2i(yc, xc - r);
}

void displayPM(void)
{
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
void receberRaio()
{
    // Função para receber o raio do círculo
    printf("Digite o novo raio (limite máximo 10): ");
    while (scanf("%d", &raio) != 1 || raio <= 0 || raio > 10) // Limita o raio entre 0 e 10, validação tmb caso o raio queja igual a 0
    {
        printf("Digite um valor válido para o raio (limite máximo 10): ");
    }
}
void teclado(unsigned char tecla, int x, int y) // Função para sair do programa
{
    switch (tecla)
    {
    case 27: // Tecla Esc para sair
        exit(0);
        break;
    }
}

int main(int argc, char **argv) // Função principal
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    receberRaio(); // Raio inicial
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(10, 10);
    PM = glutCreateWindow("Ponto Médio");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glOrtho(-11, 11, -11, 11, -1, 1); // Ajuste para cobrir o espaço adequado
    glutDisplayFunc(displayPM);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}
