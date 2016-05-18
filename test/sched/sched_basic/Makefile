

all:
	gcc glt_sched.c -o glt_sched -I/home/adcastel/GLT/src/argobots -L/home/adcastel/GLT/src/argobots -lglt -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt
	gcc glt_sched.c -o glt_sched_f -I/home/adcastel/GLT/src/argobots -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt -DFASTGLT
clean:
	rm glt_sched glt_sched_f
