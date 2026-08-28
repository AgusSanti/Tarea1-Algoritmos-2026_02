/**
 * INF-221 Tarea 1: Algoritmos y Complejidad
 * Algoritmo: Quick Sort (Optimizado con Pivote Central / Mediana)
 * Referencias: 
 * - Hoare, C. A. R. (1961). "Algorithm 64: Quicksort"
 * - Cormen, T. H. et al. "Introduction to Algorithms" (CLRS)
 */

#include <vector>
#include <algorithm>

void quick_sort_rec(std::vector<int>& arr, int low, int high) {
    int i = low;
    int j = high;
    //Seleccionar el pivote en el punto medio para mitigar el peor caso en datos ordenados
    int pivot = arr[low + (high - low) / 2];

    //Esquema de partición bidireccional
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    //Llamadas recursivas sobre los sub-arreglos resultantes
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