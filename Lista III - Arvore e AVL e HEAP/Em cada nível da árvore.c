#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

#define MAX_NODES 100

typedef struct Node {
    int value;
    int left;
    int right;
} Node;

Node nodes[MAX_NODES];
int N;

void bfs() {
    int queue[MAX_NODES]; 
    int front = 0, rear = 0;

    queue[rear++] = 0;
    int currentLevel = 1;
    int levelCount = 1; 
    int nextLevelCount = 0; 
    int levelMin, levelMax;

    while (front < rear) {
        levelMin = INT_MAX;  
        levelMax = INT_MIN;  

        for (int i = 0; i < levelCount; i++) {
            int currentNodeIndex = queue[front++];
            Node currentNode = nodes[currentNodeIndex];

            if (currentNode.value < levelMin) levelMin = currentNode.value;
            
            if (currentNode.value > levelMax) levelMax = currentNode.value;
            
            if (currentNode.left != -1) {
                queue[rear++] = currentNode.left;
                nextLevelCount++;
            }
            if (currentNode.right != -1) {
                queue[rear++] = currentNode.right;
                nextLevelCount++;
            }
        }
        printf("Nivel %d: Maior = %d, Menor = %d\n", currentLevel, levelMax, levelMin);
        currentLevel++;
        levelCount = nextLevelCount;
        nextLevelCount = 0;
    }
}

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &nodes[i].value, &nodes[i].left, &nodes[i].right);
    }

    bfs();
    return 0;
}
