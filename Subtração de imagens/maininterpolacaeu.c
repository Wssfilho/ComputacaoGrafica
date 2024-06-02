#include <stdio.h>
#include <stdlib.h>

// Função para liberar a memória alocada para a imagem
void liberarImagem(unsigned char **imagemR, unsigned char **imagemG, unsigned char **imagemB, int altura)
{
    for (int i = 0; i < altura; i++)
    {
        free(imagemR[i]);
        free(imagemG[i]);
        free(imagemB[i]);
    }
    free(imagemR);
    free(imagemG);
    free(imagemB);
}

// Função para alocar dinamicamente as matrizes R, G e B
void alocarMatrizesRGB(int largura, int altura, unsigned char ***imagemR, unsigned char ***imagemG, unsigned char ***imagemB)
{
    *imagemR = (unsigned char **)malloc(altura * sizeof(unsigned char *));
    *imagemG = (unsigned char **)malloc(altura * sizeof(unsigned char *));
    *imagemB = (unsigned char **)malloc(altura * sizeof(unsigned char *));

    if (!(*imagemR) || !(*imagemG) || !(*imagemB))
    {
        fprintf(stderr, "Erro de alocação de memória para as matrizes R, G e B\n");
        exit(1);
    }

    for (int i = 0; i < altura; i++)
    {
        (*imagemR)[i] = (unsigned char *)malloc(largura * sizeof(unsigned char));
        (*imagemG)[i] = (unsigned char *)malloc(largura * sizeof(unsigned char));
        (*imagemB)[i] = (unsigned char *)malloc(largura * sizeof(unsigned char));
        if (!(*imagemR)[i] || !(*imagemG)[i] || !(*imagemB)[i])
        {
            fprintf(stderr, "Erro de alocação de memória para as linhas das matrizes R, G e B\n");
            for (int j = 0; j < i; j++)
            {
                free((*imagemR)[j]);
                free((*imagemG)[j]);
                free((*imagemB)[j]);
            }
            free(*imagemR);
            free(*imagemG);
            free(*imagemB);
            exit(1);
        }
    }
}

// Função para carregar uma imagem a partir de um arquivo
void carregarImagem(const char *nomeArquivo, int *largura, int *altura, unsigned char ***imagemR, unsigned char ***imagemG, unsigned char ***imagemB)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo)
    {
        fprintf(stderr, "Erro ao abrir o arquivo de imagem\n");
        exit(1);
    }

    char formato[3];
    fscanf(arquivo, "%s\n%d %d\n", formato, largura, altura);

    if (formato[0] != 'P' || formato[1] != '3')
    {
        fprintf(stderr, "Formato de imagem não suportado\n");
        fclose(arquivo);
        exit(1);
    }

    alocarMatrizesRGB(*largura, *altura, imagemR, imagemG, imagemB);

    for (int i = 0; i < *altura; i++)
    {
        for (int j = 0; j < *largura; j++)
        {
            fscanf(arquivo, "%hhu %hhu %hhu", &((*imagemR)[i][j]), &((*imagemG)[i][j]), &((*imagemB)[i][j]));
        }
    }

    fclose(arquivo);
}

// Função para salvar uma imagem em um arquivo
void salvarImagem(const char *nomeArquivo, unsigned char **imagemR, unsigned char **imagemG, unsigned char **imagemB, int largura, int altura)
{
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (!arquivo)
    {
        fprintf(stderr, "Erro ao criar arquivo de imagem\n");
        exit(1);
    }

    fprintf(arquivo, "P3\n");
    fprintf(arquivo, "%d %d\n255\n", largura, altura);

    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            fprintf(arquivo, "%d %d %d ", imagemG[i][j], imagemB[i][j], imagemR[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

// Função para interpolar uma imagem usando 1-vizinhança
void interpolarImagem1Vizinhanca(unsigned char **entradaR, unsigned char **entradaG, unsigned char **entradaB, int largura, int altura, float m, float n, unsigned char ***saidaR, unsigned char ***saidaG, unsigned char ***saidaB)
{
    int novaLargura = (int)(largura * m);
    int novaAltura = (int)(altura * n);

    *saidaR = (unsigned char **)malloc(novaAltura * sizeof(unsigned char *));
    *saidaG = (unsigned char **)malloc(novaAltura * sizeof(unsigned char *));
    *saidaB = (unsigned char **)malloc(novaAltura * sizeof(unsigned char *));

    if (!(*saidaR) || !(*saidaG) || !(*saidaB))
    {
        fprintf(stderr, "Erro de alocação de memória para a imagem interpolada\n");
        exit(1);
    }

    alocarMatrizesRGB(novaLargura, novaAltura, saidaR, saidaG, saidaB);

    for (int y = 0; y < novaAltura; y++)
    {
        for (int x = 0; x < novaLargura; x++)
        {
            float origemX = (float)x / novaLargura * largura;
            float origemY = (float)y / novaAltura * altura;

            int x0 = (int)origemX;
            int y0 = (int)origemY;
            int x1 = (x0 + 1) % largura;
            int y1 = y0;
            float fracX = origemX - x0;
            float fracY = origemY - y0;

            // Interpolação bilinear
            (*saidaR)[y][x] = (1 - fracX) * (1 - fracY) * entradaR[y0][x0] +
                              fracX * (1 - fracY) * entradaR[y0][x1] +
                              (1 - fracX) * fracY * entradaR[y1][x0] +
                              fracX * fracY * entradaR[y1][x1];

            (*saidaG)[y][x] = (1 - fracX) * (1 - fracY) * entradaG[y0][x0] +
                              fracX * (1 - fracY) * entradaG[y0][x1] +
                              (1 - fracX) * fracY * entradaG[y1][x0] +
                              fracX * fracY * entradaG[y1][x1];

            (*saidaB)[y][x] = (1 - fracX) * (1 - fracY) * entradaB[y0][x0] +
                              fracX * (1 - fracY) * entradaB[y0][x1] +
                              (1 - fracX) * fracY * entradaB[y1][x0] +
                              fracX * fracY * entradaB[y1][x1];
        }
    }
}

// Função para interpolar uma imagem usando 4-vizinhança
void interpolarImagem4Vizinhanca(unsigned char **entradaR, unsigned char **entradaG, unsigned char **entradaB, int largura, int altura, float m, float n, unsigned char ***saidaR, unsigned char ***saidaG, unsigned char ***saidaB)
{
    int novaLargura = (int)(largura * m);
    int novaAltura = (int)(altura * n);

    *saidaR = (unsigned char **)malloc(novaAltura * sizeof(unsigned char *));
    *saidaG = (unsigned char **)malloc(novaAltura * sizeof(unsigned char *));
    *saidaB = (unsigned char **)malloc(novaAltura * sizeof(unsigned char *));

    if (!(*saidaR) || !(*saidaG) || !(*saidaB))
    {
        fprintf(stderr, "Erro de alocação de memória para a imagem interpolada\n");
        exit(1);
    }

    alocarMatrizesRGB(novaLargura, novaAltura, saidaR, saidaG, saidaB);

    for (int y = 0; y < novaAltura; y++)
    {
        for (int x = 0; x < novaLargura; x++)
        {
            float origemX = (float)x / novaLargura * largura;
            float origemY = (float)y / novaAltura * altura;

            int x0 = (int)origemX;
            int y0 = (int)origemY;
            int x1 = (x0 + 1) % largura;
            int y1 = (y0 + 1) % altura;
            float fracX = origemX - x0;
            float fracY = origemY - y0;

            // Interpolação bilinear
            (*saidaR)[y][x] = (1 - fracX) * (1 - fracY) * entradaR[y0][x0] +
                              fracX * (1 - fracY) * entradaR[y0][x1] +
                              (1 - fracX) * fracY * entradaR[y1][x0] +
                              fracX * fracY * entradaR[y1][x1];

            (*saidaG)[y][x] = (1 - fracX) * (1 - fracY) * entradaG[y0][x0] +
                              fracX * (1 - fracY) * entradaG[y0][x1] +
                              (1 - fracX) * fracY * entradaG[y1][x0] +
                              fracX * fracY * entradaG[y1][x1];

            (*saidaB)[y][x] = (1 - fracX) * (1 - fracY) * entradaB[y0][x0] +
                              fracX * (1 - fracY) * entradaB[y0][x1] +
                              (1 - fracX) * fracY * entradaB[y1][x0] +
                              fracX * fracY * entradaB[y1][x1];
        }
    }
}

int main(void)
{
    float m, n;
    int vizinhanca;
    char nomeArquivo[100];

    printf("Digite o valor de m (constante de proporcionalidade em relação à largura): ");
    scanf("%f", &m);

    printf("Digite o valor de n (constante de proporcionalidade em relação à altura): ");
    scanf("%f", &n);

    printf("Insira o nome do arquivo: \n");
    scanf("%s", nomeArquivo);
    printf("Escolha o tipo de vizinhança para interpolação: \n");
    printf("1 - para uma (1) vizinhanca\n");
    printf("4 - para quatro (4) vizinhanca com média aritmética simples\n");
    scanf("%d", &vizinhanca);

    if (vizinhanca != 1 && vizinhanca != 4)
    {
        fprintf(stderr, "Opção de vizinhança inválida. Saindo.\n");
        return -1;
    }

    int largura, altura;
    unsigned char **imagemR;
    unsigned char **imagemG;
    unsigned char **imagemB;

    carregarImagem(nomeArquivo, &largura, &altura, &imagemR, &imagemG, &imagemB);

    unsigned char **imagemInterpoladaR;
    unsigned char **imagemInterpoladaG;
    unsigned char **imagemInterpoladaB;

    if (vizinhanca == 1)
    {
        interpolarImagem1Vizinhanca(imagemR, imagemG, imagemB, largura, altura, m, n, &imagemInterpoladaR, &imagemInterpoladaG, &imagemInterpoladaB);
    }
    else
    {
        interpolarImagem4Vizinhanca(imagemR, imagemG, imagemB, largura, altura, m, n, &imagemInterpoladaR, &imagemInterpoladaG, &imagemInterpoladaB);
    }

    char nomeArquivoSaida[100];
    if (vizinhanca == 1)
    {
        sprintf(nomeArquivoSaida, "1vizinhanca.ppm");
    }
    else
    {
        sprintf(nomeArquivoSaida, "4vizinhanca.ppm");
    }
    salvarImagem(nomeArquivoSaida, imagemInterpoladaR, imagemInterpoladaG, imagemInterpoladaB, largura * m, altura * n);

    liberarImagem(imagemR, imagemG, imagemB, altura);
    liberarImagem(imagemInterpoladaR, imagemInterpoladaG, imagemInterpoladaB, altura * n);

    return 0;
}
