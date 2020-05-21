all: main

run: main
	./main

main: queue.o list.o adjacency_list.o algorithms.o main.o
	gcc queue.o list.o adjacency_list.o algorithms.o main.o -o main

main.o: main.c
	gcc main.c -c

algorithms.o: algorithms.c
	gcc algorithms.c -c

adjacency_list.o: adjacency_list.c
	gcc adjacency_list.c -c

list.o: list.c
	gcc list.c -c

queue.o: queue.c
	gcc queue.c -c