CC = gcc
CFLAGS = -Wall -O3

all: main

debug: CFLAGS += -g -fsanitize=address
debug: LDLFAGS += -fsanitize=address
debug: main

test: test.o lfsr.o filter.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

testf: testfilter.o lfsr.o filter.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

testf.o: testfilter.c
	$(CC) $(CFLAGS) -c $< -o $@

testl: testlfsr.o lfsr.o 
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

testl.o: testlfsr.c
	$(CC) $(CFLAGS) -c $< -o $@

test.o: test.c
	$(CC) $(CFLAGS) -c $< -o $@

main: main.o lfsr.o filter.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

main.o: main.c filter.h
	$(CC) $(CFLAGS) -c $<

lfsr.o: lfsr.c lfsr.h
	$(CC) $(CFLAGS) -c $<

filter.o: filter.c filter.h lfsr.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o main test testl

