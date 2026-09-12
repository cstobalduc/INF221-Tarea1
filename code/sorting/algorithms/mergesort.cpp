// Fuentes consultadas: CLRS / GeeksforGeeks adaptado para optimizarlo con los casos de la tarea, sino el tiempo no es el optimo
#include <vector>

void merge(std::vector<int>& vec, std::vector<int>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    // Mezclar ambas mitades directamente usando el vector temporal
    while (i <= mid && j <= right) {
        if (vec[i] <= vec[j]) {
            temp[k++] = vec[i++];
        } else {
            temp[k++] = vec[j++];
        }
    }

    while (i <= mid) temp[k++] = vec[i++];
    while (j <= right) temp[k++] = vec[j++];

    // Copiar de regreso al arreglo original
    for (int idx = left; idx <= right; idx++) {
        vec[idx] = temp[idx];
    }
}

void mergeSortRecursive(std::vector<int>& vec, std::vector<int>& temp, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRecursive(vec, temp, left, mid);
        mergeSortRecursive(vec, temp, mid + 1, right);
        merge(vec, temp, left, mid, right);
    }
}

// funcion principal a invocar desde sorting
void mergeSort(std::vector<int>& vec) {
    if (vec.size() <= 1) return;
    std::vector<int> temp(vec.size()); // Se asigna la memoria una sola vez
    mergeSortRecursive(vec, temp, 0, static_cast<int>(vec.size()) - 1);
}