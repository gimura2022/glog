all: compile

.PHONY: compile
compile: gnub
	./gnub release compile

.PHONY: compile_debug
compile_debug: gnub
	./gnub debug compile

.PHONY: install
install: gnub
	./gnub install
