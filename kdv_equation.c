
#include "kdv_equation.h"

void pdu_pdt( Vector *u, Vector *s, double dx )
{
    int i;
    double dx_3 = pow(dx,3);
    
    for( i = 0; i < N; i++ )
    { 
        VEC(s,i) = -6 * VEC(u,i) * du_x(u,i,dx) - du_xxx(u,i,dx_3);
    }
}

double du_x( Vector *u, int i, double dx )
{
    if( i == 0 )
        return (VEC(u,i+1)- VEC(u,N-1))/(2*dx);
    else if( i == N-1)
        return (VEC(u,0) - VEC(u,i-1))/(2*dx);
    else
        return (VEC(u,i+1) - VEC(u,i-1))/(2*dx);
}
double du_xxx( Vector *u, int i, double dx_3 )
{
    if( i == 0 )
        return (( VEC(u,i+2)-2*VEC(u,i+1) + VEC(u,i) ) - (VEC(u,i) -2*VEC(u,N-1)+VEC(u,N-2) ) )/ (2*dx_3);
    else if( i == 1 )
        return (( VEC(u,i+2)-2*VEC(u,i+1) + VEC(u,i) ) - (VEC(u,i) -2*VEC(u,i-1)+VEC(u,N-1) ) )/ (2*dx_3);
    else if( i == N-1)
        return (( VEC(u,1)-2*VEC(u,0) + VEC(u,i) ) - (VEC(u,i) -2*VEC(u,i-1)+VEC(u,i-2) ) )/ (2*dx_3);
    else if( i == N-2)
        return (( VEC(u,0)-2*VEC(u,i+1) + VEC(u,i) ) - (VEC(u,i) -2*VEC(u,i-1)+VEC(u,i-2) ) )/ (2*dx_3);
    else
        return (( VEC(u,i+2)-2*VEC(u,i+1) + VEC(u,i) ) - (VEC(u,i) -2*VEC(u,i-1)+VEC(u,i-2) ) )/ (2*dx_3);
}
