all: arg

CC := gcc
CFLAGS := -fPIC -I. -I../ -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt -DARGOBOTS

OBJECTS := ../glt.o ../glt_wu.o ../glt_util.o ../glt_mutex.o ../glt_barrier.o

arg: $(OBJECTS)
#gcc -Wall -c -fPIC glt.c -I. -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt -DARGOBOTS
	gcc -shared -o libglt.so $(OBJECTS) -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt
	rm ../*.o
clean:
	rm *.o *.so