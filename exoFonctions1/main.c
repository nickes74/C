int recup(int*,int*);
void sommeFrac(int, int, int, int,int*,int*);
void affichagefrac(int, int);


#include <stdio.h>
#include <stdlib.h>

int main()
{
    int resultat=0;
    int num1,num2,den1,den2,sommeNum,sommeDen;

    resultat=recup(&num1, &den1);

    if (resultat ==0)
    {

        resultat=recup(&num2, &den2);

        if (resultat ==0)
        {
            sommeFrac(num1,num2,den1,den2,&sommeNum,&sommeDen);

            affichefrac(sommeNum,sommeDen);
        }
        else
        {
            printf("\nResultat impossible");
        }

    }
    else
    {
        printf("\nResultat impossible");
    }

    return 0;
}





int recup(int* num, int* den)
{
    printf("\nEntrez un numerateur :");
    scanf("%d", num);

    printf("\nEntrez un denominateur :");
    scanf("%d", den);

    if (*den == 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }

}

void sommeFrac(int num1, int num2, int den1,int den2,int* sommeNum,int* sommeDen)
{

    *sommeDen= den1 * den2;
    *sommeNum= (num1 * den2)+(num2 * den1);

}

void affichefrac (int sommeNum,int sommeDen)
{
    printf("\nResultat de la fraction: %d/%d\n",sommeNum,sommeDen);
}
