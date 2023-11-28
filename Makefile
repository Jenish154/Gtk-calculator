CC = gcc
SRC_DIR = src
SRC = $(SRC_DIR)/*.c
LIBS = gtk+-3.0
INCLUDE_DIR = include

all: $(SRC)
	
	$(CC) `pkg-config --cflags $(LIBS)` -I $(INCLUDE_DIR) -o calculator $(SRC) `pkg-config --libs $(LIBS)`


run:
	./calculator

clean:
	rm -f calculator