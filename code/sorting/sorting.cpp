#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
#include <algorithm> // Para std::sort
#include <sys/resource.h>

//funciones en los otros archivos
void mergeSort(std::vector<int>& vec);
void quickSort(std::vector<int>& vec);
void patienceSort(std::vector<int>& vec);
std::vector<int> sortArray(std::vector<int>& arr);
// funcion para medir memoria pico (Peak RAM)
long getPeakMemoryKB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
#ifdef __APPLE__
    return usage.ru_maxrss / 1024; // macOS devuelve bytes, lo pasamos a KB
#else
    return usage.ru_maxrss;        // Linux (servidores de la U) devuelve KB
#endif
}

int main(int argc, char* argv[]) {
    // Validar argumentos de entrada
    if (argc != 6) {
        std::cerr << "Uso: ./sorting <algoritmo> <n> <tipo> <dominio> <muestra>\n";
        return 1;
    }

    std::string algoritmo = argv[1];
    std::string n_str = argv[2];
    std::string tipo = argv[3];
    std::string dominio = argv[4];
    std::string muestra = argv[5];

    // leer el archivo de entrada
    std::string input_path = "data/array_input/" + n_str + "_" + tipo + "_" + dominio + "_" + muestra + ".txt";
    std::ifstream infile(input_path);
    if (!infile) {
        std::cerr << "error al abrir archivo: " << input_path << "\n";
        return 1;
    }

    std::vector<int> arr;
    int val;
    while (infile >> val) {
        arr.push_back(val);
    }
    infile.close();

    // medir el tiempo exclusivo del algoritmo
    auto start_time = std::chrono::high_resolution_clock::now();

    if (algoritmo == "mergesort") {
        mergeSort(arr);
    } else if (algoritmo == "quicksort") {
        quickSort(arr);
    } else if (algoritmo == "patiencesort") {
        patienceSort(arr);
    } else if (algoritmo == "stdsort") {
        sortArray(arr);
    } else {
        std::cerr << "Algoritmo no reconocido.\n";
        return 1;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    double duration_ms = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    // obtener consumo de memoria
    long memory_kb = getPeakMemoryKB();

    // guardar metricas en measurements_sorting
    std::ofstream out_csv("data/measurements/mediciones.csv", std::ios::app);
    out_csv << algoritmo << "," << n_str << "," << tipo << "," << dominio << "," << muestra << ","
            << duration_ms << "," << memory_kb << "\n";
    out_csv.close();

    // construccion del nombre base del archivo
    std::string base_name = std::to_string(arr.size()) + "_" + tipo + "_" + dominio + "_" + muestra;

    // ruta de salida en la carpeta
    std::string out_path = "data/array_output/" + base_name + "_out.txt";

    std::ofstream outfile(out_path);
    if (!outfile.is_open()) {
        std::cerr << "Error al crear el archivo de salida: " << out_path << "\n";
        return 1;
    }

    for (size_t i = 0; i < arr.size(); ++i) {
        outfile << arr[i] << (i + 1 == arr.size() ? "" : " ");
    }
    outfile << "\n";
    outfile.close();
}