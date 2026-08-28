# ==============================================================================
# Tarea 1: Algoritmos de Ordenamiento y Multiplicación de Matrices
# Ramo:     INF-221 Algoritmos y Complejidad
# Semestre: 2026-2
# Autor:    Agustin Ignacio Santibañez Perez
# Rol:      [202204682-1]
# ==============================================================================

CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall

SRCS = sorting.cpp \
       algorithms/mergesort.cpp \
       algorithms/quicksort.cpp \
       algorithms/patiencesort.cpp

TARGET = sorting_runner

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
