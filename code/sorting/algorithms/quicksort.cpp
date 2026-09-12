// Fuentes consultadas: GeeksforGeeks (adaptado con pivote aleatorio)
#include <vector>
#include <cstdlib>
#include <algorithm>

int partitionHoare(std::vector<int>& vec, int low, int high) {
    // elegir pivote aleatorio para evitar peor caso en arreglos ordenados
    int random_idx = low + std::rand() % (high - low + 1);
    int pivot = vec[random_idx];

    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (vec[i] < pivot);

        do {
            j--;
        } while (vec[j] > pivot);

        if (i >= j) return j;

        std::swap(vec[i], vec[j]);
    }
}

void quickSortRecursive(std::vector<int>& vec, int low, int high) {
    if (low < high) {
        int pi = partitionHoare(vec, low, high);
        //en la partición de Hoare, el corte recursivo va de low a pi, y pi+1 a high
        quickSortRecursive(vec, low, pi);
        quickSortRecursive(vec, pi + 1, high);
    }
}

void quickSort(std::vector<int>& vec) {
    if (vec.size() <= 1) return;
    quickSortRecursive(vec, 0, static_cast<int>(vec.size()) - 1);
}