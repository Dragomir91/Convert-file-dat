#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

char taille2[8];

int convert_bi(int number,int i,char taille[8])
{
    int j  = 0;
   
        for(i = 8-1; i >= 0;i--)
        {
            
            if( ( number >> i) & 1)
            {
                //printf("1");
                taille[j] = '1';
            }
            else
            {
                //printf("0");
                taille[j] = '0';

            }
            j++;
        }

       
    return 1;
}


// conversion d'un nombre en base binaire de type float en base décimale
float convert_hex_to_float(char *tab,int signe, int exposant,int mantisse)
{
    int nombre;
    int nombre2;
    int nb_virgule;
    int inverse_pow = 0;
    float resultat;
    double puissance;
    double nb1;
    double nb2;
    double nombre3;
    double reel; 
    double decimal;
  
    // calcul de l'exposant

    puissance = 7;
    for(int i = 1; i < 9;i++)
    {
       //printf("%c",tab[i]);
        if(tab[i] == '0');
        else
        {
            
            nb1 = pow(2,puissance) + nb1;
            
        }
        puissance--;
    }

    //printf("exposant = %lf\n",nb1);
    nombre2 = (int)nb1 - 127;
    //printf("si nombre2 est > 0 sinon egal 0 = %d\n",nombre2);

    if(nombre2 > 0)
        {
            
            // nombre de bit pour le calcul : partie entiere
            nombre = (exposant + 1) + nombre2;
            
            nb1 = pow(2,(double)nombre2);
         
            for(int i = 1 + exposant; i <= (nombre - 1) ;i++)
            {   
                nombre2--; 
                
                if(tab[i] == '0');
                else
                {
                    puissance = (double)nombre2;
                    nb1 = pow(2,puissance) + nb1;
                }    
                //printf("\nnombre2 : %d\n",nombre2);
                  
            }
            // nombre entier
            reel = nb1 ;

            nb_virgule = nombre + (mantisse - nombre);

            //printf("nombre de bit compter : %d\n",nombre);
            // nombre de bit pour le calcul : parti decimal
            decimal  = 0.0;
            for(int i = nombre; i < 32 ;i++)
            {
              
                inverse_pow--;
                if(tab[i] == '0');
                else
                {   
                    puissance = (double)inverse_pow;
                    decimal = pow(2,puissance) + decimal;
                
                }
              
            }
            resultat = (float)reel + (float)decimal;
      
        }

    else
    {
        
        // nombre avant la virgule
        reel = pow(2,(double)nombre2);
        nombre2 = 0;
        nombre3 = 1;
        // calcul du nombre apres la virgule

        for(int i = 1+exposant; i <= 32 ;i++)
        {
            nombre2--;
            if(tab[i] == '0');
            else
            {
                puissance = (double)nombre2;
                nombre3 = pow(2,puissance) + nombre3;
            }     
            
        }
        
        // nombre entier
        decimal = (double)nombre3 ;
        resultat = (float)reel*1*(float)decimal;
    }
    return resultat;

}

int convert_hex_vers_asci(int nombre)
{
    int nb_ASCI;
    switch(nombre)
    {
        case 48: nb_ASCI = 0;
        break;
        case 49: nb_ASCI = 1;
        break;
        case 50: nb_ASCI = 2;
        break;
        case 51: nb_ASCI = 3;
        break;
        case 52: nb_ASCI = 4;
        break;
        case 53: nb_ASCI = 5;
        break;
        case 54: nb_ASCI = 6;
        break;
        case 55: nb_ASCI = 7;
        break;
        case 56: nb_ASCI = 8;
        break;
        case 57: nb_ASCI = 9;
        break;
    }
    return nb_ASCI;
}

struct Octet
{
    char octet1[8];
    char octet2[8];
    char octet3[8];
    char octet4[8];
};

int main()
{
    FILE *f, *fout, *fcoquille;
    struct Octet octet;
    char c1[100];
    char c2[100];
    char c3[100];
    char coquille[5];
    int date = 0;
    char tab_heure[12];
    int i = 17, j = 0, z = 17;
    int compare = 0;
    int compteur = 0;
    float volume = 0.0;
    float *VOLUME;
    unsigned int nb1, nb2, nb3, nb4, date1, date2, date3, date4, coq_chiffre1, coq_chiffre2, coq_chiffre3, coq_chiffre4;
    
    time_t raw;
    struct tm tm1;

    f=fopen("archives.dat","rb");
    fcoquille = fopen("vehicules.dat","rb");
    fout=fopen("Volume3.txt","w");
    
    if(f==NULL || fout == NULL)
    {
        printf("Erreur lors de l'ouverture d'un fichier");
        exit(1);
    }

    fprintf(fout,"Coquille |         Date         |   Volume\n");
    while(i< 511964 && j < 511964 && z < 511964)
    {
        fseek(f,i, SEEK_SET);
        fread(c1,4, sizeof(char), f);

        nb1 = (int)~c1[0]; 
        nb2 = (int)~c1[1];
        nb3 = (int)~c1[2];
        nb4 = (int)~c1[3];
        
        // si le nombre est  negative on ajoute plus 256 afin d'éviter d'avoir des données biaisées (volume carburant)

        compare = nb1;
        if(compare < 0){nb1 = nb1 + 256;}
        compare = nb2;
        if(compare < 0){nb2 = nb2 + 256;}
        compare = nb3;
        if(compare < 0){nb3 = nb3 + 256;}
        compare = nb4;
        if(compare < 0){nb4 = nb4 + 256;}
        //if(i == 4625){printf("\nb1 : %d\n, b2 : %d\n,b3 : %d\n,nb4 : %d\n",nb1,nb2,nb3,nb4);}
        convert_bi(nb4,8,octet.octet1);
        convert_bi(nb3,8,octet.octet2);
        convert_bi(nb2,8,octet.octet3);
        convert_bi(nb1,8,octet.octet4);

        volume = convert_hex_to_float(octet.octet1,0,8,23);

        fseek(f,j, SEEK_SET);
        fread(c2,4, sizeof(char), f);

        date1 = (int)~c2[0]; 
        date2 = (int)~c2[1];
        date3 = (int)~c2[2];
        date4 = (int)~c2[3];

        compare = date1;
        // si le nombre est  negative on ajoute plus 256
        /////////////////////////////////////////////////////
        // 
        if(compare < 0){date1 = date1 + 256;}
        compare = date2;
        if(compare < 0){date2 = date2 + 256;}
        compare = date3;
        if(compare < 0){date3 = date3 + 256;}
        compare = date4;
        if(compare < 0){date4 = date4 + 256;}

        date = date4*16*16*16*16*16*16 + date3*16*16*16*16 + date2*16*16 + date1;
        raw = date;
        tm1 = *localtime(&raw);

        //printf("date :%d\n", date);
        strftime(c2, 80, "%x -%I:%M%p",&tm1);
        //sprintf(tab_heure, "%d %d %d %d",nb4, nb3, nb3, nb1);
        /////////////////////////////////////////////////////////////////////////
        //Décode la coquille du bus contenu dans le fichier vehiculeX.dat
        fseek(fcoquille,z, SEEK_SET);
        fread(c3,4, sizeof(char), fcoquille);

        coq_chiffre1 = (int)~c3[0]; 
        coq_chiffre2 = (int)~c3[1];
        coq_chiffre3 = (int)~c3[2];
        coq_chiffre4 = (int)~c3[3];
        
        // si le nombre est  negative on ajoute plus 256 afin d'éviter d'avoir des données biasées 

        compare = coq_chiffre1;
        if(compare < 0){coq_chiffre1 = coq_chiffre1 + 256;}
        
        compare = coq_chiffre2;
        if(compare < 0){coq_chiffre2 = coq_chiffre2 + 256;}
        
        compare = coq_chiffre3;
        if(compare < 0){coq_chiffre3 = coq_chiffre3 + 256;}
        
        compare = coq_chiffre4;
        if(compare < 0){coq_chiffre4 = coq_chiffre4 + 256;}
        

        coq_chiffre1 = convert_hex_vers_asci(coq_chiffre1);
        coq_chiffre2 = convert_hex_vers_asci(coq_chiffre2);
        coq_chiffre3 = convert_hex_vers_asci(coq_chiffre3);
        coq_chiffre4 = convert_hex_vers_asci(coq_chiffre4);

        sprintf(coquille,"%d%d%d%d", coq_chiffre1, coq_chiffre2, coq_chiffre3, coq_chiffre4);
    
        fprintf(fout,"   %s  | %s    | %f\n", coquille,c2, volume);

        i+=512; 
        j+=512;
        z+=512;
        compteur++;
    }

    fclose(f);
    fclose(fout);
    fclose(fcoquille);
    printf("\nfin du programme");
    return 0;
}
