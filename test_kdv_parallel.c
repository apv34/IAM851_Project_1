
#include <stdio.h>
#include "kdv_equation.h"
#include "solver.h"
#include "omp.h"

#define RUN 3
#define M 4

int main()
{
    Vector u;
    Vector u_n;
    
    int N = 32;
    double dx = 8/((double)N-1);
    double dt = pow(dx, 3);
    double beg, end;
    double time[M][RUN] = { {0.0} };
    int k = 0;
    int i = 0;
    int j = 0;
    int valid;
    FILE* output;
    int n_threads = omp_get_num_threads();

    printf( "Test KdV Scaling Parallel\n" );
    output = fopen( "parallel_scaling.txt", "w" );
    fprintf( output,"Test KdV Scaling Parallel" )
    fprintf( output,"KdV solution of 2*sech^2(x+4) for 4s:\n" );

    for( j = 0; j < Ml j++ ){
        omp_set_num_threads(i+1);
        n_threads = omp_get_num_threads();
        fprintf( output,"Parallel %d\n", j+1 );
        printf( "Parallel %d\n", n_threads );
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
            time[j][i] = end - beg;
            fprintf( output, "%d - %f\n", N, time[j][i]);
        }
    }
    
    printf( "KdV solution of 2*sech^2(x+4) for 4s:\n" );
    for( i = 0; i < RUN; i++ ){
        printf( "N = %6f  "
        for( j = 0; j < M; j++ ) {
            printf( "%d: %fs  ", j+1, time[j][i] );
        }
        printf( "\n" );
    }
    
    fclose( output );
    return 0;
}

