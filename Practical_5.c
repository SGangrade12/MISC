#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct
{
    int top;
    char items[MAX_SIZE];
} Stack;

void initStack(Stack *s)
{
    s->top = -1;
}

bool isEmpty(Stack *s)
{
    return s->top == -1;
}

bool isFull(Stack *s)
{
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, char value)
{
    if (isFull(s))
    {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

char pop(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack Underflow\n");
        return '\0';
    }
    return s->items[(s->top)--];
}

char peek(Stack *s)
{
    if (isEmpty(s))
    {
        return '\0';
    }
    return s->items[s->top];
}

int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return -1;
}

bool isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

void infixToPostfix(char *infix, char *postfix)
{
    Stack stack;
    initStack(&stack);
    int i, j = 0;

    for (i = 0; infix[i]; i++)
    {
        char c = infix[i];

        if (isalnum(c))
        {
            postfix[j++] = c;
        }
        else if (c == '(')
        {
            push(&stack, c);
        }
        else if (c == ')')
        {
            while (!isEmpty(&stack) && peek(&stack) != '(')
            {
                postfix[j++] = pop(&stack);
            }

            if (!isEmpty(&stack) && peek(&stack) == '(')
            {
                pop(&stack);
            }
            else
            {
                printf("Invalid expression: Mismatched parentheses\n");
                exit(1);
            }
        }
        else if (isOperator(c))
        {
            while (!isEmpty(&stack) && peek(&stack) != '(' && precedence(c) <= precedence(peek(&stack)))
            {
                postfix[j++] = pop(&stack);
            }
            push(&stack, c);
        }
        else if (c == ' ' || c == '\t')
        {
            continue;
        }
        else
        {
            printf("Invalid character in expression: %c\n", c);
            exit(1);
        }
    }

    while (!isEmpty(&stack))
    {
        if (peek(&stack) == '(')
        {
            printf("Invalid expression: Mismatched parentheses\n");
            exit(1);
        }
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
}

bool validateInfix(char *infix)
{
    int parenCount = 0;
    int i;
    bool lastWasOperator = true;

    for (i = 0; infix[i]; i++)
    {
        char c = infix[i];

        if (c == ' ' || c == '\t')
        {
            continue;
        }

        if (c == '(')
        {
            parenCount++;
            lastWasOperator = true;
        }
        else if (c == ')')
        {
            parenCount--;
            if (parenCount < 0)
            {
                printf("Error: Mismatched parentheses\n");
                return false;
            }
            lastWasOperator = false;
        }
        else if (isOperator(c))
        {
            if (lastWasOperator)
            {
                printf("Error: Consecutive operators or operator after opening parenthesis\n");
                return false;
            }
            lastWasOperator = true;
        }
        else if (isalnum(c))
        {
            if (!lastWasOperator && i > 0 && (isalnum(infix[i - 1]) || infix[i - 1] == ')'))
            {
                printf("Error: Missing operator between operands\n");
                return false;
            }
            lastWasOperator = false;
        }
        else
        {
            printf("Error: Invalid character '%c'\n", c);
            return false;
        }
    }

    if (parenCount != 0)
    {
        printf("Error: Mismatched parentheses\n");
        return false;
    }

    if (lastWasOperator)
    {
        printf("Error: Expression ends with an operator\n");
        return false;
    }

    return true;
}

int main()
{
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("Enter infix expression: ");
    fgets(infix, MAX_SIZE, stdin);

    infix[strcspn(infix, "\n")] = 0;

    if (!validateInfix(infix))
    {
        return 1;
    }

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);
    getch();
    return 0;
}