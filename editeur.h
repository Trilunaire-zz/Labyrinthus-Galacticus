#ifndef EDITEUR_H_INCLUDED
#define EDITEUR_H_INCLUDED

void dessinerCarte(int nombre_de_cases, int Xcase[], int Ycase[], SDL_Surface *ecran, SDL_Surface cases[]);
void caseOK(int nombre_de_cases, int Xcase[], int Ycase[], int map2D[10][10]);
int entreCase(SDL_Surface *ecran);

#endif // EDITEUR_H_INCLUDED
