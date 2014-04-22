/***************************************************************/
/*                       Anthony Edmonds                       */
/*                  IAM 851 Project 1 4/22/2014                */
/*                                                             */
/*                   Row to Column Conversion                  */
/*                                                             */
/*                                                             */
/*                Purpose:                                     */
/*                    To convert the data in the file          */
/*                       specified first in the command line   */
/*                       arguments from row major data to      */
/*                       column major data using the number of */
/*                       rows, the second command line         */
/*                       argument, and the number of columns   */
/*                       the third command line argument, and  */
/*                       output the converted data to          */
/*                       rotated.txt                           */
/*                    The file can be used standalone but is   */
/*                       intended to be used in conjunction    */
/*                       with plot.bash                        */
/*                                                             */
/*                WARNING: The code will not execute if the    */
/*                       file specified does not exist, or the */
/*                       number of command line arguments was  */
/*                       incorrect.                            */
/*                WARNING: If the number of Row and/or columns */
/*                       specified is incorrect, then the data */
/*                       NOT be properly converted             */
/*                                                             */
/*                Input:                                       */
/*                    - Three Command Line Arguments:          */
/*                       - FIRST: the name of the file to be   */
/*                           converted to column major order   */
/*                       - SECOND: the number of rows the      */
/*                           specified file has                */
/*                       - THIRD: the number of columns the    */
/*                           specified file has                */
/*                                                             */
/*                Output:                                      */
/*                    - If the code detects an error it will   */
/*                       be displayed to the screen and the    */
/*                       execution terminated                  */
/*                    - The converted data will be printed to  */
/*                       rotated.txt, which will be            */
/*                       overwritten with the new data         */
/***************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
int main(int argc, char *argv[] )
{
    int rows = 10;
    int cols = 10;
    double data[MAX_N][MAX_N] = { { 1.0, 2.0, 0.0, 0.0 } };
    FILE *rotate;
    int i = 0;
    int j = 0;
    

    if( argc == 4 )
    {
        rows = atoi(argv[2] );
        cols = atoi( argv[3] );
        printf( "Opening %s\nWhich should have %d rows and "
            "%d Columns\n", argv[1], rows, cols);
        rotate = fopen( argv[1], "r" );
        if( rotate == NULL ) 
        {
            printf( "%s is an invalid file name!\n", argv[1] );
        }
        else
        {
            for( i = 0; i < rows; i++ )
            {
                for( j = 0; j < cols; j++ )
                {
                    fscanf( rotate, "%lf", &data[i][j] );
                }
            }
            fclose(rotate);
            rotate = fopen( "rotated.txt", "w" );
            for( j = 0; j < cols; j++ )
            {
                for( i = 0; i < rows; i++ )
                    fprintf( rotate,"%f ", data[i][j] );
                fprintf( rotate, "\n" );
            }
            fclose(rotate);
        }
    }
    else
    {
        printf( "Incorrect number of arguments!\n" );
    }
    
    return 0;
};