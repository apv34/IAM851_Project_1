/***************************************************************/
/*                       Anthony Edmonds                       */
/*              IAM 851 Project One - KdV Equation             */
/*                         Spring 2014                         */
/*                                                             */
/*                     Vector Operations                       */
/*                       vector_fun.c                          */
/***************************************************************/
#include "vector_fun.h"

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
/*                   Declared in vector_fun.h                  */
/***************************************************************/

void vector_add( Vector* x, double a, Vector* y, double b, Vector* z)
{
    // Check Vector Lengths
    if( x -> N != y -> N )
    {
        printf( "Error at Vector Add: Vector size mismatch\n" );
        assert( x -> N == y -> N );
    }
    
    // Reset the contents of z
    //vector_initialize( z, x -> N,
        //(double[MAX_SIZE]) {0,0}, MAX_SIZE );
    
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
/*                   Declared in vector_fun.h                  */
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
/*                   Declared in vector_fun.h                  */
/***************************************************************/

void vector_copy( Vector *x, Vector *y )
{
    // Reset the contents of x
    //vector_initialize( x, y -> N,
        //(double[MAX_SIZE]) {0,0}, MAX_SIZE );
    x -> N = y -> N;    
    for( int i = 0; i < y -> N; i++ ){
        VEC(x,i) =  VEC(y,i);
    }
}
        
        
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
