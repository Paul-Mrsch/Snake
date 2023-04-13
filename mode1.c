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
    //variable gameover
    int GameOver = 0;

    //fonction pour créer le plateau de jeu
    int board[ROWS][COLS];
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            board[i][j] = 0;
        }
    }
    

    //fonction pour créer le serpent
    typedef struct Node {
        int x;
        int y;
        struct Node* next;
    } Node;

    typedef struct {
        Node* head;
        Node* tail;
    } Snake;

    void enqueue(Snake *snake, int x, int y) {
        Node *new_node = (Node *) malloc(sizeof(Node));
        new_node->x = x;
        new_node->y = y;
        new_node->next = NULL;
        board[x][y] = 1;
        if (snake->tail == NULL) {
            snake->head = new_node;
            snake->tail = new_node;
        } else {
            snake->tail->next = new_node;
            snake->tail = new_node;
        }
    }

    void dequeue(Snake *snake) {
        if (snake->head != NULL) {
            Node *old_head = snake->head;
            board[old_head->x][old_head->y] = 0;
            snake->head = old_head->next;
            free(old_head);

            if (snake->head == NULL) {
                snake->tail = NULL;
            }
        }
    }

    void print_snake(Snake *snake) {
        Node *current = snake->head;
        while (current != NULL) {
            printf("(%d, %d) ", current->x, current->y);
            current = current->next;
        }
        printf("\n");
    }

    void up_snake(Snake *snake, int row, int col){
        enqueue(snake, row-1, col);
        dequeue(snake);
    }
    
    void down_snake(Snake *snake, int row, int col){
        enqueue(snake, row+1, col);
        dequeue(snake);
    }

    void left_snake(Snake *snake, int row, int col){
        enqueue(snake, row, col-1);
        dequeue(snake);
    }

    void right_snake(Snake *snake, int row, int col){
        enqueue(snake, row, col+1);
        dequeue(snake);
    }

    void check_snake(Snake *snake, int row, int col){
        if (board[row][col] == 1){
            GameOver = 1;
        } else if (row == 0 || row == ROWS-1 || col == 0 || col == COLS-1){
            GameOver = 1;
        }
    }

    Snake snake = { NULL, NULL };

    // Ajouter trois parties du serpent à la liste
    enqueue(&snake, 10, 59);
    enqueue(&snake, 10, 60);
    enqueue(&snake, 10, 61);
    enqueue(&snake, 10, 62);
    enqueue(&snake, 10, 63);


    //position de la tete du serpent
    int headX = 10;
    int headY = 63;

    //fonction pour afficher le plateau de jeu avec un affichage d'une bordure autour
    void printBoard(char dir){
        system("cls");
        for (int i = 0; i < ROWS; i++){
            for (int j = 0; j < COLS; j++){
                if (board[i][j] == 1 && i == headX && j == headY){
                    printf("%c", dir);
                } else if (board[i][j] == 1){
                    printf("0");
                } else if (i == 0 || i == ROWS-1){
                    printf(".");
                } else if (j == 0 || j == COLS-1){
                    printf("|");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }

    

    printBoard('>');
    while (GameOver == 0){
        //fonction pour afficher le serpent
        printf("Direction : ");
        char direction;
        scanf("%c", &direction);
        switch (direction){
            case 'z':
                //fonction pour déplacer le serpent vers le haut
                check_snake(&snake, headX-1, headY);
                if (GameOver == 1){
                    break;
                }
                up_snake(&snake, headX, headY);
                headX--;
                printBoard('^');
                printf("\n");
                break;
            case 's':
                //fonction pour déplacer le serpent vers le bas
                check_snake(&snake, headX+1, headY);
                if (GameOver == 1){
                    break;
                }
                down_snake(&snake, headX, headY);
                headX++;
                printBoard('v');
                printf("\n");
                break;
            case 'q':
                //fonction pour déplacer le serpent vers la gauche
                check_snake(&snake, headX, headY-1);
                if (GameOver == 1){
                    break;
                }
                left_snake(&snake, headX, headY);
                headY--;
                printBoard('<');
                printf("\n");
                break;
            case 'd':
                //fonction pour déplacer le serpent vers la droite
                check_snake(&snake, headX, headY+1);
                if (GameOver == 1){
                    break;
                }
                right_snake(&snake, headX, headY);
                headY++;
                printBoard('>');
                printf("\n");
                break;

            case 'e':
                GameOver = 1;
                break;

            default:
                break;
        }
        direction = '0';
        if (GameOver == 1){
            printBoard('X');
        }

    }
    printf("\n");
    printf("Game Over\n");    

}