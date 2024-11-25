# Código Python para gerar o arquivo matriz.txt
import random

# Define o tamanho da matriz
rows, cols = 3, 3

# Cria a matriz com números aleatórios
matriz = [[random.randint(1, 9) for _ in range(cols)] for _ in range(rows)]

# Abre o arquivo para escrita
with open('matriz.txt', 'w') as f:
    for row in matriz:
        f.write(" ".join(map(str, row)) + "\n")

print("Arquivo 'matriz.txt' gerado com sucesso!")

