COMMANDS = $(wildcard *.cpp)
OUTPUT = $(patsubst %.cpp,%.so,$(COMMANDS))
INCLUDEDIR = ../../include

CXXFLAGS = -O3 -Wall -Wpedantic -Wextra -Werror -std=c++17 -I$(INCLUDEDIR)
CC = clang++

program: $(OUTPUT)

%.so: %.cpp
	$(CC) $(CXXFLAGS) -fPIC -c -o ../../bin/$@ $<
