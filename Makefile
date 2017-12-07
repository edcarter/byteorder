all: main test

main:
	gcc main.c -o main

test:
	echo "Running Tests" && ./main

clean:
	rm -f *.o main 
