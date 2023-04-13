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
#define COLS 50

void mode1(){
    //variable gameover
    int GameOver = 0;

    //position de la tete du serpent
    int headX = 10;
    int headY = 25;

    //variable pour savoir si le serpent est sur l'emplacement de la pomme
    int is_snake = 0;

    //variable pour savoir si la pomme est mangée
    int on_apple = 0;

    //fonction pour créer le plateau de jeu
    int board[ROWS][COLS];
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            if (i == 0 || i == ROWS-1) {
                board[i][j] = -1;
            } else if (j == 0 || j == COLS-1) {
                board[i][j] = -2;
            } else {
                board[i][j] = 0;
            }
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


    Snake snake = { NULL, NULL };
    // Ajouter les premières parties du serpent à la liste
    enqueue(&snake, 10, 23 );
    enqueue(&snake, 10, 24 );
    enqueue(&snake, 10, 25 );

    //fonction pour faire monter le serpent
    void up_snake(Snake *snake, int row, int col){
        enqueue(snake, row-1, col);
        if (on_apple == 1){
            on_apple = 0;
        } else {
            dequeue(snake);
        }
        headX--;
    }
    
    //fonction pour faire descendre le serpent
    void down_snake(Snake *snake, int row, int col){
        enqueue(snake, row+1, col);
        if (on_apple == 1){
            on_apple = 0;
        } else {
            dequeue(snake);
        }
        headX++;
    }

    //fonction pour faire aller le serpent à gauche
    void left_snake(Snake *snake, int row, int col){
        enqueue(snake, row, col-1);
        if (on_apple == 1){
            on_apple = 0;
        } else {
            dequeue(snake);
        }
        headY--;
    }

    //fonction pour faire aller le serpent à droite
    void right_snake(Snake *snake, int row, int col){
        enqueue(snake, row, col+1);
        if (on_apple == 1){
            on_apple = 0;
        } else {
            dequeue(snake);
        }
        headY++;
    }

    //fonction de vérification de victoire
    void check_win(){
        printf("check_win \n");
        int temp = 0;
        for (int i = 0; i < ROWS; i++){
            for (int j = 0; j < COLS; j++){
                if (board[i][j] == 0){
                    temp = 1;
                }
            }
        }
        if (temp == 0){
            GameOver = 2;
        }
    }

    //fonction pour vérifier si le serpent est à l'emplacement
    void check_snake(Snake *snake, int row, int col){
        if (board[row][col] == 1){
            is_snake = 1;
            GameOver = 1;
        }
    }

    //fonction pour créer la pomme
    void apple(){
        while (1){
            int appleX = rand() % (ROWS-2) + 1;
            int appleY = rand() % (COLS-2) + 1;
            if (board[appleX][appleY] == 0){
                board[appleX][appleY] = 2;
                break;
            }
        }
    }
    
    //fonction pour vérifier si la pomme est à l'emplacement
    void check_apple(Snake *snake, int row, int col){
        if (board[row][col] == 2){
            on_apple = 1;
            apple();
        }
    }

    //fonction pour vérifier si le serpent est mort
    void check_gameover(Snake *snake, int row, int col){
        if (row == 0 || row == ROWS-1 || col == 0 || col == COLS-1){
            GameOver = 1;
        }
    }


    //fonction qui regroupe tous les checks
    void check(int row, int col){
        check_win();
        check_gameover(&snake, row, col);
        if (GameOver == 0){
            check_snake(&snake, row, col);
            check_apple(&snake, row, col);
        }
        is_snake = 0;
    }


    //fonction pour afficher le plateau de jeu avec un affichage d'une bordure autour
    void printBoard(char dir){
        system("cls");
        //mise a jour du board avec ecris win sur le tableau a la place du snake
        if (GameOver == 2){
            //7 pour W, 8 pour I, 9 pour N
            for (int i = 0; i < ROWS; i++){
                for (int j = 0; j < COLS; j++){
                    if (board[i][j] == 1 || board[i][j] == 1 && i == headX && j == headY){
                        if (board[i][j-1]==7){
                            board[i][j] = 8;
                            printf(" I ");
                        } else if (board[i][j-1]==8){
                            board[i][j] = 9;
                            printf(" N ");
                        } else if (board[i][j-1]==9){
                            board[i][j] = 7;
                            printf(" W ");
                        } else {
                            board[i][j] = 7;
                            printf(" W ");
                        }   
                    } else if (board[i][j] == -1){
                        printf("---");
                    } else if (board[i][j] == 2){
                        printf("\033[1;31m");
                        printf(" X ");
                        printf("\033[0m");
                    } else if (board[i][j] == -2){
                        printf("|");
                    }
                }
                printf("\n");
            }
        } else {
            for (int i = 0; i < ROWS; i++){
                for (int j = 0; j < COLS; j++){
                    if (board[i][j] == 1 && i == headX && j == headY){
                        printf(" %c ", dir);
                    } else if (board[i][j] == 1){
                        printf(" 0 ");
                    } else if (board[i][j] == 2){
                        printf("\033[1;31m");
                        printf(" X ");
                        printf("\033[0m");
                    } else if (board[i][j] == -1){
                        printf("---");
                    } else if (board[i][j] == -2){
                        printf("|");
                    } else if (board[i][j] == 0){
                        printf("   ");
                    }
                }
                printf("\n");
            }
        }
    }
    for (int i = 0; i < 857; i++){
        apple();
    }
 
    apple();
    printBoard('>');
    while (GameOver == 0){

        
        //fonction pour afficher le serpent
        printf("Direction : ");
        char direction;
        scanf(" %c", &direction);
        switch (direction){
            case 'z':
                //fonction pour déplacer le serpent vers le haut
                check(headX-1, headY);
                if (GameOver != 0){
                    break;
                }
                up_snake(&snake, headX, headY);
                printBoard('^');
                printf("\n");
                break;
            case 's':
                //fonction pour déplacer le serpent vers le bas
                check(headX+1, headY);
                if (GameOver != 0){
                    break;
                }
                down_snake(&snake, headX, headY);
                printBoard('v');
                printf("\n");
                break;
            case 'q':
                //fonction pour déplacer le serpent vers la gauche
                check(headX, headY-1);
                if (GameOver != 0){
                    break;
                }
                left_snake(&snake, headX, headY);
                printBoard('<');
                printf("\n");
                break;
            case 'd':
                //fonction pour déplacer le serpent vers la droite
                check(headX, headY+1);
                if (GameOver != 0){
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

        check_win();

        if (GameOver == 1){
            printBoard('X');
        } else if (GameOver == 2){
            printBoard('W');
        }

    }

    printf("\n");
    if (GameOver == 1){
        printf("Game Over\n");
    } else {
        printf("You Win\n");
    }

}