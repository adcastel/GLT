all: qth

QTHFLAGS := -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread 
CC := gcc
CFLAGS := -fPIC -I. -I../ $(QTHFLAGS) 

OBJECTS := glt.o glt_wu.o glt_util.o glt_mutex.o glt_barrier.o \
	glt_condition.o


qth: $(OBJECTS)
	gcc -shared -o libglt.so $(OBJECTS) $(QTHFLAGS)
	
clean:
	rm *.so *.o