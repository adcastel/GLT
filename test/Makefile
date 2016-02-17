




all: basic 


basic:
	gcc basic.c -o basic_mth -I/home/adcastel/GLT/src/ -L/home/adcastel/GLT/src/massivethreads/ -lglt -I/home/adcastel/massivethreads_wf/include -L/home/adcastel/massivethreads_wf/lib -lmyth  -DMASSIVETHREADS -lm
	gcc basic.c -o basic_qth -I/home/adcastel/GLT/src/ -L/home/adcastel/GLT/src/qthreads/ -lglt -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread  -DQTHREADS -lm
	gcc basic.c -o basic_arg -I/home/adcastel/GLT/src/ -L/home/adcastel/GLT/src/argobots/ -lglt -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt -DARGOBOTS -lm

clean: 
	rm *.o basic_mth basic_qth basic_arg *~
