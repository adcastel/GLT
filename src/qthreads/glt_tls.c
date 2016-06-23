/* See COPYRIGHT in top-level directory. */
/*
 * TLS functions file.
 */

#ifndef FASTGLT
#include <glt.h>
#define GLT_func_prefix 
#else
#define GLT_func_prefix static inline
#endif

GLT_func_prefix void glt_key_create(void(*destructor)(void *value), GLT_key *newkey) {
    int i;
    int ret;
    qthread_lock(&g_qth_tls_lock);
    if (!destructor){
        for (i=0;i<QTH_TLS_KEY_SIZE;i++){
			if (g_qth_tls_key_status[i]==0)break;
		}
		if (i==QTH_TLS_KEY_SIZE){
			ret=EAGAIN;
		}
		else{
			g_qth_tls_key_status[i]=1;
			*newkey=i;
		}
    }
    qthread_unlock(&g_qth_tls_lock);

    //myth_key_create(newkey, destructor);
}

GLT_func_prefix void glt_key_free(GLT_key *key) {
    int ret=0;
    qthread_lock(&g_qth_tls_lock);
	int i;
	if (g_qth_tls_list){
		for (i=0;i<g_qth_tls_list_size;i++){
			if (g_qth_tls_list[i].key==*key){
				memmove(&g_qth_tls_list[i],&g_qth_tls_list[i+1],sizeof(qth_tls_entry)*(g_qth_tls_list_size-i-1));
				g_qth_tls_list_size--;
			}
		}
		g_qth_tls_list=realloc(g_qth_tls_list,sizeof(qth_tls_entry)*g_qth_tls_list_size);
	}
	if (g_qth_tls_key_status[*key]==0){ret=EINVAL;}
	else{
		g_qth_tls_key_status[*key]=0;
	}
	qthread_unlock(&g_qth_tls_lock);
    //myth_key_delete(*key);
}

GLT_func_prefix void glt_key_set(GLT_key key, void *value) {
    	int ret=0;
	qthread_lock(&g_qth_tls_lock);
	if (g_qth_tls_key_status[key]==0){ret=EINVAL;}
	else{
		int i;
		if (g_qth_tls_list){
			for (i=0;i<g_qth_tls_list_size;i++){
				if (g_qth_tls_list[i].key==key && g_qth_tls_list[i].th==qthread_id()){
					g_qth_tls_list[i].value=value;
					break;
				}
			}
			if (i==g_qth_tls_list_size){
				g_qth_tls_list_size++;
				g_qth_tls_list=realloc(g_qth_tls_list,sizeof(qth_tls_entry)*g_qth_tls_list_size);
				g_qth_tls_list[i].key=key;
				g_qth_tls_list[i].th=qthread_id();
				g_qth_tls_list[i].value=value;
			}
		}
		else{
		        g_qth_tls_list_size = 1;
			g_qth_tls_list=malloc(sizeof(qth_tls_entry));
			g_qth_tls_list[0].key=key;
			g_qth_tls_list[0].th=qthread_id();
			g_qth_tls_list[0].value=value;
		}
	}
	qthread_unlock(&g_qth_tls_lock);
    //qth_setspecific(key, value);
}

GLT_func_prefix void glt_key_get(GLT_key key, void **value) {
	qthread_lock(&g_qth_tls_lock);
	if (g_qth_tls_key_status[key]!=0){
		int i;
		if (g_qth_tls_list){
			for (i=0;i<g_qth_tls_list_size;i++){
				if (g_qth_tls_list[i].key==key && g_qth_tls_list[i].th==qthread_id()){
					*value=g_qth_tls_list[i].value;
					break;
				}
			}
		}
	}
	qthread_unlock(&g_qth_tls_lock);
    //*value = qth_getspecific(key);
}
