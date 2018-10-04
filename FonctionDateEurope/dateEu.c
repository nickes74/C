char* dateEu(char* dat)
{
    char mois[2]="";
    char jour[2]="";
    char an[2]="";
    char date[9]="";
    int i=0;
    int j=0;

    for (i=3; i<5; i++)
    {
        jour[j]=dat[i];
        j++;
    }
    jour[j]=0;
    j=0;

    strcat(date,jour);
    strcat(date,"/");

    for (i=0; i<2; i++)
    {
        mois[j]=dat[i];
        j++;
    }
    mois[j]=0;
    j=0;

    strcat(date,mois);
    strcat(date,"/");

    for (i=6; i<9; i++)
    {
        an[j]=dat[i];
        j++;
    }
    an[j]=0;

    strcat(date,an);


    return date;
}
