#include <stdio.h>
#include <stdlib.h>

#include "../../utilitaires/entetes/dateEu.h"

int main()
{
    char dat[9];
    char date[9];


    _strdate(dat);

    printf("%s\n",dat);

    strcpy(date,dateEu(dat));

    printf("%s",date);

    return 0;
}






