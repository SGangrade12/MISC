#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int data;
    struct Node *next;
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
    newNode->next = newNode;
    return newNode;
}

bool isEmpty(struct Node *head)
{
    return head == NULL;
}

struct Node *insertAtBeginning(struct Node *head, int data)
{
    struct Node *newNode = createNode(data);

    if (isEmpty(head))
    {
        return newNode;
    }

    struct Node *temp = head;
    while (temp->next != head)
    {
        temp = temp->next;
    }

    newNode->next = head;
    temp->next = newNode;

    return newNode;
}

struct Node *insertAtEnd(struct Node *head, int data)
{
    struct Node *newNode = createNode(data);

    if (isEmpty(head))
    {
        return newNode;
    }

    struct Node *temp = head;
    while (temp->next != head)
    {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->next = head;

    return head;
}

void insertAfter(struct Node *head, int key, int data)
{
    if (isEmpty(head))
    {
        printf("List is empty. Cannot insert after a specific node.\n");
        return;
    }

    struct Node *temp = head;

    do
    {
        if (temp->data == key)
        {
            struct Node *newNode = createNode(data);
            newNode->next = temp->next;
            temp->next = newNode;
            printf("Node inserted after %d\n", key);
            return;
        }
        temp = temp->next;
    } while (temp != head);

    printf("Node with value %d not found\n", key);
}

struct Node *deleteNode(struct Node *head, int key)
{
    if (isEmpty(head))
    {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }

    if (head->data == key)
    {
        if (head->next == head)
        {
            free(head);
            return NULL;
        }

        struct Node *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }

        struct Node *newHead = head->next;
        temp->next = newHead;
        free(head);
        return newHead;
    }

    struct Node *curr = head;
    struct Node *prev = NULL;

    do
    {
        prev = curr;
        curr = curr->next;

        if (curr->data == key)
        {
            prev->next = curr->next;
            free(curr);
            printf("Node with value %d deleted\n", key);
            return head;
        }
    } while (curr != head);

    printf("Node with value %d not found\n", key);
    return head;
}

void display(struct Node *head)
{
    if (isEmpty(head))
    {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    printf("Circular Linked List: ");

    do
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("(back to %d)\n", head->data);
}

int countNodes(struct Node *head)
{
    if (isEmpty(head))
    {
        return 0;
    }

    int count = 0;
    struct Node *temp = head;

    do
    {
        count++;
        temp = temp->next;
    } while (temp != head);

    return count;
}

bool search(struct Node *head, int key)
{
    if (isEmpty(head))
    {
        return false;
    }

    struct Node *temp = head;

    do
    {
        if (temp->data == key)
        {
            return true;
        }
        temp = temp->next;
    } while (temp != head);

    return false;
}

void freeList(struct Node *head)
{
    if (isEmpty(head))
    {
        return;
    }

    struct Node *current = head;
    struct Node *next;

    do
    {
        next = current->next;
        free(current);
        current = next;
    } while (current != head);
}

int main()
{
    struct Node *head = NULL;
    int choice, data, key;

    do
    {
        printf("\n----- Circular Linked List Operations -----\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert After a Node\n");
        printf("4. Delete a Node\n");
        printf("5. Display\n");
        printf("6. Count Nodes\n");
        printf("7. Search\n");
        printf("8. Exit\n");
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
            printf("Enter the node value after which to insert: ");
            scanf("%d", &key);
            printf("Enter value to insert: ");
            scanf("%d", &data);
            insertAfter(head, key, data);
            break;

        case 4:
            printf("Enter value to delete: ");
            scanf("%d", &data);
            head = deleteNode(head, data);
            break;

        case 5:
            display(head);
            break;

        case 6:
            printf("Number of nodes: %d\n", countNodes(head));
            break;

        case 7:
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

        case 8:
            printf("Exiting program\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    freeList(head);
    getch();
    return 0;
}