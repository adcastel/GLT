all: qth

QTHFLAGS := -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread -DQTHREADS
CC := gcc
CFLAGS := -fPIC -I. -I../ $(QTHFLAGS)

OBJECTS := ../glt.o ../glt_wu.o ../glt_util.o ../glt_mutex.o ../glt_barrier.o


qth: $(OBJECTS)
	gcc -shared -o libglt.so $(OBJECTS) $(QTHFLAGS)
	rm ../*.o
clean:
	rm *.so