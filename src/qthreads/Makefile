all: qth

CC := gcc
CFLAGS := -fPIC -I. -I../ -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread -DQTHREADS

OBJECTS := ../glt.o ../glt_wu.o ../glt_util.o ../glt_mutex.o ../glt_barrier.o


qth: $(OBJECTS)
	gcc -shared -o libglt.so $(OBJECTS) -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread
	rm ../*.o
clean:
	rm *.o *.so