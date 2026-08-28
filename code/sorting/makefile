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