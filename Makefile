BINARY=./bin/project
CODEDIR=./src
INCLUDEDIR=./include

CC=clang++

# NOTE: MacOS not comptemplated
ifeq ($(OS),Windows_NT)
	rm_C = del bin\* obj\*
else
	FOLDERS_COMMAND = mkdir -p obj bin include src
	LINKFLAGS = -fuse-ld=mold
	rm_C = rm -rf $(BINARY) $(OBJECTS) $(DEPFILES) ./bin/*
endif

DEPFLAGS=-MD -MP
CXXFLAGS=-Wall -Wextra -Wformat -Wpedantic -std=c++17
CFLAGS= $(CXXFLAGS) $(foreach dir, $(INCLUDEDIR), -I$(dir)) -O3

CFILES=$(foreach dir, $(CODEDIR), $(wildcard $(dir)/*.cpp))

OBJECTS=$(patsubst ./src/%.cpp, ./obj/%.o, $(CFILES))

DEPFILES=$(patsubst ./src/%.cpp, ./obj/%.d, $(CFILES))

all: $(BINARY)
	@make -C src/commands

run: $(BINARY)
	$(BINARY)

$(BINARY): $(OBJECTS) 
	$(CC) $(LINKFLAGS) $(CFLAGS) -o $@ $^ 

obj/%.o: src/%.cpp | folders 
	$(CC) $(CFLAGS) $(DEPFLAGS) -fPIC -c -o $@ $< 

folders: 
	@$(FOLDERS_COMMAND) 

clean: 
	@$(rm_C) 

-include $(DEPFILES)
