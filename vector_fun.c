/***************************************************************/
/*                       Anthony Edmonds                       */
/*                IAM 851 As */
/***************************************************************/
#include "vector_fun.h"

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
/*                 Declared in vector.h                */
/***************************************************************/
void vec_add( Vector* x, double a, Vector* y, double b, Vector* z)
{
    // Check Vector Lengths
    if( x -> N != y -> N )
    {
        printf( "Error at Vector Add: Vector size mismatch\n" );
        assert( x -> N == y -> N );
    }
    
    // Reset the contents of z
    vector_initialize( z, x -> N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
    
    for( int i = 0; i < x -> N; i++ ){
        VEC(z,i) = a * VEC(x,i) + b * VEC(y,i);
    }
}




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
/*                 Declared in vector.h                */
/***************************************************************/

void vector_write(Vector *x, char* file_name)
{
    FILE* output;
    
    output = fopen( file_name, "a" );
    
    for (int i = 0; i < x -> N; i++) {
        fprintf( output, "%5f ", VEC(x,i) );
    }
    fprintf( output,"\n" );
    fclose( output );
}


void vector_copy( Vector *x, Vector *y )
{
    if( x -> N != y -> N )
    {
        printf( "Error at Vector Copy: Vector size mismatch\n" );
        assert( x -> N == y -> N );
    }
    // Reset the contents of z
    vector_initialize( x, x -> N,
        (double[MAX_SIZE]) {0,0}, MAX_SIZE );
        
    for( int i = 0; i < x -> N; i++ ){
        VEC(x,i) =  VEC(y,i);
    }
}
        
        
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
    double values[], int sizeVals )
{
    int i = 0;
    if ( length > MAX_SIZE ) {
        printf( "Length is larger than MAX_SIZE!\n" );
        assert( length >= MAX_SIZE );
    }
    for( i = 0; i < MAX_SIZE; i++ )
    {
        if( i < length )
        {
            if( i < sizeVals )
            {
                VEC(new,i) = values[i];
            }
            else
            {
                VEC(new,i) = 0;
            }
        }
        else
        {
            VEC(new,i) = 0;
        }
    }
    new -> N = length;
}