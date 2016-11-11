/* See COPYRIGHT in top-level directory. */
/*
 * Main functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

glt_team_t * main_team;


GLT_func_prefix void glt_start() {
    printf("Starting with QTHREADS\n");
}

GLT_func_prefix void glt_end() {
    printf("Ending with QTHREADS\n");
}

GLT_func_prefix void qth_tls_init(int nworkers)
{
	g_qth_tls_list=NULL;
	g_qth_tls_list_size=0;
	memset(g_qth_tls_key_status,0,sizeof(int)*QTH_TLS_KEY_SIZE);
}

GLT_func_prefix void qth_tls_fini(void)
{
	if (g_qth_tls_list)free(g_qth_tls_list);
	g_qth_tls_list=NULL;
	g_qth_tls_list_size=0;
}

GLT_func_prefix void glt_init(int argc, char * argv[]) {
    int num_threads = get_nprocs();
    main_team = (glt_team_t *) malloc(sizeof (glt_team_t));

    char buff[10];
    int num_workers_per_thread;

    if (getenv("GLT_NUM_THREADS") != NULL) {
        num_threads = atoi(getenv("GLT_NUM_THREADS"));
        sprintf(buff, "%d", num_threads);
        setenv("QTHREAD_NUM_SHEPHERDS", buff, 1);
    } else if (getenv("QTHREAD_NUM_SHEPHERDS") != NULL) {
        num_threads = atoi(getenv("QTHREAD_NUM_SHEPHERDS"));
    } else {
        sprintf(buff, "%d", num_threads);
        setenv("QTHREAD_NUM_SHEPHERDS", buff, 1);
    }

    if (getenv("GLT_NUM_WORKERS_PER_THREAD") != NULL) {
        num_workers_per_thread = atoi(getenv("GLT_NUM_WORKERS_PER_THREAD"));
        sprintf(buff, "%d", num_workers_per_thread);
        setenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD", buff, 1);
    } else if (getenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD") != NULL) {
        num_workers_per_thread = atoi(getenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD"));
    } else {
        setenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD", "1", 1);
    }

    if ((getenv("QTHREAD_SHEPHERD_BOUNDARY") == NULL) && 
            (getenv("QTHREAD_WORKER_UNIT") == NULL)){
        
        if (num_threads == 1 && num_workers_per_thread > 1) {
            setenv("QTHREAD_SHEPHERD_BOUNDARY", "node", 1);
            setenv("QTHREAD_WORKER_UNIT", "core", 1);
        }

        if (num_threads > 1 && num_threads <= get_nprocs() / 2) {
            setenv("QTHREAD_SHEPHERD_BOUNDARY", "core", 1);
            setenv("QTHREAD_WORKER_UNIT", "core", 1);
        }

        if (num_threads > 1 && num_threads > get_nprocs() / 2) {
            setenv("QTHREAD_SHEPHERD_BOUNDARY", "core", 1);
            setenv("QTHREAD_WORKER_UNIT", "core", 1);
        }
    }
    setenv("QTHREAD_AFFINITY", "yes", 1);

    qth_tls_init(num_threads*num_workers_per_thread);
    
    main_team->num_shepherds = num_threads;
    main_team->num_workers_per_shepherd = num_workers_per_thread;
    CHECK(qthread_initialize(),0); //qthreads
}

GLT_func_prefix void glt_finalize() {
    qth_tls_fini();
    CHECK(qthread_finalize(),0);
}
