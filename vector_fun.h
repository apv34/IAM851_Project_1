/***************************************************************/
/*                       Anthony Edmonds                       */
/*              IAM 851 Project One - KdV Equation             */
/*                         Spring 2014                         */
/*                                                             */
/*            Change Log:                                      */
/*                   4/10/2014 - Initial. Reusing code from    */
/*                                  assignment 3               */
/*                   4/12/2014 - Removed Vector Type from      */
/*                                  Vector struct              */
/*                             - Renamed linear_algebra.h to   */
/*                                  vector_fun.h               */
/*                             - Removed Matrix type           */
/*                             - Modified Vector Add to        */
/*                                  include scalar multipliers */
/*                                  before the addition        */
/*                             - Removed functions unneeded by */
/*                                  KdV problem                */
/*                             - Expanded Max Size to 100000   */
/*                             - Added VEC(v,i) to access      */
/*                                  array elements             */
/*                                  SOURCE: linear_algebra.h   */
/*                                  from IAM851 Spring 2014    */
/*                                  by Kai Germaschewski       */
/*                             - Added vector_copy function    */
/*                   4/12/2014 - Renamed vec_add to vector_add */
/*                                  for consistency            */
/*                             - Added more comments, in       */
/*                                  effort to properly         */
/*                                  Document the project       */
/*                   4/17/2014 - Continued Adding more         */
/*                                  comments, in effort to     */
/*                                  properly  Document the     */
/*                                  project                    */
/*                   4/17/2014 - Added OpenMP Parallelization  */
/*                                                             */
/*                      Vector Operations                      */
/*                         vector_fun.h                        */
/***************************************************************/
#ifndef VECTOR_FUN_H
#define VECTOR_FUN_H

#include <stdio.h>
#include <assert.h>

/*********************** Definitions ***************************/
#define VEC(v,i) (v -> element[i])

#define MAX_SIZE 100000
typedef struct 
{
    double element[MAX_SIZE];
    // Vector Length
    int N;
} Vector;

/*********************** Declarations **************************/
    
/***************************************************************/
/*            vector_add - Takes two vectors and adds the two  */
/*                     vectors and stores it in a third vector */
/*                     z = a*x+b*y                             */
/*                                                             */
/*            Input: x -- a pointer to a Vector struct that    */
/*                     stores N values in an array of doubles, */
/*                     and the length N of the vector          */
/*                   a -- a double that corresponds to the     */
/*                     scalar multiple that x is to be         */
/*                     multiplied by                           */
/*                   y -- a pointer to a Vector struct that    */
/*                     stores N values in an array of doubles, */
/*                     and the length N of the vector          */
/*                   b -- a double that corresponds to the     */
/*                     scalar multiple that y is to be         */
/*                     multiplied by                           */
/*                   z -- a pointer to a Vector struct that    */
/*                     stores N values in an array of doubles, */
/*                     and the length N of the vector that     */
/*                     will store the result of a*x+b*y        */
/*                                                             */
/*            Output: NONE                                     */
/*                                                             */
/*            Side Effects: If there is a dimension mismatch   */
/*                     there will be an assertion failure.     */
/*                     The result of the operation is stored   */
/*                     in z.                                   */
/*                                                             */
/*                    Defined in vector_fun.c                  */
/***************************************************************/
void vector_add( Vector* x, double a, Vector* y, double b, 
    Vector* z);

/***************************************************************/
/*            vector_write - Writes a vector to the file       */
/*                     specified                               */
/*                                                             */
/*            Input: x -- a pointer to a Vector struct that    */
/*                     stores N values in an array of doubles, */
/*                     and the length N of the vector          */
/*                   file_name -- a string that contains the   */
/*                     name of the file to be written to       */
/*                                                             */
/*                                                             */
/*            Output: NONE                                     */
/*                                                             */
/*            Side Effects: Writes the vector in its proper    */
/*                     form to the specified File              */
/*                                                             */
/*                    Defined in vector_fun.c                  */
/***************************************************************/
void vector_write(Vector *x, char* file_name);

/***************************************************************/
/*            vector_copy - Copies vector y into vector x      */
/*                                                             */
/*            Input: x -- a pointer to a Vector struct that    */
/*                     stores N values in an array of doubles, */
/*                     and the length N of the vector, that    */
/*                     will be overwritten                     */
/*                   y -- a pointer to a Vector struct that    */
/*                     stores N values in an array of doubles, */
/*                     and the length N of the vector          */
/*                                                             */
/*            Output: NONE                                     */
/*                                                             */
/*            Side Effects: The size of x is replaced with the */
/*                     size of y and then overwritten with the */
/*                     values in y                             */
/*                                                             */
/*                    Defined in vector_fun.c                  */
/***************************************************************/
void vector_copy( Vector *x, Vector *y );

/***************************************************************/
/*            vector_initialize - Initializes a vector to the  */
/*                     specified type, size and values         */
/*                                                             */
/*            Input: new -- a pointer to a Vector struct that  */
/*                     will be initialized                     */
/*                   length -- specifies the length of the     */
/*                     vector                                  */
/*                   values -- an array of doubles that        */
/*                     contains the values the vector is to be */
/*                     initialized to. { 0.0 } will initialize */
/*                     the Vector to all zeros                 */
/*                   sizeVals -- an integer that contains the  */
/*                     logical size of the initializing values */
/*                                                             */
/*                                                             */
/*            Output: NONE                                     */
/*                                                             */
/*            Side Effects: Sets the vector new to the         */
/*                     specified type and length, using the    */
/*                     values in values[]                      */
/*                                                             */
/*                    Defined in vector_fun.c                  */
/***************************************************************/
void vector_initialize( Vector *new, int length, 
        double values[], int sizeVals );
#endif