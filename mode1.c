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
#define COLS 20

void mode1(){
    //variable gameover
    int GameOver = 0;

    //position de la tete du serpent
    int headX = 10;
    int headY = 14;

    //variable pour savoir si la pomme est mangée
    int on_apple = 0;

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
        if (on_apple == 1){
            on_apple = 0;
        } else {
            dequeue(snake);
        }
        headX--;
    }
    
    void down_snake(Snake *snake, int row, int col){
        enqueue(snake, row+1, col);
        if (on_apple == 1){
            on_apple = 0;
        } else {
            dequeue(snake);
        }
        headX++;
    }

    void left_snake(Snake *snake, int row, int col){
        enqueue(snake, row, col-1);
        if (on_apple == 1){
            on_apple = 0;
        } else {
            dequeue(snake);
        }
        headY--;
    }

    void right_snake(Snake *snake, int row, int col){
        enqueue(snake, row, col+1);
        if (on_apple == 1){
            on_apple = 0;
        } else {
            dequeue(snake);
        }
        headY++;
    }

    void apple(){
        int appleX = rand() % (ROWS-2) + 1;
        int appleY = rand() % (COLS-2) + 1;
        board[appleX][appleY] = 2;
    }

    void check_snake(Snake *snake, int row, int col){
        if (board[row][col] == 1){
            GameOver = 1;
        }
    }

    void check_apple(Snake *snake, int row, int col){
        if (board[row][col] == 2){
            on_apple = 1;
            apple();
        }
    }

    void check_gameover(Snake *snake, int row, int col){
        if (row == 0 || row == ROWS-1 || col == 0 || col == COLS-1){
            GameOver = 1;
        }
    }

    Snake snake = { NULL, NULL };

    void check(int row, int col){
        check_snake(&snake, row, col);
        check_apple(&snake, row, col);
        check_gameover(&snake, row, col);
    }

   

    // Ajouter trois parties du serpent à la liste
    enqueue(&snake, 10, 10);
    enqueue(&snake, 10, 11);
    enqueue(&snake, 10, 12);
    enqueue(&snake, 10, 13);
    enqueue(&snake, 10, 14);


    //fonction pour afficher le plateau de jeu avec un affichage d'une bordure autour
    void printBoard(char dir){
        system("cls");
        for (int i = 0; i < ROWS; i++){
            for (int j = 0; j < COLS; j++){
                if (board[i][j] == 1 && i == headX && j == headY){
                    printf("%c", dir);
                } else if (board[i][j] == 1){
                    printf("0");
                } else if (board[i][j] == 2){
                    printf("\033[1;31m");
                    printf("X");
                    printf("\033[0m");
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

    apple();
    printBoard('>');
    while (GameOver == 0){
        //fonction pour afficher le serpent
        printf("Direction : ");
        char direction;
        scanf("%c", &direction);
        switch (direction){
            case 'z':
                //fonction pour déplacer le serpent vers le haut
                check(headX-1, headY);
                if (GameOver == 1){
                    break;
                }
                up_snake(&snake, headX, headY);
                printBoard('^');
                printf("\n");
                break;
            case 's':
                //fonction pour déplacer le serpent vers le bas
                check(headX+1, headY);
                if (GameOver == 1){
                    break;
                }
                down_snake(&snake, headX, headY);
                printBoard('v');
                printf("\n");
                break;
            case 'q':
                //fonction pour déplacer le serpent vers la gauche
                check(headX, headY-1);
                if (GameOver == 1){
                    break;
                }
                left_snake(&snake, headX, headY);
                printBoard('<');
                printf("\n");
                break;
            case 'd':
                //fonction pour déplacer le serpent vers la droite
                check(headX, headY+1);
                if (GameOver == 1){
                    break;
                }
                right_snake(&snake, headX, headY);
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
        on_apple = 0;
        if (GameOver == 1){
            printBoard('X');
        }

    }
    printf("\n");
    printf("Game Over\n");    

}