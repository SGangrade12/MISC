#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
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
    newNode->prev = NULL;
    return newNode;
}

struct Node *insertAtBeginning(struct Node *head, int data)
{
    struct Node *newNode = createNode(data);
    if (head == NULL)
    {
        return newNode;
    }
    newNode->next = head;
    head->prev = newNode;
    return newNode;
}

struct Node *insertAtEnd(struct Node *head, int data)
{
    struct Node *newNode = createNode(data);
    if (head == NULL)
    {
        return newNode;
    }
    struct Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

struct Node *deleteNode(struct Node *head, int key)
{
    if (head == NULL)
    {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }

    struct Node *temp = head;

    if (temp->data == key)
    {
        head = temp->next;
        if (head != NULL)
        {
            head->prev = NULL;
        }
        free(temp);
        return head;
    }

    while (temp != NULL && temp->data != key)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Node with value %d not found\n", key);
        return head;
    }

    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }
    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }

    free(temp);
    return head;
}

void display(struct Node *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    printf("Doubly Linked List: ");
    while (temp != NULL)
    {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

bool search(struct Node *head, int key)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        if (temp->data == key)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void freeList(struct Node *head)
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
    struct Node *head = NULL;
    int choice, data;

    do
    {
        printf("\n----- Doubly Linked List Operations -----\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Delete a Node\n");
        printf("4. Display\n");
        printf("5. Search\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &data);
            head = insertAtBeginning(head, data);
            break;

        case 2:
            printf("Enter value to insert: ");
            scanf("%d", &data);
            head = insertAtEnd(head, data);
            break;

        case 3:
            printf("Enter value to delete: ");
            scanf("%d", &data);
            head = deleteNode(head, data);
            break;

        case 4:
            display(head);
            break;

        case 5:
            printf("Enter value to search: ");
            scanf("%d", &data);
            if (search(head, data))
            {
                printf("%d found in the list\n", data);
            }
            else
            {
                printf("%d not found in the list\n", data);
            }
            break;

        case 6:
            printf("Exiting program\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    freeList(head);
    getch();
    return 0;
}