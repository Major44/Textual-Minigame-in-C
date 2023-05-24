#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>

#define strcasecmp _stricmp

/*
BUT DU JEU : L'objectif du jeu est de trouver un mot secret avec un nombre de tentative limité, fournir le score et le niveau du joueur.
L'utilisateur aura ensuite une chance de trouver un trésor en devinant la position (aléatoire) du trésor entre 1 et 10.
*/


//fonction pour tester si l'age saisi est un chiffre/nombre ou une chaine de caractère, la fonction utilisé est la fonction "strtol"
int isInteger(const char* chaineCaractere) {
    if (chaineCaractere == NULL || *chaineCaractere == '\0' || isspace(*chaineCaractere)) {
        return 0;
    }
    char* correct;
    strtol(chaineCaractere, &correct, 10);

    return (*correct == '\0');
}
int main() {

    //Déclaration des variables

    char motSecret[5][10] = { "Secret", "Soleil", "Terre", "Mars", "Paris" }; // initialisation des mots secrets dans une liste

    char motJoueur[10];

    char indice[100] = "Si vous lavez, vous voulez le partager. Si vous le partagez, vous ne l'avez plus !";

    int nbTentatives = 0;

    int maxTentatives = 5;

    int scoreJoueur = 0;

    int niveauJoueur = 1;

    char nomJoueur[20];

    char ageJoueur[10];

    char meilleurJoueur[20] = "Personne"; // initialisation du meilleur joueur

    int meilleurScore = 0; //initialisation du score du joueur

    int i;

    //Parcours des 26 lettres pour trouver les caractères composant le mot

    char lettresTrouvees[26];
    for (i = 0; i < 26; i++) {
        lettresTrouvees[i] = ' ';
    }

    srand(time(NULL)); // Initialisation pour les nombres aléatoires avec la fonction srand
    int tresorTrouve = 0;
    int positionTresor = rand() % 10 + 1;   // Position aléatoire du trésor entre 1 et 10


    // Debut de l'execution du Jeu

    printf("== Mini jeu : DEVINE LE MOT SECRET ==\n");

    printf("Un mot secret est enregistre dans la base. Maintenant, vous allez essayez de le DEVINER !\n");
    printf("*** Pour vous aider, voici un indice : %s ***\n", indice);

    printf("Entrez votre nom : ");
    scanf("%s", nomJoueur);

    while (1) {
        printf("Entrez votre Age : ");
        scanf("%s", ageJoueur);

        if (!isInteger(ageJoueur)) {
            printf("L'age saisi n'est pas un entier valide.\n");
            continue;
        }

        break;
    }

    int age = atoi(ageJoueur); //Transforme la chaine de caractére en une valeur numérique

    while (1) {
        printf("Devinez le mot : ");
        scanf("%s", motJoueur);

        int motTrouve = 0;
        for (i = 0; i < 5; i++) {
            if (strcasecmp(motJoueur, motSecret[i]) == 0) {                  //fonction "strcasecmp" permet de comparer 2 chaines en ignorant la casse. 
                motTrouve = 1;
                break;
            }
        }
        if (motTrouve) {
            printf("FÉLICITATIONS, vous avez trouve le mot !\n");
            printf("Relancez le JEU pour jouer a nouveau !\n");

            scoreJoueur += 10;
            if (scoreJoueur > meilleurScore) {

                meilleurScore = scoreJoueur;
                strcpy(meilleurJoueur, nomJoueur);
            }

            printf("Votre score actuel : %d\n", scoreJoueur);
            printf("Meilleur score : %d (Joueur : %s)\n", meilleurScore, meilleurJoueur);

            break;
        }
        else {
            printf("Ce n'est pas le mot secret. Essayez encore.\n");

            nbTentatives++;
            if (nbTentatives >= maxTentatives) {

                printf("Nombre maximum de tentatives atteint.\n");

                printf("Relancez le JEU pour jouer a nouveau !\n");

                break;
            }
        }
    }

    if (nbTentatives < maxTentatives) {

        printf("Vous avez une chance de trouver un tresor !\n");

        printf("Essayez de deviner la position du tresor (entre 1 et 10) : ");

        int positionDevinee;

        scanf("%d", &positionDevinee);

        if (positionDevinee == positionTresor) {

            printf("FELICITATIONS, vous avez trouve le trésor !\n");

            scoreJoueur += 20;

            printf("Votre score actuel : %d\n", scoreJoueur);

            tresorTrouve = 1;
        }
        else {

            printf("Dommage, vous navez pas trouver le tresor.\n");
        }
    }
    if (tresorTrouve) {

        printf("Bravo ! Vous avez atteint un nouveau niveau.\n");

        niveauJoueur++;

        printf("Votre niveau actuel : %d\n", niveauJoueur);
    }

    return 0;
}
