BIN=server client

.PHONY: clean


all: $(BIN)

%: %.c
	gcc -o $@ $^

clean:
	rm -rf $(BIN)
