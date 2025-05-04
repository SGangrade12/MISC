#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5

struct Queue
{
    int items[MAX_SIZE];
    int front;
    int rear;
    int size;
};

void initializeQueue(struct Queue *q)
{
    q->front = -1;
    q->rear = -1;
    q->size = 0;
}

bool isFull(struct Queue *q)
{
    return q->size == MAX_SIZE;
}

bool isEmpty(struct Queue *q)
{
    return q->size == 0;
}

void enqueue(struct Queue *q, int value)
{
    if (isFull(q))
    {
        printf("Queue Overflow! Cannot enqueue %d\n", value);
        return;
    }

    if (isEmpty(q))
    {
        q->front = 0;
    }

    q->rear = (q->rear + 1) % MAX_SIZE;
    q->items[q->rear] = value;
    q->size++;

    printf("%d enqueued to queue\n", value);
}

int dequeue(struct Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue Underflow! Cannot dequeue from empty queue\n");
        return -1;
    }

    int value = q->items[q->front];

    if (q->front == q->rear)
    {
        initializeQueue(q);
    }
    else
    {
        q->front = (q->front + 1) % MAX_SIZE;
        q->size--;
    }

    return value;
}

int front(struct Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }

    return q->items[q->front];
}

void display(struct Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue elements: ");

    int count = 0;
    int i = q->front;

    while (count < q->size)
    {
        printf("%d ", q->items[i]);
        i = (i + 1) % MAX_SIZE;
        count++;
    }

    printf("\n");
}

int getSize(struct Queue *q)
{
    return q->size;
}

int main()
{
    struct Queue queue;
    initializeQueue(&queue);

    int choice, value;

    do
    {
        printf("\n----- Queue Operations -----\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Front\n");
        printf("4. Display\n");
        printf("5. Size\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to enqueue: ");
            scanf("%d", &value);
            enqueue(&queue, value);
            break;

        case 2:
            value = dequeue(&queue);
            if (value != -1)
            {
                printf("Dequeued value: %d\n", value);
            }
            break;

        case 3:
            value = front(&queue);
            if (value != -1)
            {
                printf("Front element: %d\n", value);
            }
            break;

        case 4:
            display(&queue);
            break;

        case 5:
            printf("Queue size: %d\n", getSize(&queue));
            break;

        case 6:
            printf("Exiting program\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    getch();
    return 0;
}