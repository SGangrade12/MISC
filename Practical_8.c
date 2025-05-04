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

struct Node *addSparseMatrices(struct Node *mat1, struct Node *mat2)
{
    struct Node *result = NULL;
    struct Node *p1 = mat1;
    struct Node *p2 = mat2;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->row < p2->row || (p1->row == p2->row && p1->col < p2->col))
        {
            result = insert(result, p1->row, p1->col, p1->value);
            p1 = p1->next;
        }
        else if (p1->row > p2->row || (p1->row == p2->row && p1->col > p2->col))
        {
            result = insert(result, p2->row, p2->col, p2->value);
            p2 = p2->next;
        }
        else
        {
            result = insert(result, p1->row, p1->col, p1->value + p2->value);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1 != NULL)
    {
        result = insert(result, p1->row, p1->col, p1->value);
        p1 = p1->next;
    }

    while (p2 != NULL)
    {
        result = insert(result, p2->row, p2->col, p2->value);
        p2 = p2->next;
    }

    return result;
}

struct Node *subtractSparseMatrices(struct Node *mat1, struct Node *mat2)
{
    struct Node *result = NULL;
    struct Node *p1 = mat1;
    struct Node *p2 = mat2;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->row < p2->row || (p1->row == p2->row && p1->col < p2->col))
        {
            result = insert(result, p1->row, p1->col, p1->value);
            p1 = p1->next;
        }
        else if (p1->row > p2->row || (p1->row == p2->row && p1->col > p2->col))
        {
            result = insert(result, p2->row, p2->col, -p2->value);
            p2 = p2->next;
        }
        else
        {
            result = insert(result, p1->row, p1->col, p1->value - p2->value);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1 != NULL)
    {
        result = insert(result, p1->row, p1->col, p1->value);
        p1 = p1->next;
    }

    while (p2 != NULL)
    {
        result = insert(result, p2->row, p2->col, -p2->value);
        p2 = p2->next;
    }

    return result;
}

int main()
{
    struct Node *mat1 = NULL;
    struct Node *mat2 = NULL;

    mat1 = insert(mat1, 0, 0, 5);
    mat1 = insert(mat1, 1, 2, 8);
    mat1 = insert(mat1, 2, 1, 3);

    mat2 = insert(mat2, 0, 1, 4);
    mat2 = insert(mat2, 1, 2, 2);
    mat2 = insert(mat2, 2, 2, 7);

    printf("Matrix 1:\n");
    display(mat1);

    printf("\nMatrix 2:\n");
    display(mat2);

    struct Node *sum = addSparseMatrices(mat1, mat2);
    printf("\nSum of Sparse Matrices:\n");
    display(sum);

    struct Node *difference = subtractSparseMatrices(mat1, mat2);
    printf("\nDifference of Sparse Matrices:\n");
    display(difference);
    getch();
    return 0;
}