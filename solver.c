/***************************************************************/
/*                       Anthony Edmonds                       */
/*              IAM 851 Project One - KdV Equation             */
/*                         Spring 2014                         */
/*                                                             */
/*                 Runge-Kutta 4th Order Solver                */
/*                          solver.c                           */
/***************************************************************/
#include "solver.h"

/***************************************************************/
/*            runge_kutta - Preforms an RK4 numeric            */
/*                     integration on vector u using time step */
/*                     dt, spacing dx, and the function handle */
/*                     dudt the time rate of change of u and   */
/*                     stoires the result in Vector u_n        */
/*                                                             */
/*            Input: dt -- a double that is the time step of   */
/*                     the RK4 solver                          */
/*                   u -- a pointer to a Vector struct that    */
/*                     stores the values of the function at    */
/*                     the current time                        */
/*                   dx -- a double that is the spacing of the */
/*                     points in u to be used in the dudt      */
/*                     function                                */
/*                   u_n -- a pointer to a Vector struct that  */
/*                     will store the result of the RK4        */
/*                     integration for the next time step      */
/*                   dudt -- a function pointer that takes in  */
/*                     two pointers to Vector structs the      */
/*                     value of the array at the current time, */
/*                     where the next step is to be stored and */
/*                     a double that holds the spacing of the  */
/*                     points                                  */
/*                                                             */
/*            Output: 0 if the RK4 succeeds                    */
/*                    -1 if the RK4 fails                      */
/*                                                             */
/*            Side Effects: Changes the value in u_n to the    */
/*                     result of the RK4 integration on u with */
/*                     the given time step.                    */
/*                     WARNING: RK4 will fail if the time      */
/*                         step is too large, and if the       */
/*                         RK4 code detects any NaN values in  */
/*                         the final summation it will return  */
/*                         -1. This means the RK4 FAILED and   */
/*                         the time step needs to be reduced,  */
/*                         the input function needs to be      */
/*                         checked, or the points are poorly   */
/*                         behaved                             */
/*                                                             */
/*                     Declared in solver.h                    */
/***************************************************************/
int runge_kutta( double dt, Vector *u, double dx, Vector *u_n, 
    void dudt (Vector *, Vector *, double))
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

    // k1
    dudt( u, &s1, dx);
    vector_add( u, 1, &s1, 0.5*dt, &w);

    // k2
    dudt( &w, &s2, dx );
    vector_add( u, 1, &s2, 0.5*dt, &w);
    
    // k3
    dudt( &w, &s3, dx );
    vector_add( u, 1, &s3, dt, &w);

    // k4
    dudt( &w, &s4, dx);
    if( isnan(s4.element[0]) )
        return -1;
    
    // Final Summation
    #pragma omp parallel for
    for( i = 0; i < u -> N; i++)
    {
        VEC(u_n,i) = VEC(u,i) + dt/6*( s1.element[i] + 2
            * s2.element[i] + 2* s3.element[i] + s4.element[i] );
    }
    u_n -> N = u -> N;
    return 0;
}