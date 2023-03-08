#ifndef VIRGULE_FIX_H_INCLUDED
#define VIRGULE_FIX_H_INCLUDED
#define PI 3.14159
double kteta[100][2];
double x[2],y[2],xf,yf,erreurx,erreury,erreurx_max=0;

void cordic_pre_tab(int n);
void cordic(double phi, int n);

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

#endif // VIRGULE_FIX_H_INCLUDED
