#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI 3.14159
#define M_point 16384 //2^14
//#include "virgule_fix.h"


unsigned short kteta[100][2];
//double kteta[100][2];
unsigned short x[2],y[2],xf,yf,erreurx,erreury,erreurx_max=0;

unsigned short fp2fix(double M, double x) {
    return M*x;
}

double fix2fp(double M, unsigned short x) {
    return x/M;
}

void cordic_pre_tab_SHORT(int n, unsigned short M) {
    int i;

    for(i=0;i<n;i++){
        kteta[i][1]= fp2fix(M_point,atan(pow(2,-i)));
        kteta[i][0]= fp2fix(M_point,cos(atan(pow(2,-i))));
    }
}

void cordic_pre_tab(int n) {
    int i;
    for(i=0;i<n;i++){
        kteta[i][1]=atan(pow(2,-i));
        kteta[i][0]=cos(atan(pow(2,-i)));
    }
}

void cordic_short(unsigned short phi, int n) {
    unsigned short a, An, d;
    int i;
    An = 1;

    for(i=0;i<n;i++){
        An = An * kteta[i][0];
    }

    phi = fp2fix(M_point,phi * (PI/180));
    printf("phi= %u", phi);


    x[0] = An;
    a=0;
    y[0] = 0;
    d = 1;

    for(i=0;i<n;i++){
        if (a < phi) {
            x[1] = (x[0] - (y[0] >> d));
            y[1] = (y[0] + (x[0] >> d));
            a = (a + kteta[i][1]);
        } else {
            x[1] = (x[0] + (y[0] >> d));
            y[1] = (y[0] - (x[0] >> d));
            a = (a - kteta[i][1]);
        }
        //printf("\nx : %u , ",  x[1]);
        //printf("y : %u ",  y[1]);
        x[0] = x[1];
        y[0] = y[1];
        d = d << 2;
    }
    xf = x[1];
    yf = y[1];
    //printf("x : %u , ",  x[1]);
    //printf("y : %u ",  y[1]);
    /*erreurx = xf - cos(phi); //phi en radian
    erreury = yf - sin(phi);

    if (erreurx_max < erreurx) {
        erreurx_max = erreurx;
    }*/



}

int main()
{
    int n;
    unsigned short phi,i,j;
    double x_fin, y_fin;

    /* Implementation du fichier
    FILE* fmax;
    char erreur_max_char[50];
    fmax = fopen("Erreurmax.txt","w");*/


    /* ETAPE 1 PROGRAMME TEST */
    /*printf("Angle (degre) : ");
    scanf("%lf", &phi);*/
    //printf("\nNbr d'iterations : ");
    //scanf("%d", &n);
    cordic_pre_tab_SHORT(20,M_point);
    //for(j=4;j<=64;j++){
        //erreurx_max=0;
        /*for(i=0;i<=90;i++){
            cordic_short(60,13);
            printf("\nx : %u , ",  x[1]);
            printf("y : %u ",  y[1]);
            x_fin = fix2fp(M_point,x[1]);
            y_fin = fix2fp(16384,y[1]);
            printf("x : %lf , ",  x_fin);
            printf("y : %lf ",  y_fin);
            //printf("\niteration %lf",i);
            //printf("erreurx = %.40lf,erreury = %.40lf", erreurx, erreury);
        //}
        //sprintf(erreur_max_char, "%.20lf\n", erreurx_max);
        //fprintf(fmax,"%s",erreur_max_char);
    //}
    //cordic_pre_tab(n);
    //cordic(phi,n);
    */
    for(i=0;i<20;i++)
        printf("\nk = %u , teta= %u", kteta[0][i], kteta[1][i]);
    //printf("\nk = %lf , teta= %lf", kteta[0][i], kteta[1][i]);*/
    cordic_short(60,20);


    return 0;
}
