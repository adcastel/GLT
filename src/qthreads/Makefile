all: qth pth_qth

QTHFLAGS := -I/$(HOME_QTH)/include -L/$(HOME_QTH)/lib -lqthread 
CC := gcc
CFLAGS := -fPIC -I.  $(QTHFLAGS) 

OBJECTS := glt.o glt_wu.o glt_util.o glt_mutex.o glt_barrier.o \
	   glt_condition.o glt_timer.o glt_tls.o \
	   glt_event.o glt_future.o glt_thread.o glt_scheduler.o

ifeq ($(GLT_CORE), 1)
    CFLAGS += -DCORE
endif

ifeq ($(GLT_DEBUG), 1)
    CFLAGS += -g
endif


qth: $(OBJECTS)
	gcc -shared -o libglt.so $(OBJECTS) $(QTHFLAGS)

pth_qth: 
	gcc -fPIC -I. $(QTHFLAGS) -c -o glt_pthreads.o glt_pthreads.c -DFASTGLT
	gcc -shared -o libgltpthread.so glt_pthreads.o $(QTHFLAGS) -DFASTGLT -ldl

clean:
	rm *.so *.o
