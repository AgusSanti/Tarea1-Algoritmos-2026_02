/**
 * ============================================================================
 * Tarea 1: Algoritmos de Ordenamiento y Multiplicación de Matrices
 * Ramo:     INF-221 Algoritmos y Complejidad
 * Semestre: 2026-2
 * Autor:    Agustin Ignacio Santibañez Perez
 * Rol:      [202204682-1]
 * Referencias: 
 * - Mallows, C. L. (1962). "Patience Sorting"
 * - Aldous, D., & Diaconis, P. (1999). "Longest increasing subsequences: from patience sorting to the Baik-Deift-Johansson theorem"
 * ============================================================================
 */

#include <vector>
#include <queue>
#include <algorithm>

struct HeapNode {
    int value;
    size_t pile_idx;

    bool operator>(const HeapNode& other) const {
        return value > other.value;
    }
};

void patiencesort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;

    std::vector<std::vector<int>> piles;
    std::vector<int> top_elements; 

    for (int x : arr) {
        auto it = std::lower_bound(top_elements.begin(), top_elements.end(), x);
        size_t idx = std::distance(top_elements.begin(), it);

        if (it == top_elements.end()) {
            piles.push_back({x});
            top_elements.push_back(x);
        } else {
            piles[idx].push_back(x);
            top_elements[idx] = x;
        }
    }

    std::priority_queue<HeapNode, std::vector<HeapNode>, std::greater<HeapNode>> min_heap;

    for (size_t i = 0; i < piles.size(); ++i) {
        min_heap.push({piles[i].back(), i});
        piles[i].pop_back();
    }

    size_t write_idx = 0;
    while (!min_heap.empty()) {
        HeapNode node = min_heap.top();
        min_heap.pop();

        arr[write_idx++] = node.value;

        if (!piles[node.pile_idx].empty()) {
            min_heap.push({piles[node.pile_idx].back(), node.pile_idx});
            piles[node.pile_idx].pop_back();
        }
    }
}
