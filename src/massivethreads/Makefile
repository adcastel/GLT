all: mth

CC := gcc
CFLAGS := -fPIC -I. -I../ -I/home/adcastel/massivethreads_wf/include -L/home/adcastel/massivethreads_wf/lib -lmyth  -DMASSIVETHREADS

OBJECTS := ../glt.o ../glt_wu.o ../glt_util.o ../glt_mutex.o ../glt_barrier.o



mth: $(OBJECTS)
#gcc -Wall -c -fPIC glt.c -I. -I/home/adcastel/massivethreads_wf/include -L/home/adcastel/massivethreads_wf/lib -lmyth  -DMASSIVETHREADS
	gcc -shared -o libglt.so $(OBJECTS) -I/home/adcastel/massivethreads_wf/include -L/home/adcastel/massivethreads_wf/lib -lmyth
	rm ../*.o

clean:
	rm *.o *.so