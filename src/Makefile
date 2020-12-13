CC = clang
CFLAGS = -Werror -std=c99
DEPS = hash_table.h
OBJ = hash_table.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -lm -o $@ $^ $(CFLAGS)
	mv main ../build

.PHONY: clean

clean:
	rm ../build/main $(OBJ)
