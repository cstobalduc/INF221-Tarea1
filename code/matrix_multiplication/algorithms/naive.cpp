#include <vector>

using Matrix = std::vector<std::vector<int>>;

void naiveMatrixMultiply(const Matrix& A, const Matrix& B, Matrix& C, int n) {
    // Inicializar la matriz C con ceros y multiplicar
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}