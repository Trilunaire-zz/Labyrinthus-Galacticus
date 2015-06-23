#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h> //pour la gestion du menu
#include "editeur.h"
#include "ecrire.h"
#include "menu.h"
#include "niveau.h"
#include "continuer.h"

#define LARG 640
#define HAUTEUR 640

int main(int argc, char *argv[])
{
    const char titre[]= "Labyrinthus Galacticus";
    int *Xcase = NULL, *Ycase = NULL; //deux tableaux de variables pour stocker les positions des cases pour le blittage
    int nombre_de_cases = 0, choix = 0;
    int map2D[10][10] = {{0},{0}}; //Map2D va servir à la verification de la présence des cases
    SDL_Surface *ecran = NULL, *cases = NULL;
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    ecran = SDL_SetVideoMode(LARG, HAUTEUR, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

    SDL_WM_SetCaption(titre, NULL);

    choix = menu(ecran, &nombre_de_cases);//on affiche le menu

    printf("nombre de cases fction main = %d\n", nombre_de_cases);

    cases = malloc(nombre_de_cases * sizeof(SDL_Surface));
    Xcase = malloc(nombre_de_cases * sizeof(int));
    Ycase = malloc(nombre_de_cases * sizeof(int));

    //lectureNiveau(map2D);    /*trouver un moyen d'afficher la console ou de demander à l'intérieur du jeu le nombre de cases*/
        //afficher les différents niveaux disponibles, récuperer la valeur du choix des niveaux puis lancer le niveau en question

    dessinerCarte(nombre_de_cases, Xcase, Ycase, ecran, cases);


    caseOK(nombre_de_cases, Xcase, Ycase, map2D);

    continu(nombre_de_cases, Xcase, Ycase, map2D, ecran, cases);

    ///////////////////////////////////////////////////////
    ////////////////////RELEASE THE MEMORIES///////////////
    ///////////////////////////////////////////////////////

    SDL_FreeSurface (ecran), (cases);
    free (Xcase), (Ycase);//liberation des variables allouées dynamiquement (pas besoins pour cases, déja libérée avec SDL_FreeSurface)


    SDL_Quit();
    return EXIT_SUCCESS;
}
