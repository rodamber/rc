.PHONY: clean

# Declaration of variables
CC = g++
CC_FLAGS = -std=c++17 -Wall -Wextra -Wfatal-errors -Wno-unused-parameter \
					 -Wno-unused-variable -Wno-literal-suffix -Wno-parentheses \
					 -g

INCLUDES = -Ilib


# File names
EXEC = main
SOURCES = $(wildcard main.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $(INCLUDES) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
