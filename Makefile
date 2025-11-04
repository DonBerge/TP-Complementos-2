CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all clean

all: $(OBJS) | $(BIN_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

include testing.mk
test:
	$(MAKE) test_all

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	find tests \( -name "*.actual*" -o -name "tester" -o -name "*.bc" -o -name "*.check*" -o -name "*.c" -o -name "*.bin" \) -exec rm {} \;
	@echo "Se eliminaron los archivos complementarios de test."


#.PHONY: run test
#.DELETE_ON_ERROR:
#
#TGT=app/Main
#
#GHCOPTS=-prof
#RTSOPTS=+RTS -xc
#
#$(TGT): build
#
#build:
#	cabal build
#
#interp:
#	cabal repl
#
#run: build
#	 cabal run
#
#include testing.mk
#test: build vm
#	$(MAKE) test_all
#
#vm:
#	$(MAKE) -C vm
#
#clean:
#	find tests/ok/ \( -name "*.actual*" -o -name "*.bc" -o -name "*.check*" -o -name "*.c" -o -name "*.bin" \) -exec rm {} \;
#	@echo "Se eliminaron los archivos complementarios de test."
#
#.PHONY: vm
#