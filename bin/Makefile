PLATFORM := $(shell uname -s)

# Compilation falgs
ifeq ($(PLATFORM),Linux)
    CXXFLAGS := -g -O2 -std=c++17 -Wall
    LDFLAGS := `pkg-config --libs allegro-5 allegro_primitives-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5`
else ifeq ($(PLATFORM),Darwin) # macOS
    CXXFLAGS := -std=c++17
    LDFLAGS := # Especifica las librerías para macOS
else  # Windows
    CXXFLAGS := -O2
    LDFLAGS := -static -lallegro-5.0.10-monolith-md 
endif

# Folders and files
SRC_DIR := ../src
UTILS_DIR := $(SRC_DIR)/utils
INCLUDE_DIR := $(SRC_DIR) # Agregar esta línea para definir el directorio de include
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(UTILS_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,%.o,$(wildcard $(SRC_DIR)/*.cpp)) $(patsubst $(UTILS_DIR)/%.cpp,%.o,$(wildcard $(UTILS_DIR)/*.cpp))

# Main rule
rick2: $(OBJ_FILES)
	g++ -o rick2 $(OBJ_FILES) $(CXXFLAGS) $(LDFLAGS)

# Object compile rules
%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

%.o: $(UTILS_DIR)/%.cpp
	g++ $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f *.o rick2

