#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#ifndef FASTGLT
#include <glt.h>
#else
#include <fast_glt.h>
#endif
#include <math.h>
#include <sys/time.h>
//#define VERBOSE

#ifndef VERBOSE
#define TIMES 50
#else
#define TIMES 1
#endif
#define NUM_ULT 2500


/* structure to pass arguments to expand tasks */

typedef struct {
    double create_time;
    double join_time;
} main_args_t;


void final_func(void *arguments) {

#ifdef VERBOSE

    printf("#ULT: %d Thread: %d (CPU: %d)\n", (int)arguments,glt_get_thread_num(),sched_getcpu());

#endif
}

void thread_func(void *arguments){

    struct timeval t_start_create, t_end_create, t_start_join, t_end_join;
    int i;
    main_args_t *arg;
    arg = (main_args_t *) arguments;

#ifdef VERBOSE
    printf("#Thread: %d (CPU: %d)\n", glt_get_thread_num(), sched_getcpu());
#endif

#ifdef TASK
    GLT_tasklet * tasklets;
    tasklets = glt_tasklet_malloc(NUM_ULT);    
#else
    GLT_ult * ults;
    ults = glt_ult_malloc(NUM_ULT);    
#endif

    gettimeofday(&t_start_create, NULL);

    for(i = 0; i < NUM_ULT; i++){
#ifdef TASK
        glt_tasklet_create_to(final_func, (void *)i,&tasklets[i],glt_get_thread_num());        
#else	    
	glt_ult_create_to(final_func, (void *)i,&ults[i],glt_get_thread_num());        
#endif           
    }
    gettimeofday(&t_end_create, NULL);

    glt_yield();
    gettimeofday(&t_start_join, NULL);
    for (i = 0; i < NUM_ULT; i++) {
#ifdef TASK
        glt_tasklet_join(&tasklets[i]);
#else            
	glt_ult_join(&ults[i]);
#endif     
   }
   
    gettimeofday(&t_end_join, NULL);

    arg->create_time = (((t_end_create.tv_sec * 1000000 + t_end_create.tv_usec) -
                (t_start_create.tv_sec * 1000000 + t_start_create.tv_usec))/1000000.0)/NUM_ULT;
    
    arg->join_time = (((t_end_join.tv_sec * 1000000 + t_end_join.tv_usec) -
                (t_start_join.tv_sec * 1000000 + t_start_join.tv_usec))/1000000.0)/NUM_ULT;
}
    
int main(int argc, char *argv[]) {

    glt_init(argc,argv);
    
    double times[TIMES];
    double times_join[TIMES];
    int i;
    main_args_t * args;
    
    struct timeval t_start_create, t_start_join, t_end_create, t_end_join;
    
    int nthreads = glt_get_num_threads();

   
    double inner_create[TIMES];
    double inner_join[TIMES];
 
    for ( i = 0; i< TIMES; i++){
	times[i]=0.0;
	times_join[i]=0.0;
    }

    for ( i = 0; i< TIMES; i++){
	inner_create[i]=0.0;
	inner_join[i]=0.0;
    }

    args = (main_args_t *) malloc(sizeof (main_args_t)
            * nthreads);

    GLT_ult * ults;

    ults = glt_ult_malloc(nthreads);
 
    for (int t = 0; t < TIMES; t++) {
        
       gettimeofday(&t_start_create, NULL);
	
	 /* Work here */
        for (i = 0; i < nthreads; i++) {
	    glt_ult_create_to(thread_func,(void *) &args[i],&ults[i],i);
        }
       
        gettimeofday(&t_end_create, NULL);

        glt_yield();

        gettimeofday(&t_start_join, NULL);
        for (i = 0; i < nthreads; i++) {
            glt_ult_join(&ults[i]);
        }
        
        gettimeofday(&t_end_join, NULL);

        double time = (t_end_create.tv_sec * 1000000 + t_end_create.tv_usec) -
                (t_start_create.tv_sec * 1000000 + t_start_create.tv_usec);
        times[t] = (time / 1000000.0);
	double time_join = (t_end_join.tv_sec * 1000000 + t_end_join.tv_usec) -
            (t_start_join.tv_sec * 1000000 + t_start_join.tv_usec);
        times_join[t] = (time_join / 1000000.0);
      
        
        for (i = 0; i < nthreads; i++) {
	    /* Gather each thread individually*/
	    inner_create[t]+=args[i].create_time;
	    inner_join[t]+=args[i].join_time;
        }


    }
    double o_min, o_max, o_avg, o_aux, o_sigma, o_dev;
    double o_avgj=times_join[0];
    o_min = times[0];
    o_max = times[0];
    o_aux = times[0];
    for (int t = 1; t < TIMES; t++) {
        if (times[t] < o_min) o_min = times[t];
        if (times[t] > o_max) o_max = times[t];
        o_aux += times[t];
        o_avgj+=times_join[t];
    }
    o_avg = o_aux / TIMES;
    for (int t = 0; t < TIMES; t++) {
        o_sigma = o_sigma + ((times[t] - o_avg)*(times[t] - o_avg));
    }
#ifndef VERBOSE
    o_dev = sqrt(o_sigma / (TIMES - 1));
#else
    o_dev = sqrt(o_sigma);
#endif
    

    double i_min, i_max, i_avg, i_avgj ,i_aux, i_sigma, i_dev;
    i_avg = inner_create[0];
    i_avgj = inner_join[0];
    for (int t = 1; t < TIMES; t++) {
        i_avg += inner_create[t];
        i_avgj += inner_join[t];
    }

    i_avg = (i_avg / TIMES) / nthreads;
    i_avgj = (i_avgj / TIMES) / nthreads;

#ifndef VERBOSE
//printf("Nthreads OCreation OJoin ICreation IJoin" 
#endif
printf("%d %f %f %f %f\n", nthreads, o_avg, o_avgj, i_avg, i_avgj );
    
    

    glt_finalize();

    return EXIT_SUCCESS;
}



