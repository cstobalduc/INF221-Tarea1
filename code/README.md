# Tarea 1: Análisis Experimental de Algoritmos (INF-221)

**Estudiante:** Cristóbal Alonso Duarte Canales
**Rol USM:** 202473057-6
**Campus:** San Joaquín
**Asignatura:** Algoritmos y Complejidad (INF-221, 2026-2)
**Repositorio GitHub:** [https://github.com/cstobalduc/INF221-Tarea1](https://github.com/cstobalduc/INF221-Tarea1)

---

## 1. Descripción del Proyecto

Este proyecto evalúa empíricamente el rendimiento temporal y espacial de dos problemas clásicos frente a sus cotas asintóticas teóricas:
1. **Ordenamiento de arreglos unidimensionales:** MergeSort, QuickSort (pivote aleatorio y partición de Hoare), PatienceSort y `std::sort` (Introsort de la biblioteca estándar de C++).
2. **Multiplicación de matrices cuadradas:** Enfoque iterativo tradicional (Naive $\Theta(n^3)$) y algoritmo Divide y Vencerás de Strassen ($\mathcal{O}(n^{\log_2 7}) \approx \mathcal{O}(n^{2.81})$).

---

## 2. Requisitos del Sistema y Dependencias

- **Compilador C++:** `clang++` o `g++` con soporte para estándar `C++17` y bandera `-O2`.
- **Python:** Versión `3.8` o superior con las siguientes bibliotecas de análisis de datos:
  ```bash
  pip3 install matplotlib pandas numpy
  ```
- **Entorno:** Compatible con sistemas tipo UNIX (macOS / Linux) mediante la llamada al sistema `getrusage` para la medición de memoria RAM residente.

---

## 3. Estructura de Directorios

```text
code/
├── sorting/
│   ├── algorithms/            # Implementaciones en C++ (mergesort, quicksort, patiencesort, sort)
│   ├── data/
│   │   ├── array_input/       # Instancias de prueba generadas (.txt)
│   │   ├── array_output/      # Salidas ordenadas (.txt)
│   │   ├── measurements/      # mediciones.csv
│   │   └── plots/             # Gráficos generados (.png)
│   ├── scripts/
│   │   ├── array_generator.py # Generador de datos
│   │   └── plot_generator.py  # Generador de gráficos
│   ├── sorting.cpp            # Programa principal de benchmarking
│   └── Makefile
│
└── matrix_multiplication/
    ├── algorithms/            # Implementaciones en C++ (naive, strassen)
    ├── data/
    │   ├── matrix_input/      # Matrices de entrada (.txt)
    │   ├── matrix_output/     # Matrices resultantes (.txt)
    │   ├── measurements/      # mediciones.csv
    │   └── plots/             # Gráficos generados (.png)
    ├── scripts/
    │   ├── matrix_generator.py # Generador de matrices
    │   └── plot_generator.py  # Generador de gráficos
    ├── matrix_multiplication.cpp # Programa principal de benchmarking
    └── Makefile
```

---

## 4. Instrucciones de Ejecución

Para reproducir los test de forma completa, siga las instrucciones de cada submódulo. Asegúrese de generar primero las entradas antes de correr los benchmarks de C++.

### A. Ordenamiento de Arreglos (`code/sorting`)

1. Posicionarse en el directorio del módulo:
   ```bash
   cd code/sorting
   ```
2. Generar las instancias de prueba ($N \in \{10^1, 10^3, 10^5, 10^7\}$):
   ```bash
   cd scripts
   python3 array_generator.py
   cd ..
   ```
3. Compilar y ejecutar las mediciones en C++:
   ```bash
   make clean
   make run
   ```
   *Esto procesará los arreglos, generará las salidas en `data/array_output/` y guardará los tiempos y memoria en `data/measurements/mediciones.csv`.*
4. Generar las curvas comparativas:
   ```bash
   cd scripts
   python3 plot_generator.py
   cd ..
   ```
   *Las figuras PNG se almacenarán en la carpeta `data/plots/`.*

### B. Multiplicación de Matrices (`code/matrix_multiplication`)

1. Posicionarse en el directorio del módulo:
   ```bash
   cd code/matrix_multiplication
   ```
2. Generar las matrices cuadradas de prueba ($N \in [2^1, 2^8]$):
   ```bash
   cd scripts
   python3 matrix_generator.py
   cd ..
   ```
3. Compilar y ejecutar el benchmark en C++:
   ```bash
   make clean
   make run
   ```
   *El programa calculará las multiplicaciones, generará las matrices producto en `data/matrix_output/` y guardará el registro en `data/measurements/mediciones.csv`.*
4. Generar las curvas comparativas:
   ```bash
   cd scripts
   python3 plot_generator.py
   cd ..
   ```
   *Las figuras PNG se almacenarán en la carpeta `data/plots/`.*

---

## 5. Referencias y Bibliografía

1. **Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009).** *Introduction to Algorithms* (3rd ed.). The MIT Press.
2. **Knuth, D. E. (1998).** *The Art of Computer Programming, Volume 3: Sorting and Searching* (2nd ed.). Addison-Wesley.
3. **Erickson, J. (2019).** *Algorithms*. Urbana-Champaign.
4. **GeeksforGeeks.** Implementaciones de referencia algorítmica en C++.
5. **Apuntes de Cátedra INF-221.** Algoritmos y Complejidad, Universidad Técnica Federico Santa María (2026-2).