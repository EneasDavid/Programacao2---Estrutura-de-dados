#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node** createHashTable(int size) {
    Node** hashTable = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        hashTable[i] = NULL;
    }
    return hashTable;
}

void insert(Node** hashTable, int size, int key) {
    int index = key % size;
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = key;
    newNode->next = NULL;

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        Node* current = hashTable[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printHashTable(Node** hashTable, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d -> ", i);
        Node* current = hashTable[i];
        while (current != NULL) {
            printf("%d -> ", current->value);
            current = current->next;
        }
        printf("\\\n");
    }
}

void freeHashTable(Node** hashTable, int size) {
    for (int i = 0; i < size; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable);
}

int main() {
    int N;
    scanf("%d", &N); 

    for (int caseNum = 0; caseNum < N; caseNum++) {
        int M, C;
        scanf("%d %d", &M, &C); 

        Node** hashTable = createHashTable(M); 

        for (int i = 0; i < C; i++) {
            int key;
            scanf("%d", &key);
            insert(hashTable, M, key);
        }

        printHashTable(hashTable, M);
        freeHashTable(hashTable, M);

        if (caseNum < N - 1) printf("\n");
    }

    return 0;
}
