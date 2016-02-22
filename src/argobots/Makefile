all: arg
ARGFLAGS := -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt
CC := gcc
CFLAGS := -fPIC -I. -I../ $(ARGFLAGS)

OBJECTS := glt.o glt_wu.o glt_util.o glt_mutex.o glt_barrier.o glt_condition.o

arg: $(OBJECTS)
#gcc -Wall -c -fPIC glt.c -I. -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt -DARGOBOTS
	gcc -shared -o libglt.so $(OBJECTS) $(ARGFLAGS)
	
clean:
	rm *.so *.o