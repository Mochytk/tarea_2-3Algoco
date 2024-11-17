import os

# Crear la carpeta 'costos' si no existe
os.makedirs("costos", exist_ok=True)

with open("costos/cost_replace.txt", "w") as archivo:
    for i in range(26):
        text = ""
        for j in range(26):
            if i == j:
                text += "0 "
            else:
                text += "2 "
        archivo.write(text + "\n")

with open("costos/cost_transpose.txt", "w") as archivo:
    for i in range(26):
        text = ""
        for j in range(26):
            if i == j:
                text += "0 "
            else:
                text += "1 "
        archivo.write(text + "\n")

with open("costos/cost_delete.txt", "w") as archivo:
    text = "1 "
    archivo.write(text * 26 + "\n")

with open("costos/cost_insert.txt", "w") as archivo:
    text = "1 "
    archivo.write(text * 26 + "\n")