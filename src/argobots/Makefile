all: arg
ARGFLAGS := -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt
CC := gcc
CFLAGS := -fPIC -I. -I../ $(ARGFLAGS)

OBJECTS := glt.o glt_wu.o glt_util.o glt_mutex.o glt_barrier.o glt_condition.o \
	glt_timer.o glt_event_ext.o glt_future_promise_ext.o glt_pool_ext.o \
	glt_scheduler_ext.o glt_self_ext.o glt_thread_ext.o glt_tls_ext.o \
	glt_qthreads_ext.o glt_massivethreads_ext.o

ifeq ($(GLT_CORE), 1)
    CFLAGS += -DCORE
endif

ifeq ($(GLT_DEBUG), 1)
    CFLAGS += -g
endif

arg: $(OBJECTS)
#gcc -Wall -c -fPIC glt.c -I. -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt -DARGOBOTS
	gcc -shared -o libglt.so $(OBJECTS) $(ARGFLAGS)


clean:
	rm *.so *.o