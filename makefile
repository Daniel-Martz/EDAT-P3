CC = gcc
CFLAGS = -Wall -pedantic -ansi

OBJ_A = p3_e1.o vertex.o delivery.o
OBJ_B = p3_e2a.o vertex.o delivery.o queue.o
OBJ_C = p3_e2b.o vertex.o graph.o queue.o stack.o
OBJ_D = p3_e3.o list.o file_utils.o
EJS = p3_e3 p3_e2a p3_e2b p3_e1 

all: $(EJS)

p3_e1: $(OBJ_A)
	$(CC) -o $@ $^ -L. -lqueue

p3_e2a: $(OBJ_B)
	$(CC) -o $@ $^

p3_e2b: $(OBJ_C)
	$(CC) -o $@ $^

p3_e3: $(OBJ_D)
	$(CC) -o $@ $^

vertex.o: vertex.c vertex.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<
	
graph.o: graph.c graph.h vertex.h types.h queue.h stack.h
	$(CC) $(CFLAGS) -c -o $@ $<

stack.o: stack.c stack.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

queue.o: queue.c queue.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

list.o: list.c list.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

file_utils.o: file_utils.c file_utils.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

delivery.o: delivery.c delivery.h types.h queue.h
	$(CC) $(CFLAGS) -c -o $@ $<

p3_e1.o: p3_e1.c delivery.h types.h queue.h vertex.h
	$(CC) $(CFLAGS) -c -o $@ $<

p3_e2a.o: p3_e1.c delivery.h types.h queue.h vertex.h
	$(CC) $(CFLAGS) -c -o $@ $<

p3_e2b.o: p3_e2b.c graph.h vertex.h types.h
	$(CC) $(CFLAGS) -c -o $@ $<

p3_e3.o: p3_e3.c list.h types.h file_utils.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_A) $(OBJ_B) $(OBJ_C) $(EJS) *.o


runv2a: 
	valgrind --leak-check=full ./p3_e2a requests.txt

runv2b: 
	valgrind --leak-check=full ./p3_e2b city_graph.txt 100 700

runv1:
	valgrind --leak-check=full ./p3_e1 requests.txt

.PHONY: all clean runv1 runv2a runv2b runv3

