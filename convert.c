
#include <stdio.h>
#include <stdlib.h>

#define MAX 100000
int main( int argc, char *argv[]  )
{
    int rows = 0;
    int cols = 0;
    double data[MAX][MAX] = { { 0.0 } };
    FILE *rotate;
    int i = 0;
    int j = 0;
    
    
    if( argc != 4 ) 
    {
        printf( "Incorrect number of passed arguments!\n" );
        return 0;
    }
    else
    {

        rows = atoi(argv[2] );
        cols = atoi(argv[3] );
        if( rows > MAX || cols > MAX )
        {
            printf( "Number of Rows/Columns Exceeds Maximum"
                " Allowable!\n" );
            return 0;
        }
        rotate = fopen( argv[1], "r" );
        if( rotate == NULL)
        {
            printf( "File could not be opened!" );
            return 0;
        }
        else
        {
            printf( "R%d\nC%d\n", rows, cols );
            for( i = 0; i < rows; i++ ){
                for( j = 0; j < cols; j++ ){
                    fscanf(rotate, "%lf", &data[i][j] );
                }
            }
            fclose(rotate);
            rotate = fopen( argv[1], "w" );
            for( j = 0; j < cols; j++ ){
                for( i = 0; i < rows; i++ ){
                    fprintf( rotate, "%f ", data[i][j] );
                }
                fprintf( rotate, "\n" );
            }
            
        }
        fclose(rotate);
    }

    
    return 0;
}