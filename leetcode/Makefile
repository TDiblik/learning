CXX = clang++
CXXFLAGS = -std=c++23 -Wall -Wextra -Wpedantic -Wshadow -Wconversion \
           -Wformat=2 -Werror -g3 -O0 -fsanitize=address,undefined \
           -fno-omit-frame-pointer \
           -D_GLIBCXX_DEBUG \
           -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG

IS_LLDB := $(filter lldb,$(firstword $(MAKECMDGOALS)))

ifeq ($(filter clean,$(MAKECMDGOALS)),)
  ifneq ($(MAKECMDGOALS),)
    ifneq ($(IS_LLDB),)
      P := $(word 2,$(MAKECMDGOALS))
      S := $(word 3,$(MAKECMDGOALS))
      $(eval $(MAKECMDGOALS):;@:)
      $(eval lldb: run_lldb)
    else
      P := $(word 1,$(MAKECMDGOALS))
      S := $(word 2,$(MAKECMDGOALS))
      $(eval $(MAKECMDGOALS):;@:)
      $(eval $(P): all)
    endif
  endif
endif

SRC = $(P)/$(S).cpp
OUT = $(P)/$(S).out

.PHONY: all clean check-args run_lldb

all: check-args
	@echo "Building $(SRC) ..."
	@$(CXX) $(CXXFLAGS) -pthread $(SRC) -o $(OUT)
	@echo "Running $(OUT) ...\n---"
	@./$(OUT)

run_lldb: check-args
	@echo "Building $(SRC) for LLDB ..."
	@$(CXX) $(CXXFLAGS) -pthread $(SRC) -o $(OUT)
	@echo "Starting LLDB for $(OUT) ...\n---"
	@lldb ./$(OUT)

check-args:
	@if [ -z "$(P)" ] || [ -z "$(S)" ]; then \
		echo "Error: Missing arguments.\nUsage:\n  make <problem-name> <solution-name>\n  make lldb <problem-name> <solution-name>"; \
		exit 1; \
	fi
	@if [ ! -f "$(SRC)" ]; then \
		echo "Error: File '$(SRC)' does not exist."; \
		exit 1; \
	fi

clean:
	@echo "Cleaning up compiled files..."
	@rm -rf */*.out*
