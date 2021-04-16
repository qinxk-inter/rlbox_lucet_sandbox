CURRENT_DIR := $(shell pwd)
ROOT_DIR := $(CURRENT_DIR)/../..
CC := $(ROOT_DIR)/build/_deps/wasiclang-src/bin/clang
CXX := $(ROOT_DIR)/build/_deps/wasiclang-src/bin/clang++
C_SRC_DIR := $(ROOT_DIR)/c_src
C_SRC := $(wildcard $(C_SRC_DIR)/*.c)
SYSROOT_DIR := $(ROOT_DIR)/build/_deps/wasiclang-src/share/wasi-sysroot
INC := -I$(ROOT_DIR)/build/_deps/rlbox-src/code/include -I$(ROOT_DIR)/include

.PHONY: hello clean

libmylib.wasm: $(C_SRC_DIR)/lucet_sandbox_wrapper.c mylib.c mylib.h
	$(CC) --sysroot $(SYSROOT_DIR) $(C_SRC_DIR)/lucet_sandbox_wrapper.c -Wl,--export-all mylib.c -o $@

libmylib.so: libmylib.wasm
	$(ROOT_DIR)/build/cargo/release/lucetc --bindings $(ROOT_DIR)/build/_deps/mod_lucet-src/lucet-wasi/bindings.json --guard-size "4GiB" --min-reserved-size "4GiB" --max-reserved-size "4GiB" libmylib.wasm -o $@

hello: main.cpp libmylib.so $(ROOT_DIR)/build/cargo/debug/librlbox_lucet_sandbox.a
	clang++-12 -std=c++17 $^ -lpthread -ldl -lrt -Wall -o $@

clean:
	rm -f hello libmylib.so libmylib.wasm
