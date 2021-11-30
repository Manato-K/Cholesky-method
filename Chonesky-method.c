/*Cholesky method*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 3
int main(void)
{
    int i,j,k;
    float A[N][N],L[N][N],U[N][N],x[N],b[N],y[N];
    FILE *fp;
    if( (fp=fopen("20191105-2.dat","r"))==NULL ) {
        printf("cannot open file.\n");
        exit(0);
    }
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) fscanf(fp,"%f",&A[i][j]);
        fscanf(fp,"%f",&b[i]);
    }
    fclose(fp);
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) printf(" %6.2f",A[i][j]);
        printf("\t%6.2f\n",b[i]);
    }
    printf("\n");

    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
        L[i][j]=0.0;
        U[i][j]=0.0;
        }
        x[i]=0.0;
    }
/* A=LU (U=LT) -> L,U */
    for(j=0;j<N;j++) {
        for(i=j;i<N;i++) {
            if(i==j) {
            L[i][j]=A[i][j];
            for(k=0;k<i;k++)
                L[i][j]-=L[i][k]*L[i][k];
            L[i][j]=sqrt(L[i][j]);
            } else {
                L[i][j]=A[i][j];
                for(k=0;k<j;k++)
                    L[i][j]-=L[j][k]*L[i][k];
                L[i][j]/=L[j][j];
            }
            U[j][i]=L[i][j];
        }
    }
    for(i=0;i<N;i++){
        for(j=0;j<N;j++) printf(" %6.2f",L[i][j]);
        printf("\t");
        for(j=0;j<N;j++) printf(" %6.2f",U[i][j]);
        printf("\n");
    }
    printf("\n");
/* Ly=b -> y */
    for(i=0;i<N;i++) {
        y[i]=b[i];
        for(j=0;j<i;j++) y[i]-=L[i][j]*y[j];
        y[i]/=L[i][i];
    }
/* Ux=y -> x */
    for(i=N-1;i>=0;i--) {
        x[i]=y[i];
        for(j=i+1;j<N;j++) x[i]-=U[i][j]*x[j];
        x[i]/=U[i][i];
    }
/* result */
    for(i=0;i<N;i++) printf("%6.2f\n",x[i]);
}