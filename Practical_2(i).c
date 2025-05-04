#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

struct Stack
{
    int arr[MAX_SIZE];
    int top;
};

void initialize(struct Stack *stack)
{
    stack->top = -1;
}

bool isEmpty(struct Stack *stack)
{
    return (stack->top == -1);
}

bool isFull(struct Stack *stack)
{
    return (stack->top == MAX_SIZE - 1);
}

void push(struct Stack *stack, int value)
{
    if (isFull(stack))
    {
        printf("Stack Overflow! Cannot push %d\n", value);
        return;
    }

    stack->arr[++(stack->top)] = value;
    printf("%d pushed to stack\n", value);
}

int pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack Underflow! Cannot pop from empty stack\n");
        return -1;
    }

    return stack->arr[(stack->top)--];
}

int peek(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        return -1;
    }

    return stack->arr[stack->top];
}

void display(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements: ");
    for (int i = stack->top; i >= 0; i--)
    {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

int main()
{
    struct Stack stack;
    initialize(&stack);
    int choice, value;

    do
    {
        printf("\n----- Stack Operations -----\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to push: ");
            scanf("%d", &value);
            push(&stack, value);
            break;

        case 2:
            value = pop(&stack);
            if (value != -1)
            {
                printf("Popped value: %d\n", value);
            }
            break;

        case 3:
            value = peek(&stack);
            if (value != -1)
            {
                printf("Top element: %d\n", value);
            }
            break;

        case 4:
            display(&stack);
            break;

        case 5:
            printf("Exiting program\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    getch();
    return 0;
}