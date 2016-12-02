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
aligned_t g_qth_tls_lock;
qth_tls_entry *g_qth_tls_list;
int g_qth_tls_list_size;
int g_qth_tls_key_status[QTH_TLS_KEY_SIZE];

GLT_func_prefix void glt_start() {
    printf("Starting with QTHREADS\n");
}

GLT_func_prefix void glt_end() {
    printf("Ending with QTHREADS\n");
}

GLT_func_prefix glt_team_t * glt_get_team(){
    return main_team;
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
        printf("Opcion 1\n");
        
    } else if (getenv("QTHREAD_NUM_SHEPHERDS") != NULL) {
        num_threads = atoi(getenv("QTHREAD_NUM_SHEPHERDS"));
        printf("Opcion 2\n");
    } else {
        sprintf(buff, "%d", num_threads);
        setenv("QTHREAD_NUM_SHEPHERDS", buff, 1);
        printf("Opcion 3\n");
    }

    if (getenv("GLT_NUM_WORKERS_PER_THREAD") != NULL) {
        num_workers_per_thread = atoi(getenv("GLT_NUM_WORKERS_PER_THREAD"));
        sprintf(buff, "%d", num_workers_per_thread);
        setenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD", buff, 1);
        printf("Opcion 4\n");
    } else if (getenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD") != NULL) {
        num_workers_per_thread = atoi(getenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD"));
        printf("Opcion 5\n");
    } else {
        setenv("QTHREAD_NUM_WORKERS_PER_SHEPHERD", "1", 1);
        num_workers_per_thread = 1;
        printf("Opcion 6\n");
    }

    if ((getenv("QTHREAD_SHEPHERD_BOUNDARY") == NULL) && 
            (getenv("QTHREAD_WORKER_UNIT") == NULL)){
        
        if (num_threads == 1 && num_workers_per_thread > 1) {
            setenv("QTHREAD_SHEPHERD_BOUNDARY", "node", 1);
            setenv("QTHREAD_WORKER_UNIT", "core", 1);
            printf("Bind 1\n");
        }

        if (num_threads > 1 && num_threads <= get_nprocs() / 2) {
            setenv("QTHREAD_SHEPHERD_BOUNDARY", "core", 1);
            setenv("QTHREAD_WORKER_UNIT", "core", 1);
            printf("Bind 2\n");
        }

        if (num_threads > 1 && num_threads > get_nprocs() / 2) {
            setenv("QTHREAD_SHEPHERD_BOUNDARY", "core", 1);
            setenv("QTHREAD_WORKER_UNIT", "core", 1);
            printf("Bind 3\n");
        }
    }
    setenv("QTHREAD_AFFINITY", "yes", 1);

    qth_tls_init(num_threads*num_workers_per_thread);
    
    main_team->num_shepherds = num_threads;
    main_team->num_workers_per_shepherd = num_workers_per_thread;
    printf("creando %d shepherds y %d workers\n",num_threads, num_workers_per_thread);
    CHECK(qthread_initialize(),0); //qthreads
}

GLT_func_prefix void glt_finalize() {
    qth_tls_fini();
    CHECK(qthread_finalize(),0);
}
