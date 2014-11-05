CFLAGS =-Wall -g

all: ex19 epic

ex19: object.o game.o
epic: object.o game.o

clean:
	rm -f ex19
	rm -f epic
	rm -f object.o
	rm -f game.o

test:
	python ./test.py ./ex19
