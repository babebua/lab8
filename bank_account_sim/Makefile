
FLAGS = -Wall -pthread
INCLUDES = ./include

all: simulate simulate_parrallel

clean:
	rm -f simulate *~

simulate: simulate.c account.c account.h
	gcc -I $(INCLUDES) -o simulate simulate.c account.c $(FLAGS)

simulate_parrallel: simulate_parrallel.c account.c account.h
	 gcc -I $(INCLUDES) -o simulate_parrallel simulate_parrallel.c account.c $(FLAGS)
