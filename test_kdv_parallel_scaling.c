
#include <stdio.h>
#include "kdv_equation.h"
#include "solver.h"
#include "omp.h"

#define RUN 6

int runge_kutta_np( double dt, Vector *u, double dx, Vector *u_n,
    void dudt (Vector *, Vector *, double));

void vector_add_np( Vector* x, double a, Vector* y, double b, Vector* z);

void pdu_pdt_np( Vector *u, Vector *s, double dx );

void vector_copy_np( Vector *x, Vector *y );

int main()
{
    Vector u;
    Vector u_n;
    
    int N = 32;
    double dx = 8/((double)N-1);
    double dt = pow(dx, 3);
    double beg, end;
    double time[RUN] = { 0.0 };
    double ptime[RUN] = { 0.0 };
    char filename[5];
    int k = 0;
    int i = 0;
    int valid;
    FILE* output;
    int n_threads = omp_get_num_threads();

    printf( "Test KdV Scaling Parallel Vs UnParallel\n" );
    printf( "Standard\n" );
    
    sprintf(filename, "parallel_scaling_%d.txt",n_threads); 
    output = fopen( filename, "w" );
    fprintf( output,"Test KdV Scaling Parallel Vs UnParallel for "
        "%d Threads\n", n_threads);
    fprintf( output,"KdV solution of 2*sech^2(x+4) for 4s:\n" );
    fprintf( output,"Standard\n" );
    for( i = 0; i < RUN; i++ ){
        N = N*2;
        dx = 8/((double)N-1);
        dt = pow(dx, 3);
        printf( "Run %d for N = %d\n", i+1,N);
        vector_initialize( &u, N,
            (double[MAX_SIZE]) {0,0}, MAX_SIZE );
        vector_initialize( &u_n, N,
            (double[MAX_SIZE]) {0,0}, MAX_SIZE );
        simple_sec( &u, dx, 1, 4 );
        beg = WTime();
        for( k = 0; k*dt < 1; k++ )
        {
            valid = runge_kutta_np( dt, &u, dx, &u_n, pdu_pdt_np);
            vector_copy_np( &u, &u_n);
            if( valid == -1 )
            {
                printf("ERROR!\n");
                printf( "%f\n", k*dt);
                assert( valid != -1 );
                break;
            }
        }
        end = WTime();
        time[i] = end - beg;
        fprintf( output, "%d - %f\n", N, time[i]);
    }
    
    /***********************************************************/
    fprintf( output,"Parallel %d\n", n_threads );
    N = 32;
    dx = 8/((double)N-1);
    dt = pow(dx, 3);
    for( i = 0; i < RUN; i++ ){
        N = N*2;
        dx = 8/((double)N-1);
        dt = pow(dx, 3);
        printf( "Run %d for N = %d\n", i+1,N);
        vector_initialize( &u, N,
            (double[MAX_SIZE]) {0,0}, MAX_SIZE );
        vector_initialize( &u_n, N,
            (double[MAX_SIZE]) {0,0}, MAX_SIZE );
        simple_sec( &u, dx, 1, 4 );
        beg = WTime();
        for( k = 0; k*dt < 1; k++ )
        {
            valid = runge_kutta( dt, &u, dx, &u_n, pdu_pdt);
            vector_copy( &u, &u_n);
            if( valid == -1 )
            {
                printf("ERROR!\n");
                printf( "%f\n", k*dt);
                assert( valid != -1 );
                break;
            }
        }
        end = WTime();
        ptime[i] = end - beg;
        fprintf( output, "%d - %f\n", N, ptime[i]);
    }
    
    
    printf( "KdV solution of 2*sech^2(x+4) for 4s:\n" );
    for( i = 0; i < RUN; i++ ){
        printf( "N = %6f  Took: %fs\tParallel: %fs\n", 128*pow(2, i ), time[i], ptime[i]);
    }
    
    fclose( output );
    return 0;
}


int runge_kutta_np( double dt, Vector *u, double dx, Vector *u_n, void dudt (Vector *, Vector *, double))
{
    Vector s1;
    Vector s2;
    Vector s3;
    Vector s4;
    Vector w;
    int i;

    s1.N = u -> N;
    s2.N = u -> N;
    s3.N = u -> N;
    s4.N = u -> N;
    w.N = u -> N;

    dudt( u, &s1, dx);
    vector_add_np( u, 1, &s1, 0.5*dt, &w);
    if( isnan(s1.element[4]) )
    {
        printf( "s1 NAN\n" );
        return -1;
    }

    dudt( &w, &s2, dx );
    vector_add_np( u, 1, &s2, 0.5*dt, &w);
    if( isnan(s2.element[4]) )
    {
        printf( "s2 NAN\n" );
        return -1;
    }
    
    dudt( &w, &s3, dx );
    vector_add_np( u, 1, &s3, dt, &w);

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
    
    for( i = 0; i < u -> N; i++)
    {
        VEC(u_n,i) = VEC(u,i) + dt/6*( s1.element[i] + 2 * s2.element[i] + 2* s3.element[i] + s4.element[i] );
    }

    return 0;
}

void vector_add_np( Vector* x, double a, Vector* y, double b, Vector* z)
{
    // Check Vector Lengths
    if( x -> N != y -> N )
    {
        printf( "Error at Vector Add: Vector size mismatch\n" );
        assert( x -> N == y -> N );
    }
    for( int i = 0; i < x -> N; i++ ){
        VEC(z,i) = a * VEC(x,i) + b * VEC(y,i);
    }
}

void pdu_pdt_np( Vector *u, Vector *s, double dx )
{
    int i;
    double dx_3 = pow(dx,3);
    for( i = 0; i < u -> N; i++ )
    { 
        VEC(s,i) = -6 * VEC(u,i) * du_x(u,i,dx) - du_xxx(u,i,dx_3);
    }
}
    
void vector_copy_np( Vector *x, Vector *y )
{
    // Reset the contents of x
    //vector_initialize( x, y -> N,
        //(double[MAX_SIZE]) {0,0}, MAX_SIZE );
    x -> N = y -> N;    
    for( int i = 0; i < y -> N; i++ ){
        VEC(x,i) =  VEC(y,i);
    }
}