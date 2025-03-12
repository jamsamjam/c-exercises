#include <stdio.h>
#include <stdlib.h>

#ifndef type_el
#define type_el int
#endif

typedef struct node{
    type_el value;
    struct node *next;
} Node;
typedef Node *ChainList;

int insert(Node *after, type_el elem);
int push(ChainList *list, type_el value);
type_el pop(ChainList *list);
int delete(ChainList *list, type_el value);
size_t length(ChainList list);
void print(ChainList list);

int main(void)
{
    ChainList list = NULL;
    type_el element = 3;

    printf("Inserting at the head: %d\n", element);
    push(&list, element);

    printf("Inserting at the head: 2, then 1, 0, and -1.\n");
    push(&list, 2);
    push(&list, 1);
    push(&list, 0);
    push(&list, -1);

    printf("The list is:\n\t");
    print(list);
    printf("\n");

    printf("Removing the head of the list.\n");
    pop(&list);

    printf("The list after removing the head:\n\t");
    print(list);
    printf("\n");

    if (length(list) >= 3) {
        printf("Deleting %d in the list.\n", list->next->next->value);
        delete(&list, list->next->next->value);
    } else {
        printf("Skipping deletion as the 4th element does not exist.\n");
    }

    printf("The list after deletion:\n\t");
    print(list);
    printf("\n");

    if (length(list) >= 2) {
        printf("Inserting 156 in the 2nd position.\n");
        insert(list->next, 156);
    } else {
        printf("Skipping insertion as the 2nd position does not exist.\n");
    }

    printf("The list after insertion:\n\t");
    print(list);
    printf("\n");

    printf("List size: %zu\n", length(list));

    return 0;
}

// inserting a node with given value in the list after a given node
int insert(Node *after, type_el value)
{
    if (after == NULL) return 0;

    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) return 0;

    new_node->value = value;
    new_node->next = after->next;
    after->next = new_node;

    return 1;
}

// inserting a node with the given value at the top of the list
int push(ChainList *list, type_el value)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) return 0;

    new_node->value = value;
    new_node->next = *list;
    *list = new_node;
    return 1;
}

// removing the first node from the list
type_el pop(ChainList *list)
{
    if (*list == NULL) return -1;

    Node *temp = *list;
    type_el removed_value = temp->value;
    *list = temp->next;
    free(temp);

    return removed_value;
}

// deleteing a node with the given value of the list
int delete(ChainList *list, type_el value)
{
    if (*list == NULL) return -1;

    Node *temp = *list;
    Node *prev = NULL;
    int position = 0;

    // A head node should be deleted
    if (temp->value == value) {
        *list = temp->next;
        free(temp);
        return position;
    }

    while (temp != NULL && temp->value != value) {
        prev = temp;
        temp = temp->next;
        position++;
    }

    // The value was not found
    if (temp == NULL) return -1;

    prev->next = temp->next;
    free(temp);

    return position;
}

size_t length(ChainList list)
{
    size_t res = 0;

    while (list != NULL) {
        res++;
        list = list->next;
    }   
    return res;
}

void print(ChainList list)
{
    while (list != NULL) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}