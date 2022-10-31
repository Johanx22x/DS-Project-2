COMMANDS = $(wildcard *.cpp)
OUTPUT = $(patsubst %.cpp,%.so,$(COMMANDS))
INCLUDEDIR = ../../include

CXXFLAGS = -O3 -Wall -Wpedantic -Wextra -Wformat -std=c++17 -s -w $(INCLUDEDIR)
CC = clang++


program: $(OUTPUT)

%.so: %.cpp
	$(CC) $(CXXFLAGS) -fPIC -c -o ../../bin/$@ $<
