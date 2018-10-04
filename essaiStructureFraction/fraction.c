
#include <stdio.h>
#include <stdlib.h>

#include "fraction.h"

FRACTION saisie()
{
    FRACTION frac;

    printf("\nEntrez le numerateur: ");
    scanf("%d",&frac.num);

    printf("\nEntrez le denominateur : ");
    scanf("%d",&frac.den);

    return frac;
}

FRACTION sommeFrac(FRACTION frac,FRACTION frac2)
{
    FRACTION somfrac;

    somfrac.num=((frac.num)*(frac2.den))+((frac2.num)*(frac.den));
    somfrac.den=((frac.den)*(frac2.den));



    return somfrac;

}

FRACTION simplFrac(FRACTION somfrac)
{
    FRACTION somSimpl;

    int i;
    int test=1;
    int test1=1;

    i=(somfrac.den)-1;

    do
    {
        test=(somfrac.num) % i;
        test1=(somfrac.den) % i;
        i--;
    }
    while ((test!=0 || test1!=0) || i==1);

    if (test==0 && test1==0 && i>1)
    {
        somSimpl.num=(somfrac.num)/(i+1);
        somSimpl.den=(somfrac.den)/(i+1);
    }
    else
    {
        somSimpl.num=(somfrac.num);
        somSimpl.den=(somfrac.den);
    }

    return somSimpl;
}

void afficheFrac(FRACTION fraction)
{
    printf("\nSomme des fractions: %d/%d\n",fraction.num,fraction.den);

}

