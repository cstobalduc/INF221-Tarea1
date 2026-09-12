#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
#include <sys/resource.h>

using Matrix = std::vector<std::vector<int>>;

//declaraciones de los algoritmos
void naiveMatrixMultiply(const Matrix& A, const Matrix& B, Matrix& C, int n);
void strassenMatrixMultiply(const Matrix& A, const Matrix& B, Matrix& C, int size);

//medicion de memoria RAM máxima utilizada (en KB)
long getPeakMemoryKB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
#ifdef __APPLE__
    return usage.ru_maxrss / 1024;
#else
    return usage.ru_maxrss;
#endif
}

//carga una matriz cuadrada de tamaño n x n desde disco a RAM
Matrix readMatrix(const std::string& filename, int n) {
    Matrix M(n, std::vector<int>(n));
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada: " << filename << "\n";
        exit(1);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            infile >> M[i][j];
        }
    }
    return M;
}

// Guarda la matriz resultante en un archivo de texto
void writeMatrix(const Matrix& M, const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error al crear el archivo de salida: " << filename << "\n";
        exit(1);
    }
    for (const auto& row : M) {
        for (size_t j = 0; j < row.size(); ++j) {
            outfile << row[j] << (j == row.size() - 1 ? "" : " ");
        }
        outfile << "\n";
    }
}

int main(int argc, char* argv[]) {
    // Control estricto de parámetros ingresados por terminal
    if (argc != 6) {
        std::cerr << "Uso: " << argv[0] << " <algoritmo> <N> <tipo> <dominio> <muestra>\n";
        return 1;
    }

    std::string algoritmo = argv[1];
    int n = std::stoi(argv[2]);
    std::string tipo = argv[3];
    std::string dominio = argv[4];
    std::string muestra = argv[5];

    // construccion de rutas de archivos basada en la estructura del proyecto

    std::string base_name = std::to_string(n) + "_" + tipo + "_" + dominio + "_" + muestra;
    std::string fileA = "data/matrix_input/" + base_name + "_1.txt";
    std::string fileB = "data/matrix_input/" + base_name + "_2.txt";
    std::string fileOut = "data/matrix_output/" + base_name + "_out.txt";

    // Cargar datos en memoria
    Matrix A = readMatrix(fileA, n);
    Matrix B = readMatrix(fileB, n);
    Matrix C(n, std::vector<int>(n, 0));

    //cedir tiempo de procesamiento CPU
    auto start_time = std::chrono::high_resolution_clock::now();

    if (algoritmo == "naive") {
        naiveMatrixMultiply(A, B, C, n);
    } else if (algoritmo == "strassen") {
        strassenMatrixMultiply(A, B, C, n);
    } else {
        std::cerr << "Error: Algoritmo no reconocido (" << algoritmo << "). Usa 'naive' o 'strassen'.\n";
        return 1;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    // otener consumo de RAM
    long peak_mem = getPeakMemoryKB();

    // guardar metricas en CSV
    std::ofstream out_csv("data/measurements/mediciones.csv", std::ios::app);
    if (out_csv.is_open()) {
        out_csv << algoritmo << "," << n << "," << tipo << "," << dominio << "," << muestra << ","
                << duration_ms << "," << peak_mem << "\n";
    }

    // guardar la matriz
    writeMatrix(C, fileOut);

    return 0;
}