HOME_GLT=/home/adcastel/GLT/

all: sched fast_sched

sched:
	gcc glt_sched.c -o glt_sched_mth -I$(HOME_GLT)/src/massivethreads -L$(HOME_GLT)/src/massivethreads/ -lglt -I$(HOME_MTH)/include -L$(HOME_MTH)/lib -lmyth-native  -lm $(DEB)
	gcc glt_sched.c -o glt_sched_qth  -I$(HOME_GLT)src/qthreads -L$(HOME_GLT)/src/qthreads/ -lglt -I$(HOME_QTH)/include -L$(HOME_QTH)/lib -lqthread -lm $(DEB)
	gcc glt_sched.c -o glt_sched_pth  -I$(HOME_GLT)/src/pthreads -L$(HOME_GLT)/src/pthreads/ -lglt -lpthread -lm $(DEB)
	gcc glt_sched.c -o glt_sched_arg -I$(HOME_GLT)/src/argobots -L$(HOME_GLT)/src/argobots/ -lglt -I$(HOME_ARG)/include -L$(HOME_ARG)/lib -labt  -lm $(DEB)

fast_sched:
	gcc glt_sched.c -o glt_sched_f_mth -I/$(HOME_GLT)/src/massivethreads -I/$(HOME_MTH)/include -L/$(HOME_MTH)/lib -lmyth-native  -lm -DFASTGLT $(DEB)
	gcc glt_sched.c -o glt_sched_f_qth  -I/$(HOME_GLT)/src/qthreads -I/$(HOME_QTH)/include -L/$(HOME_QTH)/lib -lqthread -lm -DFASTGLT $(DEB)
	gcc glt_sched.c -o glt_sched_f_pth  -I/$(HOME_GLT)/src/pthreads -lpthread -lm -DFASTGLT $(DEB)
	gcc glt_sched.c -o glt_sched_f_arg -I/$(HOME_GLT)/src/argobots -I/$(HOME_ARG)/include -L/$(HOME_ARG)/lib -labt  -lm -DFASTGLT $(DEB)

clean:
	rm glt_sched_*
