




all: basic fast_basic


basic:
	gcc basic.c -o basic_mth -I/home/adcastel/GLT/src/massivethreads -L/home/adcastel/GLT/src/massivethreads/ -lglt -I/home/adcastel/massivethreads_wf/include -L/home/adcastel/massivethreads_wf/lib -lmyth  -lm
	gcc basic.c -o basic_qth -g -I/home/adcastel/GLT/src/qthreads -L/home/adcastel/GLT/src/qthreads/ -lglt -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread -lm
	gcc basic.c -o basic_arg -I/home/adcastel/GLT/src/argobots -L/home/adcastel/GLT/src/argobots/ -lglt -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt  -lm

fast_basic:
	gcc basic.c -o basic_mth -I/home/adcastel/GLT/src/massivethreads -I/home/adcastel/massivethreads_wf/include -L/home/adcastel/massivethreads_wf/lib -lmyth  -lm -DFASTGLT
	gcc basic.c -o basic_qth -g -I/home/adcastel/GLT/src/qthreads -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread -lm -DFASTGLT
	gcc basic.c -o basic_arg -I/home/adcastel/GLT/src/argobots -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt  -lm -DFASTGLT

clean: 
	rm *.o basic_mth basic_qth basic_arg *~
