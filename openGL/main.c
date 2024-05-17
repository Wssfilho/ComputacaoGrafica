#include <GL/glut.h> // Inclui a biblioteca GLUT para lidar com janelas e gráficos OpenGL
#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <math.h> // Inclui a biblioteca matemática para funções matemáticas

int DDA, PM; // Variáveis para armazenar os identificadores das janelas
int numVertices = 0; // Número de vértices do polígono
int vertices[10][2]; // Array para armazenar os vértices do polígono
void keyboard(unsigned char key, int x, int y); // Protótipo da função para lidar com eventos do teclado
void displayDDA(void); // Protótipo da função de renderização usando o algoritmo DDA
void displayPM(void); // Protótipo da função de renderização usando o algoritmo do Ponto Médio
void iniciarDDA(void); // Protótipo da função para iniciar a janela do algoritmo DDA
void iniciarPM(void); // Protótipo da função para iniciar a janela do algoritmo do Ponto Médio
int obterQtdUsuario(); // Protótipo da função para obter a quantidade de vértices do usuário
void desenharPoligonoDDA(); // Protótipo da função para desenhar um polígono usando o algoritmo DDA
void desenharPoligonoPM(); // Protótipo da função para desenhar um polígono usando o algoritmo do Ponto Médio
void rasterizarLinhaDDA(int x1, int y1, int x2, int y2); // Protótipo da função para rasterizar uma linha usando o algoritmo DDA
void rasterizarLinhaPM(int x1, int y1, int x2, int y2); // Protótipo da função para rasterizar uma linha usando o algoritmo do Ponto Médio

int main(int argc, char **argv)
{
  glutInit(&argc, argv); // Inicializa o GLUT
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Configura o modo de exibição com buffer único e cores RGB
  numVertices = obterQtdUsuario(); // Obtém a quantidade de vértices do usuário
  iniciarDDA(); // Inicializa a janela para o algoritmo DDA
  iniciarPM(); // Inicializa a janela para o algoritmo do Ponto Médio
  glutKeyboardFunc(keyboard); // Define a função de callback para eventos de teclado
  glutMainLoop(); // Entra no loop principal do GLUT
  return 0; // Retorna 0 para indicar sucesso
}

int obterQtdUsuario()
{
  int quantidade; // Variável para armazenar a quantidade de vértices inserida pelo usuário
  do
  {
    printf("Digite a quantidade de vértices (1-10): "); // Solicita a quantidade de vértices ao usuário
    scanf("%d", &quantidade); // Lê a quantidade de vértices
  } while (quantidade < 1 || quantidade > 10); // Continua solicitando até que a quantidade esteja dentro do intervalo especificado
  for (int i = 0; i < quantidade; i++) // Loop para ler as coordenadas de cada vértice
  {
    printf("Digite as coordenadas do vértice %d (x y): ", i + 1); // Solicita as coordenadas do vértice ao usuário
    scanf("%d %d", &vertices[i][0], &vertices[i][1]); // Lê as coordenadas do vértice
  }
  return quantidade; // Retorna a quantidade de vértices inserida pelo usuário
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27: // Se a tecla pressionada for a tecla Esc (código 27)
    exit(0); // Sai do programa
  }
}

void iniciarDDA(void)
{
  glutInitWindowSize(640, 640); // Define o tamanho inicial da janela
  glutInitWindowPosition(10, 10); // Define a posição inicial da janela na tela
  DDA = glutCreateWindow("DDA"); // Cria a janela para o algoritmo DDA e armazena o identificador
  glClearColor(1.0, 1.0, 1.0, 0.0); // Define a cor de fundo da janela como branco
  glOrtho(-2, 12, -2, 12, -1, 1); // Define a projeção ortográfica
  glutDisplayFunc(displayDDA); // Define a função de renderização para a janela do algoritmo DDA
}

void iniciarPM(void)
{
  glutInitWindowSize(640, 640); // Define o tamanho inicial da janela
  glutInitWindowPosition(1000, 10); // Define a posição inicial da janela na tela
  PM = glutCreateWindow("Ponto Médio"); // Cria a janela para o algoritmo do Ponto Médio e armazena o identificador
  glClearColor(1.0, 1.0, 1.0, 0.0); // Define a cor de fundo da janela como branco
  glOrtho(-2, 12, -2, 12, -1, 1); // Define a projeção ortográfica
  glutDisplayFunc(displayPM); // Define a função de renderização para a janela do algoritmo do Ponto Médio
}

void displayDDA(void)
{
  // Renderiza o conteúdo da janela do algoritmo DDA
  glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cor com a cor de fundo definida
  glColor3f(0.0, 0.0, 0.0); // Define a cor atual como preto

  // Desenha os eixos x e y
  glLineWidth(2.0); // Define a largura da linha
  glBegin(GL_LINES); // Inicia o desenho de linhas
  glVertex3i(0, 0, 0.0); // Define o ponto inicial da linha do eixo x
  glVertex3i(0.0, 10, 0.0); // Define o ponto final da linha do eixo x
  glVertex3i(0.0, 0, 0.0); // Define o ponto inicial da linha do eixo y
  glVertex3i(10, 0, 0.0); // Define o ponto final da linha do eixo y
  glEnd(); // Finaliza o desenho de linhas

  // Desenha as setas nos extremos dos eixos
  glBegin(GL_TRIANGLES); // Inicia o desenho de triângulos
  glVertex3f(-0.2, 10, 0.0); // Define o primeiro vértice do triângulo da seta do eixo y
  glVertex3f(0.0, 10.2, 0.0); // Define o segundo vértice do triângulo da seta do eixo y
  glVertex3f(0.2, 10, 0.0); // Define o terceiro vértice do triângulo da seta do eixo y
  glVertex3f(10, 0.2, 0.0); // Define o primeiro vértice do triângulo da seta do eixo x
  glVertex3f(10, -0.2, 0.0); // Define o segundo vértice do triângulo da seta do eixo x
  glVertex3f(10.2, 0.0, 0.0); // Define o terceiro vértice do triângulo da seta do eixo x
  glEnd(); // Finaliza o desenho de triângulos

  // Desenha os vértices do polígono
  glColor3f(1.0, 0.0, 0.0); // Define a cor dos vértices como vermelho
  glPointSize(4.0); // Define o tamanho dos pontos
  glBegin(GL_POINTS); // Inicia o desenho de pontos
  for (int i = 0; i < numVertices; i++) // Loop para desenhar todos os vértices
  {
    glVertex3i(vertices[i][0], vertices[i][1], 0.0); // Define a posição de cada vértice
  }
  glEnd(); // Finaliza o desenho de pontos

  // Desenha o polígono usando o algoritmo DDA
  desenharPoligonoDDA();

  glFlush(); // Força a renderização
}

void displayPM(void)
{
  // Renderiza o conteúdo da janela do algoritmo do Ponto Médio
  glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cor com a cor de fundo definida
  glColor3f(0.0, 0.0, 0.0); // Define a cor atual como preto

  // Desenha os eixos x e y
  glLineWidth(2.0); // Define a largura da linha
  glBegin(GL_LINES); // Inicia o desenho de linhas
  glVertex3i(0, 0, 0.0); // Define o ponto inicial da linha do eixo x
  glVertex3i(0.0, 10, 0.0); // Define o ponto final da linha do eixo x
  glVertex3i(0.0, 0, 0.0); // Define o ponto inicial da linha do eixo y
  glVertex3i(10, 0, 0.0); // Define o ponto final da linha do eixo y
  glEnd(); // Finaliza o desenho de linhas

  // Desenha as setas nos extremos dos eixos
  glBegin(GL_TRIANGLES); // Inicia o desenho de triângulos
  glVertex3f(-0.2, 10, 0.0); // Define o primeiro vértice do triângulo da seta do eixo y
  glVertex3f(0.0, 10.2, 0.0); // Define o segundo vértice do triângulo da seta do eixo y
  glVertex3f(0.2, 10, 0.0); // Define o terceiro vértice do triângulo da seta do eixo y
  glVertex3f(10, 0.2, 0.0); // Define o primeiro vértice do triângulo da seta do eixo x
  glVertex3f(10, -0.2, 0.0); // Define o segundo vértice do triângulo da seta do eixo x
  glVertex3f(10.2, 0.0, 0.0); // Define o terceiro vértice do triângulo da seta do eixo x
  glEnd(); // Finaliza o desenho de triângulos

  // Desenha os vértices do polígono
  glColor3f(1.0, 0.0, 0.0); // Define a cor dos vértices como vermelho
  glPointSize(4.0); // Define o tamanho dos pontos
  glBegin(GL_POINTS); // Inicia o desenho de pontos
  for (int i = 0; i < numVertices; i++) // Loop para desenhar todos os vértices
  {
    glVertex3i(vertices[i][0], vertices[i][1], 0.0); // Define a posição de cada vértice
  }
  glEnd(); // Finaliza o desenho de pontos

  // Desenha o polígono usando o algoritmo do Ponto Médio
  desenharPoligonoPM();

  glFlush(); // Força a renderização
}

void desenharPoligonoDDA()
{
  // Desenha um polígono usando o algoritmo DDA
  glLineWidth(2.0); // Define a largura da linha
  glColor3f(0.0, 0.0, 0.0); // Define a cor das linhas como preto
  glBegin(GL_POINTS); // Inicia o desenho de pontos
  for (int i = 0; i < numVertices; i++) // Loop para desenhar todas as arestas do polígono
  {
    int j = (i + 1) % numVertices; // Índice do próximo vértice (tratamento de fechamento do polígono)
    rasterizarLinhaDDA(vertices[i][0], vertices[i][1], vertices[j][0], vertices[j][1]); // Rasteriza a linha entre os vértices
  }
  glEnd(); // Finaliza o desenho de pontos
}

void desenharPoligonoPM()
{
  // Desenha um polígono usando o algoritmo do Ponto Médio
  glLineWidth(1.0); // Define a largura da linha
  glColor3f(0.0, 0.0, 0.0); // Define a cor das linhas como preto
  glBegin(GL_POINTS); // Inicia o desenho de pontos
  for (int i = 0; i < numVertices; i++) // Loop para desenhar todas as arestas do polígono
  {
    int j = (i + 1) % numVertices; // Índice do próximo vértice (tratamento de fechamento do polígono)
    rasterizarLinhaPM(vertices[i][0], vertices[i][1], vertices[j][0], vertices[j][1]); // Rasteriza a linha entre os vértices
  }
  glEnd(); // Finaliza o desenho de pontos
}

void rasterizarLinhaDDA(int x1, int y1, int x2, int y2)
{
  // Rasteriza uma linha usando o algoritmo DDA
  int dx = x2 - x1; // Variação em x
  int dy = y2 - y1; // Variação em y
  int passos = abs(dx) > abs(dy) ? abs(dx) : abs(dy); // Determina o número de passos com base na maior variação
  float xInc = (float)dx / (float)passos; // Incremento em x por passo
  float yInc = (float)dy / (float)passos; // Incremento em y por passo
  float x = (float)x1; // Coordenada inicial de x
  float y = (float)y1; // Coordenada inicial de y
  glBegin(GL_POINTS); // Inicia o desenho de pontos
  for (int i = 0; i <= passos; i++) // Loop para desenhar cada ponto da linha
  {
    glVertex2i(round(x), round(y)); // Desenha o ponto atual, arredondando para as coordenadas inteiras mais próximas
    x += xInc; // Atualiza a coordenada x
    y += yInc; // Atualiza a coordenada y
  }
  glEnd(); // Finaliza o desenho de pontos
}

void rasterizarLinhaPM(int x1, int y1, int x2, int y2)
{
  // Rasteriza uma linha usando o algoritmo do Ponto Médio
  int dx = abs(x2 - x1); // Variação absoluta em x
  int dy = abs(y2 - y1); // Variação absoluta em y
  int x = x1; // Coordenada inicial de x
  int y = y1; // Coordenada inicial de y
  int incrE, incrNE, d; // Variáveis auxiliares para o algoritmo
  glBegin(GL_POINTS); // Inicia o desenho de pontos
  if (dx >= dy) // Se a linha estiver mais na horizontal
  {
    int incrY = (y2 > y1) ? 1 : -1; // Determina se a linha sobe ou desce
    int incrX = (x2 > x1) ? 1 : -1; // Determina se a linha vai para a direita ou esquerda

    incrE = 2 * dy; // Incremento quando o ponto do meio está acima da linha
    incrNE = 2 * (dy - dx); // Incremento quando o ponto do meio está acima e à direita da linha
    d = 2 * dy - dx; // Critério de decisão inicial

    glVertex2i(x, y); // Desenha o primeiro ponto da linha
    while (x != x2) // Loop até alcançar o segundo ponto
    {
      if (d <= 0) // Verifica o critério de decisão
      {
        d += incrE; // Seleciona o próximo ponto acima da linha
      }
      else
      {
        d += incrNE; // Seleciona o próximo ponto acima e à direita da linha
        y += incrY; // Move para o próximo ponto na direção y
      }
      x += incrX; // Move para o próximo ponto na direção x
      glVertex2i(x, y); // Desenha o próximo ponto da linha
    }
  }
  else // Se a linha estiver mais na vertical
  {
    int incrX = (x2 > x1) ? 1 : -1; // Determina se a linha vai para a direita ou esquerda
    int incrY = (y2 > y1) ? 1 : -1; // Determina se a linha sobe ou desce

    incrE = 2 * dx; // Incremento quando o ponto do meio está à direita da linha
    incrNE = 2 * (dx - dy); // Incremento quando o ponto do meio está acima e à direita da linha
    d = 2 * dx - dy; // Critério de decisão inicial

    glVertex2i(x, y); // Desenha o primeiro ponto da linha
    while (y != y2) // Loop até alcançar o segundo ponto
    {
      if (d <= 0) // Verifica o critério de decisão
      {
        d += incrE; // Seleciona o próximo ponto à direita da linha
      }
      else
      {
        d += incrNE; // Seleciona o próximo ponto acima e à direita da linha
        x += incrX; // Move para o próximo ponto na direção x
      }
      y += incrY; // Move para o próximo ponto na direção y
      glVertex2i(x, y); // Desenha o próximo ponto da linha
    }
  }
  glEnd(); // Finaliza o desenho de pontos
}
