#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Queue
{
    struct Node *front, *rear;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Queue *initializeQueue()
{
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    if (queue == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

bool isEmpty(struct Queue *queue)
{
    return (queue->front == NULL);
}

void enqueue(struct Queue *queue, int data)
{
    struct Node *newNode = createNode(data);

    if (isEmpty(queue))
    {
        queue->front = queue->rear = newNode;
        printf("%d enqueued to the queue\n", data);
        return;
    }

    queue->rear->next = newNode;
    queue->rear = newNode;
    printf("%d enqueued to the queue\n", data);
}

int dequeue(struct Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }

    struct Node *temp = queue->front;
    int data = temp->data;

    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(temp);
    return data;
}

int peek(struct Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty. Cannot peek.\n");
        return -1;
    }
    return queue->front->data;
}

void display(struct Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty.\n");
        return;
    }

    struct Node *temp = queue->front;
    printf("Queue elements: ");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeQueue(struct Queue *queue)
{
    struct Node *current = queue->front;
    struct Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(queue);
}

int main()
{
    struct Queue *queue = initializeQueue();
    int choice, data;

    do
    {
        printf("\n----- Queue Operations -----\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &data);
            enqueue(queue, data);
            break;

        case 2:
            data = dequeue(queue);
            if (data != -1)
            {
                printf("Dequeued value: %d\n", data);
            }
            break;

        case 3:
            data = peek(queue);
            if (data != -1)
            {
                printf("Front element: %d\n", data);
            }
            break;

        case 4:
            display(queue);
            break;

        case 5:
            printf("Exiting program\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    freeQueue(queue);
    getch();
    return 0;
}