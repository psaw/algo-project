CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra

# Flags are close to the test environment, adapted for macOS
TEST_ENV_MACOS_FLAGS = -std=c++14 \
    -nostdinc++ \
    -I./libcxx/include \
    -L./libcxx/lib \
    -Wl,-rpath,./libcxx/lib \
    -nodefaultlibs \
    -lc++ \
    -lc++abi \
    -lm \
    -lc \
    -O0 \
    -fno-inline \
    -fno-vectorize

all: run gen

run: run.cpp
	$(CXX) $(TEST_ENV_MACOS_FLAGS) -o run run.cpp

gen: gen.cpp
	$(CXX) $(TEST_ENV_MACOS_FLAGS) -o gen gen.cpp

clean:
	rm -f run gen

.PHONY: clean
