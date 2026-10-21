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

.PHONY: build run lldb clean all

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

all:
	@for problem_dir in ./*; do \
		[ ! -d "$$problem_dir" ] && continue; \
		[ "$$(basename "$$problem_dir")" = "build" ] && continue; \
		for sol_file in "$$problem_dir"/*.cpp; do \
			[ ! -f "$$sol_file" ] && continue; \
			sol_name="$$(basename "$$sol_file" .cpp)"; \
			prob_name="$$(basename "$$problem_dir")"; \
			$(MAKE) prob="$$prob_name" sol="$$sol_name" run; \
		done; \
	done

clean:
	@rm -rf $(OUT_DIR)
