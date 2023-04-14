#include <stdio.h>
#include <stdlib.h>
#include "mode1.c"



int main(){
    int stop = 0;
    while (stop == 0) {
        system("cls");
        printf("Bienvenue sur mon jeu de snake !\n");
        printf("\n");
        printf("Ce jeu poss%cde 3 modes :\n", 138);
        printf("1. Mode facile\n");
        printf("2. Mode automatique\n");
        printf("3. Mode classique\n");
        printf("0. Quitter le jeu\n");

        int mode;
        char input[10];
        do {
            printf("\n");
            printf("Veuillez choisir un mode : ");
            scanf("%s", &input);

            if (isdigit(input[0])) { // Vérifier si le premier caractère est un chiffre
                mode = input[0] - '0'; // Convertir le caractère en entier
                if (mode< 0 || mode > 3) {
                    printf("\nOption invalide. Veuillez r%cessayer.\n", 130);
                }
            }else {
                printf("\nEntr%ce invalide. Veuillez entrer un nombre.\n", 130);
            }
        } while (mode <0 || mode >3);
        
        printf("\n");
        switch(mode){
            case 1:
                printf("Vous avez choisi le mode facile !\n");
                mode1();
                break;
            case 2:
                printf("Vous avez choisi le mode automatique !\n");
                break;
            case 3:
                printf("Vous avez choisi le mode classique !\n");
                break;
            case 0:
                printf("Vous avez choisi de quitter le jeu !\n");
                stop = 1;
                break;
            default:
                printf("Vous n'avez pas choisi un mode valide !\n");
                break;
        }
    }
}