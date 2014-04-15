
#include <stdio.h>
#include "kdv_equation.h"
#include "solver.h"

void initial( Vector *u0, double dx )
{
    int i;
    for( i = 0; i < u0 -> N; i++ )
        VEC(u0,i) = 2/ pow(cosh(dx*i-2), 2)+ 6/ pow(cosh(dx*i-6), 2);
}

int main()
{
    Vector u;
    Vector u_n;
    
    int steps = 10000;
    int N = 128;
    double dx = 8/((double)N-1);
    double dt = pow(dx, 3);
    double beg, end;
    int i = 0;
    int k = 0;
    int write = 10;
    int valid;
    FILE* output;

    printf( "Test KdV Two Waves Two\n" );
    beg = WTime();
    vector_initialize( &u, N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
    vector_initialize( &u_n, N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
    initial( &u, dx);
    output = fopen( "comp_wave_two.txt", "w" );
    fclose( output );
    end = WTime();
    printf( "Set-up took: %fs\n", end-beg);
    beg = WTime();
    while( i < steps )
    {
        if( k % write == 0 )
        {
            vector_write( &u, "comp_wave_two.txt" );
            i++;
            if( i / (double) steps == .25 )
                printf( "25%% Completed\n" );
            else if(  i / (double) steps == .50 )
                printf( "50%% Completed\n" );
            else if(  i / (double) steps == .75 )
                printf( "75%% Completed\n" );
        }
        k++;
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
    
    printf( "RK4 with %d Points written every %d steps", N, write);
    printf( " for %d Steps took: %fs\n", steps, end-beg);
    printf( "For a simulation of %fs\n", k*dt);
    
    return 0;
}
