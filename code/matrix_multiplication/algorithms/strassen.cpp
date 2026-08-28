/**
 * ============================================================================
 * Tarea 1: Algoritmos de Ordenamiento y Multiplicación de Matrices
 * Ramo:     INF-221 Algoritmos y Complejidad
 * Semestre: 2026-2
 * Autor:    Agustin Ignacio Santibañez Perez
 * Rol:      [202204682-1]
 * Referencias:
 * Strassen, V. (1969). "Gaussian Elimination is not Optimal"
 * ============================================================================
 */

#include <vector>

void naive_multiply(const std::vector<std::vector<int>>& A, 
                    const std::vector<std::vector<int>>& B, 
                    std::vector<std::vector<int>>& C, 
                    int n);

static void add_matrix(const std::vector<std::vector<int>>& A, 
                       const std::vector<std::vector<int>>& B, 
                       std::vector<std::vector<int>>& C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
}

static void sub_matrix(const std::vector<std::vector<int>>& A, 
                       const std::vector<std::vector<int>>& B, 
                       std::vector<std::vector<int>>& C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen_rec(const std::vector<std::vector<int>>& A, 
                  const std::vector<std::vector<int>>& B, 
                  std::vector<std::vector<int>>& C, int n) {
    if (n <= 64) {
        naive_multiply(A, B, C, n);
        return;
    }

    int k = n / 2;
    std::vector<std::vector<int>> A11(k, std::vector<int>(k)), A12(k, std::vector<int>(k)),
                                 A21(k, std::vector<int>(k)), A22(k, std::vector<int>(k));
    std::vector<std::vector<int>> B11(k, std::vector<int>(k)), B12(k, std::vector<int>(k)),
                                 B21(k, std::vector<int>(k)), B22(k, std::vector<int>(k));

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    std::vector<std::vector<int>> S1(k, std::vector<int>(k)), S2(k, std::vector<int>(k));
    std::vector<std::vector<int>> M1(k, std::vector<int>(k)), M2(k, std::vector<int>(k)),
                                 M3(k, std::vector<int>(k)), M4(k, std::vector<int>(k)),
                                 M5(k, std::vector<int>(k)), M6(k, std::vector<int>(k)),
                                 M7(k, std::vector<int>(k));

    add_matrix(A11, A22, S1, k);
    add_matrix(B11, B22, S2, k);
    strassen_rec(S1, S2, M1, k);

    add_matrix(A21, A22, S1, k);
    strassen_rec(S1, B11, M2, k);

    sub_matrix(B12, B22, S2, k);
    strassen_rec(A11, S2, M3, k);

    sub_matrix(B21, B11, S2, k);
    strassen_rec(A22, S2, M4, k);

    add_matrix(A11, A12, S1, k);
    strassen_rec(S1, B22, M5, k);

    sub_matrix(A21, A11, S1, k);
    add_matrix(B11, B12, S2, k);
    strassen_rec(S1, S2, M6, k);

    sub_matrix(A12, A22, S1, k);
    add_matrix(B21, B22, S2, k);
    strassen_rec(S1, S2, M7, k);

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            C[i][j]         = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + k]     = M3[i][j] + M5[i][j];
            C[i + k][j]     = M2[i][j] + M4[i][j];
            C[i + k][j + k] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }
}

void strassen(const std::vector<std::vector<int>>& A, 
              const std::vector<std::vector<int>>& B, 
              std::vector<std::vector<int>>& C, int n) {
    if (n <= 0) return;
    strassen_rec(A, B, C, n);
}
