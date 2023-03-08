#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "virgule_fix.h"


unsigned short fp2fix(double M, double x) {
    return M*x;
}

double fix2fp(double M, unsigned short x) {
    return x/M;
}

void cordic_pre_tab_SHORT(int n, double M) {
    int i;

    for(i=0;i<n;i++){
        kteta[i][1]= fp2fix(M,atan(pow(2,-i)));
        kteta[i][0]=fp2fix(M,cos(atan(pow(2,-i))));
    }
}


int main()
{
    int n;
    double phi,i,j;

    /* Implementation du fichier
    FILE* fmax;
    char erreur_max_char[50];
    fmax = fopen("Erreurmax.txt","w");*/


    /* ETAPE 1 PROGRAMME TEST */
    /*printf("Angle (degre) : ");
    scanf("%lf", &phi);*/
    printf("\nNbr d'iterations : ");
    //scanf("%d", &n);
    cordic_pre_tab_SHORT(64,10000);
    for(j=4;j<=64;j++){
        erreurx_max=0;
        for(i=0;i<=90;i++){
            cordic(i,j);
            printf("\niteration %lf",i);
            printf("erreurx = %.40lf,erreury = %.40lf", erreurx, erreury);
        }
        //sprintf(erreur_max_char, "%.20lf\n", erreurx_max);
        //fprintf(fmax,"%s",erreur_max_char);
    }
    //cordic_pre_tab(n);
    //cordic(phi,n);

    return 0;
}
