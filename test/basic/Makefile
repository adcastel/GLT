HOME_GLT=/home/adcastel/src/GLT/

#all: basic fast_basic
all: basic 
#DEB=-g

basic:
#	gcc basic.c -o basic_mth -I$(HOME_GLT)/src/massivethreads -L$(HOME_GLT)/src/massivethreads/ -lglt -I$(HOME_MTH)/include -L$(HOME_MTH)/lib -lmyth-native  -lm $(DEB)
#	gcc basic.c -o basic_qth  -I$(HOME_GLT)src/qthreads -L$(HOME_GLT)/src/qthreads/ -lglt -I$(HOME_QTH)/include -L$(HOME_QTH)/lib -lqthread -lm $(DEB)
#	gcc basic.c -o basic_pth  -I$(HOME_GLT)/src/pthreads -L$(HOME_GLT)/src/pthreads/ -lglt -lpthread -lm $(DEB)
	gcc basic.c -o basic_arg -I$(HOME_GLT)/src/argobots -L$(HOME_GLT)/src/argobots/ -lglt -I$(HOME_ARG)/include -L$(HOME_ARG)/lib -labt  -lm $(DEB)

fast_basic:
	gcc basic.c -o basic_f_mth -I/$(HOME_GLT)/src/massivethreads -I/$(HOME_MTH)/include -L/$(HOME_MTH)/lib -lmyth-native  -lm -DFASTGLT $(DEB)
	gcc basic.c -o basic_f_qth  -I/$(HOME_GLT)/src/qthreads -I/$(HOME_QTH)/include -L/$(HOME_QTH)/lib -lqthread -lm -DFASTGLT $(DEB)
	gcc basic.c -o basic_f_pth  -I/$(HOME_GLT)/src/pthreads -lpthread -lm -DFASTGLT $(DEB)
	gcc basic.c -o basic_f_arg -I/$(HOME_GLT)/src/argobots -I/$(HOME_ARG)/include -L/$(HOME_ARG)/lib -labt  -lm -DFASTGLT $(DEB)

clean: 
	rm basic_*
