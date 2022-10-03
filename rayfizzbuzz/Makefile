CC=gcc
CFLAGS=--std=c99 --pedantic -ggdb -Wall -Wextra
LIBS=`pkg-config --libs raylib`


run : rayfizzbuzz
	@./rayfizzbuzz
rayfizzbuzz : main.c
	$(CC) $(CLFAGS) -o $@ $^ $(LIBS)

clean: 
	@rm rayfizzbuzz
