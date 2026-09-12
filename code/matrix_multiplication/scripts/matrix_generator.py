import numpy as np
import os
import random
from itertools import product

def generar_matriz(n, tipo, dominio):
    if dominio == 'D0':
        valores = [0, 1]
    elif dominio == 'D10':
        valores = list(range(10))
    else:
        raise ValueError("Dominio no valido. Usa 'D0' o 'D10'.")

    if tipo == 'densa':
        matriz = np.random.choice(valores, size=(n, n))
    elif tipo == 'diagonal':
        matriz = np.zeros((n, n), dtype=int)
        diag_vals = np.random.choice(valores, size=n)
        np.fill_diagonal(matriz, diag_vals)
    elif tipo == 'dispersa':
        matriz = np.zeros((n, n), dtype=int)
        cantidad = max(1, (n * n) // 10)

        # Optimización NumPy: elegir coordenadas únicas para no sobreescribir celdas
        indices_plano = np.random.choice(n * n, cantidad, replace=False)
        filas = indices_plano // n
        columnas = indices_plano % n

        # Rellenar con valores distintos de cero
        valores_no_cero = [v for v in valores if v != 0]
        matriz[filas, columnas] = np.random.choice(valores_no_cero, size=cantidad)
    else:
        raise ValueError("Tipo no válido.")

    return matriz

def guardar_matriz(matriz, nombre_archivo):
    with open(nombre_archivo, 'w') as f:
        for fila in matriz:
            f.write(' '.join(map(str, fila)) + '\n')

def generar_y_guardar(n, t, d, m, carpeta="../data/matrix_input"):
    # Asegurar que la carpeta de destino exista
    os.makedirs(carpeta, exist_ok=True)

    M1 = generar_matriz(n, t, d)
    M2 = generar_matriz(n, t, d)

    base = f"{n}_{t}_{d}_{m}"
    archivo1 = os.path.join(carpeta, f"{base}_1.txt")
    archivo2 = os.path.join(carpeta, f"{base}_2.txt")

    guardar_matriz(M1, archivo1)
    guardar_matriz(M2, archivo2)

def generar_todos():
    # Potencias de 2 desde 2^1 hasta 2^9 (2, 4, 8, 16, 32, 64, 128, 256, 512)
    Ns = [2**k for k in range(1, 9)]
    Ts = ["dispersa", "diagonal", "densa"]
    Ds = ["D0", "D10"]
    Ms = ["a", "b", "c"]

    total = len(Ns) * len(Ts) * len(Ds) * len(Ms)
    print(f"Generando {total * 2} archivos de matrices...")

    for n, t, d, m in product(Ns, Ts, Ds, Ms):
        generar_y_guardar(n, t, d, m)

    print("Todas las matrices se generaron exitosamente.")

if __name__ == "__main__":
    generar_todos()