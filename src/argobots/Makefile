all: arg
ARGFLAGS := -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt
CC := gcc
CFLAGS := -fPIC -I. $(ARGFLAGS)

OBJECTS := glt.o glt_wu.o glt_util.o glt_mutex.o glt_barrier.o glt_condition.o \
	glt_timer.o glt_event.o glt_future_promise.o glt_pool.o \
	glt_scheduler.o glt_self.o glt_thread.o glt_tls.o \
	glt_qthreads.o glt_massivethreads.o

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