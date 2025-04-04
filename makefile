CC = gcc
CFLAGS = -Wall -pedantic -ansi

OBJ_A = p3_e1.o vertex.o delivery.o
OBJ_B = p3_e2a.o vertex.o delivery.o queue.o
EJS = p3_e2a p3_e1 

all: $(EJS)

p3_e1: $(OBJ_A)
	$(CC) -o $@ $^ -L. -lqueue

p3_e2a: $(OBJ_B)
	$(CC) -o $@ $^

vertex.o: vertex.c vertex.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

queue.o: queue.c queue.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

delivery.o: delivery.c delivery.h types.h queue.h
	$(CC) $(CFLAGS) -c -o $@ $<

p3_e1.o: p3_e1.c delivery.h types.h queue.h vertex.h
	$(CC) $(CFLAGS) -c -o $@ $<

p3_e2a.o: p3_e1.c delivery.h types.h queue.h vertex.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_A) $(OBJ_B) $(EJS)

.PHONY: all clean
