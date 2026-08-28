# Documentación del Código y Experimentación

## Entrega

La entrega se realiza vía aula.usm.cl en formato .zip.

---

## Multiplicación de matrices

Módulo ubicado en code/matrix_multiplication/. Contiene la implementación y experimentación de los algoritmos de multiplicación matricial: Tradicional Cúbico (Naive) y Algoritmo de Strassen.

### Programa principal

- Archivo fuente: matrix_multiplication.cpp
- Algoritmos implementados:
  - algorithms/naive.cpp: Algoritmo tradicional de tres bucles anidados O(n³).
  - algorithms/strassen.cpp: Algoritmo de división y conquista de Strassen O(n^(log₂7)) ≈ O(n^(2.807)).
- Compilación:
  make
  (Genera el ejecutable matrix_runner con optimización -O3 y estándar C++17)
- Ejecución:
  ./matrix_runner
  (Lee las matrices de data/matrix_input/, mide tiempo de CPU y memoria RSS, y guarda resultados en measurements/matrix_multiplication/matrix_measurements.csv)

### Scripts

- scripts/matrix_generator.py: Genera matrices sintéticas en data/matrix_input/ variando tamaños (16, 64, 256, 1024), estructuras (densas, dispersas, diagonales) y niveles de impureza (D0, D10) con 3 réplicas (a, b, c).
- scripts/plot_generator.py: Procesa matrix_measurements.csv y genera los gráficos comparativos de tiempo y memoria en data/plots/.

---

## Ordenamiento de arreglo unidimensional

Módulo ubicado en code/sorting/. Contiene la implementación y análisis empírico de algoritmos de ordenamiento de arreglos.

Algoritmos: MergeSort, QuickSort, PatienceSort y std::sort (Introsort).

### Programa principal

- Archivo fuente: sorting.cpp
- Algoritmos implementados:
  - algorithms/mergesort.cpp: Ordenamiento por mezcla O(n log n).
  - algorithms/quicksort.cpp: Ordenamiento rápido con partición O(n log n) promedio.
  - algorithms/patiencesort.cpp: Ordenamiento por paciencia basado en pilas y min-heap.
  - algorithms/sort.cpp: Envoltura de la función estándar optimizada std::sort.
- Compilación:
  make
  (Genera el ejecutable sorting_runner con optimización -O3 y estándar C++17)
- Ejecución:
  ./sorting_runner
  (Lee los arreglos de data/array_input/, mide tiempo y memoria RSS, y guarda resultados en measurements/sorting/sorting_measurements.csv)

### Scripts

- scripts/array_generator.py: Genera arreglos sintéticos en data/array_input/ con tamaños de 10 a 10^7 elementos, configuraciones (ascendente, descendente, aleatorio) y perturbaciones (D1, D7) con réplicas (a, b, c).
- scripts/plot_generator.py: Procesa sorting_measurements.csv y produce los gráficos de rendimiento y memoria guardados en data/plots/.
