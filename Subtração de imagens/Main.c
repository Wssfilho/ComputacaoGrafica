#include <stdio.h>
#include <stdlib.h>

FILE *fpin1, *fpin2, *fpout_movimento, *fpout_seg, *fpin, *fpout;
float percentual_erro = 0.0; // delcaração de variáveis globais

void abrir_arquivos(int argc, char *argv[]);
void ler_cabecalho(FILE *fpin, int *ncol, int *nlin, int *quant_nivel_cinza);
void ler_imagem(FILE *fpin, int **imagemR, int **imagemG, int **imagemB, int ncol, int nlin);
void gravar_cabecalho(FILE *fpout, int ncol, int nlin, int quant_nivel_cinza);
void gravar_imagem(FILE *fpout, int **imagemR, int **imagemG, int **imagemB, int ncol, int nlin);
void fechar_arquivos(void); // CABEÇALHO DE FUNÇÕES
void subtrair_imagens(int **imagem1R, int **imagem1G, int **imagem1B, int **imagem2R, int **imagem2G, int **imagem2B, int **resultadoR, int **resultadoG, int **resultadoB, int ncol, int nlin);
void normalizar_imagem(int **resultadoR, int **resultadoG, int **resultadoB, int **imagemOriginalR, int **imagemOriginalG, int **imagemOriginalB, int ncol, int nlin);
void alocar_memoria_imagem(int ***imagemR, int ***imagemG, int ***imagemB, int nlin, int ncol);
void liberar_memoria_imagem(int ***imagemR, int ***imagemG, int ***imagemB, int nlin);

int main(int argc, char *argv[])
{
    // chamadas a função e declaração de variáveis
    printf("Insira o percentual de erro: ");
    scanf("%f", &percentual_erro);
    abrir_arquivos(argc, argv);
    int ncol, nlin, quant_nivel_cinza;
    ler_cabecalho(fpin1, &ncol, &nlin, &quant_nivel_cinza);
    int **foto1R, **foto1G, **foto1B;
    alocar_memoria_imagem(&foto1R, &foto1G, &foto1B, nlin, ncol);
    ler_imagem(fpin1, foto1R, foto1G, foto1B, ncol, nlin);

    ler_cabecalho(fpin2, &ncol, &nlin, &quant_nivel_cinza);
    int **foto2R, **foto2G, **foto2B;
    alocar_memoria_imagem(&foto2R, &foto2G, &foto2B, nlin, ncol);
    ler_imagem(fpin2, foto2R, foto2G, foto2B, ncol, nlin);

    int **sub_movimentoR, **sub_movimentoG, **sub_movimentoB;
    alocar_memoria_imagem(&sub_movimentoR, &sub_movimentoG, &sub_movimentoB, nlin, ncol);
    subtrair_imagens(foto1R, foto1G, foto1B, foto2R, foto2G, foto2B, sub_movimentoR, sub_movimentoG, sub_movimentoB, ncol, nlin);

    gravar_cabecalho(fpout_movimento, ncol, nlin, quant_nivel_cinza);
    gravar_imagem(fpout_movimento, sub_movimentoR, sub_movimentoG, sub_movimentoB, ncol, nlin);

    normalizar_imagem(sub_movimentoR, sub_movimentoG, sub_movimentoB, foto1R, foto1G, foto1B, ncol, nlin);

    gravar_cabecalho(fpout_seg, ncol, nlin, quant_nivel_cinza);
    gravar_imagem(fpout_seg, sub_movimentoR, sub_movimentoG, sub_movimentoB, ncol, nlin);

    fechar_arquivos();

    liberar_memoria_imagem(&foto1R, &foto1G, &foto1B, nlin);
    liberar_memoria_imagem(&foto2R, &foto2G, &foto2B, nlin);
    liberar_memoria_imagem(&sub_movimentoR, &sub_movimentoG, &sub_movimentoB, nlin);

    return 0;
}

void abrir_arquivos(int argc, char *argv[]) //Função abrir arquivo, onde chama as duas imagens utilizadas como entrada
{
    if (argc < 2)
    {
        printf("Modo correto de uso: <prog> <fotocomobj> <fotosemobj>\n");
        exit(1);
    }
    if ((fpin1 = fopen(argv[1], "r")) == NULL || (fpin2 = fopen(argv[2], "r")) == NULL)
    {
        printf("Não foi possível abrir um dos arquivos de imagem.\n");
        exit(1);
    }
    if ((fpout_movimento = fopen("SUB.ppm", "w")) == NULL || (fpout_seg = fopen("SIG.ppm", "w")) == NULL)
    {
        printf("Não foi possível abrir os arquivos de saída.\n");
        exit(1);
    }
}

void ler_cabecalho(FILE *fpin, int *ncol, int *nlin, int *quant_nivel_cinza)
{
    fscanf(fpin, "P3\n%d %d\n%d\n", ncol, nlin, quant_nivel_cinza); //funcao onde ler o cabeçalho (é necessário que NÃO HAJA COMENTÁRIO NO ARQUIVO)
}

void ler_imagem(FILE *fpin, int **imagemR, int **imagemG, int **imagemB, int ncol, int nlin) //Pega cada matriz da imagem ppm e coloca nas matrizes correspondentes a cada cor RGB
{
    for (int lin = 0; lin < nlin; lin++)
    {
        for (int col = 0; col < ncol; col++)
        {
            fscanf(fpin, "%d %d %d ", &imagemR[lin][col], &imagemG[lin][col], &imagemB[lin][col]);
        }
    }
}

void gravar_cabecalho(FILE *fpout, int ncol, int nlin, int quant_nivel_cinza) //funcao onde grava o cabeçalho!
{
    fprintf(fpout, "P3\n%d %d\n%d\n", ncol, nlin, quant_nivel_cinza);
}

void gravar_imagem(FILE *fpout, int **imagemR, int **imagemG, int **imagemB, int ncol, int nlin) //funcao onde grava as imagens
{
    for (int lin = 0; lin < nlin; lin++)
    {
        for (int col = 0; col < ncol; col++)
        {
            fprintf(fpout, "%d %d %d ", imagemR[lin][col], imagemG[lin][col], imagemB[lin][col]);
        }
        fprintf(fpout, "\n");
    }
}

void fechar_arquivos(void) //funcao onde fecha os arquivos
{
    fclose(fpin1);
    fclose(fpin2);
    fclose(fpout_movimento);
    fclose(fpout_seg);
}

void subtrair_imagens(int **imagem1R, int **imagem1G, int **imagem1B, int **imagem2R, int **imagem2G, int **imagem2B, int **resultadoR, int **resultadoG, int **resultadoB, int ncol, int nlin)
{
    //funcao subtrair imagem, onde é calculado a subtração das imagens 1 & 2:
    //É calculado para cada espaço na matriz [lin][col] a subtração e é colocado em outras matrizes correspondentes, ou seja, R X R, G X G, e B X B;
    for (int lin = 0; lin < nlin; lin++)
    {
        for (int col = 0; col < ncol; col++)
        {
            int diferencaR = abs(imagem1R[lin][col] - imagem2R[lin][col]); //subtração das matrizes, com utilização da funcao abs (pega somente os valores absolutors, ou seja 0+)
            int diferencaG = abs(imagem1G[lin][col] - imagem2G[lin][col]);
            int diferencaB = abs(imagem1B[lin][col] - imagem2B[lin][col]);
            if ((diferencaR > percentual_erro) || (diferencaG > percentual_erro) || (diferencaB > percentual_erro)) //onde tudo acontece: se for detectado movimento, ou seja falta de algum pixel
            { //ao longo da imagem de subtração essa for maior que a diferença que usamos para saber se houve movimento ou não. Se for detectado, faz a substituição desses pixel por 255 (branco) em cada matriz de cor
                resultadoR[lin][col] = 255; //na imagem de resultado da subtração acima.
                resultadoG[lin][col] = 255;
                resultadoB[lin][col] = 255;
            }
            else //caso não seja movimento, os pixels (espacos da matriz) recebe 0 (baixa luminosidade), o que faz a foto de subtração destacar silhueta do objeto movimentado
            {
                resultadoR[lin][col] = 0;
                resultadoG[lin][col] = 0;
                resultadoB[lin][col] = 0;
            }
        }
    }
}

void normalizar_imagem(int **resultadoR, int **resultadoG, int **resultadoB, int **imagemOriginalR, int **imagemOriginalG, int **imagemOriginalB, int ncol, int nlin)
{ //funcao usada para retornar uma imagem que esteja normalizada, ou seja, pegar a imagem da subtração e devolver os pixels originais da imagem com objeto para o espaço em branco gerado pela subtração()
    for (int lin = 0; lin < nlin; lin++)
    {
        for (int col = 0; col < ncol; col++)
        {
            if (resultadoR[lin][col] != 0 && resultadoG[lin][col] != 0 && resultadoB[lin][col] != 0) //para cada pixel, espaço da matriz resultado (matriz de sub), haverá uma comparação se os pixeis são diferentes de (0,0,0)
            { //se tais espaços da matriz estão em branco, entao devolva os pixels originais para esse espaço
                resultadoR[lin][col] = (imagemOriginalR[lin][col]);
                resultadoG[lin][col] = (imagemOriginalG[lin][col]);
                resultadoB[lin][col] = (imagemOriginalB[lin][col]);
            }
            else //então se for (0,0,0) significa que ali tem baixa luminosidade, ou seja, continua 0,0,0. Essa parte não seria necessário, mas usamos para garantir que os espaços continuarão em 0,0,0
            {
                resultadoR[lin][col] = 0;
                resultadoG[lin][col] = 0;
                resultadoB[lin][col] = 0;
            }
        }
    }
}

void alocar_memoria_imagem(int ***imagemR, int ***imagemG, int ***imagemB, int nlin, int ncol) //funcão para alocação dinâmica de memória
{
    *imagemR = (int **)malloc(nlin * sizeof(int *));
    *imagemG = (int **)malloc(nlin * sizeof(int *));
    *imagemB = (int **)malloc(nlin * sizeof(int *));
    for (int i = 0; i < nlin; i++)
    {
        (*imagemR)[i] = (int *)malloc(ncol * sizeof(int));
        (*imagemG)[i] = (int *)malloc(ncol * sizeof(int));
        (*imagemB)[i] = (int *)malloc(ncol * sizeof(int));
    }
}

void liberar_memoria_imagem(int ***imagemR, int ***imagemG, int ***imagemB, int nlin) //função de liberação de memória!
{
    for (int i = 0; i < nlin; i++)
    {
        free((*imagemR)[i]);
        free((*imagemG)[i]);
        free((*imagemB)[i]);
    }
    free(*imagemR);
    free(*imagemG);
    free(*imagemB);
}
