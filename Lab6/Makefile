
# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall `pkg-config --cflags glfw3 glew`

# Source files
SRCS = Lab6.cpp \
	   ./stb_image/stb_image.cpp

# Executable name
TARGET = lab6.out

# Object files
OBJS = $(SRCS:.cpp=.o)

# Include directories
INCLUDES = -I/usr/include -I.

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
$(TARGET): $(OBJS)
	$(CXX)  -o $@ $^ $(CXXFLAGS)

# Objects rules
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: exec clean
exec:
	./$(TARGET)

clean:
	rm $(TARGET) $(OBJS)

run: clean all exec
