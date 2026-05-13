CC = clang
CFLAGS = -Wall -Wextra -pedantic -g -fsanitize=address

.PHONY: clean


test_list: test_list.o list.o
	$(CC) $(CFLAGS) test_list.o list.o -o test_list

test_vector: test_vector.o vector.o
	$(CC) $(CFLAGS) test_vector.o vector.o -o test_vector

%.o : %.c ds.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o test_list


