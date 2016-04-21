#include <stdarg.h>
#include <assert.h>
#ifndef FASTGLT
#include "glt.h"
#else
#include "fast_glt.h"
#endif

GLT_sched_config_var param_a = {
  .idx = 0,
  .type = ABT_SCHED_CONFIG_INT
};

GLT_sched_config_var param_b = {
  .idx = 1,
  .type = ABT_SCHED_CONFIG_DOUBLE
};

int main(int argc, char *argv[])
{
    int a = 5;
    double b = 3.0;
    GLT_sched_config config1, config2, config3, config4;

    int a2;
    double b2;

    /* Initialize */
    glt_init(argc, argv);

    glt_scheduler_config_create(&config1, param_a, a, GLT_sched_config_var_end);
    a2 = 0; b2 = 0.0;
    glt_scheduler_config_read(config1, 2, &a2, &b2);
    glt_scheduler_config_free(&config1);
    assert(a2 == a && b2 == 0.0);

    glt_scheduler_config_create(&config2, param_b, b, GLT_sched_config_var_end);
    a2 = 0; b2 = 0.0;
    glt_scheduler_config_read(config2, 2, &a2, &b2);
    glt_scheduler_config_free(&config2);
    assert(a2 == 0 && b2 == b);

    glt_scheduler_config_create(&config3, param_a, a, param_b, b,
                          GLT_sched_config_var_end);
    a2 = 0; b2 = 0.0;
    glt_scheduler_config_read(config3, 2, &a2, &b2);
    glt_scheduler_config_free(&config3);
    assert(a2 == a && b2 == b);

    glt_scheduler_config_create(&config4, param_b, b, param_a, a,
                          GLT_sched_config_var_end);
    a2 = 0; b2 = 0.0;
    glt_scheduler_config_read(config4, 2, &a2, &b2);
    glt_scheduler_config_free(&config4);
    assert(a2 == a && b2 == b);

    /* Finalize */

    printf("All past\n");

    glt_finalize();
    return 0;
}

