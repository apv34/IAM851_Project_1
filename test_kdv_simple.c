/***************************************************************/
/*                       Anthony Edmonds                       */
/*                  IAM 851 Project 1 4/22/2014                */
/*                                                             */
/*                   KdV Test With Simple Wave                 */
/*                                                             */
/*                                                             */
/*                Purpose:                                     */
/*                    To test the RK4 method used to solve the */
/*                       KdV equation for a simple input wave  */
/*                       of 2 sech^2(x-4) and output the       */
/*                       resulting solution to a text file     */
/*                       to be plotted using gnuplot or MATLAB */
/*                                                             */
/*                Input:                                       */
/*                    - None.                                  */
/*                                                             */
/*                Output:                                      */
/*                    - The result of the the RK4 for 10000    */
/*                       steps every 10 iterations of RK4 to   */
/*                       the file simple.txt                   */
/*                    - The Progress of the solver and the     */
/*                       resultant time of the simulation      */
/***************************************************************/
#include <stdio.h>
#include "kdv_equation.h"
#include "solver.h"

/*********************** Definitions ***************************/
    
#define STEPS 900

/***************************************************************/

int main()
{
    Vector u;
    Vector u_n;
    
    int steps = STEPS;
    int N = 100;
    double dx = 8/((double)N-1);
    double dt = pow(dx, 3);
    double beg, end;
    #ifdef PROFILE
    double pb, pe;
    #endif
    int i = 0;
    int k = 0;
    int write = 10;
    int valid;
    FILE* output;

    printf( "Test KdV Simple\n" );
    beg = WTime();
    vector_initialize( &u, N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
    vector_initialize( &u_n, N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
    simple_sec( &u, dx, 1, 4 );
    output = fopen( "simple.txt", "w" );
    fclose( output );
    end = WTime();
    printf( "Set-up took: %fs\n", end-beg);
    
    beg = WTime();
    while( i < steps )
    {
        if( k % write == 0 )
        {
            START
            vector_write( &u, "simple.txt" );
            i++;
            if( i / (double) steps == .25 )
                printf( "25%% Completed\n" );
            else if(  i / (double) steps == .50 )
                printf( "50%% Completed\n" );
            else if(  i / (double) steps == .75 )
                printf( "75%% Completed\n" );
			END
            #ifdef PROFILE
			printf( "Write Took: %fs\n", PTIME );
            #endif
        }
        k++;
		START
        valid = runge_kutta( dt, &u, dx, &u_n, pdu_pdt);
		END
        #ifdef PROFILE    
		printf ( "RK4 took  %fs\n", PTIME);
        #endif
		START
        vector_copy( &u, &u_n);
		END
        #ifdef PROFILE
		printf ("Copy took: %fs\n", PTIME );
        #endif
        if( valid == -1 )
        {
            printf("ERROR!\n");
            printf( "%f\n", k*dt);
            assert( valid != -1 );
            break;
        }
    }
    end = WTime();
    printf("RK4 with %d Points written every %d steps", N,write);
    printf( " for %d Steps took: %fs\n", steps, end-beg);
    printf( "For a simulation of %fs\n", k*dt);
    print_timing( steps, dt, write, 0, 8, dx, "simple", "txt" );
    return 0;
}
