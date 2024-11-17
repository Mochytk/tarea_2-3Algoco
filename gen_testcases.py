import os
import random
import string

# Crear una carpeta para los archivos de casos de prueba
os.makedirs("testcases", exist_ok=True)
os.makedirs("testcases/test1", exist_ok=True)
os.makedirs("testcases/test2", exist_ok=True)
os.makedirs("testcases/test3", exist_ok=True)
os.makedirs("testcases/test4", exist_ok=True)
os.makedirs("testcases/test5", exist_ok=True)

# Función para generar una cadena aleatoria de longitud dada
def generar_cadena(longitud):
    return ''.join(random.choices(string.ascii_lowercase, k=longitud))

def generar_cadena_repetida(largo, repetidos):
    # Generamos un conjunto de caracteres únicos para cada cadena
    caracteres_1 = random.sample(string.ascii_lowercase, repetidos)
    caracteres_2 = [c for c in string.ascii_lowercase if c not in caracteres_1]
    caracteres_2 = random.sample(caracteres_2, repetidos)
    
    # Generamos las cadenas repitiendo los caracteres
    cadena_1 = ''.join(random.choices(caracteres_1, k=largo))
    cadena_2 = ''.join(random.choices(caracteres_2, k=largo))
    
    return cadena_1, cadena_2


def generar_cadenas_intercaladas(largo):
    # Elegimos dos letras aleatorias distintas
    letra1, letra2 = random.sample(string.ascii_lowercase, 2)
    
    cadena1 = ""
    cadena2 = ""
    
    # Generamos las cadenas intercaladas
    for i in range(largo):
        if i % 2 == 0:
            cadena1 += letra1
            cadena2 += letra2
        else:
            cadena1 += letra2
            cadena2 += letra1
    
    return cadena1, cadena2

# Parámetros de generación de casos de prueba
tamanos = [10, 50, 100, 500, 1000]  # Diferentes tamaños de cadena para probar el rendimiento
num_casos = 5  # Número de casos de prueba por tamaño

# Generar archivos de casos de prueba

# Generar archivo para test1
with open(f"testcases/test1/testcase1.txt", "w") as archivo:
    cadena1 = ""
    cadena2 = ""
    archivo.write(f"{cadena1} {cadena2}\n")

# Generar archivos para test2
for tamano in tamanos:
    with open(f"testcases/test2/testcase_{tamano}.txt","w") as archivo:
        for _ in range(num_casos):
            cadena1, cadena2 = generar_cadena_repetida(tamano, 3)
            archivo.write(f"{cadena1} {cadena2}\n")

# Generar archivos para test3
for tamano in tamanos:
    with open(f"testcases/test3/testcase_{tamano}.txt","w") as archivo:
        for _ in range(num_casos):
            cadena1, cadena2 = generar_cadenas_intercaladas(tamano)
            archivo.write(f"{cadena1} {cadena2}\n")

# Palabras de Ejemplo, pueden ser modificadas
palabras_invertidas = [
    "arodatupmoc",  # computadora
    "etnafele",     # elefante
    "anatnev",      # ventana
    "noicamargorp", # programación
    "ollarased"     # desarrollo
]

# Generar archivos para test4
for tamano in tamanos:
    with open(f"testcases/test4/testcase_{tamano}.txt","w") as archivo:
        for i in range(num_casos):
            cadena1 = palabras_invertidas[i-1]
            cadena2 = ''.join(reversed(palabras_invertidas[i-1]))
            archivo.write(f"{cadena1} {cadena2}\n")

for tamano in tamanos:
    with open(f"testcases/test5/testcase_{tamano}.txt", "w") as archivo:
        for _ in range(num_casos):
            cadena1 = generar_cadena(tamano)
            cadena2 = generar_cadena(tamano)
            archivo.write(f"{cadena1} {cadena2}\n")
    print(f"Archivo de casos de prueba para tamaño {tamano} generado.")

print("Generación de casos de prueba completada.")