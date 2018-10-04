typedef struct
{
    int num;
    int den;
} Fraction;


int saisie(Fraction*);
void sommeFrac(Fraction*,Fraction*,Fraction*);
void afficheFrac(Fraction*);
void simplFrac(Fraction*,Fraction*);


#include <stdio.h>
#include <stdlib.h>

int main()
{
    Fraction frac;
    Fraction frac2;
    Fraction somfrac;
    Fraction somSimpl;
    int resultat=0;

    resultat=saisie(&frac);

    if (resultat !=0)
    {
        printf("\n\nfraction impossible car non divisible par 0\n");
    }
    else
    {
        resultat=saisie(&frac2);

        if (resultat !=0)
        {
            printf("\n\nfraction impossible car non divisible par 0\n");
        }
        else
        {
            sommeFrac(&frac,&frac2,&somfrac);

            afficheFrac (&somfrac);

            simplFrac(&somfrac,&somSimpl);

            printf("\nSomme des fractions simplifiee: %d/%d\n",somSimpl.num,somSimpl.den);

        }

    }


    return 0;
}


int saisie(Fraction* frac)
{
    printf("\nEntrez le numerateur: ");
    scanf("%d",&frac->num);

    printf("\nEntrez le denominateur : ");
    scanf("%d",&frac->den);

    if (frac->den==0)
    {
        return -1;
    }
    return 0;
}

void sommeFrac(Fraction* frac,Fraction* frac2,Fraction* somfrac)
{

    somfrac->num=(frac->num*frac2->den)+(frac2->num*frac->den);
    somfrac->den=(frac->den*frac2->den);

}

void simplFrac(Fraction* somfrac,Fraction* somSimpl)
{
    int i;
    int test=1;
    int test1=1;

    i=(somfrac->den)-1;

    do
    {
        test=(somfrac->num) % i;
        test1=(somfrac->den) % i;
        i--;
    }
    while ((test!=0 || test1!=0) || i==1);

    if (test==0 && test1==0 && i>1)
    {
        somSimpl->num=(somfrac->num)/(i+1);
        somSimpl->den=(somfrac->den)/(i+1);
    }
    else
    {
        somSimpl->num=(somfrac->num);
        somSimpl->den=(somfrac->den);
    }


}

void afficheFrac(Fraction* somfrac)
{
    printf("\nSomme des fractions: %d/%d\n",somfrac->num,somfrac->den);

}

