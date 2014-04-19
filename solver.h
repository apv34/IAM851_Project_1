/***************************************************************/
/*                       Anthony Edmonds                       */
/*              IAM 851 Project One - KdV Equation             */
/*                         Spring 2014                         */
/*                                                             */
/*            Change Log:                                      */
/*                   4/10/2014 - Initial.                      */
/*                   4/12/2014 - Added function handle call to */
/*                                  RK4 method                 */
/*                   4/17/2014 - Added WTime() to profile code */
/*                   4/18/2014 - Added OpenMP Parallelization  */
/*                             - Added comments                */
/*                             - Added PROFILING Command       */
/*                                  definition                 */
/*                             - Replaced spot NaN checks with */
/*                                  a check at every point in  */
/*                                  s4                         */
/*                                                             */
/*                 Runge-Kutta 4th Order Solver                */
/*                          solver.h                           */
/***************************************************************/

#ifndef SOLVER_H
#define SOLVER_H

#include <math.h>
#include "vector_fun.h"


/**************************************************************/
    
#ifdef PROFILE
#define START pb = WTime();
#define END pe = WTime();
#define PTIME pe - pb
#else
#define START
#define END
#define PTIME -1.0
#endif

/**************************************************************/
    
/***************************************************************/
/*            runge_kutta - Preforms an RK4 numeric            */
/*                     integration on vector u using time step */
/*                     dt, spacing dx, and the function handle */
/*                      dudt the time rate of change of u and  */
/*                      stoires the result in Vector u_n       */
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
/*                   Declared in vector_fun.h                  */
/***************************************************************/

int runge_kutta( double dt, Vector *u, double dx, Vector *u_n,
    void dudt (Vector *, Vector *, double));


/* Code Below is from IAM 851 Spring 2014 by Kai Germaschewski */
/* Returns the Time in seconds that the function was called    */
/*-------------------------------------------------------------*/
#include <sys/time.h>
#include <stdlib.h>
static inline double
WTime(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec / 1e6;
}
#endif