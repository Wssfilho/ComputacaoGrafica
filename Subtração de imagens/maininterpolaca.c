#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char vermelho, verde, azul;
} Pixel;

typedef struct {
    int largura, altura;
    Pixel* dados;
} Imagem;

void liberarImagem(Imagem* img) {
    free(img->dados);
    free(img);
}

Imagem* carregarImagem(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        fprintf(stderr, "Erro ao abrir o arquivo de imagem\n");
        return NULL;
    }

    Imagem* img = (Imagem*)malloc(sizeof(Imagem));
    if (!img) {
        fprintf(stderr, "Erro de alocação de memória para a estrutura de imagem\n");
        fclose(arquivo);
        return NULL;
    }

    char magica[3];
    fscanf(arquivo, "%s %d %d %*d", magica, &(img->largura), &(img->altura));

    if (magica[0] != 'P' || magica[1] != '3') {
        fprintf(stderr, "Formato de imagem não suportado\n");
        free(img);
        fclose(arquivo);
        return NULL;
    }

    img->dados = (Pixel*)malloc(img->largura * img->altura * sizeof(Pixel));
    if (!img->dados) {
        fprintf(stderr, "Erro de alocação de memória para os pixels da imagem\n");
        free(img);
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < img->largura * img->altura; i++) {
        fscanf(arquivo, "%hhu %hhu %hhu", &(img->dados[i].vermelho), &(img->dados[i].verde), &(img->dados[i].azul));
    }

    fclose(arquivo);
    return img;
}

void salvarImagem(const char* nomeArquivo, Imagem* img) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        fprintf(stderr, "Erro ao criar arquivo PPM\n");
        return;
    }

    fprintf(arquivo, "P3\n");
    fprintf(arquivo, "%d %d\n255\n", img->largura, img->altura);

    for (int i = 0; i < img->largura * img->altura; i++) {
        fprintf(arquivo, "%d %d %d\n", img->dados[i].vermelho, img->dados[i].verde, img->dados[i].azul);
    }

    fclose(arquivo);
}

Pixel interpolarPixel1Vizinhanca(Imagem* entrada, float x, float y) {
    int x0 = (int)x;
    int y0 = (int)y;

    int x1, y1;
    x1 = (x0 + 1) % entrada->largura;
    y1 = y0;
    float fracX = x - x0;
    float fracY = y - y0;

    // Interpolação bilinear
    Pixel pixelInterpolado;
    pixelInterpolado.vermelho = (1 - fracX) * (1 - fracY) * entrada->dados[y0 * entrada->largura + x0].vermelho +
                                fracX * (1 - fracY) * entrada->dados[y0 * entrada->largura + x1].vermelho +
                                (1 - fracX) * fracY * entrada->dados[y1 * entrada->largura + x0].vermelho +
                                fracX * fracY * entrada->dados[y1 * entrada->largura + x1].vermelho;

    pixelInterpolado.verde = (1 - fracX) * (1 - fracY) * entrada->dados[y0 * entrada->largura + x0].verde +
                             fracX * (1 - fracY) * entrada->dados[y0 * entrada->largura + x1].verde +
                             (1 - fracX) * fracY * entrada->dados[y1 * entrada->largura + x0].verde +
                             fracX * fracY * entrada->dados[y1 * entrada->largura + x1].verde;

    pixelInterpolado.azul = (1 - fracX) * (1 - fracY) * entrada->dados[y0 * entrada->largura + x0].azul +
                            fracX * (1 - fracY) * entrada->dados[y0 * entrada->largura + x1].azul +
                            (1 - fracX) * fracY * entrada->dados[y1 * entrada->largura + x0].azul +
                            fracX * fracY * entrada->dados[y1 * entrada->largura + x1].azul;

    return pixelInterpolado;
}

Pixel interpolarPixel4Vizinhanca(Imagem* entrada, float x, float y) {
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = (x0 + 1) % entrada->largura;
    int y1 = (y0 + 1) % entrada->altura;

    float fracX = x - x0;
    float fracY = y - y0;

    // Interpolação bilinear
    Pixel pixelInterpolado;
    pixelInterpolado.vermelho = (1 - fracX) * (1 - fracY) * entrada->dados[y0 * entrada->largura + x0].vermelho +
                                fracX * (1 - fracY) * entrada->dados[y0 * entrada->largura + x1].vermelho +
                                (1 - fracX) * fracY * entrada->dados[y1 * entrada->largura + x0].vermelho +
                                fracX * fracY * entrada->dados[y1 * entrada->largura + x1].vermelho;

    pixelInterpolado.verde = (1 - fracX) * (1 - fracY) * entrada->dados[y0 * entrada->largura + x0].verde +
                             fracX * (1 - fracY) * entrada->dados[y0 * entrada->largura + x1].verde +
                             (1 - fracX) * fracY * entrada->dados[y1 * entrada->largura + x0].verde +
                             fracX * fracY * entrada->dados[y1 * entrada->largura + x1].verde;

    pixelInterpolado.azul = (1 - fracX) * (1 - fracY) * entrada->dados[y0 * entrada->largura + x0].azul +
                            fracX * (1 - fracY) * entrada->dados[y0 * entrada->largura + x1].azul +
                            (1 - fracX) * fracY * entrada->dados[y1 * entrada->largura + x0].azul +
                            fracX * fracY * entrada->dados[y1 * entrada->largura + x1].azul;

    return pixelInterpolado;
}

Imagem* interpolarImagem4Vizinhanca(Imagem* entrada, float m, float n) {
    int novaLargura = (int)(entrada->largura * m);
    int novaAltura = (int)(entrada->altura * n);

    Imagem* saida = (Imagem*)malloc(sizeof(Imagem));
    if (!saida) {
        fprintf(stderr, "Erro de alocação de memória para a imagem interpolada\n");
        return NULL;
    }

    saida->largura = novaLargura;
    saida->altura = novaAltura;
    saida->dados = (Pixel*)malloc(novaLargura * novaAltura * sizeof(Pixel));

    if (!saida->dados) {
        fprintf(stderr, "Erro de alocação de memória para os pixels da imagem interpolada\n");
        free(saida);
        return NULL;
    }

    for (int y = 0; y < novaAltura; y++) {
        for (int x = 0; x < novaLargura; x++) {
            float origemX = (float)x / novaLargura * entrada->largura;
            float origemY = (float)y / novaAltura * entrada->altura;

            // 4-vizinhança (média aritmética simples)
            saida->dados[y * novaLargura + x] = interpolarPixel4Vizinhanca(entrada, origemX, origemY);
        }
    }

    return saida;
}

Imagem* interpolarImagem1Vizinhanca(Imagem* entrada, float m, float n) {
    int novaLargura = (int)(entrada->largura * m);
    int novaAltura = (int)(entrada->altura * n);

    Imagem* saida = (Imagem*)malloc(sizeof(Imagem));
    if (!saida) {
        fprintf(stderr, "Erro de alocação de memória para a imagem interpolada\n");
        return NULL;
    }

    saida->largura = novaLargura;
    saida->altura = novaAltura;
    saida->dados = (Pixel*)malloc(novaLargura * novaAltura * sizeof(Pixel));

    if (!saida->dados) {
        fprintf(stderr, "Erro de alocação de memória para os pixels da imagem interpolada\n");
        free(saida);
        return NULL;
    }

    for (int y = 0; y < novaAltura; y++) {
        for (int x = 0; x < novaLargura; x++) {
            float origemX = (float)x / novaLargura * entrada->largura;
            float origemY = (float)y / novaAltura * entrada->altura;

            // 1-vizinhança com escolha de vizinho
            saida->dados[y * novaLargura + x] = interpolarPixel1Vizinhanca(entrada, origemX, origemY);
        }
    }

    return saida;
}

int main(void) {
    float m, n;
    int vizinhanca;
    char nomeArquivo[100];

    printf("Digite o valor de m (constante de proporcionalidade em relação à largura): ");
    scanf("%f", &m);

    printf("Digite o valor de n (constante de proporcionalidade em relação à altura): ");
    scanf("%f", &n);

    printf("Insira o nome do arquivo: \n");
    scanf("%s%*c", nomeArquivo);
    printf("Escolha o tipo de vizinhança para interpolação: \n");
    printf("1 - para uma (1) vizinhanca\n");
    printf("4 - para quatro (4) vizinhanca com média aritmética simples\n");
    scanf("%d", &vizinhanca);

    if (vizinhanca != 1 && vizinhanca != 4) {
        fprintf(stderr, "Opção de vizinhança inválida. Saindo.\n");
        return -1;
    }

    Imagem* imagemOriginal = carregarImagem(nomeArquivo);
    if (!imagemOriginal) {
        return -1;
    }

    Imagem* imagemInterpolada;
    if (vizinhanca == 1) {
        imagemInterpolada = interpolarImagem1Vizinhanca(imagemOriginal, m, n);
    } else {
        imagemInterpolada = interpolarImagem4Vizinhanca(imagemOriginal, m, n);
    }

    if (!imagemInterpolada) {
        liberarImagem(imagemOriginal);
        return -1;
    }

    if (vizinhanca == 1) {
        salvarImagem("1vizinhanca1.ppm", imagemInterpolada);
    } else if (vizinhanca == 4) {
        salvarImagem("4vizinhanca2.ppm", imagemInterpolada);
    }

    liberarImagem(imagemOriginal);
    liberarImagem(imagemInterpolada);

    return 0;
}
