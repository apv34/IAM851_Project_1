/***************************************************************/
/*                       Anthony Edmonds                       */
/*                  IAM 851 Project 1 4/22/2014                */
/*                                                             */
/*                      KdV Scaling Test                       */
/*                                                             */
/*                                                             */
/*                Purpose:                                     */
/*                    To test the scaling of the RK4 method    */
/*                       for the following values of N: 64,    */
/*                       128, 256, 512, 1024 and 2048          */
/*                       This test will run on the number of   */
/*                       specified threads                     */
/*                                                             */
/*                Input:                                       */
/*                    - None.                                  */
/*                                                             */
/*                Output:                                      */
/*                    - The Progress of the solver and the     */
/*                       resultant time of the simulation      */
/***************************************************************/
#include <stdio.h>
#include "kdv_equation.h"
#include "solver.h"

#define RUN 6

int main()
{
    Vector u;
    Vector u_n;
    
    int N = 32;
    double dx = 8/((double)N-1);
    double dt = pow(dx, 3);
    double beg, end;
    double time[RUN] = { 0.0 };
    int k = 0;
    int i = 0;
    int valid;

    printf( "Test KdV Scaling\n" );
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
        time[i] = end - beg;
    }
    printf( "KdV solution of 2*sech^2(x+4) for 1s:\n" );
    for( i = 0; i < RUN; i++ ){
        printf( "N = %6f  Took: %fs\n", 128*pow(2, i ), time[i]);
    }
    
    return 0;
}
