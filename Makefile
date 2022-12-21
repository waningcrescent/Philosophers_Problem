main: PhilosopherA1 PhilosopherB1

PhilosopherA1: PhilosopherA1.c
	gcc PhilosopherA1.c -lpthread -o PhilosopherA1

PhilosopherB1: PhilosopherB1.c
	gcc PhilosopherB1.c -lpthread -o PhilosopherB1

clean:
	rm -f PhilosopherA1 PhilosopherB1
