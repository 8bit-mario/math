#include<stdio.h>
#include<string.h>
#include<math.h>
#include<malloc.h>

/* for memory allocated on stack */
/* ToDo: change to dynamic memory allocation */
#define N 4

void printM(char* name, double M[N][N]);
void LU(double A[N][N], double L[N][N], double U[N][N]);
void LUSolve(double L[N][N], double U[N][N], double B[N], double X[N]);
void printEq(double A[N][N], double X[N]);
void read(double A[N][N], double B[N]);

int main(int argc, char *argv[])
{
	double L[N][N], U[N][N], X[N];
	double A[N][N] = {{1, 2, -3, 4},
					{2,  2, -2,  3},
					{0,  1,  1,  0},
					{1, -1,  1, -2}};
	double B[N] = {12, 10, -1, -4};
	memset(L, 0, sizeof(L));
	memset(U, 0, sizeof(U));

	read(A, B);
	printf("\nSolving System Of Linear Equation\n");
	printEq(A, B);
	
	printf("\nLU decomposition\n");
	LU(A, L, U);
	printM("L", L);
	printf("\n");
	printM("U", U);

	LUSolve(L, U, B, X);
	printf("\nSolution\n");
	for(int i = 0; i < N; i++)
		printf("x%d = %8.2f\n", i, X[i]);
	printf("\n");
	return 0;
}

void read(double A[N][N], double B[N])
{
	printf("Enter 4 equation in format a*x0 + b*x1 + c*x2 + d*x3 = f\n");
	for(int i = 0; i < N; i++)
	{
		printf(">>  ");
		for(int j = 0; j < N+1; j++)
		{
			if(j == N)
			{
				scanf("%lf", &B[i]);
			}
			else
			{
				scanf("%lf", &A[i][j]);
			}
		}
	}
}

void LUSolve(double L[N][N], double U[N][N], double B[N], double X[N])
{
	double Y[N];
	/* Ly = b */
	for(int i = 0; i < N; i++)
	{
		double sum = 0.0;
		for(int k = 0; k < i; k++)
		{
			sum += L[i][k] * Y[k];
		}
		Y[i] = (B[i] - sum) / L[i][i];
	}
	
	/* Ux = y */	
	for(int i = N-1; i >= 0; i--)
	{
		double sum = 0.0;
		for(int k = i+1; k < N; k++)
		{
			sum += U[i][k]*X[k];
		}
		X[i] = (Y[i] - sum) / U[i][i];
	}	
}

void LU(double A[N][N], double L[N][N], double U[N][N])
{
	int n;
	for(n=0; n < N; n++)
	{
		/* Compute U row by row */
		for(int j = n; j < N; j++)
		{
			double sum = 0.0;
			for(int k = 0; k < n; k++)
				sum += U[k][j]*L[n][k];
			U[n][j] = A[n][j] - sum;
		}

		/* Compute L column by column */
		for(int i = n; i < N; i++)
		{
			if(i == n)
			{
				L[i][i] = 1.0;
			}
			else
			{
				double sum = 0.0;
				for(int k = 0; k < n; k++)
					sum += U[k][n]*L[i][k];
				L[i][n] = (A[i][n] - sum) / U[n][n];
			}
		}
	}
}

void fill(int n);
void printM(char* name, double M[N][N])
{
	int dx = strlen(name);
	printf("%s = ", name);
	dx += 3;
	for(int i = 0; i < N; i++)
	{
		printf("%8.2f  ", M[0][i]);
	}
	printf("\n");
	for(int i = 1; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(j == 0)
			{
				fill(dx);
			}
			printf("%8.2f  ", M[i][j]); 
		}
		printf("\n");
	}
}

void fill(int n)
{
	for(int i = 0; i < n; i++)
	{
		putc(' ', stdout);
	}
}

void printEq(double A[N][N], double X[N])
{
	char sign;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(j == N-1)
				printf("%6.1f * x%d = ", fabs(A[i][j]), j);
			else
			{
				(A[i][j+1] < 0) ? (sign = '-') : (sign = '+');
				printf("%6.1f * x%d   %c ", fabs(A[i][j]), j, sign);
			}
		}
		printf("%6.1f", X[i]);
		printf("\n");
	}
}
