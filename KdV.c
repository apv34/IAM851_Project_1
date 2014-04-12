#include <stdio.h>
#include <math.h>
#include <assert.h>

#define N 1000
#define STEPS 10000

void pdu_pdt( double u[N], double s[N], double dx );
int runge_kutta( double dt, double u[N], double dx, double u_n[N]);
void initial( double u0[N],double dx );
void copy( double a[N], double b[N] );

double du_x( double u[N], int i, double dx );
double du_xxx( double u[N], int i, double dx_3 );

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main()
{
    //double test[STEPS][N] = { { 0.0} };
    double holda[N] = { 0.0 };
    double holdb[N] = {0.0 };
    int size = N;
    double dx = 8/((double)N-1);
    double dt = pow(dx, 3);//1e-4;
    int i = 0;
    int j;
    int k = 0;
    int valid = 0;
    
    FILE *file;
    file = fopen( "output.txt", "w" );
    printf("Initialize\n");
    //initial( test[0], dx );
    initial(holda, dx);
    printf("Time Step\n");
    //for(i = 0; i < N; i++)
    //    printf("%f ", holda[i]);
    //printf("\n");
    while(i < STEPS)
    {
        //printf("Time: %f\n", k*dt);
        
        
        //printf("\n");
        //if( i < STEPS-1 )
        
        
        if( k % 10 == 0 )
        {
			if( i % 10 == 0 )
				printf("Record at %f\n", k*dt);
            for(j = 0; j < N; j++ )
            {
                //printf("%f", test[i][j] );
                fprintf(file, "%f\t", holda[j] );
            }
            fprintf(file, "\n");
            i++;
        }
        k++;
        valid = runge_kutta(dt, holda, dx, holdb );
        copy(holda, holdb );
        if( valid == -1 )
            break;
    }
    
    fclose(file);
    printf("i %d k %d\n", i, k);
    return 0;
}


void pdu_pdt( double u[N], double s[N], double dx )
{
    int i;
    //double dx_2 = pow(dx,2);
    double dx_3 = pow(dx,3);
    
    for( i = 0; i < N; i++ )
    { 
        s[i] = -6*u[i]*du_x(u,i,dx) - du_xxx(u,i,dx_3);
        /*
        if( i > 1 && i < N-2 )
        {
            s[i] = (-0.5 * u[i+2] + (3*u[i]*dx_2 + 1 )*u[i+1] - (3*u[i]*dx_2 + 1 )*u[i-1] 
                + 0.5 * u[i-2])/dx_3;
        }/*
        else if( i <= 1 )
            s[i] = -1;
        else
            s[i] = -1;
			
		else if( i == 1 )
			s[i] = (-0.5 * u[i+2] + (3*u[i]*dx_2 + 1 )*u[i+1] - (3*u[i]*dx_2 + 1 )*u[i-1] 
                + 0.5 * u[N-1])/dx_3;
		else if( i == 0 )
			s[i] = (-0.5 * u[i+2] + (3*u[i]*dx_2 + 1 )*u[i+1] - (3*u[i]*dx_2 + 1 )*u[N-2] 
                + 0.5 * u[N-1])/dx_3;
		else if (i == N-1 )
			s[i] = (-0.5 * u[1] + (3*u[i]*dx_2 + 1 )*u[0] - (3*u[i]*dx_2 + 1 )*u[i-1] 
                + 0.5 * u[i-2])/dx_3;
		else
			s[i] = (-0.5 * u[0] + (3*u[i]*dx_2 + 1 )*u[i+1] - (3*u[i]*dx_2 + 1 )*u[i-1] 
                + 0.5 * u[i-2])/dx_3;
            */
            //s[i] = (-0.5 * u[0] + (3*u[i]*pow(dx,2) + 1 )*u[i+1] - (3*u[i]*pow(dx,2) + 1 )*u[i-1]  + 0.5 * u[i-2])/pow(dx,3);
    }
}

int runge_kutta( double dt, double u[N], double dx, double u_n[N])
{
    double s1[N];
    double s2[N];
    double s3[N];
    double s4[N];
    double w[N];
    int i;
    
    pdu_pdt( u, s1, dx);
    for( i = 0; i < N;i++ )
    {
        w[i] = u[i] + dt/2*s1[i];
    }
    pdu_pdt(w, s2, dx );
    for( i = 0; i < N;i++ )
    {
        w[i] = u[i] + dt/2*s2[i];
    }
    pdu_pdt(w,s3, dx );
    for( i = 0; i < N;i++ )
    {
        w[i] = u[i] + dt*s3[i];
        if( isnan(w[i]) ){
            printf( "s3 w[%d] = NaN\n", i );
            return -1;
        }
    }
    pdu_pdt(w,s4, dx);
    for( i = 0; i < N;i++ )
    {
        u_n[i] = u[i] + dt/6*(s1[i]+2*s2[i]+2*s3[i]+s4[i] );
    }
    return 0;
}

void initial( double u0[N], double dx )
{
    int i;
	int a = 9;
	int b = 16;
	int c = 2;
    double x;
    for( i = 0; i < N; i++ )
    {
        //u0[i] = .5*(1-tanh(((i*dx)-25)/5));
        //x = 0.5*(8-0)+0.5*(8-0)*cos( ( 2 * i - 1)/(2*(double)N) * M_PI );
		//u0[i] = 3*a*a/pow(cosh(.5*a*i*dx),2);
        u0[i] = 2 / pow(cosh(dx*i-4), 2);
    //printf("%f ", u0[i]);
    }
    //printf("\n");
}

void copy( double a[N], double b[N] )
{
    int i;
    for(i = 0; i < N; i++ )
        a[i] = b[i];
}

double du_x( double u[N], int i, double dx )
{
    if( i == 0 )
        return (u[i+1] - u[N-1])/(2*dx);
    else if( i == N-1)
        return (u[0] - u[i-1])/(2*dx);
    else
        return (u[i+1] - u[i-1])/(2*dx);
}
double du_xxx( double u[N], int i, double dx_3 )
{
    if( i == 0 )
        return (( u[i+2]-2*u[i+1] + u[i] ) - (u[i] -2*u[N-1]+u[N-2] ) )/ (2*dx_3);
    else if( i == 1 )
        return (( u[i+2]-2*u[i+1] + u[i] ) - (u[i] -2*u[i-1]+u[N-1] ) )/ (2*dx_3);
    else if( i == N-1)
        return (( u[1]-2*u[0] + u[i] ) - (u[i] -2*u[i-1]+u[i-2] ) )/ (2*dx_3);
    else if( i == N-2)
        return (( u[0]-2*u[i+1] + u[i] ) - (u[i] -2*u[i-1]+u[i-2] ) )/ (2*dx_3);
    else
        return (( u[i+2]-2*u[i+1] + u[i] ) - (u[i] -2*u[i-1]+u[i-2] ) )/ (2*dx_3);
}