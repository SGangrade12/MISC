#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *left, *right;
} Node;

Node *createNode(int key)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *insert(Node *root, int key)
{
    if (root == NULL)
    {
        return createNode(key);
    }
    if (key < root->key)
    {
        root->left = insert(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = insert(root->right, key);
    }
    return root;
}

Node *search(Node *root, int key)
{
    if (root == NULL || root->key == key)
    {
        return root;
    }
    if (key < root->key)
    {
        return search(root->left, key);
    }
    return search(root->right, key);
}

Node *findMin(Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

Node *deleteNode(Node *root, int key)
{
    if (root == NULL)
    {
        return root;
    }
    if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node *temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void inOrder(Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

void preOrder(Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(Node *root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

int main()
{
    Node *root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("In-order traversal: ");
    inOrder(root);
    printf("\n");

    printf("Pre-order traversal: ");
    preOrder(root);
    printf("\n");

    printf("Post-order traversal: ");
    postOrder(root);
    printf("\n");

    int key = 40;
    Node *foundNode = search(root, key);
    if (foundNode)
    {
        printf("Key %d found in the BST.\n", key);
    }
    else
    {
        printf("Key %d not found in the BST.\n", key);
    }

    root = deleteNode(root, 20);
    printf("In-order traversal after deleting 20: ");
    inOrder(root);
    printf("\n");
    getch();
    return 0;
}