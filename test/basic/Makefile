




all: basic fast_basic
#DEB=-g

basic:
	gcc basic.c -o basic_mth -I/home/adcastel/GLT/src/massivethreads -L/home/adcastel/GLT/src/massivethreads/ -lglt -I/home/adcastel/massivethreads_wf/include -L/home/adcastel/massivethreads_wf/lib -lmyth  -lm $(DEB)
	gcc basic.c -o basic_qth  -I/home/adcastel/GLT/src/qthreads -L/home/adcastel/GLT/src/qthreads/ -lglt -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread -lm $(DEB)
	gcc basic.c -o basic_pth  -I/home/adcastel/GLT/src/pthreads -L/home/adcastel/GLT/src/pthreads/ -lglt -lpthread -lm $(DEB)
	gcc basic.c -o basic_arg -I/home/adcastel/GLT/src/argobots -L/home/adcastel/GLT/src/argobots/ -lglt -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt  -lm $(DEB)

fast_basic:
	gcc basic.c -o basic_f_mth -I/home/adcastel/GLT/src/massivethreads -I/home/adcastel/massivethreads_wf/include -L/home/adcastel/massivethreads_wf/lib -lmyth  -lm -DFASTGLT $(DEB)
	gcc basic.c -o basic_f_qth  -I/home/adcastel/GLT/src/qthreads -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread -lm -DFASTGLT $(DEB)
	gcc basic.c -o basic_f_pth  -I/home/adcastel/GLT/src/pthreads -lpthread -lm -DFASTGLT $(DEB)
	gcc basic.c -o basic_f_arg -I/home/adcastel/GLT/src/argobots -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt  -lm -DFASTGLT $(DEB)

clean: 
	rm basic_pth basic_mth basic_qth basic_arg *_f_*
