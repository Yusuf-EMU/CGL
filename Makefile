exec = cgl
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -I/usr/local/include -L/usr/local/lib -lglfw3 -ldl -lm -lGLEW -lGLU -lGL -lX11 -pthread

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