all: mth pth_mth

MYTHFLAGS := -I/$(HOME_MTH)/include -L/$(HOME_MTH)/lib -lmyth-native 
CC := gcc
CFLAGS := -fPIC -I. $(MYTHFLAGS) 

OBJECTS := glt.o glt_wu.o glt_util.o glt_mutex.o glt_barrier.o \
	glt_condition.o glt_timer.o glt_tls.o glt_scheduler.o \
	glt_event.o glt_future.o glt_thread.o

ifeq ($(GLT_CORE), 1)
    CFLAGS += -DCORE
endif

ifeq ($(GLT_DEBUG), 1)
    CFLAGS += -g
endif

mth: $(OBJECTS)
	gcc -shared -o libglt.so $(OBJECTS) $(MYTHFLAGS)

pth_mth: 
	gcc -fPIC -I. -I/$(HOME_MTH)/include -L/$(HOME_MTH)/lib -lmyth-native -c -o glt_pthreads.o glt_pthreads.c -DFASTGLT
	gcc -shared -o libgltpthread.so glt_pthreads.o $(MYTHFLAGS) -DFASTGLT -ldl

clean:
	rm *.so *.o
