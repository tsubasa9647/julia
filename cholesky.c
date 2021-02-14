/*
 cholesky1.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h> /* INT_MAX のため */
typedef double *vector;
typedef vector *matrix;

/* [0,1) 範囲の一様疑似乱数 */
double drandom()
{
    return rand() / (double)INT_MAX;
}

/* 行列の積 */
void mul_mm(int n, matrix ab, matrix a, matrix b)
{
    int i, j, k;
    double s;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
        {
            s = 0;
            for (k = 1; k <= n; k++)
                s += a[i][k] * b[k][j];
            ab[i][j] = s;
        }
}

/* 行列の表示 */
void print_matrix(int n, matrix a)
{
    int i, j;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
            printf("%f ", a[i][j]);
        printf("\n");
    }
}

void clear_m(int n, matrix a)
{
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            a[i][j] = 0;
}

/* 自乗 */
double sqr(double x) { return x * x; }

matrix new_matrix(int m, int n)
{
    int i;
    vector ap;
    matrix a;
    if ((a = malloc(sizeof(vector) * m)) == NULL)
    {
        return NULL;
    }
    if ((ap = malloc(sizeof(double) * (m * n))) == NULL)
    {
        free(a);
        return NULL;
    }
    for (i = 0; i < m; i++)
        a[i] = ap + i * n;
    return a;
}

/* Cholesky 分解 */
void cholesky(int n, matrix L, matrix a)
{
    int i, j, k;
    double s;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j < i; j++)
        {
            s = a[i][j];
            for (k = 1; k < j; k++)
                s -= L[i][k] * L[j][k];
            L[i][j] = s / L[j][j];
        }
        /* L[i][i] の計算 */
        s = a[i][i];
        for (k = 1; k < i; k++)
            s -= sqr(L[i][k]);
        if (s < 0)
        {
            fprintf(stderr, "s < 0\n");
            exit(0);
        }
        L[i][i] = sqrt(s);
    }
}

int main()
{
    int i, j, N;
    matrix a, L, Lt;
    printf("N=");
    scanf("%d", &N);
    a = new_matrix(N + 1, N + 1);
    L = new_matrix(N + 1, N + 1);
    Lt = new_matrix(N + 1, N + 1);
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= i; j++)
            Lt[j][i] = L[i][j] = drandom();
        for (j = i + 1; j <= N; j++)
            Lt[j][i] = L[i][j] = 0.0;
    }
    mul_mm(N, a, L, Lt);
    printf("L=\n");
    print_matrix(N, L);
    printf("a=\n");
    print_matrix(N, a);

    clear_m(N, L);
    cholesky(N, L, a);
    printf("L=\n");
    print_matrix(N, L);

    return 0;
}
