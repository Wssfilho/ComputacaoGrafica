import cv2
import numpy as np

# Função para realizar a interpolação de 1-vizinhança
def vizinho1(image):
    linha, coluna, fim = image.shape
    Imagem = np.zeros((2 * linha, 2 * coluna, fim), dtype=np.uint8)

    for i in range(linha):
        for j in range(coluna):
            pixel = image[i, j]
            Imagem[2 * i, 2 * j] = pixel

    return Imagem

# Função para realizar a interpolação de 4-vizinhança
def Vizinho4(image):
    linha, coluna, fim = image.shape
    Imagem = np.zeros((2 * linha, 2 * coluna, fim), dtype=np.uint8)

    for i in range(linha):
        for j in range(coluna):
            pixel = image[i, j]
            Imagem[2 * i, 2 * j] = pixel

            if i + 1 < linha:
                Imagem[2 * i + 1, 2 * j] = pixel
            if j + 1 < coluna:
                Imagem[2 * i, 2 * j + 1] = pixel
            if i + 1 < linha and j + 1 < coluna:
                Imagem[2 * i + 1, 2 * j + 1] = pixel

    return Imagem

# Ler a imagem de entrada
input_image = cv2.imread('/home/yuri/Área de Trabalho/imagem/cavalo.png')

# Ler os valores de m e n via teclado
m = int(input("Digite o valor de m: "))
n = int(input("Digite o valor de n: "))

# Realizar a interpolação de 1-vizinhança
Interpolacao1 = vizinho1(input_image)

# Realizar a interpolação de 4-vizinhança
Interpolacao4 = Vizinho4(input_image)

# Salvar as imagens interpoladas
cv2.imwrite('1_Vizinho.png', Interpolacao1)
cv2.imwrite('4_Vizinho.png', Interpolacao4)

print("Imagens interpoladas foram salvas") 