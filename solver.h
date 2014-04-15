
#ifndef SOLVER_H
#define SOLVER_H

#include <math.h>
#include "vector_fun.h"

int runge_kutta( double dt, Vector *u, double dx, Vector *u_n,
    void dudt (Vector *, Vector *, double));

/*-------------------------------------------------------------*/
#include <sys/time.h>
#include <stdlib.h>
static inline double
WTime(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec / 1e6;
}
#endif