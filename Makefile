all: hex

COMPILE = g++ -std=gnu++1z -O3 -g -Wall -c
LINK = g++ -std=gnu++1z -O3 -g -Wall

nibble.o: nibble.cpp nibble.h
	$(COMPILE) -o $@ $<

256.o: 256.cpp 256.h
	 $(COMPILE) -o $@ $<

hex: hex.cpp nibble.o 256.o
	$(LINK) -I../../benchmark/include -o $@ $^ ../../benchmark/src/libbenchmark.a -lpthread /usr/lib/libfmt.a

clean:
	rm -f hex nibble.o 256.o

run: hex
	./hex
