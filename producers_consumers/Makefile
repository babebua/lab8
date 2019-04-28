
FLAGS = -Wall -pthread
INCLUDES = ./include

all: client

clean:
	rm -f client *~

client: client.c sbuf.c
	gcc -I $(INCLUDES) -o client client.c sbuf.c $(FLAGS)

