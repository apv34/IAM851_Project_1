/***************************************************************/
/*                       Anthony Edmonds                       */
/*              IAM 851 Project One - KdV Equation             */
/*                         Spring 2014                         */
/*                                                             */
/*            Change Log:                                      */
/*                   4/10/2014 - Initial.                      */
/*                   4/12/2014 - Rewrote to use Vector struct  */
/*                             - Adapted to using VEC(v,i)     */
/*                   4/15/2014 - Modified simple_sec to work   */
/*                                  with a location as well as */
/*                                  a height value             */
/*                   4/17/2014 - Added more comments, in       */
/*                                  effort to properly         */
/*                                  Document the project       */
/*                   4/17/2014 - Added OpenMP Parallelization  */
/*                                                             */
/*                       KdV Definitions                       */
/*                       kdv_equation.h                        */
/***************************************************************/
#ifndef KDV_EQUATION_H
#define KDV_EQUATION_H

#include <math.h>
#include "vector_fun.h"

/*********************** Declarations **************************/

/***************************************************************/
/*            pdu_pdt - Uses the passed pointer to u to use    */
/*                     a finite difference approximation of    */
/*                     right-hand side of the KdV equation     */
/*                     to get the time rate of change of u     */
/*                     and stores it in Vector s               */
/*                                                             */
/*            Input: u -- a pointer to a Vector struct that    */
/*                     stores the values to be descritized     */
/*                     over                                    */
/*                   s -- a pointer to a Vector struct that    */
/*                     will store the result of the finite     */
/*                     differences                             */
/*                   dx -- a double that is the spacing to be  */
/*                     used in the finite differences          */
/*                                                             */
/*            Output: NONE                                     */
/*                                                             */
/*            Side Effects: Sets the vector s to the time      */
/*                     rate of change of the descritized KdV   */
/*                     equation                                */
/*                                                             */
/*                  Defined in kdv_equation.c                  */
/***************************************************************/

void pdu_pdt( Vector *u, Vector *s, double dx );

/***************************************************************/
/*            du_x - Uses the passed pointer to u to           */
/*                     perform a centered first order finite   */
/*                     difference approximation of the form    */
/*                     ( u_(i+1) - u_(i-1) ) / ( 2 * dx )      */
/*                     and returns that value                  */
/*                                                             */
/*            Input: u -- a pointer to a Vector struct that    */
/*                     stores the values the finite difference */
/*                     will be performed over                  */
/*                   i -- the integer that corresponds to the  */
/*                     node the finite diff. approx. is        */
/*                     centered around                         */
/*                   dx -- a double that is the spacing to be  */
/*                     used in the finite difference           */
/*                                                             */
/*            Output: The result of the first order finite     */
/*                     difference                              */
/*                                                             */
/*            Side Effects: NONE                               */
/*                                                             */
/*                  Defined in kdv_equation.c                  */
/***************************************************************/
double du_x( Vector *u, int i, double dx );

/***************************************************************/
/*            du_xxx - Uses the passed pointer to u to         */
/*                     perform a centered third order finite   */
/*                     difference approximation of the form    */
/*                     ( du_xx(i+1) - du_xx(i-1) ) /( 2 * dx ) */
/*                     where du_xx(i) is                       */
/*                     ( u_(i+1) -2*u_i + u(i-1) ) /( dx^2 )   */
/*                     and returns that value                  */
/*                                                             */
/*            Input: u -- a pointer to a Vector struct that    */
/*                     stores the values the finite difference */
/*                     will be performed over                  */
/*                   i -- the integer that corresponds to the  */
/*                     node the finite diff. approx. is        */
/*                     centered around                         */
/*                   dx_3 -- a double that is the spacing to   */
/*                     be used in the finite difference cubed  */
/*                                                             */
/*            Output: The result of the third order finite     */
/*                     difference                              */
/*                                                             */
/*            Side Effects: NONE                               */
/*                                                             */
/*                  Defined in kdv_equation.c                  */
/***************************************************************/
double du_xxx( Vector *u, int i, double dx_3 );


/***************************************************************/
/*            simple_sec - Initializes u0 to a sech^2 wave     */
/*                     using M(M+1) as a constant multiple     */
/*                     and loc the as the location of the      */
/*                     center                                  */
/*                     M(M+1) sech(x-loc)^2                    */
/*                                                             */
/*            Input: u0 -- a pointer to a Vector struct that   */
/*                     will stores the values of the initial   */
/*                     sech^2 wave                             */
/*                   dx -- a double that contains the spacing  */
/*                     of the nodes                            */
/*                   M -- a double that defines the magnitude  */
/*                     of the wave                             */
/*                   loc -- a double that defines the where    */
/*                     the center of the wave is. Positive     */
/*                     values shift the wave to the right      */
/*                                                             */
/*            Output: NONE                                     */
/*                                                             */
/*            Side Effects: Sets u0 to the initial wave        */
/*                                                             */
/*                  Defined in kdv_equation.c                  */
/***************************************************************/
void simple_sec( Vector *u0, double dx, double M, double loc);

void print_timing( double numSteps, double dt, int writeEvery,  
    double left, double right, double dx, char* file_name );


#endif