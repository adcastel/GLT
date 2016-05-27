HOME_GLT=/home/adcastel/GLT/
all: fast_pth_main
#DEB=-g

fast_pth_main:
	gcc pth_main.c -o pth_main_f_mth -I/$(HOME_GLT)/src/massivethreads -I/$(HOME_MTH)/include -L/$(HOME_MTH)/lib -L/$(HOME_GLT)/src/massivethreads -lgltpthread -lmyth-native -lm -DFASTGLT $(DEB)
	gcc pth_main.c -o pth_main_f_qth  -I/$(HOME_GLT)/src/qthreads -I/$(HOME_QTH)/include -L/$(HOME_QTH)/lib -L/$(HOME_GLT)/src/qthreads -lgltpthread -lqthread -lm -DFASTGLT $(DEB)
	gcc pth_main.c -o pth_main_f_arg -I/$(HOME_GLT)/src/argobots -I/$(HOME_ARG)/include -L/$(HOME_ARG)/lib -L/$(HOME_GLT)/src/argobots -lgltpthread -labt  -lm -DFASTGLT $(DEB)

clean: 
	rm pth_main_* 

