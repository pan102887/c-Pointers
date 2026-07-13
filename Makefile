BUILD_DIR := build

.PHONY: all configure build run list clean

all: build

configure:
	cmake -S . -B $(BUILD_DIR)

build: configure
	cmake --build $(BUILD_DIR)

run: build
	./$(BUILD_DIR)/c-demo

list: build
	./$(BUILD_DIR)/c-demo --list

clean:
	cmake --build $(BUILD_DIR) --target clean
