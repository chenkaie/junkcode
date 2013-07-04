BIN=server client client2 client3

.PHONY: clean

all: $(BIN)

%: %.c
	gcc -o $@ $^

clean:
	rm -rf $(BIN)
