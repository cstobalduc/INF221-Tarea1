import pandas as pd
import matplotlib.pyplot as plt
import os

CSV_PATH = "../data/measurements/mediciones.csv"
PLOT_DIR = "../data/plots"

# crear carpeta de destino si no existe
os.makedirs(PLOT_DIR, exist_ok=True)

try:
    # cargar los datos (sin encabezados en el CSV original)
    columnas = ["Algoritmo", "N", "Tipo", "Dominio", "Muestra", "Tiempo_ms", "Memoria_KB"]
    df = pd.read_csv(CSV_PATH, names=columnas)

    # agrupar y promediar las 3 muestras
    df_avg = df.groupby(["Algoritmo", "N", "Tipo", "Dominio"]).mean(numeric_only=True).reset_index()

    tipos = df_avg['Tipo'].unique()
    dominios = df_avg['Dominio'].unique()

    # generar un grafico por cada combinación de tipo y domnonio
    for tipo in tipos:
        for dominio in dominios:
            subset = df_avg[(df_avg['Tipo'] == tipo) & (df_avg['Dominio'] == dominio)]
            if subset.empty:
                continue

            plt.figure(figsize=(12, 5))

            # grafico 1: tiemppo vs n
            plt.subplot(1, 2, 1)
            for alg in subset['Algoritmo'].unique():
                data_alg = subset[subset['Algoritmo'] == alg].sort_values("N")
                plt.plot(data_alg['N'], data_alg['Tiempo_ms'], marker='o', label=alg)

            plt.xscale('log')
            plt.yscale('log') # Escala Log-Log para ver claramente las curvas O(n log n) vs O(n^2)
            plt.title(f'Tiempo de Ejecución - {tipo.capitalize()} ({dominio})')
            plt.xlabel('Tamaño del Arreglo (N)')
            plt.ylabel('Tiempo (ms)')
            plt.legend()
            plt.grid(True, which="both", ls="--", alpha=0.5)

            # grafico 2: memoria vs n
            plt.subplot(1, 2, 2)
            for alg in subset['Algoritmo'].unique():
                data_alg = subset[subset['Algoritmo'] == alg].sort_values("N")
                plt.plot(data_alg['N'], data_alg['Memoria_KB'], marker='s', label=alg)

            plt.xscale('log')
            plt.title(f'Consumo de Memoria - {tipo.capitalize()} ({dominio})')
            plt.xlabel('Tamaño del Arreglo (N)')
            plt.ylabel('Memoria Pico (KB)')
            plt.legend()
            plt.grid(True, which="both", ls="--", alpha=0.5)

            # guardar imagen
            filename = f"{PLOT_DIR}/sorting_{tipo}_{dominio}.png"
            plt.tight_layout()
            plt.savefig(filename)
            plt.close()

    print(f"Graficos generados en {PLOT_DIR}/")

except FileNotFoundError:
    print(f"Error: No se encontro el archivo {CSV_PATH}.")