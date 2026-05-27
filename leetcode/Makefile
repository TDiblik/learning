CXX = clang++
CXXFLAGS_DEV = -std=c++23 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -g -O0
CXXFLAGS_PROD = -std=c++23 -O3 -DNDEBUG

FIRST_TARGET := $(firstword $(MAKECMDGOALS))
ifeq ($(filter $(FIRST_TARGET),dev prod),$(FIRST_TARGET))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))

  P := $(word 1,$(RUN_ARGS))
  S := $(word 2,$(RUN_ARGS))

  $(eval $(RUN_ARGS):;@:)
endif
SRC = $(P)/$(S).cpp
OUT = $(P)/$(S).out

check-args:
	@if [ -z "$(P)" ] || [ -z "$(S)" ]; then \
		echo "Error: Missing arguments.\nUsage: make [dev|prod] <problem-name> <solution-name>"; \
		exit 1; \
	fi
	@if [ ! -f "$(SRC)" ]; then \
		echo "Error: File '$(SRC)' does not exist."; \
		exit 1; \
	fi

dev: check-args
	@echo "Building [DEV] $(SRC) ..."
	@$(CXX) $(CXXFLAGS_DEV) $(SRC) -o $(OUT)
	@echo "Running $(OUT) ...\n---"
	@./$(OUT)

prod: check-args
	@echo "Building [PROD] $(SRC) ..."
	@$(CXX) $(CXXFLAGS_PROD) $(SRC) -o $(OUT)
	@echo "Running $(OUT) ...\n---"
	@./$(OUT)

clean:
	@echo "Cleaning up compiled files..."
	@rm -rf */*.out*
