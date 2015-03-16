CC = gcc
FLAGS = -c
OBJS = demo.o doubly_linked_list_adt.o datatype_int.o
EXECUTABLE_NAME = dllist-demo

# Compile
all: $(OBJS)
	$(CC) $(OBJS) -o $(EXECUTABLE_NAME)
	rm -f $(OBJS)

demo.o: demo.c
	$(CC) $(FLAGS) demo.c

doubly_linked_list_adt.o: doubly_linked_list_adt.c
	$(CC) $(FLAGS) doubly_linked_list_adt.c

datatype_int.o: datatype_int.c
	$(CC) $(FLAGS) datatype_int.c

run:
	./$(EXECUTABLE_NAME)

# Clean-up
clean:
	rm -f $(EXECUTABLE_NAME)
