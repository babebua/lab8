
FLAGS = -Wall -pthread
INCLUDES = ./include

all: client

clean:
	rm -f client *~

client: client.c smoker.c
	gcc -I $(INCLUDES) -o client client.c smoker.c $(FLAGS)

