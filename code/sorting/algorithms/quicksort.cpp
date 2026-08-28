/**
 * ============================================================================
 * Tarea 1: Algoritmos de Ordenamiento y Multiplicación de Matrices
 * Ramo:     INF-221 Algoritmos y Complejidad
 * Semestre: 2026-2
 * Autor:    Agustin Ignacio Santibañez Perez
 * Rol:      [202204682-1]
 * Referencias: 
 * - Hoare, C. A. R. (1961). "Algorithm 64: Quicksort"
 * - Cormen, T. H. et al. "Introduction to Algorithms" (CLRS)
 * ============================================================================
 */

#include <vector>
#include <algorithm>

void quick_sort_rec(std::vector<int>& arr, int low, int high) {
    int i = low;
    int j = high;
    int pivot = arr[low + (high - low) / 2];

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (low < j) {
        quick_sort_rec(arr, low, j);
    }
    if (i < high) {
        quick_sort_rec(arr, i, high);
    }
}

void quicksort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;
    quick_sort_rec(arr, 0, static_cast<int>(arr.size()) - 1);
}
