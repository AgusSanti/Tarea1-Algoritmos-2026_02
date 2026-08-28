/**
 * ============================================================================
 * Tarea 1: Algoritmos de Ordenamiento y Multiplicación de Matrices
 * Ramo:     INF-221 Algoritmos y Complejidad
 * Semestre: 2026-2
 * Autor:    Agustin Ignacio Santibañez Perez
 * Rol:      [202204682-1]
 * Referencia: Introducción a los Algoritmos (CLRS) / GeeksforGeeks
 * ============================================================================
 */

#include <vector>

void merge(std::vector<int>& arr, std::vector<int>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (int idx = left; idx <= right; ++idx) {
        arr[idx] = temp[idx];
    }
}

void merge_sort_rec(std::vector<int>& arr, std::vector<int>& temp, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    merge_sort_rec(arr, temp, left, mid);
    merge_sort_rec(arr, temp, mid + 1, right);
    merge(arr, temp, left, mid, right);
}

void mergesort(std::vector<int>& arr) {
    if (arr.empty()) return;
    std::vector<int> temp(arr.size());
    merge_sort_rec(arr, temp, 0, static_cast<int>(arr.size()) - 1);
}
