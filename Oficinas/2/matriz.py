import serial
import time
import numpy as n

# Configuração da porta serial (ajuste conforme necessário)
arduino_port = 'COM9'  # Porta serial no Windows
baud_rate = 9600 # Deve ser o mesmo que no código do Arduinop


time.sleep(2)  # Aguarda o Arduino inicializar
arduino = serial.Serial(arduino_port, baud_rate)


# Gera a matriz 50x50 com 1 na diagonal
res = 50
matriz = np.zeros((res, res), dtype=int)
np.fill_diagonal(matriz, 1)

# Envia a matriz para o Arduino
print("Enviando a matriz para o Arduino...")
for i in range(res):
    for j in range(res):
        ser.write(f"{matriz[i][j]}\n".encode())  # Envia cada valor de matriz como uma linha
        time.sleep(0.01)  # Ajuste o delay conforme necessário para não sobrecarregar a comunicação

# Função para aguardar e confirmar o feedback do Arduino
def wait_for_feedback():
    # Aguarda o Arduino processar o movimento e, em seguida, imprime o feedback
    print("Movimento concluído. Aguardando próximo...")

# Recebe feedback após o envio da matriz
for i in range(res):
    for j in range(res):
        if matriz[i][j] == 1:
            wait_for_feedback()  # Simula feedback após cada movimento

# Fecha a comunicação serial
ser.close()
print("Comunicação encerrada.")

