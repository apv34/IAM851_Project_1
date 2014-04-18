
#include "solver.h"

int runge_kutta( double dt, Vector *u, double dx, Vector *u_n, void dudt (Vector *, Vector *, double))
{
    Vector s1;
    Vector s2;
    Vector s3;
    Vector s4;
    Vector w;
    int i;
    /*
    vector_initialize( &s1, u_n -> N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
    vector_initialize( &s2, u_n -> N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
    vector_initialize( &s3, u_n -> N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
    vector_initialize( &s4, u_n -> N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
    vector_initialize( &w, u_n -> N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
    */
    s1.N = u -> N;
    s2.N = u -> N;
    s3.N = u -> N;
    s4.N = u -> N;
    w.N = u -> N;

    dudt( u, &s1, dx);
    vector_add( u, 1, &s1, 0.5*dt, &w);
    if( isnan(s1.element[4]) )
    {
        printf( "s1 NAN\n" );
        return -1;
    }

    dudt( &w, &s2, dx );
    vector_add( u, 1, &s2, 0.5*dt, &w);
    if( isnan(s2.element[4]) )
    {
        printf( "s2 NAN\n" );
        return -1;
    }
    
    dudt( &w, &s3, dx );
    vector_add( u, 1, &s3, dt, &w);

    if( isnan(s3.element[4]) )
    {
        printf( "s3 NAN\n" );
        return -1;
    }
    dudt( &w, &s4, dx);
    if( isnan(s4.element[4]) )
    {
        printf( "s4 NAN\n" );
        return -1;
    }
    #pragma omp parallel for
    for( i = 0; i < u -> N; i++)
    {
        VEC(u_n,i) = VEC(u,i) + dt/6*( s1.element[i] + 2 * s2.element[i] + 2* s3.element[i] + s4.element[i] );
    }

    return 0;
}