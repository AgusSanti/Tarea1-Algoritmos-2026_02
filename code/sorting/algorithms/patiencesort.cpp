/**
 * INF-221 Tarea 1: Algoritmos y Complejidad
 * Algoritmo: Patience Sort (Optimizado con Búsqueda Binaria y Min-Heap)
 * Referencias: 
 * - Mallows, C. L. (1962). "Patience Sorting"
 * - Aldous, D., & Diaconis, P. (1999). "Longest increasing subsequences: from patience sorting to the Baik-Deift-Johansson theorem"
 */

#include <vector>
#include <queue>
#include <algorithm>

//Estructura para almacenar el tope actual y el índice de la pila a la que pertenece
struct HeapNode {
    int value;
    size_t pile_idx;

    //Sobrecarga del operador > para que std::priority_queue actúe como un Min-Heap
    bool operator>(const HeapNode& other) const {
        return value > other.value;
    }
};

void patiencesort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;

    //FASE 1: Distribución en pilas usando Búsqueda Binaria O(n log k)
    std::vector<std::vector<int>> piles;
    std::vector<int> top_elements; // Guarda únicamente los topes para búsqueda binaria en memoria contigua

    for (int x : arr) {
        //lower_bound encuentra la primera posición donde tope >= x en O(log k)
        auto it = std::lower_bound(top_elements.begin(), top_elements.end(), x);
        size_t idx = std::distance(top_elements.begin(), it);

        if (it == top_elements.end()) {
            //Si todos los topes son menores que x, se abre una nueva pila
            piles.push_back({x});
            top_elements.push_back(x);
        } else {
            //Si encontramos una pila válida, colocamos x encima y actualizamos el tope
            piles[idx].push_back(x);
            top_elements[idx] = x;
        }
    }

    //FASE 2: Fusión K-Way Merge usando Min-Heap O(n log k)
    std::priority_queue<HeapNode, std::vector<HeapNode>, std::greater<HeapNode>> min_heap;

    //Inicializamos el heap con el elemento superior de cada pila
    for (size_t i = 0; i < piles.size(); ++i) {
        min_heap.push({piles[i].back(), i});
        piles[i].pop_back();
    }

    size_t write_idx = 0;
    while (!min_heap.empty()) {
        HeapNode node = min_heap.top();
        min_heap.pop();

        //Escribimos el menor elemento directamente sobre el arreglo original
        arr[write_idx++] = node.value;

        //Si la pila de origen aún tiene elementos, insertamos su nuevo tope en el heap
        if (!piles[node.pile_idx].empty()) {
            min_heap.push({piles[node.pile_idx].back(), node.pile_idx});
            piles[node.pile_idx].pop_back();
        }
    }
}