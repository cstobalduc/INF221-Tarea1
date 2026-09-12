// Fuentes consultadas: Rosetta Code / GeeksforGeeks (adaptado con busqueda Binaria)
#include <vector>
#include <queue>
#include <algorithm>

// estructura para almacenar el elemento en la cola de prioridad de la fusión
struct HeapNode {
    int value;
    int pile_index;

    // comparador para que el menor valor tenga mayor prioridad
    bool operator>(const HeapNode& other) const {
        return value > other.value;
    }
};

void patienceSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;

    std::vector<std::vector<int>> piles;
    std::vector<int> top_cards; // mantiene el valor superior de cada pila para búsqueda binaria

    // distribuir elementos en pilas usando búsqueda binaria O(n log k)
    for (int x : arr) {
        auto it = std::lower_bound(top_cards.begin(), top_cards.end(), x);
        int idx = std::distance(top_cards.begin(), it);

        if (it == top_cards.end()) {
            piles.push_back({x});
            top_cards.push_back(x);
        } else {
            piles[idx].push_back(x);
            top_cards[idx] = x;
        }
    }

    // fusion de pilas
    std::priority_queue<HeapNode, std::vector<HeapNode>, std::greater<HeapNode>> min_heap;

    for (size_t i = 0; i < piles.size(); ++i) {
        min_heap.push({piles[i].back(), static_cast<int>(i)});
        piles[i].pop_back();
    }

    int out_idx = 0;
    while (!min_heap.empty()) {
        HeapNode node = min_heap.top();
        min_heap.pop();

        arr[out_idx++] = node.value;

        // si la pila de donde provino el elemento aun tiene, insertamos el siguiente
        if (!piles[node.pile_index].empty()) {
            min_heap.push({piles[node.pile_index].back(), node.pile_index});
            piles[node.pile_index].pop_back();
        }
    }
}