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
#include <chrono>
#include <filesystem>
#include <sys/resource.h>

namespace fs = std::filesystem;

void naive_multiply(const std::vector<std::vector<int>>& A, 
                    const std::vector<std::vector<int>>& B, 
                    std::vector<std::vector<int>>& C, int n);

void strassen(const std::vector<std::vector<int>>& A, 
              const std::vector<std::vector<int>>& B, 
              std::vector<std::vector<int>>& C, int n);

long get_peak_memory_kb() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return usage.ru_maxrss;
    }
    return 0;
}

std::vector<std::vector<int>> leer_matriz(const std::string& ruta, int n) {
    std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));
    std::ifstream infile(ruta);
    if (!infile.is_open()) {
        std::cerr << "Error: No se pudo abrir " << ruta << std::endl;
        return mat;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            infile >> mat[i][j];
        }
    }
    return mat;
}

int main() {
    std::vector<int> Ns = {16, 64, 256, 1024};
    std::vector<std::string> Ts = {"dispersa", "diagonal", "densa"};
    std::vector<std::string> Ds = {"D0", "D10"};
    std::vector<std::string> Ms = {"a", "b", "c"};

    fs::path out_dir = "../../measurements/matrix_multiplication";
    if (!fs::exists(out_dir)) {
        out_dir = "measurements/matrix_multiplication";
    }
    fs::create_directories(out_dir);
    std::string out_csv = (out_dir / "matrix_measurements.csv").string();
    std::ofstream csv(out_csv);

    csv << "algoritmo,n,tipo,dominio,muestra,tiempo_segundos,memoria_peak_kb\n";

    std::cout << "========================================================\n";
    std::cout << " INICIANDO BENCHMARKS DE MULTIPLICACION DE MATRICES\n";
    std::cout << "========================================================\n";

    for (int n : Ns) {
        for (const auto& t : Ts) {
            for (const auto& d : Ds) {
                for (const auto& m : Ms) {
                    std::string base = std::to_string(n) + "_" + t + "_" + d + "_" + m;
                    std::string ruta1 = "data/matrix_input/" + base + "_1.txt";
                    std::string ruta2 = "data/matrix_input/" + base + "_2.txt";

                    std::cout << "\n[CASO] " << base << " (n=" << n << ")\n";

                    auto A = leer_matriz(ruta1, n);
                    auto B = leer_matriz(ruta2, n);
                    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

                    // Benchmark Naive
                    {
                        auto start = std::chrono::high_resolution_clock::now();
                        naive_multiply(A, B, C, n);
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> elapsed = end - start;
                        long mem = get_peak_memory_kb();

                        csv << "naive," << n << "," << t << "," << d << "," << m << ","
                            << elapsed.count() << "," << mem << "\n";
                        csv.flush();
                        std::cout << "  - Naive    | Tiempo: " << elapsed.count() << " s | RSS: " << mem << " KB\n";
                    }

                    // Benchmark Strassen
                    {
                        auto start = std::chrono::high_resolution_clock::now();
                        strassen(A, B, C, n);
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> elapsed = end - start;
                        long mem = get_peak_memory_kb();

                        csv << "strassen," << n << "," << t << "," << d << "," << m << ","
                            << elapsed.count() << "," << mem << "\n";
                        csv.flush();
                        std::cout << "  - Strassen | Tiempo: " << elapsed.count() << " s | RSS: " << mem << " KB\n";
                    }
                }
            }
        }
    }

    std::cout << "\n========================================================\n";
    std::cout << "Mediciones guardadas en: " << out_csv << "\n";
    std::cout << "========================================================\n";

    return 0;
}
