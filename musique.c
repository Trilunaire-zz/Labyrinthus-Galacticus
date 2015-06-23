#include <fmodex/fmod.h>
#include <stdio.h> /* pour la variable de type NULL */
#include <stdlib.h> /* pour la variable de type EXIT_FAILURE */

/*fonction de type fmod_sound, pour bien renvoyer la taille exact du pointeur, sinon, faute de segmentation,
 la taille du pointeur fmod_sound étant relatif a un fichier*/

FMOD_SOUND *lireMusique(const char FICHIER[], FMOD_SYSTEM *system, FMOD_SOUND *musique, FMOD_RESULT resultat)
{
 /* partie de la gestion de la musique */
    FMOD_System_Create(&system); //creation du pointeur, et parametrage de son type
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL); //initialisation de la bibliothèque (1 pour le nombre de canaux)

    /* On ouvre la musique */
    resultat = FMOD_System_CreateSound(system, FICHIER, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique); //le flag createstream permet de charger en streaming

    /* On vérifie si elle a bien été ouverte (IMPORTANT) */
    if (resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier ogg\n");
        exit(EXIT_FAILURE);
    }

    /* On active la répétition de la musique à l'infini */
    FMOD_Sound_SetLoopCount(musique, -1); /*-1 pour le nombre de répét = infini */

    /* On joue la musique */
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);

    return musique;
    /*fin */
}
