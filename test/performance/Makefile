HOME_GLT=/home/adcastel/src/GLT/
all: main fast_main
#DEB=-g

main:
#	gcc main.c -o main_mth -I$(HOME_GLT)/src/massivethreads -L$(HOME_GLT)/src/massivethreads/ -lglt -I$(HOME_MTH)/include -L$(HOME_MTH)/lib -lmyth-native  -lm $(DEB)
	gcc main.c -o main_qth  -I$(HOME_GLT)src/qthreads -L$(HOME_GLT)/src/qthreads/ -lglt -I$(HOME_QTH)/include -L$(HOME_QTH)/lib -lqthread -lm $(DEB)
#	gcc main.c -o main_pth  -I$(HOME_GLT)/src/pthreads -L$(HOME_GLT)/src/pthreads/ -lglt -lpthread -lm $(DEB)
	gcc main.c -o main_arg -I$(HOME_GLT)/src/argobots -L$(HOME_GLT)/src/argobots/ -lglt -I$(HOME_ARG)/include -L$(HOME_ARG)/lib -labt  -lm $(DEB)

fast_main:
#	gcc main.c -o main_f_mth -I/$(HOME_GLT)/src/massivethreads -I/$(HOME_MTH)/include -L/$(HOME_MTH)/lib -lmyth-native  -lm -DFASTGLT $(DEB)
	gcc main.c -o main_f_qth  -I/$(HOME_GLT)/src/qthreads -I/$(HOME_QTH)/include -L/$(HOME_QTH)/lib -lqthread -lm -DFASTGLT $(DEB)
#	gcc main.c -o main_f_pth  -I/$(HOME_GLT)/src/pthreads -lpthread -lm -DFASTGLT $(DEB)
	gcc main.c -o main_f_arg -I/$(HOME_GLT)/src/argobots -I/$(HOME_ARG)/include -L/$(HOME_ARG)/lib -labt  -lm -DFASTGLT $(DEB)

clean: 
	rm main_* 
