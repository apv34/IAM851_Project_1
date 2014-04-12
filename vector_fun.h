
#ifndef VECTOR_FUN_H
#define VECTOR_FUN_H

#include <stdio.h>
#include <assert.h>

#define VEC(v,i) (v -> element[i])

#define MAX_SIZE 100000
typedef struct 
{
    double element[MAX_SIZE];
    // Vector Length
    int N;
} Vector;

/***************************************************************/
/*            vec_add - Takes two vectors and adds the two     */
/*                     vectors and stores it in a third vector */
/*                                                             */
/*            Input: x -- a pointer to a Vector struct that    */
/*                     stores N values in an array of doubles, */
/*                     the value N, and the vector type of the */
/*                     first vector                            */
/*                   y -- a pointer to a Vector struct that    */
/*                     stores N values in an array of doubles, */
/*                     the value N, and the vector type of the */
/*                     second vector                           */
/*                   z -- a pointer to a Vector struct that    */
/*                     stores N values in an array of doubles, */
/*                     the value N, and the vector type of the */
/*                     vector that will store the result of    */
/*                     x+y                                     */
/*                                                             */
/*            Output: NONE                                     */
/*                                                             */
/*            Side Effects: If there is a dimension mismatch   */
/*                     there will be an assertion failure.     */
/*                     The contents of z are reset to zero,    */
/*                     and then the result of the operation    */
/*                     is stored in z.                         */
/*                                                             */
/*                  Defined in vector.c                       */
/***************************************************************/
void vec_add( Vector* x, double a, Vector* y, double b, Vector* z);

/***************************************************************/
/*            vector_write - Writes a vector to the file       */
/*                     specified                               */
/*                                                             */
/*            Input: x -- a pointer to a Vector struct that    */
/*                     stores N values in an array of doubles, */
/*                     the value N,and the vector type of the  */
/*                     vector to be printed                    */
/*                   file_name -- a string that contains the   */
/*                     name of the file to be written to       */
/*                                                             */
/*                                                             */
/*            Output: NONE                                     */
/*                                                             */
/*            Side Effects: Writes the vector in its proper    */
/*                     form to the specified File              */
/*                                                             */
/*               Defined in vector.c                     */
/***************************************************************/
void vector_write(Vector *x, char* file_name);

void vector_copy( Vector *x, Vector *y );

/***************************************************************/
/*            vector_initialize - Initializes a vector to the  */
/*                     specified type, size and values         */
/*                                                             */
/*            Input: new -- a pointer to a Vector struct that  */
/*                     will be initialized                     */
/*                   type -- specifies the type of the vector  */
/*                     This is to be used with the Vector_Type */
/*                     enum and the values COLUMN and ROW      */
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
/*              Defined in linear_algebra.c                    */
/***************************************************************/
void vector_initialize( Vector *new, int length, 
        double values[], int sizeVals );
#endif