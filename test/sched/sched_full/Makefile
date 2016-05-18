OBJ=sched_user_ws

all:
	gcc $(OBJ).c -o glt_a_ws -I/home/adcastel/GLT/src/argobots -L/home/adcastel/GLT/src/argobots -lglt -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt
	gcc $(OBJ).c -o glt_a_ws_f -I/home/adcastel/GLT/src/argobots -I/home/adcastel/argobots/include -L/home/adcastel/argobots/lib -labt -DFASTGLT
clean:
	rm glt_a_ws glt_a_ws_f
