#include <stdio.h>
#include <stdlib.h>

FILE *fpin, *fpoutViz1, *fpoutViz4;
int **imagemR, **imagemG, **imagemB, ncol, nlin, quant_nivel_cinza;

void abrir_arquivos(int argc, char *argv[]);
void ler_cabecalho(void);
void ler_imagem(void);
void gravar_cabecalho(FILE *fp);
void gravar_imagem(FILE *fp, int **imagem);
void fechar_arquivos(void);
void vizinho1(int **imagem, int linha, int coluna, int **Imagem);
void Vizinho4(int **imagem, int linha, int coluna, int **Imagem);

void abrir_arquivos(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Modo correto de uso: <prog> <imagemIn>\n");
        exit(0);
    }
    if ((fpin = fopen(argv[1], "r")) == NULL) {
        printf("Nao foi possivel abrir arquivo de imagem %s\n", argv[1]);
        exit(1);
    }
    if ((fpoutViz1 = fopen("ImagemViz1.ppm", "w")) == NULL) {
        printf("Nao foi possivel abrir arquivo de saida Vizinho 1\n");
        exit(1);
    }
    if ((fpoutViz4 = fopen("ImagemViz4.ppm", "w")) == NULL) {
        printf("Nao foi possivel abrir arquivo de saida Vizinho 4\n");
        exit(1);
    }
}

void ler_imagem(void) {
    int cont, col, lin;
    imagemR = (int **)malloc((nlin + 1) * sizeof(int *));
    imagemG = (int **)malloc((nlin + 1) * sizeof(int *));
    imagemB = (int **)malloc((nlin + 1) * sizeof(int *));
    for (cont = 0; cont < nlin; cont++) {
        imagemR[cont] = (int *)malloc(ncol * sizeof(int));
        imagemG[cont] = (int *)malloc(ncol * sizeof(int));
        imagemB[cont] = (int *)malloc(ncol * sizeof(int));
        if (imagemR[cont] == NULL || imagemG[cont] == NULL || imagemB[cont] == NULL) {
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }
    }
    for (lin = 0; lin < nlin; lin++) {
        for (col = 0; col < ncol; col++) {
            fscanf(fpin, "%d", &imagemR[lin][col]);
            fscanf(fpin, "%d", &imagemG[lin][col]);
            fscanf(fpin, "%d", &imagemB[lin][col]);
        }
    }
}

void ler_cabecalho(void) {
    char controle[4];
    fscanf(fpin, "%s", controle);
    fscanf(fpin, "%d %d", &ncol, &nlin);
    fscanf(fpin, "%d", &quant_nivel_cinza);
}

void fechar_arquivos(void) {
    fclose(fpin);
    fclose(fpoutViz1);
    fclose(fpoutViz4);
}

void gravar_cabecalho(FILE *fp) {
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d\n", ncol, nlin);
    fprintf(fp, "%d\n", quant_nivel_cinza);
}

void gravar_imagem(FILE *fp, int **imagem) {
    int lin, col;
    gravar_cabecalho(fp);
    for (lin = 0; lin < nlin; lin++) {
        for (col = 0; col < ncol; col++) {
            fprintf(fp, "%d ", imagem[lin][col]);
        }
        fprintf(fp, "\n");
    }
}

void vizinho1(int **imagem, int linha, int coluna, int **Imagem) {
    int i, j;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            Imagem[2 * i][2 * j] = imagem[i][j];
        }
    }
}

void Vizinho4(int **imagem, int linha, int coluna, int **Imagem) {
    int i, j;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            Imagem[2 * i][2 * j] = imagem[i][j];

            if (i + 1 < linha) {
                Imagem[2 * i + 1][2 * j] = imagem[i][j];
            }
            if (j + 1 < coluna) {
                Imagem[2 * i][2 * j + 1] = imagem[i][j];
            }
            if (i + 1 < linha && j + 1 < coluna) {
                Imagem[2 * i + 1][2 * j + 1] = imagem[i][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    abrir_arquivos(argc, argv);
    ler_cabecalho();
    ler_imagem();

    int **Interpolacao1_R = (int **)malloc(2 * nlin * sizeof(int *));
    int **Interpolacao1_G = (int **)malloc(2 * nlin * sizeof(int *));
    int **Interpolacao1_B = (int **)malloc(2 * nlin * sizeof(int *));
    vizinho1(imagemR, nlin, ncol, Interpolacao1_R);
    vizinho1(imagemG, nlin, ncol, Interpolacao1_G);
    vizinho1(imagemB, nlin, ncol, Interpolacao1_B);
    gravar_imagem(fpoutViz1, Interpolacao1_R);

    int **Interpolacao4_R = (int **)malloc(2 * nlin * sizeof(int *));
    int **Interpolacao4_G = (int **)malloc(2 * nlin * sizeof(int *));
    int **Interpolacao4_B = (int **)malloc(2 * nlin * sizeof(int *));
    Vizinho4(imagemR, nlin, ncol, Interpolacao4_R);
    Vizinho4(imagemG, nlin, ncol, Interpolacao4_G);
    Vizinho4(imagemB, nlin, ncol, Interpolacao4_B);
    gravar_imagem(fpoutViz4, Interpolacao4_R);

    fechar_arquivos();
    return 0;
}
