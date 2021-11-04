################################################################################
## Declaracion de variables del fichero «Makefile»

## DIRECTORIOS
SOURCE_DIR = src
BUILD_DIR = build
BIN_DIR = bin

VPATH = $(SOURCE_DIR) 

## COMPILADOR Y OPCIONES DE COMPILACIÓN:
CXX = g++
CXXFLAGS = -g -Wall -Wextra -Icifrado-cesar


## FICHEROS OBJETO (RESULTADOS INTERMEDIOS DE COMPILACIÓN):
OBJECTS = $(addprefix $(BUILD_DIR)/, analisis-cesar.o cesar.o cesar-main.o diccionario.o pedir-nombre-fichero.o)

################################################################################
## Reglas del fichero «Makefile»

all: cifrado-cesar

cifrado-cesar: $(OBJECTS) | $(BIN_DIR)  
	$(CXX) -g $^ -o $(BIN_DIR)/$@ 

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@  

$(BUILD_DIR)/analisis-cesar: analisis-cesar.hpp cesar.hpp diccionario.hpp
$(BUILD_DIR)/cesar.o: cesar.hpp
$(BUILD_DIR)/cesar-main.o: pedir-nombre-fichero.hpp cesar.hpp analisis-cesar.hpp
$(BUILD_DIR)/diccionario.o: diccionario.hpp
$(BUILD_DIR)/pedir-nombre-fichero.o: pedir-nombre-fichero.hpp

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
ifeq ($(OS),Windows_NT)
	if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)
	if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
else
	rm -f $(OBJECTS) $(TESTING_OBJECTS) $(BIN_DIR)/*
endif

clean:
ifeq ($(OS),Windows_NT)
	if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)
	if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
else
	rm -f $(OBJECTS) $(TESTING_OBJECTS) $(BIN_DIR)/*
endif
