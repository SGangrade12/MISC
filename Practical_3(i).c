#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Stack
{
    struct Node *top;
    int size;
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

struct Stack *initializeStack()
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    if (stack == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

bool isEmpty(struct Stack *stack)
{
    return (stack->top == NULL);
}

void push(struct Stack *stack, int data)
{
    struct Node *newNode = createNode(data);

    newNode->next = stack->top;

    stack->top = newNode;

    stack->size++;

    printf("%d pushed to stack\n", data);
}

int pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack Underflow! Cannot pop from empty stack\n");
        return -1;
    }

    struct Node *temp = stack->top;
    int data = temp->data;

    stack->top = stack->top->next;

    free(temp);
    stack->size--;

    return data;
}

int peek(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->top->data;
}

void display(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        return;
    }

    struct Node *temp = stack->top;
    printf("Stack elements: ");

    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int getSize(struct Stack *stack)
{
    return stack->size;
}

void freeStack(struct Stack *stack)
{
    struct Node *current = stack->top;
    struct Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(stack);
}

int main()
{
    struct Stack *stack = initializeStack();
    int choice, data;

    do
    {
        printf("\n----- Stack Operations -----\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Size\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to push: ");
            scanf("%d", &data);
            push(stack, data);
            break;

        case 2:
            data = pop(stack);
            if (data != -1)
            {
                printf("Popped value: %d\n", data);
            }
            break;

        case 3:
            data = peek(stack);
            if (data != -1)
            {
                printf("Top element: %d\n", data);
            }
            break;

        case 4:
            display(stack);
            break;

        case 5:
            printf("Stack size: %d\n", getSize(stack));
            break;

        case 6:
            printf("Exiting program\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    freeStack(stack);
    getch();
    return 0;
}