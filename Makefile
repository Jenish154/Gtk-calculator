CC = gcc
SRC = calc.c
LIBS = gtk+-3.0

all: $(SRC)
	
	$(CC) `pkg-config --cflags $(LIBS)` -o calculator $(SRC) `pkg-config --libs $(LIBS)`


run:
	./calculator

clean:
	rm -f calculator