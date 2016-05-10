all: mth
PTHFLAGS := -lpthread 
CC := gcc
CFLAGS := -fPIC -I. $(PTHFLAGS)

OBJECTS := glt.o glt_wu.o glt_util.o glt_mutex.o glt_barrier.o \
	glt_condition.o glt_timer.o glt_tls.o \
	glt_argobots.o glt_qthreads.o glt_massivethreads.o glt_scheduler.o

ifeq ($(GLT_CORE), 1)
    CFLAGS += -DCORE
endif

ifeq ($(GLT_DEBUG), 1)
    CFLAGS += -g
endif

mth: $(OBJECTS)
	gcc -shared -o libglt.so $(OBJECTS) $(PTHFLAGS)

clean:
	rm *.so *.o
