all: arg mth qth

arg:
	gcc -Wall -c -fPIC glt.c -I. -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt -DARGOBOTS
	gcc -shared -o libglt.so glt.o -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt
	mkdir -p argobots
	mv libglt.so argobots/

mth:
	gcc -Wall -c -fPIC glt.c -I. -I/home/adcastel/massivethreads_wf/include -L/home/adcastel/massivethreads_wf/lib -lmyth  -DMASSIVETHREADS
	gcc -shared -o libglt.so glt.o -I/home/adcastel/massivethreads_wf/include -L/home/adcastel/massivethreads_wf/lib -lmyth
	mkdir -p massivethreads
	mv libglt.so massivethreads/
qth:
	gcc -Wall -c -fPIC glt.c -I. -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread -DQTHREADS
	gcc -shared -o libglt.so glt.o -I/home/adcastel/qthreads/include -L/home/adcastel/qthreads/lib -lqthread
	mkdir -p qthreads
	mv libglt.so qthreads/
clean:
	rm *.o qthreads/*.so massivethreads/*.so argobots/*.so