#include <SDL.h>
#include <SDL_image.h>
#include <fmodex/fmod.h>
#include "musique.h"
#include "ecrire.h"


const char CHEMIN_MUSIQUE[] = "sound/12 - Timeworn Pagoda.ogg";

int deplacementOK(SDL_Rect position);
int presenceCase(int map2D[10][10], SDL_Rect position);
int objectif(SDL_Rect positionObjectif, SDL_Rect position, SDL_Surface *ecran);

void continu(int nombre_de_cases, int Xcase[], int Ycase[], int map2D[10][10], SDL_Surface *ecran, SDL_Surface *cases[])
{
    /* <initialisation des variables> */
    int continuer = 1, i = 0;
    int Xlast = Xcase[0], Ylast = Ycase[0];
    SDL_Rect position, positionCase, positionHalo, positionObjectif;
    SDL_Surface *obj = NULL, *halo = NULL, *perso = NULL;
    SDL_Event event;
    /* </initialisation des variables> */

    position.x = Xcase[0];
    position.y = Ycase[0];
    positionObjectif.x = Xcase[nombre_de_cases - 1];//l'objectif sera placé à la dernière case (-1 car les tableaux ont une case 0, donc si le nombre de cases max est 50, l'abscisse de la case 50 est Xcase[49])
    positionObjectif.y = Ycase[nombre_de_cases - 1];

    perso = IMG_Load("pictures/sprite_normal.png");
    halo = IMG_Load("pictures/textures/halo1.png");
    obj = IMG_Load("pictures/objectif.png");

    SDL_EnableKeyRepeat(150,100);

    /* <partie musicale> */
    FMOD_SYSTEM *system = NULL; //allocation d'un pointeur vers un système qui va définir le comportement de la librairie
    FMOD_SOUND *musique = NULL; //variable allouant de la mémoire pour la musique
    FMOD_RESULT resultat = 0; //variable qui servira d'ouverture et de verification de la lecture du fichier

    musique = lireMusique(CHEMIN_MUSIQUE, system, musique, resultat);
    /* </partie musicale> */

    while(continuer)
    {
        //gestion des évenements
        if(objectif(positionObjectif, position, ecran) == 0)
        {
                SDL_WaitEvent(&event);/* on utilise PollEvent, et pas waitEvent, pour que le programme ne bloque pas: gestion des animations*/
                switch(event.type) /*test du type d'evenement & switch n°1 */
                {
                /* partie de la gestion de la sortie du programme */
                    case SDL_QUIT: /* si c'est un évenement quitter*/
                        continuer = 0;
                        break;
                    case SDL_KEYDOWN://si appuis sur une touche
                        switch (event.key.keysym.sym)//recuperation de la valeur de la lettre pressé dans l'evenement "event"
                        {
                        //la SDL_Image supporte les .gif, mais pas les animations :( on va devoir se debrouiller avec SDL_Delay et SDL_GetTicks
                            case SDLK_UP:
                                position.y = (position.y-64);
                                perso = IMG_Load("pictures/sprite_normal.png");
                            break;
                            case SDLK_DOWN:
                                position.y = (position.y+64);
                                perso = IMG_Load("pictures/sprite_normal.png");
                            break;
                            case SDLK_RIGHT:
                                position.x = (position.x+64);
                                perso = IMG_Load("pictures/deplacement/deplacementR.png");
                            break;
                            case SDLK_LEFT:
                                position.x = (position.x-64);
                                perso = IMG_Load("pictures/deplacement/deplacementL.png");
                            break;
                            case SDLK_ESCAPE:
                                continuer = 0;
                            break;
                            default:
                                continuer = 1;
                                break;
                        }
                        break;
                }
                    /*gestion du déplacemenet sur un cadrillage */
                if(deplacementOK(position) && presenceCase(map2D, position))
                {
                    printf("%d\n", position.x);
                    printf("%d\n", position.y);
                    positionHalo.x = position.x - 608; //la moitié de l'image de 1280*1280, moins la moitié du personnage (64/2), pour centrer le halo sur le perso
                    positionHalo.y = position.y - 608;
                    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));/* coloration de l'écran */
                    for(i = 0; i != nombre_de_cases; i++) //blittage des cases
                    {
                        positionCase.x = Xcase[i];
                        positionCase.y = Ycase[i];
                        SDL_BlitSurface(cases[i], NULL, ecran, &positionCase);
                    }
                    SDL_BlitSurface(obj, NULL, ecran, &positionObjectif);
                    SDL_BlitSurface(perso, NULL, ecran, &position);
                    SDL_BlitSurface(halo, NULL, ecran, &positionHalo);
                    SDL_Flip(ecran);
                    Xlast = position.x;
                    Ylast = position.y;
                }
                else
                {
                    position.x = Xlast;
                    position.y = Ylast;
                }
        }
        else
        {
            positionHalo.x = position.x - 608; //la moitié de l'image de 1280*1280, moins la moitié du personnage (64/2), pour centrer le halo sur le perso
            positionHalo.y = position.y - 608;
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));/* coloration de l'écran */
            for(i = 0; i != nombre_de_cases; i++) //blittage des cases
            {
                positionCase.x = Xcase[i];
                positionCase.y = Ycase[i];
                SDL_BlitSurface(cases[i], NULL, ecran, &positionCase);
            }
            SDL_BlitSurface(obj, NULL, ecran, &positionObjectif);
            SDL_BlitSurface(halo, NULL, ecran, &positionHalo);
            SDL_Flip(ecran);
            //on montre seulement la coupe//
            SDL_Delay(1000);
            objectif(positionObjectif, position, ecran);
            SDL_Flip(ecran);
            SDL_Delay(2000);
            continuer = 0;
        }
    }

    /*pas besoin de commenter ce code*/
    FMOD_Sound_Release(musique);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    SDL_FreeSurface (obj), (halo), (perso);
}




int deplacementOK(SDL_Rect position) //permettra la gestion des colisions
{
    //int X = 0, Y = 0;
    int deplacement = 0;
    if ((position.x > 576 || position.y > 576) || (position.x < 0 || position.y < 0)) /* on verifie si le joueur n'est pas au bord de l'ecran */
        deplacement = 0; //576 = 640-64
    else
        deplacement = 1;
    return deplacement;
}



int presenceCase(int map2D[10][10], SDL_Rect position)
{
    int CASE = 0;
    if(map2D[position.x/64][position.y/64] == 1)
        CASE = 1;
    else
        CASE = 0;
    printf("Case: %d\n", CASE);
    printf("Map2D[%d][%d]: %d\n", position.x/64, position.y/64, map2D[position.x/64][position.y/64]);
    return CASE;
}




int objectif(SDL_Rect positionObjectif, SDL_Rect position, SDL_Surface *ecran)
{
    int victoire = 0;
    char gagne[] = "Victoire!!";
    SDL_Color couleurBlanche = {255,255,255};//initialisation d'une couleur blanche pour colorer la police
    SDL_Surface *win = NULL;
    SDL_Rect positionTxt;
    if(position.x == positionObjectif.x && position.y == positionObjectif.y) //si le personnage est sur la case de l'objectif
    {
        win = ecrireSurEcran(gagne, 60, couleurBlanche);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));/* coloration de l'écran */
        positionTxt.x = (ecran->w /2) - (win->w /2);
        positionTxt.y = (ecran->h /2) - (win->h /2);
        SDL_BlitSurface(win, NULL, ecran, &positionTxt);
        victoire = 1; //il gagne
    }
    else //sinon, il ne se passe rien
    {
        victoire = 0;
    }
    printf("victoire = %d\n", victoire); //pour les test à la console
    return victoire;
}
