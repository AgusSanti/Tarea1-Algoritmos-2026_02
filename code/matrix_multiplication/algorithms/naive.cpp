/**
 * ============================================================================
 * Tarea 1: Algoritmos de Ordenamiento y Multiplicación de Matrices
 * Ramo:     INF-221 Algoritmos y Complejidad
 * Semestre: 2026-2
 * Autor:    Agustin Ignacio Santibañez Perez
 * Rol:      [202204682-1]
 * Referencias:
 * - Cormen et al. (2022). Introduction to Algorithms (4th ed.), Cap. 4.
 * - Hennessy & Patterson (2017). Computer Architecture (optimizacion de bucles i-k-j).
 * ============================================================================
 */

#include <vector>

void naive_multiply(const std::vector<std::vector<int>>& A, 
                    const std::vector<std::vector<int>>& B, 
                    std::vector<std::vector<int>>& C, 
                    int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            int r = A[i][k];
            for (int j = 0; j < n; ++j) {
                C[i][j] += r * B[k][j];
            }
        }
    }
}
