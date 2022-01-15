main: main.c 
	gcc -Wall -Werror -pedantic -o main main.c

clean:
	rm -f *.o main