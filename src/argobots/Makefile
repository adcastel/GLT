all: arg pth_arg

ARGFLAGS := -I/$(HOME_ARG)/include -L/$(HOME_ARG)/lib -labt
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
	gcc -shared -o libglt.so $(OBJECTS) $(ARGFLAGS)

pth_arg: 
	gcc -fPIC -I. -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt -c -o glt_pthreads.o glt_pthreads.c -DFASTGLT
	gcc -shared -o libgltpthread.so glt_pthreads.o $(ARGFLAGS) -DFASTGLT -ldl

simple:
	gcc simple.c -o simple -I/home/adcastel/GLT/src/argobots -I/home/adcastel/argobots/include -L/home/adcastel/GLT/src/argobots -lgltpthread -DFASTGLT -ldl
#-I/home/adcastel/GLT/src/argobots $(ARGFLAGS)

clean:
	rm *.so *.o

