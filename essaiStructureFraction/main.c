
#include <stdio.h>
#include <stdlib.h>

#include "fraction.h"

int main()
{
    FRACTION frac;
    FRACTION frac2;
    FRACTION somfrac;
    FRACTION somSimpl;

    frac=saisie();

    if (frac.den ==0)
    {
        printf("\n\nfraction impossible car non divisible par 0\n");
    }
    else
    {
        frac2=saisie();

        if (frac2.den ==0)
        {
            printf("\n\nfraction impossible car non divisible par 0\n");
        }
        else
        {
            somfrac=sommeFrac(frac,frac2);

            afficheFrac(somfrac);

            somSimpl=simplFrac(somfrac);

            afficheFrac(somSimpl);

        }

    }


    return 0;
}
