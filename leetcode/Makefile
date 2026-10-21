UNAME := $(shell uname)

CXX = g++
CXXFLAGS = -std=c++23 -g -O0 -Wall -Werror -Wpedantic -Wshadow -Wconversion -fsanitize=address,undefined
OUT_DIR = ./build
OUTPUT = $(OUT_DIR)/$(prob)/$(sol)

ifeq ($(UNAME), Darwin)
	CXX = clang++
endif

# Precompile catch2
CATCH_OBJ = $(OUT_DIR)/catch2/catch_main.o
CATCH_MAiN = ../vendor/catch2/catch_main.cpp
$(CATCH_OBJ): $(CATCH_MAiN)
	@mkdir -p $(OUT_DIR)/catch2
	$(CXX) $(CXXFLAGS) -c $(CATCH_MAiN) -o $(CATCH_OBJ)

.PHONY: build run lldb clean

build: $(CATCH_OBJ)
ifeq ($(and $(prob), $(sol)), )
		$(error Example usage: make prob="proble-name" sol="solution-name" build/run/lldb)
endif
	@mkdir -p $(OUT_DIR)/$(prob)
	$(CXX) $(CXXFLAGS) $(prob)/$(sol).cpp $(CATCH_OBJ) -o $(OUTPUT)

run: build
	$(OUTPUT)

lldb: build
	lldb $(OUTPUT)

clean:
	@rm -rf $(OUT_DIR)
