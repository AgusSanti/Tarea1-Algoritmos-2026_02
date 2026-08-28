# Tarea 1 - INF-221: Algoritmos y Complejidad (2026-2)

Este repositorio contiene la documentación, el código fuente, la experimentación empírica y las instrucciones necesarias para la realización de la Tarea 1 de la asignatura INF221 Algoritmos y Complejidad.

Entrega: archivo .zip vía aula.usm.cl

---

## Estructura del Repositorio

- assignment_statement/: Enunciado oficial y fuentes en LaTeX (.tex).
- code/: Código fuente, datasets, mediciones y scripts de visualización.
  - sorting/: Implementaciones de std::sort, MergeSort, QuickSort y PatienceSort.
  - matrix_multiplication/: Implementaciones de Multiplicación Tradicional (Naive) y Algoritmo de Strassen.
- report/: Fuentes en LaTeX e informe final compilado (report.pdf).
- README.md: Instrucciones de compilación y ejecución.

---

## Instrucciones de Compilación y Ejecución

### 1. Algoritmos de Ordenamiento

Navegar a la carpeta:
cd code/sorting

Compilar el ejecutable:
make

Generar los conjuntos de datos de prueba:
python3 scripts/array_generator.py

Ejecutar las pruebas de rendimiento:
./sorting_runner

Generar los gráficos comparativos:
python3 scripts/plot_generator.py

Limpiar archivos binarios:
make clean

---

### 2. Multiplicación de Matrices

Navegar a la carpeta:
cd code/matrix_multiplication

Compilar el ejecutable:
make

Generar las matrices de prueba:
python3 scripts/matrix_generator.py

Ejecutar los experimentos de multiplicación:
./matrix_runner

Generar los gráficos comparativos:
python3 scripts/plot_generator.py

Limpiar archivos binarios:
make clean

---

## Informe Final

El informe final compilado en formato PDF se encuentra en:
report/report.pdf
