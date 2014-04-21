/***************************************************************/
/*                       Anthony Edmonds                       */
/*              IAM 851 Project One - KdV Equation             */
/*                         Spring 2014                         */
/*                                                             */
/*                       KdV Definitions                       */
/*                       kdv_equation.c                        */
/***************************************************************/
#include "kdv_equation.h"

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
/*                   dx -- a doubles that is the spacing to be */
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
void pdu_pdt( Vector *u, Vector *s, double dx )
{
    int i;
    double dx_3 = pow(dx,3);
    #pragma omp parallel for
    for( i = 0; i < u -> N; i++ )
    { 
        VEC(s,i) = -6 *VEC(u,i) * du_x(u,i,dx) -du_xxx(u,i,dx_3);
    }
}


/***************************************************************/
/*            du_x - Uses the passed pointer to u to           */
/*                     perform a centered first order finite   */
/*                     difference approximation of the form    */
/*                     (u_(i+1) - u_(i-1) ) / ( 2 * dx )       */
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

double du_x( Vector *u, int i, double dx )
{
    if( i == 0 )
        return (VEC(u,i+1) - VEC(u,(u -> N)-1))/(2*dx);
    else if( i == (u -> N)-1)
        return (VEC(u,0) - VEC(u,i-1))/(2*dx);
    else
        return (VEC(u,i+1) - VEC(u,i-1))/(2*dx);
}


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

double du_xxx( Vector *u, int i, double dx_3 )
{
    if( i == 0 )
        return (( VEC(u,i+2)-2*VEC(u,i+1) + VEC(u,i) ) - 
            (VEC(u,i) -2*VEC(u,(u -> N) -1)+VEC(u,(u -> N)-2) ) )
            / (2*dx_3);
    else if( i == 1 )
        return (( VEC(u,i+2)-2*VEC(u,i+1) + VEC(u,i) ) - 
            (VEC(u,i) -2*VEC(u,i-1)+VEC(u,(u->N)-1) ) )/(2*dx_3);
    else if( i == (u -> N)-1)
        return (( VEC(u,1)-2*VEC(u,0) + VEC(u,i) ) - 
            (VEC(u,i) -2*VEC(u,i-1)+VEC(u,i-2) ) )/ (2*dx_3);
    else if( i == (u -> N)-2)
        return (( VEC(u,0)-2*VEC(u,i+1) + VEC(u,i) ) - 
            (VEC(u,i) -2*VEC(u,i-1)+VEC(u,i-2) ) )/ (2*dx_3);
    else
        return (( VEC(u,i+2)-2*VEC(u,i+1) + VEC(u,i) ) - 
            (VEC(u,i) -2*VEC(u,i-1)+VEC(u,i-2) ) )/ (2*dx_3);
}


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

void simple_sec( Vector *u0, double dx, double M,  double loc )
{
    int i;
    for( i = 0; i < u0 -> N; i++ )
    {
        VEC(u0, i) = (M*(M+1) )/ pow(cosh(dx*i-loc), 2);
    }
}


void print_timing( double numSteps, double dt, int writeEvery,  
    double left, double right, double dx, char* file_name, 
    char* extension )
{
    int i = 0;
    int k = 0;
    FILE* output;
    char name[MAX_WORD];
    
    sprintf( name, "%s_t.%s", file_name, extension );
    output = fopen( name, "w" );
    // Time
    
    while( i < numSteps)
    {
        if( k % writeEvery == 0 ) {
            fprintf( output, "%f\n", k*dt );
            i++;
        }
        k++;
    }
    fclose( output );
    sprintf( name, "%s_x.%s", file_name, extension );
    output = fopen( name, "w" );
    // x
    for( i = 0; (left+i*dx) < right; i++ )
    {
        fprintf( output, "%f\n", left+i*dx );
    }
    fclose(output);
}