#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Simptom
{
    char ime[1000];
    int pojavljivanje;
};

int upisatiSimptome(struct Simptom** simptom)
{
    char str1[1000];
    int i,j,ctr;
    printf("Unesite simptome: ");
    scanf(" %[^\n]s", str1);
    j=0;
    ctr=0;

    for(i=0; i<=(strlen(str1)); i++)
    {


        if((str1[i]>='a' && str1[i]<='z')||(str1[i]>='A' && str1[i]<='Z')||(str1[i]==' ' && ((str1[i-1]>='a' && str1[i-1]<='z')||(str1[i-1]>='A' && str1[i-1]<='Z'))))
        {
            while((str1[i]>='a' && str1[i]<='z')||(str1[i]>='A'&&str1[i]<='Z')||(str1[i]==' '))
                ++i;
            ++j;
        }
    }
    i=0;
    while((str1[i]<'a' || str1[i]>'z')&&(str1[i]<'A' || str1[i]>'Z'))
        ++i;

    (*simptom)=(struct Simptom*)malloc(sizeof(struct Simptom)*j);
    int povratna=j;
    j=0;
    for(i=i; i<=(strlen(str1)); i++)
    {


        if(str1[i]==' ' &&((str1[i+1]<'a' || str1[i+1]>'z')||(str1[i-1]==',')))
        {
            while(((str1[i-1]==',')|| (str1[i]!=','))&&(((str1[i+1]<'a' || str1[i+1]>'z')&&(str1[i+1]<'A' || str1[i+1]>'Z'))))
                ++i;
        }
        if((str1[i]<'a' || str1[i]>'z')&&(str1[i]<'A' || str1[i]>'Z')&&(str1[i]!=' '))
        {
            (*simptom)[ctr].ime[j]='\0';
            while((str1[i+1]<'a' || str1[i+1]>'z')&&(str1[i+1]<'A' || str1[i+1]>'Z'))
                ++i;
            ctr++;
            j=0;
        }
        else
        {
            (*simptom)[ctr].ime[j]=str1[i];
            j++;
        }
    }

    for(i=0; i<povratna; ++i)
    {
        printf("Unesite koliko puta se pojavljivalo/la %s  u poslednjih godinu dana: ", (*simptom)[i].ime);
        scanf("%i", &(*simptom)[i].pojavljivanje);
    }
    return povratna;
}
int izdvajanjeSimptoma(char* s1,struct Simptom** simptomi)
{
    FILE* f1=fopen(s1, "r");
    char s2[1000];
    while(fscanf(f1, " %[^\n]", s2)!=EOF)
    {

        if(strstr(s2, "Simptomi")!=NULL)
            break;
    }
    int j=0;
    for(int t=0; t<strlen(s2); ++t)
    {
        if(s2[t]==',')
            ++j;
        if(t+1==strlen(s2))
            ++j;
    }
    *simptomi=(struct Simptom*)malloc(sizeof(struct Simptom)*j);
    j=0;
    while(s2[j]!=':')
        ++j;
    ++j;
    int a=0;
    int b=0;
    for(int t=j; t<strlen(s2); ++t)
    {
        if(s2[t]==',')
        {
            (*simptomi)[b].ime[a]='\0';
            a=0;
            ++b;
            continue;
        }

        (*simptomi)[b].ime[a]=s2[t];
        ++a;
    }

    fseek(f1, 0, SEEK_SET);
    while(fscanf(f1, " %[^\n]", s2)!=EOF)
    {
        if(strstr(s2, "Broj pojavljivanja u poslednjih godinu dana")!=NULL)
            break;
    }
    j=0;
    while(s2[j]!=':')
        ++j;
    ++j;

    char s3[b][1000];
    a=0;
    b=0;
    for(int t=j; t<strlen(s2); ++t)
    {
        if(s2[t]==',')
        {
            s3[b][a]='\0';
            a=0;

            sscanf(s3[b], " %i", &((*simptomi)[b].pojavljivanje));
            ++b;
            continue;
        }
        s3[b][a]=s2[t];
        ++a;
    }
    fclose(f1);
    return b;
}
void dodavanjeBolesti()
{
    int ID;
    printf("Unesite ID bolesti: ");
    scanf("%i", &ID);
    char s2[1000];
    sprintf(s2, "%i.txt", ID);
    FILE* fp=fopen(s2, "r");
    if(fp==NULL)
    {
        fclose(fp);
        fp=fopen(s2, "w");
    }
    else
    {



        do
        {
            printf("ID mora biti jedinstven!");
            fclose(fp);
            scanf("%i", &ID);
            sprintf(s2, "%i.txt", ID);
            fp=fopen(s2, "r");
            if(fp==NULL)
            {
                fclose(fp);
                fp=fopen(s2, "w");
                break;
            }
        }
        while(1==1);
    }
    printf("Unesite naziv bolesti: ");
    char s3[50];
    scanf(" %[^\n]", s3);
    int tip;
    printf("Izaberite tip bolesti(1.Akutna, 2.Hronicna): ");
    int boolean;
    scanf("%i", &boolean);
    if(boolean!=1 && boolean!=2)
    {
        while(boolean!=1 && boolean!=2)
        {
            printf("Izaberite tip bolesti(1.Akutna, 2.Hronicna): ");
            scanf("%i", &boolean);
        }
    }
    if(boolean==1)
    {
        tip=0;
    }
    else
    {
        tip=1;
    }
    struct Simptom* simptom;

    int j=upisatiSimptome(&simptom);

    fprintf(fp, "ID:%i\nNaziv:%s\nTip:%i\nBroj pojavljivanja u poslednjih godinu dana:", ID, s3, tip);
    for(int i=0; i < j; i++)
    {



        fprintf(fp, "%i,",simptom[i].pojavljivanje);
    }
    fprintf(fp, "\nSimptomi:");
    for(int i=0; i < j; i++)
    {



        fprintf(fp, "%s,",simptom[i].ime);
    }
    fclose(fp);
    fp=fopen("spisakbolesti.txt", "a");
    fseek(fp, 0, SEEK_END);
    int kraj=ftell(fp);
    if(kraj==0)
    {
        fprintf(fp,"%i-%s", ID, s3);
    }
    else
    {
        fprintf(fp, "\n%i-%s", ID, s3);
    }
    fclose(fp);
}
void prikaz()
{
    FILE* f1=fopen("spisakbolesti.txt", "r");
    if(f1!=NULL)
    {
        fseek(f1, 0, SEEK_END);
        int kraj=ftell(f1);
        if(0==kraj)
        {
            printf("Nema nijedne bolesti!\n");
            return;
        }
    }
    fseek(f1, 0, SEEK_SET);

    char s1[1000];
    while(fscanf(f1, " %[^\n]", s1)!=EOF)
    {
        int i;
        sscanf(s1, " %i-", &i);
        char s2[1000];
        sprintf(s2, "%i.txt", i);
        FILE* f2=fopen(s2, "r");
        char s3[1000];
        while(fscanf(f2, " %[^\n]",s3)!=EOF)
        {

            if(strstr(s3, "Naziv")!=NULL || strstr(s3, "Simptomi")!=NULL)
                printf("%s\n", s3);
        }
        fclose(f2);
    }
    fclose(f1);
}
void Pretraga(int *broj, int **spisak)
{
Ponovo:

    printf("1. pretraga po ID, 2. pretraga po nazivu: ");
    int i;
    scanf("%i", &i);

    if(i!=1 && i!=2)
    {
        while(i!=1 && i!=2)
        {
            printf("1. pretraga po ID, 2. pretraga po nazivu: ");
            scanf(" %i", &i);
        }
    }
    if(i==1)
    {

        int ID;

        printf("Unesite ID: ");
        scanf("%i", &ID);
        char s1[1000];
        sprintf(s1, "%i.txt", ID);
        FILE* f1=fopen(s1, "r");
        if(f1==NULL)
        {
            fclose(f1);
            printf("Ne postoji bolest sa ovim ID-om!\nDa li zelite da ponovite pretragu?(1.DA, 2.NE): ");
            int j;

            scanf("%i", &j);
            if(j!=1 && j!=2)
            {
                while(j!=1 && j!=2)
                {
                    printf("(1.DA, 2.NE): ");
                    scanf("%i", &j);
                }
            }
            if(j==2)
            {
                return;
            }
            else
                goto Ponovo;
        }
        *broj=1;
        *spisak=(int*)malloc(sizeof(int)*1);
        (*spisak)[(*broj)-1]=ID;

        fclose(f1);
    }
    else
    {
        printf("Unesite naziv: ");
        char s1[1000];
        scanf(" %[^1-9\n]", s1);
        FILE* f1=fopen("spisakbolesti.txt", "r");
        char s2[1000];
        *broj=0;
        while(fscanf(f1, " %[^\n]", s2)!=EOF)
        {
            if(strstr(s2, s1)!=NULL)
            {
                ++(*broj);
            }
        }
        if((*broj)==0)
        {
            fclose(f1);
            printf("Nije pronadjena nijedna bolest sa unetim nazivom!\nDa li zelite da ponovite pretragu?(1.DA, 2.NE): ");
            int j;
            scanf(" %i", &j);


            if(j!=1 && j!=2)
            {
                while(j!=1 && j!=2)
                {
                    printf("(1.DA, 2.NE): ");
                    scanf(" %i", &j);
                }
            }

            if(j==2)
                return;
            else
                goto Ponovo;
        }
        (*spisak)=(int*)malloc(sizeof(int)*(*broj));
        int b=(*broj);
        fseek(f1, 0, SEEK_SET);
        *broj=0;
        while(fscanf(f1, " %[^\n]", s2)!=EOF)
            if(strstr(s2, s1)!=NULL)
            {
                sscanf(s2, " %i-", &(*spisak)[(*broj)]);
                ++(*broj);
                if(b>1)
                    printf("%i. %s\n",(*broj), s2);

            }
        fclose(f1);
    }
}
void PretragaBolesti()
{
    int broj=0;
    int* spisak;
    Pretraga(&broj, &spisak);
    if(broj==0)
        return;
    FILE *f1;
    if(broj==1)
    {
        char s3[1000];
        sprintf(s3, "%i.txt", spisak[0]);
        f1=fopen(s3, "r");

        while(fscanf(f1, " %[^\n]", s3)!=EOF)
        {
            if(strstr(s3, "Broj pojavljivanja")!=NULL)
            {
                continue;
            }
            if(strstr(s3,"Tip")!=NULL)
            {
                if(strstr(s3,"1")!=NULL)
                {
                    printf("Tip:Hronicna\n");
                }
                else
                {
                    printf("Tip:Akutna");
                }
                continue;
            }

            printf("%s\n", s3);

        }
        fclose(f1);
    }
    else
    {
        printf("1. ispisi podatke za samo jednu pronadjenu bolest, 2. ispisi podatke za sve pronadjene bolesti: ");
        int j;
        scanf("%i", &j);
        if(j!=1 && j!=2)
        {
            while(j!=1 && j!=2)
            {
                printf("1. ispisi podatke za samo jednu pronadjenu bolest, 2. ispisi podatke za sve pronadjene bolesti: ");
                scanf("%i", &j);
            }
        }
        if(j==1)
        {
            printf("Izaberite jedan od brojeva (1-%i)!\n", broj);
            int a;
            scanf("%i", &a);
            if(a<1 || a>broj)
            {
                while(a<1 || a>broj)
                {
                    printf("Izaberite jedan od brojeva (1-%i)!\n", broj);
                    scanf("%i", &a);
                }
            }
            char s3[1000];
            sprintf(s3, "%i.txt", spisak[a-1]);
            f1=fopen(s3, "r");
            while(fscanf(f1, " %[^\n]", s3)!=EOF)
            {
                if(strstr(s3,"Tip")!=NULL)
                {
                    if(strstr(s3,"1")!=NULL)
                    {
                        printf("Tip:Hronicna\n");
                    }
                    else
                    {
                        printf("Tip:Akutna");
                    }
                    continue;
                }
                if(strstr(s3,"Broj pojavljivanja")!=NULL)
                    continue;
                printf("%s\n", s3);
            }
            fclose(f1);
        }
        else if(j==2)
        {
            for(int i=0; i<broj; i++)
            {
                char s3[1000];
                sprintf(s3, "%i.txt", spisak[i]);
                f1=fopen(s3, "r");
                while(fscanf(f1," %[^\n]",s3)!=EOF)
                {
                    if(strstr(s3,"Tip")!=NULL)
                    {
                        if(strstr(s3,"1")!=NULL)
                        {
                            printf("Tip:Hronicna\n");
                        }
                        else
                        {
                            printf("Tip:Akutna");
                        }
                        continue;
                    }
                    if(strstr(s3,"Broj pojavljivanja")!=NULL)
                        continue;
                    printf("%s\n", s3);
                }
                fclose(f1);
            }
        }

    }
}
void upisatiNaziv(char *s1)
{
    FILE* f1=fopen(s1, "r");
    char s2[1000];
    char s3[1000];
    while(fscanf(f1, " %[^\n]", s2)!=EOF)
    {
        if(strstr(s2, "Naziv")!=NULL)
            break;
    }

    FILE* f2=fopen("izmena.txt", "w");
    fseek(f1, 0, SEEK_SET);
    while(fscanf(f1, " %[^\n]", s2)!=EOF)
    {
        if(strstr(s2,"Naziv")!=NULL)
        {

            printf("Zelite da preimenujete ovu bolest u: ");
            scanf(" %[^\n]", s3);
            fprintf(f2, "Naziv:%s\n",s3);
            continue;
        }
        fputs(s2, f2);
        if(strstr(s2, "Simptomi")!=NULL)
            continue;
        fprintf(f2,"\n");
    }
    fclose(f2);
    fclose(f1);
    remove(s1);
    rename("izmena.txt", s1);
    char ID[1000];
    int i=0;
    while(s1[i]!='.')
    {
        ID[i]=s1[i];
        ++i;
    }
    ID[i]='\0';
    f1=fopen("spisakbolesti.txt","r");
    f2=fopen("izmena.txt","w");
    fseek(f1,0,SEEK_SET);
    while(fscanf(f1," %[^\n]",s2)!=EOF)
    {
        fseek(f2, 0, SEEK_END);
        int kraj=ftell(f2);
        if(kraj!=0)
        {
            fprintf(f2,"\n");
        }

        if(strstr(s2,ID)!=NULL)
        {
            fprintf(f2,"%s-%s",ID,s3);
            continue;
        }
        fputs(s2,f2);
    }
    fclose(f2);
    fclose(f1);
    remove("spisakbolesti.txt");
    rename("izmena.txt","spisakbolesti.txt");
}
void dodatiSimptom(char* s1)
{
    struct Simptom *simptom;

    int granica=upisatiSimptome(&simptom);
    FILE* f1=fopen(s1, "r");
    FILE* f2=fopen("izmena.txt", "w");
    char s2[1000];
    while(fscanf(f1, " %[^\n]", s2)!=EOF)
    {
        if(strstr(s2,"Broj")!=NULL)
        {

            for(int t=0; t<granica; ++t)
            {
                char s3[1000];
                sprintf(s3, "%i,", simptom[t].pojavljivanje);
                strcat(s2,s3);
            }
            fprintf(f2, "%s\n", s2);
            continue;
        }
        fprintf(f2, "%s", s2);
        if(strstr(s2, "Simptomi")==NULL)
            fprintf(f2, "\n");
    }
    fclose(f1);
    fclose(f2);
    remove(s1);
    rename("izmena.txt", s1);
    f1=fopen(s1, "a");
    fseek(f1, 0, SEEK_END);
    for(int t=0; t<granica; ++t)
    {
        fprintf(f1, "%s,",simptom[t].ime);
    }
    fclose(f1);
}
void izbrisatiSimptom(char* s1)
{
    struct Simptom* simptomi;
    int b=izdvajanjeSimptoma(s1, &simptomi);

    for(int t=0; t<b; ++t)
    {
        printf("%i. %s\n", t+1, simptomi[t].ime);
    }
    printf("Koliko simptoma zelite da izbrisete?\n");
    int delbroj;
    scanf("%i", &delbroj);
    if(delbroj<0 || delbroj>b)
    {
        while(delbroj<0 || delbroj>b)
        {
            printf("Koliko simptoma zelite da izbrisete?\n");
            scanf("%i", &delbroj);
        }
    }
    if(delbroj==0)
        return;
    int delbrojevi[delbroj];
    for(int t=0; t<delbroj; ++t)
    {
        printf("Unesite broj sa liste od %i. simptoma kog zelite da izbrisete: ",t+1);
        scanf("%i", &delbrojevi[t]);
        if(1>delbrojevi[t] || delbrojevi[t]>b)
        {
            while(1>delbrojevi[t] || delbrojevi[t]>b)
            {
                printf("Unesite broj sa liste od %i. simptoma kog zelite da izbrisete: ",t+1);
                scanf("%i", &delbrojevi[t]);
            }
        }
        for(int h=0; h<t; ++h)
        {
            if(delbrojevi[h]==delbrojevi[t])
            {
                while(delbrojevi[h]!=delbrojevi[t])
                {
                    printf("Unesite broj sa liste od %i. simptoma kog zelite da izbrisete: ",t+1);
                    scanf("%i", &delbrojevi[t]);
                    if(1>delbrojevi[t] || delbrojevi[t]>b)
                    {
                        while(1>delbrojevi[t] || delbrojevi[t]>b)
                        {
                            printf("Unesite broj sa liste od %i. simptoma kog zelite da izbrisete: ",t+1);
                            scanf("%i", &delbrojevi[t]);
                        }
                    }
                }
            }
        }
    }
    FILE* f1=fopen(s1, "r");
    FILE* f2=fopen("izmena.txt", "w");
    char s2[1000];
    fseek(f1, 0, SEEK_SET);
    while(fscanf(f1, " %[^\n]", s2)!=EOF)
    {
        if(strstr(s2, "Broj pojavljivanja u poslednjih godinu dana")!=NULL)
        {
            int check;
            fprintf(f2, "Broj pojavljivanja u poslednjih godinu dana:");
            for(int s=0; s<b; ++s)
            {

                check=0;
                for(int t=0; t<delbroj; ++t)
                {

                    if(delbrojevi[t]==s+1)
                    {
                        ++check;
                    }

                }
                if(check==0)
                {

                    fprintf(f2, "%i,",simptomi[s].pojavljivanje);
                }
            }
            fprintf(f2,"\n");
        }
        else if(strstr(s2, "Simptomi")!=NULL)
        {
            int check;
            fprintf(f2, "Simptomi:");
            for(int s=0; s<b; ++s)
            {
                check=0;

                for(int t=0; t<delbroj; ++t)
                {

                    if(delbrojevi[t]==s+1)
                    {
                        ++check;
                    }

                }
                if(check==0)
                {

                    fprintf(f2, "%s,",simptomi[s].ime);
                }
            }
        }
        else
        {
            fprintf(f2, "%s\n", s2);
        }
    }

    fclose(f1);
    fclose(f2);
    remove(s1);
    rename("izmena.txt", s1);
}
void izmenitiSimptom(char* s1)
{
    printf("Zelite li da: 1.dodate simptome 2. izbrisete simptome 3. izbrisete i dodate simptome?");
    int f;
    scanf("%i", &f);
    if(f<1 || f>3)
    {
        while(f<1 || f>3)
        {
            printf("Zelite li da: 1.dodate simptome 2. izbrisete simptome 3.izbrisete i dodate simptome?");
            scanf("%i", &f);
        }
    }
    if(f==1)
    {
        dodatiSimptom(s1);
    }
    if(f==2)
    {
        izbrisatiSimptom(s1);
    }
    if(f==3)
    {
        izbrisatiSimptom(s1);
        dodatiSimptom(s1);
    }
}
void IzmenaBolesti()
{
    int broj=0;
    int* spisak;
    Pretraga(&broj, &spisak);

    char s1[1000];
    if(broj==0)
        return;
    if(broj==1)
    {

        sprintf(s1,"%i.txt", *spisak);

    }
    else
    {
        printf("Izaberite indeks bolesti koji zelite da izmenite: ");
        int indeks;
        scanf("%i", &indeks);
        if(indeks<1 || indeks>broj)
        {
            while(indeks<1 || indeks>broj)
            {
                printf("Izaberite indeks bolesti koji zelite da izmenite: ");
                scanf("%i", &indeks);
            }
        }
        sprintf(s1,"%i.txt", spisak[indeks-1]);
    }
    FILE* f1=fopen(s1, "r");
    char s2[1000];
    char s3[1000];
    while(fscanf(f1," %[^\n]",s2)!=EOF)
    {
        if(strstr(s2,"Naziv")!=NULL)
        {
            break;
        }
    }
    fclose(f1);
    int a=0;
    while(s2[a]!=':')
    {
        ++a;
    }
    ++a;
    int b=0;
    for(a=a; a<strlen(s2); ++a)
    {
        s3[b]=s2[a];
        ++b;
    }
    s3[b]='\0';
    printf("Sta zelite da promenite kod %s-a?(1.Naziv, 2.Simptome, 3.I naziv i simptome, 4.Nista): ",s3);
    int i;
    scanf("%i", &i);
    if(i<1 || i>4)
    {
        while(i<1 || i>4)
        {
            printf("Sta zelite da promenite kod %s-a?(1.Naziv, 2.Simptome, 3.I naziv i simptome, 4.Nista): ",s3);
            scanf("%i", &i);
        }
    }
    if(i==1)
    {
        upisatiNaziv(s1);

    }
    else if(i==2)
    {
        izmenitiSimptom(s1);
    }
    else if(i==3)
    {
        upisatiNaziv(s1);
        izmenitiSimptom(s1);
    }
    else if(i==4)
    {
        return;
    }

}

void brisanjeBolesti()
{
    int broj=0;
    int* spisak;
    Pretraga(&broj, &spisak);
    char s1[1000];
    if(broj==0)
        return;
    else if(broj==1)
    {
        sprintf(s1, "%i", *spisak);
    }
    else
    {
        printf("Izaberite indeks bolesti koju zelite da izbrisete: ");
        int index;
        scanf("%i", &index);
        if(index<1 || index>broj)
        {
            while(index<1 || index>broj)
            {
                printf("Izaberite indeks bolesti koju zelite da izbrisete: ");
                scanf("%i", &index);
            }
        }
        sprintf(s1,"%i",spisak[index-1]);
    }

    char s2[1000];
    FILE* f1=fopen("spisakbolesti.txt","r");
    fseek(f1,0,SEEK_SET);
    while(fscanf(f1," %[^\n]",s2)!=EOF)
    {
        if(strstr(s2,s1)!=NULL)
            break;
    }
    fclose(f1);
    int a=0;
    while(s2[a]!='-')
        ++a;
    ++a;
    char s3[1000];
    int b=0;
    for(a=a; a<strlen(s2); ++a)
    {
        s3[b]=s2[a];
        ++b;
    }
    s3[b]='\0';
    printf("Da li zelite da izbrisete %s?(1.DA 2.NE): ",s3);
    int i;
    scanf("%i", &i);
    if(i<1 || i>2)
    {
        while(i<1 || i>2)
            printf("Da li zelite da izbrisete %s?(1.DA 2.NE): ",s3);
        scanf("%i", &i);
    }

    if(i==2)
    {
        return;
    }
    else
    {
        FILE* f2=fopen("izmena.txt","w");
        FILE* f1=fopen("spisakbolesti.txt","r");
        while(fscanf(f1, " %[^\n]",s2)!=EOF)
        {
            fseek(f2,0,SEEK_END);
            int kraj=ftell(f2);
            if(strstr(s2,s1)!=NULL)
                continue;
            if(kraj!=0)
                fprintf(f2,"\n");
            fputs(s2,f2);
        }
        fclose(f2);
        fclose(f1);
        remove("spisakbolesti.txt");
        rename("izmena.txt", "spisakbolesti.txt");
        char s3[1000];
        sprintf(s3,"%s.txt",s1);
        remove(s3);
    }
}
struct Spisak
{
    char naziv[1000];
    float koeficijent;
    struct Spisak* next;
};
void push(struct Spisak** head, char* s1, float koeficijent)
{
    struct Spisak* novaBolest=(struct Spisak*)malloc(sizeof(struct Spisak));
    int i;
    for( i=0; i<strlen(s1); ++i)
    {
        novaBolest->naziv[i]=s1[i];
    }
    novaBolest->naziv[i]='\0';
    novaBolest->koeficijent=koeficijent;
    novaBolest->next=NULL;
    if(*head==NULL)
    {
        *head=novaBolest;
        (*head)->next=NULL;
        return;
    }
    if((*head)->koeficijent<=koeficijent)
    {
        novaBolest->next=*head;
        *head=novaBolest;
        return;
    }
    else
    {
        struct Spisak* start=*head;
        while(start->koeficijent>=koeficijent)
        {
              if(start->next==NULL)
            {
                novaBolest->next=NULL;
                start->next=novaBolest;
                return;
            }
            start=start->next;

        }
        novaBolest->next=start->next;
        start->next=novaBolest;

    }
}
void printPriorityQueue(struct Spisak* head)
{
    while(head!=NULL)
    {
        if(head->koeficijent>=35)
            printf("%s, ",head->naziv);
        struct Spisak* temp=head;
        head=head->next;
        free(temp);
    }
    printf("\n");
}
void Dijagnoza()
{
    struct Simptom* unetiSimptomi;
    int brojUnetihSimptoma=upisatiSimptome(&unetiSimptomi);
    FILE* f1=fopen("spisakbolesti.txt", "r");
    if(f1==NULL)
    {
        printf("Nema nijedne bolesti!");
        return;
    }
    if(f1!=NULL)
    {
        fseek(f1, 0, SEEK_END);
        int kraj=ftell(f1);
        if(0==kraj)
        {
            printf("Nema nijedne bolesti!\n");
            return;
        }
    }
    fseek(f1, 0, SEEK_SET);
    char s1[1000];
    struct Spisak* head=NULL;
    while(fscanf(f1, " %[^\n]", s1)!=EOF)
    {
        int ID;
        sscanf(s1, " %i-", &ID);
        char s2[1000];
        sprintf(s2, "%i.txt", ID);
        FILE* f2=fopen(s2, "r");
        char s3[1000];
        int broj=0;
        char naziv[1000];
        while(fscanf(f2, " %[^\n]", s3)!=EOF)
        {
            if(strstr(s3,"Naziv")!=NULL)
            {
                int a=0;
                while(s3[a]!=':')
                    ++a;
                ++a;
                int b=0;
                for(a=a; a<strlen(s3); ++a)
                {
                    naziv[b]=s3[a];
                    ++b;
                }
                naziv[b]='\0';
            }
            if(strstr(s3,"Tip:1")!=NULL)
            {
                ++broj;
            }
        }
        fclose(f2);
        struct Simptom* simptomi;
        int brojIzdvojenihSimptoma=izdvajanjeSimptoma(s2, &simptomi);
        float koeficijent=0;
        if(broj==0)
        {
            for(int t=0; t<brojIzdvojenihSimptoma; ++t)
            {
                int flag;
                for(int f=0; f<brojUnetihSimptoma; ++f)
                {
                    for(int n=0; simptomi[t].ime[n]!='\0'; ++n)
                    {
                        if(simptomi[t].ime[n]==unetiSimptomi[f].ime[n])
                            flag=0;
                        else
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(flag==0)
                        ++koeficijent;

                }
            }
        }

        if(broj==1)
        {
            for(int t=0; t<brojIzdvojenihSimptoma; ++t)
            {
                int flag;
                for(int f=0; f<brojUnetihSimptoma; ++f)
                {
                    for(int n=0; simptomi[t].ime[n]!='\0'; ++n)
                    {
                        if(simptomi[t].ime[n]==unetiSimptomi[f].ime[n])
                            flag=0;
                        else
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(flag==0 && unetiSimptomi[f].pojavljivanje>=simptomi[t].pojavljivanje)
                        ++koeficijent;
                }
            }
        }
        float posto=(koeficijent/brojIzdvojenihSimptoma)*100;
        push(&head, naziv, posto);
    }
    fclose(f1);
    free(unetiSimptomi);
    printPriorityQueue(head);
}


void meni()
{
    printf("_______BOLNICA_______________\n\n\n");
    int i=-1;
    while(i!=0)
    {
        printf("1. Dodavanje bolesti\n2. Prikazi sve bolesti\n3. Pretraga\n4.Izmena bolesti\n5. Brisanje bolesti\n6. Dijagnoza\n0. Kraj\n");
        scanf("%i",&i);
        switch(i)
        {
        case 1:
            dodavanjeBolesti();
            break;
        case 2:
            prikaz();
            break;
        case 3:
            PretragaBolesti();
            break;
        case 4:
            IzmenaBolesti();
            break;
        case 5:
            brisanjeBolesti();
            break;
        case 6:
            Dijagnoza();
            break;
        case 0:
            break;
        default:
            printf("Izabrali ste pogresnu opciju sa konzole!\n");
        }
    }
}
int main()
{

    meni();

    return 0;
}
