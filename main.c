#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>

void inverse(double* A, lapack_int N)
{
    lapack_int *IPIV = (lapack_int *) malloc(N * sizeof(lapack_int));
    int INFO;

    /*
        DGETRF computes an LU factorization of a general M-by-N matrix A
        using partial pivoting with row interchanges.

        The factorization has the form
            A = P * L * U
        where P is a permutation matrix, L is lower triangular with unit
        diagonal elements (lower trapezoidal if m > n), and U is upper
        triangular (upper trapezoidal if m < n).

        This is the right-looking Level 3 BLAS version of the algorithm.
    
        lapack_int LAPACKE_dgetrf( int matrix_layout, lapack_int m, lapack_int n,
                        double* a, lapack_int lda, lapack_int* ipiv );
    
        INFO is INTEGER
          = 0:  successful exit
          < 0:  if INFO = -i, the i-th argument had an illegal value
          > 0:  if INFO = i, U(i,i) is exactly zero. The factorization
                has been completed, but the factor U is exactly
                singular, and division by zero will occur if it is used
                to solve a system of equations.
    */
    
    INFO = LAPACKE_dgetrf(LAPACK_ROW_MAJOR,N,N,A,N,IPIV);
    printf("%d ", INFO);

    //DGETRI computes the inverse of a matrix using the LU factorization
    //computed by DGETRF.

    //This method inverts U and then computes inv(A) by solving the system
    //inv(A)*L = inv(U) for inv(A).
    //lapack_int LAPACKE_dgetri( int matrix_layout, lapack_int n, double* a,
    //          lapack_int lda, const lapack_int* ipiv );
    INFO = LAPACKE_dgetri(LAPACK_ROW_MAJOR,N,A,N,IPIV);
    printf("%d \n", INFO);

    free(IPIV);
}

int main(){

    double A [2*2] = {
        1,2,
        3,4
    };

    inverse(A, 2);

    printf("%f %f\n", A[0], A[1]);
    printf("%f %f\n", A[2], A[3]);

    return 0;
}
