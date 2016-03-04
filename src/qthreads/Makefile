all: qth

QTHFLAGS := -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread 
CC := gcc
CFLAGS := -fPIC -I. -I../ $(QTHFLAGS) 

OBJECTS := glt.o glt_wu.o glt_util.o glt_mutex.o glt_barrier.o \
	glt_condition.o glt_timer.o glt_basic_ext.o  \
	glt_atomic_ext.o glt_feb_ext.o glt_sinc_ext.o glt_loop_ext.o \
	glt_data_structures_ext.o glt_syscall_ext.o glt_runtime_ext.o \
	glt_memory_ext.o glt_argobots_ext.o glt_massivethreads_ext.o

ifeq ($(CORE), 1)
    CFLAGS += -DCORE
endif


qth: $(OBJECTS)
	gcc -shared -o libglt.so $(OBJECTS) $(QTHFLAGS)
	
clean:
	rm *.so *.o