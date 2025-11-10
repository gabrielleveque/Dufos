CXX = g++
CXXFLAGS = -std=c++17 -Iecs/include -I/opt/homebrew/Cellar/raylib/5.5/include
LDFLAGS = -L/opt/homebrew/Cellar/raylib/5.5/lib -lraylib -framework IOKit -framework Cocoa -framework OpenGL

ECS_SRC_DIR = ecs/src
CLIENT_SRC_DIR = client/src
OBJ_DIR = obj
BIN_DIR = .

ECS_SOURCES = $(wildcard $(ECS_SRC_DIR)/Entity/*.cpp) \
              $(wildcard $(ECS_SRC_DIR)/Component/*.cpp) \
              $(wildcard $(ECS_SRC_DIR)/Registry/*.cpp)

CLIENT_SOURCES = $(wildcard $(CLIENT_SRC_DIR)/*.cpp)

SOURCES = $(ECS_SOURCES) $(CLIENT_SOURCES)

ECS_OBJECTS = $(patsubst $(ECS_SRC_DIR)/%.cpp,$(OBJ_DIR)/ecs/%.o,$(ECS_SOURCES))
CLIENT_OBJECTS = $(patsubst $(CLIENT_SRC_DIR)/%.cpp,$(OBJ_DIR)/client/%.o,$(CLIENT_SOURCES))

OBJECTS = $(ECS_OBJECTS) $(CLIENT_OBJECTS)

TARGET = $(BIN_DIR)/app

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/ecs/%.o: $(ECS_SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/client/%.o: $(CLIENT_SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
