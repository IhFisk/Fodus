#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "jeux.h"

// Sauvegarde la partie
void sauvegarde(map m,persoTab joueurs,int nbJoueurs,int numJ);

// Charge une partie
int sauvegarde_charger(char *cheminMap,char *cheminPers,map m,persoTab joueurs);

#endif