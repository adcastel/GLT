all: arg pth_arg

ARGFLAGS := -I/$(HOME_ARG)/include -L/$(HOME_ARG)/lib -labt
CC := gcc
CFLAGS := -fPIC -I. $(ARGFLAGS) 

OBJECTS := glt.o glt_wu.o glt_util.o glt_mutex.o glt_barrier.o glt_condition.o \
	glt_timer.o glt_event.o glt_future_promise.o  \
	glt_scheduler.o  glt_thread.o glt_tls.o 

ifeq ($(GLT_CORE), 1)
    CFLAGS += -DCORE
endif

ifeq ($(GLT_DEBUG), 1)
    CFLAGS += -g
endif

arg: $(OBJECTS)
	gcc -shared -o libglt.so $(OBJECTS) $(ARGFLAGS)

pth_arg: 
	gcc -fPIC -I. $(ARGFLAGS) -c -o glt_pthreads.o glt_pthreads.c -DFASTGLT
	gcc -shared -o libgltpthread.so glt_pthreads.o $(ARGFLAGS) -DFASTGLT -ldl

clean:
	rm *.so *.o

