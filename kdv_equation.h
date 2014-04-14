
#ifndef KDV_EQUATION_H
#define KDV_EQUATION_H

#include <math.h>
#include "vector_fun.h"

#define N 200 
void pdu_pdt( Vector *u, Vector *s, double dx );
double du_x( Vector *u, int i, double dx );
double du_xxx( Vector *u, int i, double dx_3 );


#endif