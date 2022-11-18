COMMANDS = $(wildcard *.cpp)
OUTPUT = $(patsubst %.cpp,%.so,$(COMMANDS))
INCLUDEDIR = ../../include
OBJECTS = $(wildcard ../../obj/*.o)
DEPS = $(wildcard *.d)

CXXFLAGS = -O3 -Wall -Wpedantic -MP -MD -Wextra -std=c++17 -I$(INCLUDEDIR)
CC = clang++

program: $(OUTPUT)

%.so: %.cpp $(OBJECTS)
	$(CC) $(CXXFLAGS) -shared -fPIC -o ../../bin/$@ $^

-include $(DEPS)
