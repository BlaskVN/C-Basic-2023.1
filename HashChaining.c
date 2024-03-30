#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ULL unsigned long long 
#define M 10000

typedef struct TNode{
    ULL id;
    struct TNode* next;
} Node;

Node* T[M];

ULL h(ULL key) {
    return key % M;
}

int find(ULL key) {
    Node* curr = T[h(key)];
    while (curr != NULL) {
        if (curr->id == key) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

int insert(ULL key) {
    if (find(key)) {
        return 0;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = key;
    newNode->next = T[h(key)];
    T[h(key)] = newNode;
    return 1;
}

int main() {

    for (int i = 0; i < M; i++) {
        T[i] = NULL;
    }

    char key[20];
    while (1)
    {
        scanf("%s", key);
        if (strcmp(key, "*") == 0) {
            break;
        }
        else
        {
            insert(atoll(key));
        }
    }
    while (1)
    {
        char command[20];
        scanf("%s", command);
        if (strcmp(command, "find") == 0) {
            scanf("%s", key);
            printf("%d\n", find(atoll(key)));
        }
        else if (strcmp(command, "insert") == 0) {
            scanf("%s", key);
            printf("%d\n", insert(atoll(key)));
        }
        if (!strcmp(command, "***")) {
            break;
        }
    }
    
    


    for (int i = 0; i < M; i++) {
        Node* currentNode = T[i];
        while (currentNode != NULL) {
            Node* temp = currentNode;
            currentNode = currentNode->next;
            free(temp);
        }
    }

    return 0;
}
