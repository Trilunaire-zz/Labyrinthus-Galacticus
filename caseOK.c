#include <SDL.h>
#include <stdlib.h>

//bug au niveau de cette fonction, pas le temps de le regler pour l'instant: quand on met une case en ordonné 0 ou en ordonné 9, le personnage peux passer à travers les cases: map2D[0][5] = 1, alors qu'il n'y a pas de case
//bug résolu: pas assez d'alocation au niveau de map2D: 9 cases allouée au lieu de 10 (ouf ^^)//
void caseOK(int nombre_de_cases, int Xcase[], int Ycase[], int map2D[10][10])
{
    /* parcours chaque rangs d'abscisse , puis d'ordonnée */
    /* si il y a une case, la map2D prendra la valeur 1 au niveau de la position de la case dans le cadrillage */
    int i = 0, j = 0;
    for(i = 0; i < nombre_de_cases; i++)
    {
        /* divise la position de la case par 64 pour trouver son numero sur le cadrillage */
        map2D[(Xcase[i]/64)][(Ycase[i]/64)] = 1; /* stocage de la présence d'une case en fonction de son numero au niveau de l'ordonné et de son abscisse */
        printf("map2D[%d][%d] = %d \n", Xcase[i]/64, Ycase[i]/64, map2D[(Xcase[i]/64)][(Ycase[i]/64)]);
    }
    //partie servant à verifier si il y a des bugs
    for(i = 0; i != 10; i++)
    {
        for(j = 0; j != 10; j++)
        {
            printf("%d", map2D[j][i]);
        }
        printf("\n");
    }
}
