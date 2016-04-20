all: mth
MYTHFLAGS := -I/home/adcastel/massivethreads_wf/include -L/home/adcastel/massivethreads_wf/lib -lmyth 
CC := gcc
CFLAGS := -fPIC -I. $(MYTHFLAGS)

OBJECTS := glt.o glt_wu.o glt_util.o glt_mutex.o glt_barrier.o \
	glt_condition.o glt_timer.o glt_wsapi.o glt_prof_log.o \
	glt_tls.o glt_felock.o \
	glt_argobots.o glt_qthreads.o

ifeq ($(GLT_CORE), 1)
    CFLAGS += -DCORE
endif

ifeq ($(GLT_DEBUG), 1)
    CFLAGS += -g
endif

mth: $(OBJECTS)
	gcc -shared -o libglt.so $(OBJECTS) $(MYTHFLAGS)

clean:
	rm *.so *.o