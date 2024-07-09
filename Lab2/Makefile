
# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall `pkg-config --cflags glfw3 glew`

# Imgui
IMGUI_DIR = ./imgui
IMGUI_SRCS = ./$(IMGUI_DIR)/imgui.cpp \
			./$(IMGUI_DIR)/imgui_demo.cpp \
			./$(IMGUI_DIR)/imgui_draw.cpp \
			./$(IMGUI_DIR)/imgui_tables.cpp \
			./$(IMGUI_DIR)/imgui_widgets.cpp \
			./$(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \
			./$(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

# Source files
SRCS = Lab2-imgui.cpp
# SRCS = Lab2+imgui_indexedDrawing_color.cpp

# Executable name
TARGET = lab2.out

# Object files
OBJS = $(SRCS:.cpp=.o)
IMGUI_OBJS = $(IMGUI_SRCS:.cpp=.o)

# Include directories
INCLUDES = -I/usr/include -I. -I$(IMGUI_DIR)

# Library directories
LIB_DIRS = -L/usr/lib

# Libraries to link
LD_FLAGS = $(LIB_DIRS) `pkg-config --libs glfw3 glew` 

CXXFLAGS += $(INCLUDES) $(LD_FLAGS)


##---------------
## BUILD RULES
##---------------

# Main target
all: $(TARGET)

# Executable rules
$(TARGET): $(OBJS) $(IMGUI_OBJS)
	$(CXX)  -o $@ $^ $(CXXFLAGS)

# Objects rules
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: exec clean
exec:
	./$(TARGET)

clean:
	rm $(TARGET) $(OBJS) $(IMGUI_OBJS)

run: clean all exec
