#include <stdio.h>
#include <stdlib.h>

typedef unsigned char IP_addr[4];

typedef struct node {
    IP_addr address;
    const struct node **neighbors;
    size_t nb_neighbors;
} Node;

Node *create(unsigned char a1, unsigned char a2, unsigned char a3, unsigned char a4)
{
    Node *n = malloc(sizeof(Node));
    if (n == NULL) return NULL;

    n->address[0] = a1;
    n->address[1] = a2;
    n->address[2] = a3;
    n->address[3] = a4;

    n->neighbors = NULL;
    n->nb_neighbors = 0;

    return n;
}

void link_neighbors(Node *n1, Node *n2)
{
    if (n1 == NULL || n2 == NULL) return;

    n1->neighbors = realloc(n1->neighbors, (n1->nb_neighbors + 1) * sizeof(Node *));
    n2->neighbors = realloc(n2->neighbors, (n2->nb_neighbors + 1) * sizeof(Node *));
    
    if (n1->neighbors == NULL || n2->neighbors == NULL) return;

    n1->neighbors[n1->nb_neighbors++] = n2;
    n2->neighbors[n2->nb_neighbors++] = n1;
}

unsigned int common_neighbors(Node *n1, Node *n2)
{
    if (n1 == NULL || n2 == NULL) return 0;

    unsigned int count = 0;

    for (int i = 0; i < n1->nb_neighbors; i++) {
        for (int j = 0; j < n2->nb_neighbors; j++) {
            if (n1->neighbors[i] == n2->neighbors[j]) {
                count++;
            }
        }
        
    }
    return count;    
}

void node_print(Node *n)
{
    if (n == NULL) return;

    printf("%u.%u.%u.%u has %zu neighbor(s): ",
        n->address[0], n->address[1], n->address[2], n->address[3],
        n->nb_neighbors);

    for (int i = 0; i < n->nb_neighbors; i++) {
        printf("%u.%u.%u.%u",
            n->neighbors[i]->address[0], n->neighbors[i]->address[1],
            n->neighbors[i]->address[2], n->neighbors[i]->address[3]);
        if (i < n->nb_neighbors - 1) printf(", ");
        }
    printf(".\n");
}

int main(void)
{
    Node *list[] = {
        create(192, 168, 1, 1), // 0
        create(192, 168, 1, 2), // 1
        create(192, 168, 1, 3), // 2
        create(192, 168, 10, 1), // 3
        create(192, 168, 10, 2), // 4
        create(192, 168, 20, 1), // 5
        create(192, 168, 20, 2) // 6
    };

    link_neighbors(list[0], list[1]);
    link_neighbors(list[0], list[2]);
    link_neighbors(list[1], list[2]);
    link_neighbors(list[1], list[3]);
    link_neighbors(list[1], list[5]);
    link_neighbors(list[2], list[3]);
    link_neighbors(list[2], list[5]);
    link_neighbors(list[3], list[4]);
    link_neighbors(list[3], list[5]);
    link_neighbors(list[5], list[6]);
    
    node_print(list[3]);

    Node *n1 = list[0];
    Node *n2 = list[5];
    unsigned int nb = common_neighbors(n1, n2);

    printf("%u.%u.%u.%u and %u.%u.%u.%u have %u common neighbor(s).\n",
        n1->address[0], n1->address[1], n1->address[2], n1->address[3],
        n2->address[0], n2->address[1], n2->address[2], n2->address[3],
        nb);

    Node *n3 = list[1];
    Node *n4 = list[2];
    unsigned int nb1 = common_neighbors(n3, n4);

    printf("%u.%u.%u.%u and %u.%u.%u.%u have %u common neighbor(s).\n",
        n3->address[0], n3->address[1], n3->address[2], n3->address[3],
        n4->address[0], n4->address[1], n4->address[2], n4->address[3],
        nb1);

    return 0;
}
