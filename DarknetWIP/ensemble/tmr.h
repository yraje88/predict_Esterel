#include "ensemble.h"

#include <sys/time.h>
#include <assert.h>

void predict_Esterel();
int predict_tmr(char *datacfg, char *cfgfile, char *weightfile, char *filename, int full);
void run_tmr(int argc, char **argv);
