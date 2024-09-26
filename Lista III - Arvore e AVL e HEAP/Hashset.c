#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node** table;
    int size;
    int count; 
} HashTable;

HashTable* createHashTable(int initialSize) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = initialSize;
    ht->count = 0;
    ht->table = (Node**)malloc(initialSize * sizeof(Node*));
    for (int i = 0; i < initialSize; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void freeHashTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        freeList(ht->table[i]);
    }
    free(ht->table);
    free(ht);
}

int hash(int k, int size) {
    return k % size;
}

void rehash(HashTable* ht) {
    int newSize = 2 * ht->size - 1;
    Node** newTable = (Node**)malloc(newSize * sizeof(Node*));
    for (int i = 0; i < newSize; i++) {
        newTable[i] = NULL;
    }

    for (int i = 0; i < ht->size; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            Node* next = current->next;
            int newIndex = hash(current->value, newSize);
            current->next = newTable[newIndex];
            newTable[newIndex] = current;
            current = next;
        }
    }

    free(ht->table);
    ht->table = newTable;
    ht->size = newSize;
}

int add(HashTable* ht, int k, int* comparisons) {
    int index = hash(k, ht->size);
    Node* current = ht->table[index];

    while (current != NULL) {
        if (current->value == k) {
            (*comparisons)++;
            return 0; 
        }
        current = current->next;
        (*comparisons)++;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = k;
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
    ht->count++;

    if ((double)ht->count / ht->size >= 0.75) rehash(ht);

    return 1; 
}

int delete(HashTable* ht, int k, int* comparisons) {
    int index = hash(k, ht->size);
    Node* current = ht->table[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (current->value == k) {
            if (prev == NULL) {
                ht->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            ht->count--;
            return 1;
        }
        prev = current;
        current = current->next;
        (*comparisons)++;
    }

    return 0; 
}

int has(HashTable* ht, int k, int* comparisons) {
    int index = hash(k, ht->size);
    Node* current = ht->table[index];

    while (current != NULL) {
        if (current->value == k) return 1; 
        current = current->next;
        (*comparisons)++;
    }
    return 0; 
}

void printTable(HashTable* ht, int operationIndex) {
    int maxLength = 0;
    for (int i = 0; i < ht->size; i++) {
        int length = 0;
        Node* current = ht->table[i];
        while (current != NULL) {
            length++;
            current = current->next;
        }
        if (length > maxLength) {
            maxLength = length;
        }
    }
    printf("%d %d %d %d\n", operationIndex, ht->size, ht->count, maxLength);
}

int main() {
    HashTable* ht = createHashTable(7);
    char operation[4];
    int k, operationIndex = 0;

    while (scanf("%s", operation) != EOF) {
        if (operation[0] == 'A') { 
            scanf("%d", &k);
            int comparisons = 0;
            int result = add(ht, k, &comparisons);
            printf("%d %d %d\n", operationIndex++, result, comparisons);
        } else if (operation[0] == 'D') { 
            scanf("%d", &k);
            int comparisons = 0;
            int result = delete(ht, k, &comparisons);
            printf("%d %d %d\n", operationIndex++, result, comparisons);
        } else if (operation[0] == 'H') { 
            scanf("%d", &k);
            int comparisons = 0;
            int result = has(ht, k, &comparisons);
            printf("%d %d %d\n", operationIndex++, result, comparisons);
        } else if (operation[0] == 'P') { 
            printTable(ht, operationIndex++);
        }
    }

    freeHashTable(ht);
    return 0;
}