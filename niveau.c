#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "ecrire.h"

int choixNiveau(SDL_Surface *ecran)
{
    const int nbreDeChiffres = 20, tempsEntreDeuxImages = 250;
    char chiffre[2] = " ";
    int tempsPrecedent = 0, tempsActuel = 0, tempsImageU = 0, tempsImageU1 = 0, numeroNiveau = 0, continuer = 1, i = 0, j = 1, up = 0;
    SDL_Surface *bords = NULL, *texte[2] = {NULL}, *curseur = NULL, *carres = NULL, *fond[3] = {NULL}, *niveau[20] = {NULL};
    SDL_Rect positionFond, positionBord, positionCurseur, positionTexte[2], positionCases[20], positionNombre[20];
    SDL_Event event;
    SDL_Color black = {0,0,0};

    for(i = 0; i < nbreDeChiffres; i++)
    {
        sprintf(chiffre, "%d", j);//convertis la valeur du int en char, avec chiffre un char
        niveau[i] = ecrireSurEcran(chiffre, 26, black);
        j++;
    }

    texte[0] = ecrireSurEcran("choose your level", 40, black);
    texte[1] = ecrireSurEcran("with arrows", 38, black);
    bords = IMG_Load("pictures/menu/BackgroundMenuCoins.png");
    carres = SDL_CreateRGBSurface(SDL_HWSURFACE, 56, 56, 32, 0, 0, 0, 0);
    SDL_FillRect(carres, NULL, SDL_MapRGB(ecran->format, 204, 67, 53));
    fond[0] = IMG_Load("pictures/menu/1.png");
    fond[1] = IMG_Load("pictures/menu/2.png");
    fond[2] = IMG_Load("pictures/menu/3.png");
    //faire l'image du curseur avec les crochets à la taille 20-18

    positionBord.x = 0;
    positionBord.y = 0;
    positionFond.x = 28;
    positionFond.y = 32;
    positionTexte[0].x = (ecran->w/2) - (texte[0]->w/2);
    positionTexte[0].y = 50;
    positionTexte[1].x = (ecran->w/2) - (texte[1]->w/2);
    positionTexte[1].y = texte[0]->h + 50;
    for(i = 0; i<15; i++)
    {
        positionCases[i+2].x = (ecran->w /2) - (carres->w/2);
        positionCases[i+2].y = (positionTexte[1].y + texte[1]->h)+50 + 106*(i/5);
        positionNombre[i+2].x = (ecran->w /2) - (niveau[i+2]->w/2);
        positionNombre[i+2].y = positionCases[i+2].y + (carres->h/2) - (niveau[i+2]->h/2);
        positionCases[i+1].x = positionCases[i+2].x - 106;
        positionCases[i+1].y = positionCases[i+2].y;
        positionNombre[i+1].x = positionCases[i+1].x + (carres->w/2) - (niveau[i+1]->w/2);
        positionNombre[i+1].y = positionCases[i+1].y + (carres->h/2) - (niveau[i+1]->h/2);
        positionCases[i].x = positionCases[i+1].x - 106;
        positionCases[i].y = positionCases[i+2].y;
        positionNombre[i].x = positionCases[i].x + (carres->w/2) - (niveau[i]->w/2);
        positionNombre[i].y = positionCases[i].y + (carres->h/2) - (niveau[i]->h/2);
        positionCases[i+3].x = positionCases[i+2].x + 106;
        positionCases[i+3].y = positionCases[i+2].y;
        positionNombre[i+3].x = positionCases[i+3].x + (carres->w/2) - (niveau[i+3]->w/2);
        positionNombre[i+3].y = positionCases[i+3].y + (carres->h/2) - (niveau[i+3]->h/2);
        positionCases[i+4].x = positionCases[i+3].x + 106;
        positionCases[i+4].y = positionCases[i+2].y;
        positionNombre[i+4].x = positionCases[i+4].x + (carres->w/2) - (niveau[i+4]->w/2);
        positionNombre[i+4].y = positionCases[i+4].y + (carres->h/2) - (niveau[i+4]->h/2);
    }

    while(continuer)
    {
        i = 0;
        while(i<3)
        {
            tempsActuel = SDL_GetTicks();
            tempsImageU = SDL_GetTicks();
            if(tempsActuel - tempsPrecedent > 20)//si il s'est écoulé 20 ms
            {
                SDL_PollEvent(&event);
                switch(event.type)
                {
                    case SDL_QUIT:
                        i = 3;
                        continuer = 0;
                        break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_UP:
                                if(up)
                                    positionCurseur.y = positionCurseur.y - 106;
                                up = 0;
                                break;
                            case SDLK_DOWN:
                                if(up)
                                    positionCurseur.y = positionCurseur.y + 106;
                                up = 0;
                                break;
                            case SDLK_RIGHT:
                                if(up)
                                    positionCurseur.x = positionCurseur.x + 106;
                                up = 0;
                                break;
                            case SDLK_LEFT:
                                if(up)
                                    positionCurseur.x = positionCurseur.x - 106;
                                up = 0;
                            case SDLK_RETURN:
                                if(up)
                                {//valider le niveau choisi
                                    up = 0;
                                    i = 3;
                                    continuer = 0;
                                }
                                break;
                            default:
                                continuer = 1;
                                break;
                        }
                        break;
                    case SDL_KEYUP:
                        up = 1;
                        break;
                    default:
                        continuer = 1;
                        break;
                }
            }
            if(tempsImageU - tempsImageU1 >= tempsEntreDeuxImages)
            {
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                SDL_BlitSurface(bords, NULL, ecran, &positionBord);
                SDL_BlitSurface(fond[i], NULL, ecran, &positionFond);
                SDL_BlitSurface(texte[0], NULL, ecran, &positionTexte[0]);
                SDL_BlitSurface(texte[1], NULL, ecran, &positionTexte[0]);
                for(j = 0; j<nbreDeChiffres; j++)
                {
                    SDL_BlitSurface(carres, NULL, ecran, &positionCases[j]);
                    SDL_BlitSurface(niveau[j], NULL, ecran, &positionNombre[j]);
                }
                i++;
            }
            if(tempsImageU - tempsImageU1 < tempsEntreDeuxImages)
            {
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                SDL_BlitSurface(bords, NULL, ecran, &positionBord);
                SDL_BlitSurface(fond[i], NULL, ecran, &positionFond);
                SDL_BlitSurface(texte[0], NULL, ecran, &positionTexte[0]);
                SDL_BlitSurface(texte[1], NULL, ecran, &positionTexte[0]);
                for(j = 0; j<20; j++)
                {
                    SDL_BlitSurface(carres, NULL, ecran, &positionCases[j]);
                    SDL_BlitSurface(niveau[j], NULL, ecran, &positionNombre[j]);
                }
            }
            else
                SDL_Delay(20 - (tempsActuel-tempsPrecedent));
            //faire le cas du if>250 et le SDL_Delay pour les 20ms
        }
    }

    //liberer les surfaces
    return numeroNiveau;
}

void lectureNiveau(int map2D[10][10])
{
    int X = 0, Y = 0, i = 0, j = 0;
    char caractereActuel;
    FILE *fichier = NULL;

    fichier = fopen("niveaux/1", "r");
    do
    {
        caractereActuel = fgetc(fichier);//lit le premier caractère et implémente le curseur de 1, donc passe à la ligne automatiquement
        printf("%c", caractereActuel);
        map2D[X][Y] = caractereActuel - '0';//atoi permet de convertir la valeur d'un chiffre ascii en decimal
        X++;
        if(X > 9)//quand on passe une ligne
        {
            Y++;
            X = 0;//on remet X à 0, histoire de stocker le caractère au bon endroit
        }
    }while(caractereActuel != EOF);

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            printf("%d", map2D[j][i]);
        }
        printf("\n");
    }
    fclose(fichier);
    printf("lecture marche");
}

//cette fonction doit contabiliser le nombre de 1, pour allouer dynamiquement le nombre suffisant de case et de Xcase & Ycases
void convertirNiveau(int Xcase[], int Ycase[], int map2D[10][10], SDL_Surface *cases[])
{
    int i = 0, j = 0, k = 0, nombreCases = 0;
    //comptage ud nombre de Cases
    for(i = 0; i != 10; i++)
    {
        for(j = 0; j != 10; j++)
        {
            if(map2D[j][i] == 1)//on regarde si il y a une case
                nombreCases++;//si oui, on augment le nombre de cases
        }
    }
    printf("il y a %d cases\n", nombreCases);

    //allocation dynamique en fonction du nombre de cases

    printf("alloc dynamique marche");

    for(i = 0; i != 10; i++)
    {
        for(j = 0; j != 10; j++)
        {
            if(map2D[j][i] == 1)
            {
                Xcase[k] = j*64;//on stocke la position en abscisse de la case k en multipliant sa position /10 par 64.
                Ycase[k] = i*64;
                k++;
            }
        }
    }

    for(i = 0; i != 100; i++)
    {
        cases[i] = IMG_Load("pictures/textures/sol.png");
    }
}
