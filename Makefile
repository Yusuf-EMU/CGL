exec = cgl
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g 

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp $(exec) /usr/local/bin/$(exec)

test:
	echo No tests

clean:
	-rm $(exec)
	-rm src/*.o

debug:
	make
	gdb $(exec)
