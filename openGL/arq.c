#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int R = 0, G = 0, B = 0;

void display(void);
void keyboard(unsigned char key, int x, int y);
void Special_keyboard(GLint tecla, int x, int y);
void DesenhaTexto(char *string);
void ApagaFiguraAnterior();

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(400, 200);
    glutCreateWindow(argv[0]);
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glOrtho(-1, 1, -1, 1, -1, 1);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(Special_keyboard);
    glutMainLoop();
    printf("\nTestando... \n");
    return 0;
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    DesenhaTexto("Exemplo de texto para a atividade 2");
    glColor3ub(R, G, B);
    ApagaFiguraAnterior();
}

void keyboard(unsigned char key, int x, int y){
    printf("*** Tratamento de teclas comuns\n");
    printf(">>> Tecla pressionada: %c\n", key);

    switch (key) {
        case 27: // Tecla ESC
            ApagaFiguraAnterior();
            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_LINES);
                glVertex2f(-0.25, 0.25); // base esquerda
                glVertex2f(0.0, 0.5);    // topo
                glVertex2f(0.25, 0.25);  // base direita
            glEnd();
            glFlush();
            break;
        case 32: // Tecla de espaço
            ApagaFiguraAnterior();
            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_TRIANGLES);
                glVertex2f(-0.25, 0.25); // base esquerda
                glVertex2f(0.25, 0.25);  // base direita
                glVertex2f(0.0, 0.5);     // topo
            glEnd();
            glFlush();
            break;
        case 63: // Tecla '?'
    ApagaFiguraAnterior();
    glColor3f(0.0, 0.0, 0.0);
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
    glFlush();
    break;
    case 'q': // Tecla 'q' para desenhar dois quadrados
            ApagaFiguraAnterior();
    glColor3f(0.0, 0.0, 0.0);
            // Desenha dois quadrados dentro do polígono
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
            glFlush();
            break;

    }
}

void Special_keyboard(GLint tecla, int x, int y) {
    switch (tecla) {
        case GLUT_KEY_F12: R = 0; G = 200; B = 200; glutPostRedisplay(); break; 
        case GLUT_KEY_F10: R = 0; G = 100; B = 200; glutPostRedisplay(); break;
    }
}

void DesenhaTexto(char *string) {
    glColor3ub(150, 200, 250);
    glPushMatrix();
        glRasterPos2f(-0.4, -0.4);
        while (*string)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
    glPopMatrix();
    glColor3ub(255, 255, 255);
}

void ApagaFiguraAnterior() {
    glClear(GL_COLOR_BUFFER_BIT);
    DesenhaTexto("Exemplo de texto para a atividade 2");
    glColor3ub(R, G, B);
glColor3f(1.0, 1.0, 1.0);
    // Redesenha o quadrado
    glBegin(GL_POLYGON);
        glVertex2f(-0.25, -0.25); // inferior esquerdo
        glVertex2f(0.25, -0.25);  // inferior direito
        glVertex2f(0.25, 0.25);   // superior direito
        glVertex2f(-0.25, 0.25);  // superior esquerdo
    glEnd();
    glFlush();
     glColor3f(0.0, 0.0, 0.0);
            // Desenha dois quadrados dentro do polígono
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
            glFlush();
}
