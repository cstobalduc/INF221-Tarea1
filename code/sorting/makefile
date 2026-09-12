# Variables de compilacion
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17
SRCS = sorting.cpp algorithms/mergesort.cpp algorithms/quicksort.cpp algorithms/patiencesort.cpp algorithms/sort.cpp
TARGET = sorting


all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

#regla para limpiar archivos ejecutables generados
clean:
	rm -f $(TARGET)


#nueva regla para ejecutar la batería de pruebas completa
run: $(TARGET)
	@rm -f data/measurements/mediciones.csv
	@echo "Iniciando pruebas de Sorting..."
	@for alg in mergesort quicksort patiencesort stdsort; do \
		for n in 10 1000 100000 10000000; do \
			for t in ascendente descendente aleatorio; do \
				for d in D1 D7; do \
					for m in a b c; do \
						echo "Corriendo: $$alg - N: $$n - Tipo: $$t - Dom: $$d - Muestra: $$m"; \
						./$(TARGET) $$alg $$n $$t $$d $$m; \
					done \
				done \
			done \
		done \
	done
	@echo "Pruebas finalizadas!"