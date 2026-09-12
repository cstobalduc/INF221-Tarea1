#include <vector>

using Matrix = std::vector<std::vector<int>>;

// Funciones auxiliares para sumar y restar matrices
void addMatrix(const Matrix& A, const Matrix& B, Matrix& C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subMatrix(const Matrix& A, const Matrix& B, Matrix& C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassenMatrixMultiply(const Matrix& A, const Matrix& B, Matrix& C, int size) {
    // Caso base: Matriz de 1x1
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    Matrix a(newSize, std::vector<int>(newSize)), b(newSize, std::vector<int>(newSize)),
           c(newSize, std::vector<int>(newSize)), d(newSize, std::vector<int>(newSize)),
           e(newSize, std::vector<int>(newSize)), f(newSize, std::vector<int>(newSize)),
           g(newSize, std::vector<int>(newSize)), h(newSize, std::vector<int>(newSize)),
           c11(newSize, std::vector<int>(newSize)), c12(newSize, std::vector<int>(newSize)),
           c21(newSize, std::vector<int>(newSize)), c22(newSize, std::vector<int>(newSize)),
           p1(newSize, std::vector<int>(newSize)), p2(newSize, std::vector<int>(newSize)),
           p3(newSize, std::vector<int>(newSize)), p4(newSize, std::vector<int>(newSize)),
           p5(newSize, std::vector<int>(newSize)), p6(newSize, std::vector<int>(newSize)),
           p7(newSize, std::vector<int>(newSize)), fResult(newSize, std::vector<int>(newSize)),
           sResult(newSize, std::vector<int>(newSize));

    // Dividir las matrices en 4 submatrices iguales
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            a[i][j] = A[i][j];
            b[i][j] = A[i][j + newSize];
            c[i][j] = A[i + newSize][j];
            d[i][j] = A[i + newSize][j + newSize];

            e[i][j] = B[i][j];
            f[i][j] = B[i][j + newSize];
            g[i][j] = B[i + newSize][j];
            h[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calcular las 7 fórmulas de Strassen (p1 a p7)
    subMatrix(f, h, sResult, newSize);
    strassenMatrixMultiply(a, sResult, p1, newSize);

    addMatrix(a, b, fResult, newSize);
    strassenMatrixMultiply(fResult, h, p2, newSize);

    addMatrix(c, d, fResult, newSize);
    strassenMatrixMultiply(fResult, e, p3, newSize);

    subMatrix(g, e, sResult, newSize);
    strassenMatrixMultiply(d, sResult, p4, newSize);

    addMatrix(a, d, fResult, newSize);
    addMatrix(e, h, sResult, newSize);
    strassenMatrixMultiply(fResult, sResult, p5, newSize);

    subMatrix(b, d, fResult, newSize);
    addMatrix(g, h, sResult, newSize);
    strassenMatrixMultiply(fResult, sResult, p6, newSize);

    subMatrix(a, c, fResult, newSize);
    addMatrix(e, f, sResult, newSize);
    strassenMatrixMultiply(fResult, sResult, p7, newSize);

    // Calcular los cuadrantes de la matriz C
    addMatrix(p1, p2, c12, newSize); // c12 = p1 + p2
    addMatrix(p3, p4, c21, newSize); // c21 = p3 + p4

    addMatrix(p4, p5, fResult, newSize);
    addMatrix(fResult, p6, sResult, newSize);
    subMatrix(sResult, p2, c11, newSize); // c11 = p4 + p5 + p6 - p2

    subMatrix(p1, p3, fResult, newSize);
    addMatrix(fResult, p5, sResult, newSize);
    subMatrix(sResult, p7, c22, newSize); // c22 = p1 - p3 + p5 - p7

    // Agrupar los resultados en la matriz final C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = c11[i][j];
            C[i][j + newSize] = c12[i][j];
            C[i + newSize][j] = c21[i][j];
            C[i + newSize][j + newSize] = c22[i][j];
        }
    }
}