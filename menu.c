#include <SDL.h>
#include <SDL_image.h>
#include <fmodex/fmod.h>
#include "musique.h"
#include "ecrire.h"
#include "editeur.h"

const int fps = 20, nombre_image = 3, temps_entre_image = 250;
const SDL_Color NOIR = {0,0,0};
const char chemin_musique[]= "sound/01 - Opening.ogg";

//réediter les deux images du curseur et aussi la position (10 petits px en + pour que ce ne soit pas collé)
int menu(SDL_Surface *ecran, int* nombre_de_cases)
{
    int i = 0, continuer = 1, tempsActuel = 0, tempsPrecedent = 0, tempsImageX1 = 0, tempsImageX2 = 0, up = 1, choix = 1;

    SDL_Surface *bords = NULL, *banniere = NULL, *jouerTxT = NULL, *editeur = NULL, *curseur[2] = {NULL}, *titre[2] = {NULL}, *fond[3] = {NULL};
    SDL_Rect positionFond, positionBord, positionBanniere[2], positionCurseur[2], positionTexte[2], positionTitre1, positionTitre2;
    SDL_Event event;


    jouerTxT = ecrireSurEcran("Play", 40, NOIR);
    editeur = ecrireSurEcran("Editor", 40, NOIR);
    titre[0] = ecrireSurEcran("Labyrinthus", 55, NOIR);
    titre[1] = ecrireSurEcran("Galacticus", 50, NOIR);
    curseur[0] = IMG_Load("pictures/menu/LSign.png");
    curseur[1] = IMG_Load("pictures/menu/RSign.png");
    fond[0] = IMG_Load("pictures/menu/1.png");
    fond[1] = IMG_Load("pictures/menu/2.png");
    fond[2] = IMG_Load("pictures/menu/3.png");
    bords = IMG_Load("pictures/menu/BackgroundMenuCoins.png");
    banniere = IMG_Load("pictures/menu/banière_300x120.png");


    positionFond.x = 28;//les dimentions à partir desquelles on a plus de bords
    positionFond.y = 32;
    positionBord.x = 0;
    positionBord.y = 0;
    positionBanniere[0].x = ((ecran->w /2) - (banniere->w /2));
    positionBanniere[0].y = ((ecran->h /2) - (banniere->h /2)) - 25;
    positionBanniere[1].x = ((ecran->w /2) - (banniere->w /2));
    positionBanniere[1].y = (ecran->h /2) + 25;
    positionTexte[0].x = ((ecran->w /2) - (jouerTxT->w /2));//on centre le texte
    positionTexte[0].y = positionBanniere[0].y + (banniere->h /2) - (jouerTxT->h /2); //on centre le texte en ordonnée en fonction de sa taille
    positionTexte[1].x = ((ecran->w /2) - (editeur->w /2));//on centre le texte
    positionTexte[1].y = positionBanniere[1].y + (banniere->h /2) - (editeur->h /2);
    positionCurseur[0].x = positionTexte[0].x - (curseur[0]->w) - 10;//on position le curseur gauche au niveau du début du mot
    positionCurseur[0].y = positionBanniere[0].y + (banniere->h /2) - (curseur[0]->h /2);
    positionCurseur[1].x = positionTexte[0].x + (jouerTxT->w) + 10;//on position le curseur au niveau de la fin du mot
    positionCurseur[1].y = positionBanniere[0].y + (banniere->h /2) - (curseur[1]->h /2);
    positionTitre1.x = ((ecran->w /2) - (titre[0]->w /2));
    positionTitre1.y = 50;
    positionTitre2.x = ((ecran->w /2) - (titre[1]->w /2));
    positionTitre2.y = 50 + (titre[0]->h);


    FMOD_SYSTEM *system = NULL; //allocation d'un pointeur vers un système qui va définir le comportement de la librairie
    FMOD_SOUND *musique = NULL; //variable allouant de la mémoire pour la musique
    FMOD_RESULT resultat = 0; //variable qui servira d'ouverture et de verification de la lecture du fichier
    musique = lireMusique(chemin_musique, system, musique, resultat);


    while(continuer)
    {
        i = 0;
        while(i<nombre_image)
        {
            tempsActuel = SDL_GetTicks();
            tempsImageX1 = SDL_GetTicks();

            if(tempsActuel - tempsPrecedent > fps)
            {
                SDL_PollEvent(&event);

                switch(event.type) /*test du type d'evenement & switch n°1 */
                {
                /* partie de la gestion de la sortie du programme */
                case SDL_QUIT: /* si c'est un évenement quitter*/
                    continuer = 0;
                    i = nombre_image;
                    SDL_Quit();
                    break;

                case SDL_KEYDOWN://si appuis sur une touche
                    switch (event.key.keysym.sym)//recuperation de la valeur de la lettre pressé dans l'evenement "event"
                    {
                    case SDLK_UP:
                        if(up)
                        {
                            positionCurseur[0].x = positionTexte[0].x - (curseur[0]->w) - 10;//on position le curseur gauche au niveau du début du mot
                            positionCurseur[0].y = positionBanniere[0].y + (banniere->h /2) - (curseur[0]->h /2);
                            positionCurseur[1].x = positionTexte[0].x + (jouerTxT->w) + 10;//on position le curseur au niveau de la fin du mot
                            positionCurseur[1].y = positionBanniere[0].y + (banniere->h /2) - (curseur[1]->h /2);
                            choix = 1;
                        }
                        up = 0;
                        break;

                    case SDLK_DOWN:
                        if(up)
                        {
                            positionCurseur[0].x = positionTexte[1].x - (curseur[0]->w) - 10;//on position le curseur gauche au niveau du début du mot
                            positionCurseur[0].y = positionBanniere[1].y + (banniere->h /2) - (curseur[0]->h /2);
                            positionCurseur[1].x = positionTexte[1].x + (editeur->w) + 10;//on position le curseur au niveau de la fin du mot
                            positionCurseur[1].y = positionBanniere[1].y + (banniere->h /2) - (curseur[1]->h /2);
                            choix = 2;
                        }
                        up = 0;
                        break;

                    case SDLK_RETURN: //si appuis sur ENTREE
                        if(up)
                        {
                            continuer = 0;
                            i = nombre_image;
                        }
                        up = 0; //on remet à 0 pour qu'il n'y ai pas de réétitions d'évenements
                        break;

                    case SDLK_ESCAPE:
                        if(up)
                        {
                            continuer = 0;
                            i = nombre_image;
                        }
                        up = 0;

                    default:
                        continuer = 1;
                        break;

                    }
                    break;

                case SDL_KEYUP:
                    up = 1;
                    break;
                }

                printf("tempsActuel = %d\n", tempsActuel);
                printf("tempsP = %d\n", tempsPrecedent);

                if(tempsImageX1 - tempsImageX2 > temps_entre_image)//si il s'est passé + de 250ms
                {
                    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                    SDL_BlitSurface(bords, NULL, ecran, &positionBord);
                    SDL_BlitSurface(fond[i], NULL, ecran, &positionFond);
                    SDL_BlitSurface(banniere, NULL, ecran, &positionBanniere[0]);
                    SDL_BlitSurface(banniere, NULL, ecran, &positionBanniere[1]);
                    SDL_BlitSurface(jouerTxT, NULL, ecran, &positionTexte[0]);
                    SDL_BlitSurface(editeur, NULL, ecran, &positionTexte[1]);
                    SDL_BlitSurface(curseur[0], NULL, ecran, &positionCurseur[0]);
                    SDL_BlitSurface(curseur[1], NULL, ecran, &positionCurseur[1]);
                    SDL_BlitSurface(titre[0], NULL, ecran, &positionTitre1);
                    SDL_BlitSurface(titre[1], NULL, ecran, &positionTitre2);
                    SDL_Flip(ecran);
                    printf("%d\n", i);
                    i++;
                    tempsImageX2 = tempsImageX1;
                }

                tempsPrecedent = tempsActuel;
            }

            else //si il ne s'est pas passé 20ms
            {
                printf("dans le else \n");
                SDL_Delay(fps - (tempsActuel - tempsPrecedent));//on met en pause pdt le temps qu'l reste
            }

            printf("tempsActuel = %d\n", tempsActuel);
            printf("tempsPrecedent = %d\n", tempsPrecedent);
        }
    }

    for(i = 0; i < 3; i++)
        SDL_FreeSurface(fond[i]);

    for(i = 0; i < 2; i++)
    {
        SDL_FreeSurface (curseur[i]);
        SDL_FreeSurface (titre[i]);
    }

    SDL_FreeSurface (bords), (banniere), (jouerTxT), (editeur);


    if(choix == 2)
        *nombre_de_cases = entreCase(ecran); //on envois le pointeur de nombre_de_cases pour modifier la variable dans le main


    FMOD_Sound_Release(musique);
    FMOD_System_Close(system);
    FMOD_System_Release(system);

    return choix;
}

