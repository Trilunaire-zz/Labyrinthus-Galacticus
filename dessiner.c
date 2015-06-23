/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////CE FICIER DOIT CONTENIR UNIQUEMENT LES FONCTIONS DE LA GESTION DES SDL_Surface//////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////TOUJOURS METTRE LE MODE ET LE BUT DE LA FONCTION EN COMMENTAIRE/////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SDL.h>
#include <SDL_image.h> //pour les sprites ;) //

void dessinerCarte(int nombre_de_cases, int Xcase[], int Ycase[], SDL_Surface *ecran, SDL_Surface *cases[])
{
    //<DÉCLARATION PART>//
    int continuer = 1, i = 0;
    SDL_Event event;
    SDL_Rect positionCase;
    //</DECLARATION PART>//
    printf("Creation de la carte avec les fleches (pour l'instant ;) ) \n");
    positionCase.x = (ecran->w /2 - 64);
    positionCase.y = (ecran->h /2 - 64);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));/* coloration de l'écran */

    for(i = 0; i != nombre_de_cases; i++)
    {
        cases[i] = IMG_Load("pictures/textures/sol.png");
    }

    i = 0;
    while(continuer)
    {
        while(i < nombre_de_cases)
        {
            //gestion des évenements
            SDL_WaitEvent(&event);//en attente d'évenement
            switch(event.type) /*test du type d'evenement & switch n°1 */
            {
                /* partie de la gestion de la sortie du programme */
                case SDL_QUIT: /* si c'est un évenement quitter*/
                    continuer = 0;
                    i = nombre_de_cases;
                    break;
                case SDL_KEYDOWN://si appuis sur une touche
                    switch (event.key.keysym.sym)//recuperation de la valeur de la lettre pressé dans l'evenement "event"
                    {
                        case SDLK_UP:
                            positionCase.y = (positionCase.y-64);
                            break;
                        case SDLK_DOWN:
                            positionCase.y = (positionCase.y+64);
                            break;
                        case SDLK_RIGHT:
                            positionCase.x = (positionCase.x+64);
                            break;
                        case SDLK_LEFT:
                            positionCase.x = (positionCase.x-64);
                            break;
                    }
                    printf("Nbre de cases %d  \n", i);
                    Xcase[i] = positionCase.x; //stocage de l'abscisse de la case
                    Ycase[i] = positionCase.y; //stocage de l'ordonnée de la case
                    SDL_BlitSurface(cases[i], NULL, ecran, &positionCase); /*blittage de la surface ici car il s'execute que si l'on appuis sur une touche*/
                    i++; /* i defini ici, car il s'incremente UNIQUEMENT si une touche est APPUYÉ, ET NON RELACHÉE */
                    SDL_Flip(ecran);//raffraichissement de l'écran
                    break;
            }
        }
        continuer = 0;
        printf("fin de la creation de la carte\n");
    }
}

//////il n'y a pas d'œuf de Paques ici/////////=> pour les lapins par ICI <=
