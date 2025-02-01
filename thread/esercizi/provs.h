#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include<sys/mman.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int numElementi;
} Queue;

void initializeQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int isQueueEmpty(Queue* queue) {
    return (queue->front == NULL);
}

void enqueue(Queue* queue, int data) {
    Node* newNode = (Node*)mmap(NULL, sizeof(Node), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    newNode->data=data;
    newNode->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        newNode->prev = queue->rear;
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->numElementi++;
}

int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        fprintf(stderr, "Queue is empty. Cannot dequeue.\n");
        exit(EXIT_FAILURE);
    }

    int element = queue->front->data;
    Node* temp = queue->front;

    if (queue->front == queue->rear) {
        // Last element in the queue
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
        queue->front->prev = NULL;
    }

    queue->numElementi--;

    munmap(temp, sizeof(Node));
    return element;
}