
FLAGS = -Wall -pthread
INCLUDES = ./include

all: simulate simulate_parrallel

clean:
	rm -f simulate *~

simulate: simulate.c account.c account.h
	gcc -I $(INCLUDES) -o simulate simulate.c account.c $(FLAGS)

simulate_parrallel: sim_par.c account.c account.h
	 gcc -I $(INCLUDES) -o sim_par sim_par.c account.c $(FLAGS)
