#include <stdio.h>
#include <stdlib.h>

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

int main() {
    Snake snake = { NULL, NULL };

    // Ajouter trois parties du serpent à la liste
    enqueue(&snake, 0, 0);
    enqueue(&snake, 1, 0);
    enqueue(&snake, 2, 0);

    // Afficher le serpent dans le terminal
    printf("Serpent : ");
    print_snake(&snake);

    // Supprimer la première partie du serpent
    dequeue(&snake);

    // Afficher le serpent dans le terminal après la suppression
    printf("Serpent : ");
    print_snake(&snake);

    return 0;
}
