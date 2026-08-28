/**
 * ============================================================================
 * Tarea 1: Algoritmos de Ordenamiento y Multiplicación de Matrices
 * Ramo:     INF-221 Algoritmos y Complejidad
 * Semestre: 2026-2
 * Autor:    Agustin Ignacio Santibañez Perez
 * Rol:      [202204682-1]
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <filesystem>
#include <algorithm>
#include <sys/resource.h>

namespace fs = std::filesystem;

//Declaraciones externas de los algoritmos
void mergesort(std::vector<int>& arr);
void quicksort(std::vector<int>& arr);
void patiencesort(std::vector<int>& arr);

//Wrapper para std::sort
void std_sort_wrapper(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
}

//Medicion de memoria maxima residente (Peak RSS) en Kilobytes usando sys/resource.h
long get_peak_memory_kb() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return usage.ru_maxrss;
    }
    return 0;
}

//Lectura del arreglo desde archivo plano
std::vector<int> leer_arreglo(const std::string& ruta, int n) {
    std::vector<int> arr;
    arr.reserve(n);
    std::ifstream infile(ruta);
    if (!infile.is_open()) {
        std::cerr << "Error: No se pudo abrir " << ruta << std::endl;
        return arr;
    }
    int val;
    while (infile >> val) {
        arr.push_back(val);
    }
    return arr;
}

struct Algoritmo {
    std::string nombre;
    void (*func)(std::vector<int>&);
};

int main() {
    // Parametros del experimento segun el enunciado
    std::vector<int> N = {10, 1000, 100000, 10000000};
    std::vector<std::string> T = {"ascendente", "descendente", "aleatorio"};
    std::vector<std::string> D = {"D1", "D7"};
    std::vector<std::string> M = {"a", "b", "c"};

    std::vector<Algoritmo> algoritmos = {
        {"std_sort", std_sort_wrapper},
        {"mergesort", mergesort},
        {"quicksort", quicksort},
        {"patiencesort", patiencesort}
    };

    //Se crea directorio de mediciones segun estructura requerida por el enunciado: measurements/sorting/
    fs::path out_dir = "../../measurements/sorting";
    if (!fs::exists(out_dir)) {
        out_dir = "measurements/sorting"; 
    }
    fs::create_directories(out_dir);
    std::string out_csv = (out_dir / "sorting_measurements.csv").string();
    std::ofstream csv(out_csv);

    //Cabecera CSV
    csv << "algoritmo,n,tipo,dominio,muestra,tiempo_segundos,memoria_peak_kb\n";

    std::cout << "========================================================\n";
    std::cout << " INICIANDO BENCHMARKS DE SORTING (TIEMPO Y MEMORIA)\n";
    std::cout << "========================================================\n";

    for (int n : N) {
        for (const auto& t : T) {
            for (const auto& d : D) {
                for (const auto& m : M) {
                    std::string filename = std::to_string(n) + "_" + t + "_" + d + "_" + m + ".txt";
                    std::string filepath = "data/array_input/" + filename;

                    std::cout << "\n[CASO] " << filename << "\n";
                    std::vector<int> base_arr = leer_arreglo(filepath, n);

                    if (base_arr.empty()) {
                        std::cerr << "  -> Archivo no encontrado o vacio: " << filepath << std::endl;
                        continue;
                    }

                    for (const auto& algo : algoritmos) {
                        std::vector<int> arr_copy = base_arr;

                        auto start = std::chrono::high_resolution_clock::now();
                        algo.func(arr_copy);
                        auto end = std::chrono::high_resolution_clock::now();

                        std::chrono::duration<double> elapsed = end - start;
                        long peak_mem = get_peak_memory_kb();

                        csv << algo.nombre << ","
                            << n << ","
                            << t << ","
                            << d << ","
                            << m << ","
                            << elapsed.count() << ","
                            << peak_mem << "\n";
                        csv.flush();

                        std::cout << "  - " << algo.nombre 
                                  << " | Tiempo: " << elapsed.count() << " s"
                                  << " | Peak RSS: " << peak_mem << " KB\n";
                    }
                }
            }
        }
    }

    std::cout << "\n========================================================\n";
    std::cout << "Mediciones guardadas exitosamente en: " << out_csv << "\n";
    std::cout << "========================================================\n";

    return 0;
}
