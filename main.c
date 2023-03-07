#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI 3.14159

double kteta[100][2];
double x[2],y[2],xf,yf,erreurx,erreury,erreurx_max=0;

void cordic_pre_tab(int n) {
    int i;

    for(i=0;i<n;i++){
        kteta[i][1]=atan(pow(2,-i));
        kteta[i][0]=cos(atan(pow(2,-i)));
    }
}

void cordic(double phi, int n) {
    double a, An, d;
    int i;
    An = 1;

    for(i=0;i<n;i++){
        An = An * kteta[i][0];
    }

    phi = phi * (PI/180);


    x[0] = An;
    a=0.0;
    y[0] = 0.0;
    d = 1.0;

    for(i=0;i<n;i++){
        if (a < phi) {
            x[1] = (x[0] - (y[0] / d));
            y[1] = (y[0] + (x[0] / d));
            a = (a + kteta[i][1]);
        } else {
            x[1] = (x[0] + (y[0] / d));
            y[1] = (y[0] - (x[0] / d));
            a = (a - kteta[i][1]);
        }
        x[0] = x[1];
        y[0] = y[1];
        d = d * 2;
    }
    xf = x[1];
    yf = y[1];
    //printf("x : %lf , ",  x[1]);
    //printf("y : %lf ",  y[1]);
    erreurx = xf - cos(phi); //phi en radian
    erreury = yf - sin(phi);

    if (erreurx_max < erreurx) {
        erreurx_max = erreurx;
    }



}

int main()
{
    int n;
    double phi,i,j;

    /* Implementation du fichier */
    FILE* fmax;
    char erreur_max_char[50];
    fmax = fopen("Erreurmax.txt","w");


    /* ETAPE 1 PROGRAMME TEST */
    /*printf("Angle (degre) : ");
    scanf("%lf", &phi);*/
    printf("\nNbr d'iterations : ");
    //scanf("%d", &n);
    cordic_pre_tab(64);
    for(j=4;j<=64;j++){
        erreurx_max=0;
        for(i=0;i<=90;i++){
            cordic(i,j);
            printf("\niteration %lf",i);
            printf("erreurx = %.40lf,erreury = %.40lf", erreurx, erreury);
        }
        sprintf(erreur_max_char, "%.20lf\n", erreurx_max);
        fprintf(fmax,"%s",erreur_max_char);
    }
    //cordic_pre_tab(n);
    //cordic(phi,n);

    return 0;
}
