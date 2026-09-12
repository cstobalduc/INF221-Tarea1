#variables de compilacion
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17
SRCS = matrix_multiplication.cpp algorithms/naive.cpp algorithms/strassen.cpp
TARGET = matrix_mult


all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

#limpiar archivos ejecutables generados
clean:
	rm -f $(TARGET)

# ejecutar pruebas completas
run: $(TARGET)
	@rm -f data/measurements/mediciones.csv
	@echo "Iniciando pruebas de Multiplicacion de Matrices..."
	@mkdir -p data/measurements
	@for alg in naive strassen; do \
		for n in 2 4 8 16 32 64 128 256; do \
			for t in densa dispersa diagonal; do \
				for d in D0 D10; do \
					for m in a b c; do \
						echo "Corriendo: $$alg - N: $$n - Tipo: $$t - Dom: $$d - Muestra: $$m"; \
						./$(TARGET) $$alg $$n $$t $$d $$m; \
					done \
				done \
			done \
		done \
	done
	@echo "Pruebas finalizadas!"