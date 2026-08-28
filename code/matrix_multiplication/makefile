CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall

SRCS = matrix_multiplication.cpp \
       algorithms/naive.cpp \
       algorithms/strassen.cpp

TARGET = matrix_runner

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)