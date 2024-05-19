CC = clang++
EXAMPLE_PROJECT_DIR := /Volumes/V/CCatter/rust/target/aarch64-apple-darwin/debug
export PKG_CONFIG_PATH := $(EXAMPLE_PROJECT_DIR):$(PKG_CONFIG_PATH)

CFLAGS = -Wall -Wextra -g
INCLUDES = `pkg-config --cflags --static rust_deps`
LIBS = `pkg-config --libs --static rust_deps`

all:	build ccatter

build:
	mkdir -p build

ccatter: build/main.o
	echo $(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o build/ccatter $(LIBS)

build/main.o:	src/main.c rust
	@echo "Invoking ValeRuster"
	@grep '^#pragma vrinclude' src/main.c | /Volumes/V/Vale/ValeRuster/target/debug/ValeRuster --crate std --cargo_toml Dependencies.toml --output_dir rust instantiate
	@echo "Compiling the C file..."
	echo $(CC) $(CFLAGS) $(INCLUDES) -I . -c $< -o $@
	$(CC) $(CFLAGS) $(INCLUDES) -I . -c $< -o $@

rust:
	mkdir rust

.PHONY: clean
clean:
	rm -rf *.o *.d *.h rust build clibthing
