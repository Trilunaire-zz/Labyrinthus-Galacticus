#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h> //pour les sprites ;) //
#include "ecrire.h"

int chiffreActuel(SDL_Surface *Curseur, SDL_Surface *chiffres[], SDL_Rect positionNombre[], SDL_Rect positionCurseur);
int presenceChiffre(SDL_Surface *Curseur, SDL_Surface *chiffres[], SDL_Rect positionNombre[], SDL_Rect positionCurseur);

const int largeurCase = 64, hauteurCase = 64, tailleCadrillage = 10;
const int tailleChiffres = 72, tailleTitres = 35;
const SDL_Color NOIR = {0,0,0};
void dessinerCarte(int nombre_de_cases, int Xcase[], int Ycase[], SDL_Surface *ecran, SDL_Surface *cases[])
{
    //<DÉCLARATION PART>//
    int continuer = 1, i = 0;
    SDL_Event event;
    SDL_Rect positionCase;
    //</DECLARATION PART>//


    printf("Creation de la carte avec les fleches (pour l'instant ;) ) \n");
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));/* coloration de l'écran */


    for(i = 0; i != nombre_de_cases; i++)//on défini toutes les cases
    {
        cases[i] = IMG_Load("pictures/textures/sol.png");
    }
    positionCase.x = (ecran->w /2 - (cases[0]->w));
    positionCase.y = (ecran->h /2 - (cases[0]->h));


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
                i = nombre_de_cases;//i prends la valeur nombre_de_cases pour qu'on sorte de la boucle
                break;
            case SDL_KEYDOWN://si appuis sur une touche
                switch (event.key.keysym.sym)//recuperation de la valeur de la lettre pressé dans l'evenement "event"
                {
                case SDLK_UP:
                    positionCase.y = (positionCase.y-(cases[0]->h));
                    break;
                case SDLK_DOWN:
                    positionCase.y = (positionCase.y+(cases[0]->h));
                    break;
                case SDLK_RIGHT:
                    positionCase.x = (positionCase.x+(cases[0]->w));
                    break;
                case SDLK_LEFT:
                    positionCase.x = (positionCase.x-(cases[0]->w));
                    break;
                default:
                    break;
                }
                printf("Nbre de cases %d\n", i);
                /* Enlever les tableaux Xcases et Ycases et mettre un pointeur sur positionCase*/
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

void caseOK(int nombre_de_cases, int Xcase[], int Ycase[], int map2D[10][10])
{
    /* parcours chaque rangs d'abscisse , puis d'ordonnée */
    /* si il y a une case, la map2D prendra la valeur 1 au niveau de la position de la case dans le cadrillage */
    int i = 0, j = 0;


    for(i = 0; i < nombre_de_cases; i++)
    {
        /* divise la position de la case par 64 pour trouver son numero sur le cadrillage */
        map2D[(Xcase[i]/largeurCase)][(Ycase[i]/hauteurCase)] = 1; /* stocage de la présence d'une case en fonction de son numero au niveau de l'ordonné et de son abscisse */
        printf("map2D[%d][%d] = %d \n", Xcase[i]/largeurCase, Ycase[i]/hauteurCase, map2D[(Xcase[i]/largeurCase)][(Ycase[i]/hauteurCase)]);
    }


    //partie servant à verifier si il y a des bugs
    for(i = 0; i != tailleCadrillage; i++)
    {
        for(j = 0; j != tailleCadrillage; j++)
        {
            printf("%d", map2D[j][i]);
        }
        printf("\n");
    }
}

int entreCase(SDL_Surface *ecran) //penser a la gestion du debordement pour le curseur
{
    //on defini les varibles.
    char nombredeCases[3] = "  ", numero[2] = " ";
    int nombreCases = 0, tempsActuel = 0, tempsPrecedent = 0, tempsImageU = 0, tempsImageU1 = 0, continuer = 1, chiffre = 0, up = 1, i = 0, j = 0, k = 0;
    SDL_Surface *fond = NULL, *Banniere = NULL, *curseur = NULL, *nombreTapee = NULL, *consigne[2] = {NULL}, *fondAnime[3] = {NULL}, *chiffres[10] = {NULL};
    SDL_Rect positionFond, positionChiffreTapee, positionBanniere, positionFondAnime, positionCurseur, positionCurseurPrecedente, positionConsigne[2], positionNombre[10];
    SDL_Event event;
    SDL_Color noir = {0,0,0};

    //On les paramètres
    nombreTapee = ecrireSurEcran(nombredeCases, 85, noir);
    fond = IMG_Load("pictures/menu/BackgroundMenuCoins.png");
    curseur = IMG_Load("pictures/menu/Cursor.png");
    fondAnime[0] = IMG_Load("pictures/menu/1.png");
    fondAnime[1] = IMG_Load("pictures/menu/2.png");
    fondAnime[2] = IMG_Load("pictures/menu/3.png");
    consigne[0] = ecrireSurEcran("How many squares put you??", tailleTitres, noir);
    consigne[1] = ecrireSurEcran("between 20 and 50", tailleTitres, noir);

    for(i = 0; i <= 9;i++)
    {
        sprintf(numero, "%d", i);//convertis la valeur du int en char, avec chiffre un char
        chiffres[i] = ecrireSurEcran(numero, tailleChiffres, noir);
    }

    Banniere = SDL_CreateRGBSurface(SDL_HWSURFACE, 440, 100, 32, 0, 0, 0, 0);

    SDL_FillRect(Banniere, NULL, SDL_MapRGB(ecran->format, 204, 67, 53));//on colore la bannière

    //on positionne tous le basard
    positionFond.x = 0;
    positionFond.y = 0;
    positionCurseur.x = (ecran->w/2) - (curseur->w/2);
    positionCurseur.y = 300 + (chiffres[2]->h);
    positionBanniere.x = (ecran->w /2) - (Banniere->w /2);
    positionBanniere.y = 175;
    positionFondAnime.x = 28;//les dimentions à partir desquelles on a plus de bords
    positionFondAnime.y = 32;

    /*Trouver un moyen d'alleger cette écriture*/
    positionChiffreTapee.x = (ecran->w/2) - (nombreTapee->w/2);
    positionChiffreTapee.y = 175;
    positionConsigne[0].x = (ecran->w/2) - (consigne[0]->w/2);//on centre la consigne en x
    positionConsigne[0].y = 50;
    positionConsigne[1].x = (ecran->w/2) - (consigne[1]->w/2);//on centre la consigne en x
    positionConsigne[1].y = 50 + (consigne[0]->h);
    positionNombre[0].x = (ecran->w/2) - (chiffres[9]->w /2);
    positionNombre[0].y = 300 + (chiffres[1]->h) + (chiffres[4]->h) + (chiffres[7]->h);
    positionNombre[1].x = ((ecran->w /2) - 175 - (chiffres[1]->w /2));
    positionNombre[1].y = 300;
    positionNombre[2].x = (ecran->w /2) - (chiffres[2]->w /2);
    positionNombre[2].y = 300;
    positionNombre[3].x = ((ecran->w /2) + 175) - (chiffres[3]->w /2);
    positionNombre[3].y = 300;
    positionNombre[4].x = ((ecran->w /2) - 175- (chiffres[4]->w /2));
    positionNombre[4].y = 300 + (chiffres[1]->h);
    positionNombre[5].x = (ecran->w /2) - (chiffres[5]->w /2);
    positionNombre[5].y = 300 + (chiffres[2]->h);
    positionNombre[6].x = ((ecran->w /2) + 175) - (chiffres[6]->w /2);
    positionNombre[6].y = 300 + (chiffres[3]->h);
    positionNombre[7].x = ((ecran->w /2) - 175 - (chiffres[7]->w /2));
    positionNombre[7].y = 300 + (chiffres[1]->h) + (chiffres[4]->h);
    positionNombre[8].x = (ecran->w /2) - (chiffres[8]->w /2);
    positionNombre[8].y = 300 + (chiffres[2]->h) + (chiffres[5]->h);
    positionNombre[9].x = ((ecran->w /2) + 175) - (chiffres[9]->w /2);
    positionNombre[9].y = 300 + (chiffres[3]->h) + (chiffres[6]->h);


    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_BlitSurface(fond, NULL, ecran, &positionFond);
    SDL_BlitSurface(fondAnime[0], NULL, ecran, &positionFondAnime);
    SDL_BlitSurface(consigne[0], NULL, ecran, &positionConsigne[0]);
    SDL_BlitSurface(consigne[1], NULL, ecran, &positionConsigne[1]);
    SDL_BlitSurface(Banniere, NULL, ecran, &positionBanniere);
    SDL_BlitSurface(nombreTapee, NULL, ecran, &positionChiffreTapee);

    for(i = 0; i < 10; i++)
    {
        SDL_BlitSurface(chiffres[i], NULL, ecran, &positionNombre[i]);
    }

    SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur);
    SDL_Flip(ecran);


    while(continuer)
    {
        i = 0;
        while(i<3)
        {
            tempsActuel = SDL_GetTicks();
            tempsImageU = SDL_GetTicks();
            if(tempsActuel - tempsPrecedent > 20)
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
                                if(up){positionCurseur.y = positionCurseur.y - (chiffres[0]->h);}//up permet de bloquer la répétition de touches toutes le 10ms
                                up = 0;
                                break;
                            case SDLK_DOWN:
                                if(up){positionCurseur.y = positionCurseur.y + (chiffres[0]->h);}
                                up = 0;
                                break;
                            case SDLK_RIGHT:
                                if(up){positionCurseur.x = positionCurseur.x + 175;}
                                up = 0;
                                break;
                            case SDLK_LEFT:
                                if(up){positionCurseur.x = (positionCurseur.x - 175);}
                                up = 0;
                                break;
                            case SDLK_SPACE:
                                if(up)
                                {
                                    chiffre = chiffreActuel(curseur, chiffres, positionNombre, positionCurseur);
                                    if(k == 0)
                                        nombreCases = nombreCases + chiffre;
                                    else
                                        nombreCases = nombreCases*10 + chiffre;
                                    k++;
                                    sprintf(nombredeCases, "%d", nombreCases);//convertis la valeur du int en char, avec nombredeCases un char
                                    nombreTapee = ecrireSurEcran(nombredeCases, 85, noir);//réactualise la surface
                                    positionChiffreTapee.x = (ecran->w/2) - (nombreTapee->w/2);//recentre l'abscisse
                                }
                                up = 0;
                                break;
                            case SDLK_RETURN:
                                if(up)
                                {
                                    if(nombreCases <= 50 && nombreCases >= 20)
                                    {
                                        i = 3;
                                        continuer = 0;
                                    }
                                    else
                                    {
                                        nombreCases = 0;
                                        nombreTapee = ecrireSurEcran("invalid number", 50, noir);
                                        positionChiffreTapee.x = (ecran->w/2) - (nombreTapee->w/2);//recentre l'abscisse
                                    }
                                }
                                up = 0;
                                break;
                            case SDLK_ESCAPE:
                                i = 3;
                                continuer = 0;
                                up = 0;
                                break;
                            default:
                                continuer = 1;
                                break;
                        }
                            break;
                    case SDL_KEYUP:
                        up = 1;//comme ça l'utilisateur ne peux déplacer le curseur que appuis par appuis.
                        break;
                }
                if((tempsImageU - tempsImageU1 > 250) && presenceChiffre(curseur, chiffres, positionNombre, positionCurseur))
                {
                    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                    SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                    SDL_BlitSurface(fondAnime[i], NULL, ecran, &positionFondAnime);
                    SDL_BlitSurface(consigne[0], NULL, ecran, &positionConsigne[0]);
                    SDL_BlitSurface(consigne[1], NULL, ecran, &positionConsigne[1]);
                    SDL_BlitSurface(Banniere, NULL, ecran, &positionBanniere);
                    SDL_BlitSurface(nombreTapee, NULL, ecran, &positionChiffreTapee);
                    for(j = 0; j < 10; j++)
                    {
                        SDL_BlitSurface(chiffres[j], NULL, ecran, &positionNombre[j]);
                    }
                    SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur);
                    SDL_Flip(ecran);
                    i++; //on imcremente i pour changer l'image de fond.
                    positionCurseurPrecedente = positionCurseur;
                    tempsImageU1 = tempsImageU;
                }
                if((tempsImageU - tempsImageU1 > 250) && !presenceChiffre(curseur, chiffres, positionNombre, positionCurseur))
                {
                    positionCurseur = positionCurseurPrecedente;
                    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                    SDL_BlitSurface(fond, NULL, ecran, &positionFond);
                    SDL_BlitSurface(fondAnime[i], NULL, ecran, &positionFondAnime);
                    SDL_BlitSurface(consigne[0], NULL, ecran, &positionConsigne[0]);
                    SDL_BlitSurface(consigne[1], NULL, ecran, &positionConsigne[1]);
                    SDL_BlitSurface(Banniere, NULL, ecran, &positionBanniere);
                    SDL_BlitSurface(nombreTapee, NULL, ecran, &positionChiffreTapee);
                    for(j = 0; j < 10; j++)
                    {
                        SDL_BlitSurface(chiffres[j], NULL, ecran, &positionNombre[j]);
                    }
                    SDL_BlitSurface(curseur, NULL, ecran, &positionCurseur);
                    SDL_Flip(ecran);
                    i++; //on imcremente i pour changer l'image de fond.
                    tempsImageU1 = tempsImageU;
                }
                tempsPrecedent = tempsActuel;
                printf("up= %d\n", up);
                printf("nombre de cases: %d", nombreCases);
            }
            else{ SDL_Delay(20 - (tempsActuel-tempsPrecedent)); }
        }
    }
    SDL_FreeSurface (fond), (Banniere), (curseur), (nombreTapee), (consigne[0]), (consigne[1]), (fondAnime[0]), (fondAnime[1]), (fondAnime[2]);
    for(i = 0; i<10; i++)
    {SDL_FreeSurface(chiffres[i]);}
    return nombreCases;
}

int chiffreActuel(SDL_Surface *Curseur, SDL_Surface *chiffres[], SDL_Rect positionNombre[], SDL_Rect positionCurseur)
{
    int continuer = 1, i = 0;
    while(continuer)
    {
        //on prends la position centrée du curseur.
        if(((positionCurseur.x + (Curseur->w /2)) == (positionNombre[i].x + (chiffres[i]->w /2))) && (positionCurseur.y == positionNombre[i].y))
        //si la position du curseur coincide avec la position du nombre, alors on ferme la boucle et on prends la valeur du nombre
            continuer = 0;
        else
        i++;
    }
    return i;
}

int presenceChiffre(SDL_Surface *Curseur, SDL_Surface *chiffres[], SDL_Rect positionNombre[], SDL_Rect positionCurseur)
{
    int chiffreOk = 0, i = 0, continuer = 1;
    while(continuer)
    {
        printf("marche pour i = %d\n", i);
        if(i >= 10)//si on a verifié que la position centré du curseur ne correspondait à aucune position centré des nombres, on renvois 0;
            continuer = 0;
        else
        {
            if(((positionCurseur.x + (Curseur->w /2)) == (positionNombre[i].x + (chiffres[i]->w /2))) && (positionCurseur.y == positionNombre[i].y))
            {
                chiffreOk = 1;
                continuer = 0;
            }
            else
            {
                chiffreOk = 0;
                i++;
            }
        }
    }
    return chiffreOk;
}

//////il n'y a pas d'œuf de Paques ici/////////=> pour les lapins par ICI <=
