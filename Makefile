BUILD_DIR := build

.PHONY: all configure configure-tests build test list clean

all: build

configure:
	cmake -S . -B $(BUILD_DIR) -DCP_BUILD_TESTS=OFF

configure-tests:
	cmake -S . -B $(BUILD_DIR) -DCP_BUILD_TESTS=ON

build: configure
	cmake --build $(BUILD_DIR)

test: configure-tests
	cmake --build $(BUILD_DIR)
	ctest --test-dir $(BUILD_DIR) --output-on-failure

list: configure-tests
	cmake --build $(BUILD_DIR)
	./$(BUILD_DIR)/c-demo-tests --list

clean:
	cmake --build $(BUILD_DIR) --target clean
