import random

def generar_matriz(valores_random):
    matriz = [[0 if i == j else (random.randint(1, 10) if valores_random else 1) 
               for j in range(26)] for i in range(26)]
    return matriz

# Generar la matriz con valores aleatorios fuera de la diagonal principal
valores_random = True  # Cambia a False para que todos los valores fuera de la diagonal sean 1
matriz = generar_matriz(valores_random)

# Imprimir la matriz
for fila in matriz:
    print(fila)