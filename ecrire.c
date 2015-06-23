#include <SDL.h>
#include <SDL_ttf.h>

SDL_Surface *ecrireSurEcran(char texte[], int taille, SDL_Color Color)
{
    SDL_Surface *texteEcran;

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de SDL_TTF: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    TTF_Font *police = NULL;//pointeur, qui ira vers un fichier
    police = TTF_OpenFont("fonts/pixel.ttf", taille); //chargement de la police en taille 22

    /* on utilise le rendu blended, qui utilise l'anti aliasing (pour la rondeur du texte) mais aussi la transparence du font */
    texteEcran = TTF_RenderText_Blended(police, texte, Color);

    TTF_CloseFont(police);
    TTF_Quit();
    return texteEcran;
}
