CC = clang++
EXAMPLE_PROJECT_DIR := /Volumes/V/CCatter/rust/target/aarch64-apple-darwin/debug
export PKG_CONFIG_PATH := $(EXAMPLE_PROJECT_DIR):$(PKG_CONFIG_PATH)

CFLAGS = -Wall -Wextra -g
INCLUDES = `pkg-config --cflags --static rust_deps`
LIBS = `pkg-config --libs --static rust_deps`

all:	build ccatter	tests

build:
	mkdir -p build

ccatter: build/main.o
	echo $(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o build/ccatter $(LIBS)
# 	build/ccatter || (echo "catter test failed!"; exit 1)

build/main.o:	src/main.c build	rust
	@echo "Invoking ValeRuster"
	@grep '^#pragma vrinclude' src/main.c | /Volumes/V/Vale/ValeRuster/target/debug/ValeRuster --crate std --cargo_toml Dependencies.toml --output_dir rust instantiate
	@echo "Compiling the C file..."
	echo $(CC) $(CFLAGS) $(INCLUDES) -I . -c $< -o $@
	$(CC) $(CFLAGS) $(INCLUDES) -I . -c $< -o $@


strlen: build/strlen.o
	echo $(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o build/strlen $(LIBS)
	build/strlen || (echo "strlen test failed!"; exit 1)
	@echo strlen test succeeded!

build/strlen.o:	src/strlen.c build	rust
	@echo "Doing strlen test..."
	@grep '^#pragma vrinclude' src/strlen.c | /Volumes/V/Vale/ValeRuster/target/debug/ValeRuster --crate std --cargo_toml Dependencies.toml --output_dir rust instantiate
	echo $(CC) $(CFLAGS) $(INCLUDES) -I . -c $< -o $@
	$(CC) $(CFLAGS) $(INCLUDES) -I . -c $< -o $@

mkdir: build/mkdir.o
	echo $(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o build/mkdir $(LIBS)
	- rmdir x
	build/mkdir || (echo "mkdir test failed!"; exit 1)
	@echo mkdir test succeeded!

build/mkdir.o:	src/mkdir.c build	rust
	@echo "Doing mkdir test..."
	@grep '^#pragma vrinclude' src/mkdir.c | /Volumes/V/Vale/ValeRuster/target/debug/ValeRuster --crate std --cargo_toml Dependencies.toml --output_dir rust instantiate
	echo $(CC) $(CFLAGS) $(INCLUDES) -I . -c $< -o $@
	$(CC) $(CFLAGS) $(INCLUDES) -I . -c $< -o $@

reverse: build/reverse.o
	echo $(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o build/reverse $(LIBS)
	build/reverse || (echo "reverse test failed!"; exit 1)
	@echo reverse test succeeded!

build/reverse.o:	src/reverse.c build	rust
	@echo "Doing reverse test..."
	@grep '^#pragma vrinclude' src/reverse.c | /Volumes/V/Vale/ValeRuster/target/debug/ValeRuster --crate std --cargo_toml Dependencies.toml --output_dir rust instantiate
	echo $(CC) $(CFLAGS) $(INCLUDES) -I . -c $< -o $@
	$(CC) $(CFLAGS) $(INCLUDES) -I . -c $< -o $@

catter: build/catter.o
	echo $(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o build/catter $(LIBS)
	build/catter || (echo "catter test failed!"; exit 1)
	@echo catter test succeeded!

build/catter.o:	src/catter.c build	rust
	@echo "Doing catter test..."
	@grep '^#pragma vrinclude' src/catter.c | /Volumes/V/Vale/ValeRuster/target/debug/ValeRuster --crate std --cargo_toml Dependencies.toml --output_dir rust instantiate
	echo $(CC) $(CFLAGS) $(INCLUDES) -I . -c $< -o $@
	$(CC) $(CFLAGS) $(INCLUDES) -I . -c $< -o $@

# tests:	catter reverse mkdir strlen
# 	@echo "All tests succeeded!"

rust:
	mkdir rust

.PHONY: clean
clean:
	rm -rf *.o *.d *.h rust build clibthing
