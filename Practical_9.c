#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int row;
    int col;
    int value;
    struct Node *next;
};

struct Node *createNode(int row, int col, int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

struct Node *insert(struct Node *head, int row, int col, int value)
{
    struct Node *newNode = createNode(row, col, value);
    newNode->next = head;
    return newNode;
}

void display(struct Node *head)
{
    struct Node *temp = head;
    printf("Row\tCol\tValue\n");
    while (temp != NULL)
    {
        printf("%d\t%d\t%d\n", temp->row, temp->col, temp->value);
        temp = temp->next;
    }
}

struct Node *multiplySparseMatrices(struct Node *mat1, struct Node *mat2, int rows1, int cols1, int cols2)
{
    struct Node *result = NULL;

    struct Node *p1 = mat1;
    while (p1 != NULL)
    {
        struct Node *p2 = mat2;
        while (p2 != NULL)
        {
            if (p1->col == p2->row)
            {
                int row = p1->row;
                int col = p2->col;
                int value = p1->value * p2->value;
                result = insert(result, row, col, value);
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }

    return result;
}

void freeSparseMatrix(struct Node *head)
{
    struct Node *current = head;
    struct Node *next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

int main()
{
    struct Node *mat1 = NULL;
    struct Node *mat2 = NULL;

    mat1 = insert(mat1, 0, 0, 5);
    mat1 = insert(mat1, 0, 1, 3);
    mat1 = insert(mat1, 1, 0, 4);
    mat1 = insert(mat1, 1, 2, 2);

    mat2 = insert(mat2, 0, 0, 2);
    mat2 = insert(mat2, 1, 0, 1);
    mat2 = insert(mat2, 2, 1, 3);
    mat2 = insert(mat2, 2, 2, 4);

    printf("Matrix 1:\n");
    display(mat1);

    printf("\nMatrix 2:\n");
    display(mat2);

    struct Node *product = multiplySparseMatrices(mat1, mat2, 2, 3, 3);
    printf("\nProduct of Sparse Matrices:\n");
    display(product);

    freeSparseMatrix(mat1);
    freeSparseMatrix(mat2);
    freeSparseMatrix(product);
    getch();
    return 0;
}