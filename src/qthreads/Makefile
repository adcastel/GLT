all: qth

QTHFLAGS := -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread 
CC := gcc
CFLAGS := -fPIC -I.  $(QTHFLAGS) 

OBJECTS := glt.o glt_wu.o glt_util.o glt_mutex.o glt_barrier.o \
	glt_condition.o glt_timer.o glt_basic.o  \
	glt_atomic.o glt_feb.o glt_sinc.o glt_loop.o \
	glt_data_structures.o glt_syscall.o glt_runtime.o \
	glt_memory.o glt_argobots.o glt_massivethreads.o

ifeq ($(GLT_CORE), 1)
    CFLAGS += -DCORE
endif

ifeq ($(GLT_DEBUG), 1)
    CFLAGS += -g
endif


qth: $(OBJECTS)
	gcc -shared -o libglt.so $(OBJECTS) $(QTHFLAGS)
	
clean:
	rm *.so *.o