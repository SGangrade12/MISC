#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int top;
    int items[MAX_SIZE];
} IntStack;

typedef struct {
    int top;
    char items[MAX_SIZE];
} CharStack;

void initIntStack(IntStack* s) {
    s->top = -1;
}

void initCharStack(CharStack* s) {
    s->top = -1;
}

bool isIntStackEmpty(IntStack* s) {
    return s->top == -1;
}

bool isCharStackEmpty(CharStack* s) {
    return s->top == -1;
}

bool isIntStackFull(IntStack* s) {
    return s->top == MAX_SIZE - 1;
}

bool isCharStackFull(CharStack* s) {
    return s->top == MAX_SIZE - 1;
}

void intPush(IntStack* s, int value) {
    if (isIntStackFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

void charPush(CharStack* s, char value) {
    if (isCharStackFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

int intPop(IntStack* s) {
    if (isIntStackEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->items[(s->top)--];
}

char charPop(CharStack* s) {
    if (isCharStackEmpty(s)) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return s->items[(s->top)--];
}

int intPeek(IntStack* s) {
    if (isIntStackEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->items[s->top];
}

char charPeek(CharStack* s) {
    if (isCharStackEmpty(s)) {
        printf("Stack is empty\n");
        return '\0';
    }
    return s->items[s->top];
}

int precedence(char op) {
    switch (op) {
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

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int performOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("Error: Division by zero\n");
                exit(1);
            }
            return a / b;
        case '^': {
            int result = 1;
            for (int i = 0; i < b; i++)
                result *= a;
            return result;
        }
    }
    return 0;
}

int evaluatePostfix(char* expression) {
    IntStack stack;
    initIntStack(&stack);
    
    for (int i = 0; expression[i]; i++) {
        if (expression[i] == ' ' || expression[i] == '\t')
            continue;
        
        if (isdigit(expression[i])) {
            int num = 0;
            
            while (isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--; 
            
            intPush(&stack, num);
        }
        else if (isOperator(expression[i])) {
            int val2 = intPop(&stack);
            int val1 = intPop(&stack);
            
            intPush(&stack, performOperation(val1, val2, expression[i]));
        }
    }
    
    return intPop(&stack);
}

int evaluatePrefix(char* expression) {
    IntStack stack;
    initIntStack(&stack);
    
    int len = strlen(expression);
    
    for (int i = len - 1; i >= 0; i--) {
        if (expression[i] == ' ' || expression[i] == '\t')
            continue;
        
        if (isdigit(expression[i])) {
            int num = 0;
            int power = 1;
            
            while (i >= 0 && isdigit(expression[i])) {
                num = num + (expression[i] - '0') * power;
                power *= 10;
                i--;
            }
            i++; 
            
            intPush(&stack, num);
        }
        else if (isOperator(expression[i])) {
            int val1 = intPop(&stack);
            int val2 = intPop(&stack);
            
            intPush(&stack, performOperation(val1, val2, expression[i]));
        }
    }
    
    return intPop(&stack);
}

void infixToPostfix(char* infix, char* postfix) {
    CharStack stack;
    initCharStack(&stack);
    int j = 0;
    
    for (int i = 0; infix[i]; i++) {
        char c = infix[i];
        
        if (isdigit(c)) {
            while (isdigit(infix[i]))
                postfix[j++] = infix[i++];
            i--;
            postfix[j++] = ' ';
        }
        else if (c == '(') {
            charPush(&stack, c);
        }
        else if (c == ')') {
            while (!isCharStackEmpty(&stack) && charPeek(&stack) != '(')
                postfix[j++] = charPop(&stack);
            
            if (!isCharStackEmpty(&stack) && charPeek(&stack) != '(')
                printf("Invalid expression\n");
            else
                charPop(&stack);
        }
        else if (isOperator(c)) {
            while (!isCharStackEmpty(&stack) && precedence(c) <= precedence(charPeek(&stack)))
                postfix[j++] = charPop(&stack);
            charPush(&stack, c);
        }
    }
    
    while (!isCharStackEmpty(&stack))
        postfix[j++] = charPop(&stack);
    
    postfix[j] = '\0';
}

void reverseString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void infixToPrefix(char* infix, char* prefix) {
    char reversedInfix[MAX_SIZE];
    strcpy(reversedInfix, infix);
    reverseString(reversedInfix);
    
    for (int i = 0; reversedInfix[i]; i++) {
        if (reversedInfix[i] == '(')
            reversedInfix[i] = ')';
        else if (reversedInfix[i] == ')')
            reversedInfix[i] = '(';
    }
    
    char reversedPostfix[MAX_SIZE];
    infixToPostfix(reversedInfix, reversedPostfix);
    
    strcpy(prefix, reversedPostfix);
    reverseString(prefix);
}

int evaluateInfix(char* expression) {
    char postfix[MAX_SIZE];
    infixToPostfix(expression, postfix);
    return evaluatePostfix(postfix);
}

int main() {
    char expression[MAX_SIZE];
    int choice;
    
    do {
        printf("\n----- Expression Evaluator -----\n");
        printf("1. Evaluate Infix Expression\n");
        printf("2. Evaluate Postfix Expression\n");
        printf("3. Evaluate Prefix Expression\n");
        printf("4. Convert Infix to Postfix\n");
        printf("5. Convert Infix to Prefix\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        if (choice >= 1 && choice <= 5) {
            printf("Enter the expression: ");
            fgets(expression, MAX_SIZE, stdin);
            expression[strcspn(expression, "\n")] = 0;
        }
        
        switch (choice) {
            case 1:
                printf("Result: %d\n", evaluateInfix(expression));
                break;
                
            case 2:
                printf("Result: %d\n", evaluatePostfix(expression));
                break;
                
            case 3:
                printf("Result: %d\n", evaluatePrefix(expression));
                break;
                
            case 4: {
                char postfix[MAX_SIZE];
                infixToPostfix(expression, postfix);
                printf("Postfix expression: %s\n", postfix);
                break;
            }
            
            case 5: {
                char prefix[MAX_SIZE];
                infixToPrefix(expression, prefix);
                printf("Prefix expression: %s\n", prefix);
                break;
            }
            
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