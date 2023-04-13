/*
I : Un snake qui ne bouge pas tant que l'user n'a pas choisi ou aller

    * une structure de données pour stocker les coordonnées de la tête du serpent
    * une structure de données pour stocker les coordonnées du corps du serpent
    * une structure de données pour stocker les coordonnées de la nourriture
    * une fonction pour afficher le serpent
    * une fonction pour afficher la nourriture
    * une fonction pour déplacer le serpent
    * une fonction pour déplacer la nourriture
    * une fonction pour vérifier si le serpent a mangé la nourriture
    * une fonction pour vérifier si le serpent est mort
    * une fonction pour vérifier si le serpent a atteint la fin du jeu
    * une fonction pour gérer les entrées clavier

*/

#include <stdio.h>
#include <stdlib.h>
#define ROWS 20
#define COLS 200

void mode1(){
    //fonction pour créer le plateau de jeu
    char board[ROWS][COLS];
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            board[i][j] = 0;
        }
    }
    //fonction pour afficher le plateau de jeu avec un affichage d'une bordure autour

    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            if (i == 0 || i == ROWS-1){
                printf(".");
            } else if (j == 0 || j == COLS-1){
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }


    bool GameOver = false;

    while (!GameOver){
        
    }    

}