/***************************************************************/
/*                       Anthony Edmonds                       */
/*                  IAM 851 Project 1 4/22/2014                */
/*                                                             */
/*               KdV Test With Compound Wave Three             */
/*                                                             */
/*                                                             */
/*                Purpose:                                     */
/*                    To test the RK4 method used to solve the */
/*                       KdV equation for a compound input     */
/*                       wave of 2 sech^2(x-2) +               */
/*                       4.8125 sech^2(x-6) and output the     */
/*                       resulting solution to text file to be */
/*                       plotted using gnuplot or MATLAB       */
/*                                                             */
/*                Input:                                       */
/*                    - None.                                  */
/*                                                             */
/*                Output:                                      */
/*                    - The result of the the RK4 for 10000    */
/*                       steps every 10 iterations of RK4 to   */
/*                       the file comp_wave_three.txt          */
/*                    - The Progress of the solver and the     */
/*                       resultant time of the simulation      */
/***************************************************************/
#include <stdio.h>
#include "kdv_equation.h"
#include "solver.h"


/***************************************************************/
/*            initial - Initializes u0 to a compound sech^2    */
/*                     wave of 2 sech^2(x-2) +                 */
/*                     4.8125 sech^2(x-5)                      */
/*                                                             */
/*            Input: u0 -- a pointer to a Vector struct that   */
/*                     will stores the values of the initial   */
/*                     sech^2 wave                             */
/*                   dx -- a double that contains the spacing  */
/*                     of the nodes                            */
/*                                                             */
/*            Output: NONE                                     */
/*                                                             */
/*            Side Effects: Sets u0 to the initial wave        */
/***************************************************************/
void initial( Vector *u0, double dx )
{
    int i;
    for( i = 0; i < u0 -> N; i++ )
        VEC(u0,i) = 2/ pow(cosh(dx*i-2), 2)- 4.8125/ 
            pow(cosh(dx*i-6), 2);
}

/***************************************************************/
    
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

    printf( "Test KdV Two Waves Three\n" );
    beg = WTime();
    vector_initialize( &u, N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
    vector_initialize( &u_n, N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
    initial( &u, dx);
    output = fopen( "comp_wave_three.txt", "w" );
    fclose( output );
    end = WTime();
    printf( "Set-up took: %fs\n", end-beg);
    beg = WTime();
    while( i < steps )
    {
        if( k % write == 0 )
        {
            vector_write( &u, "comp_wave_three.txt" );
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
