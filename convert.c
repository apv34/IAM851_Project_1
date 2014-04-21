
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
        printf( "Opening %s\nWhich should have %d rows and %d Columns\n", argv[1], rows, cols);
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
            rotate = fopen( "test_r.txt", "w" );
            printf( "B\n" );
            for( j = 0; j < cols; j++ )
            {
                for( i = 0; i < rows; i++ )
                    fprintf( rotate,"%f ", data[i][j] );
                fprintf( rotate, "\n" );
            }
            fclose(rotate);
            
            printf( "C\n" );
        }
    }
    else
    {
        printf( "Incorrect number of arguments!\n" );
    }
    
    return 0;
};