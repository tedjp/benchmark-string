all: hex

nibble.o: nibble.cpp nibble.h
	g++ -Wall -O3 -g -c -o $@ $<

256.o: 256.cpp 256.h
	g++ -Wall -O3 -g -c -o $@ $<

hex: hex.cpp nibble.o 256.o
	g++ -Wall -O3 -g -I../../benchmark/include -o $@ $^ ../../benchmark/src/libbenchmark.a -lpthread /usr/lib/libfmt.a

clean:
	rm -f hex nibble.o

run: hex
	./hex
