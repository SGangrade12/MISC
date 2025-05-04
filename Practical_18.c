#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TABLE_SIZE 10
#define DELETED_NODE (struct DataItem*)(0xFFFFFFFFFFFFFFFL)
struct DataItem {
    int key;
    int data;};
struct LinkedListNode {
    int key;
    int data;
    struct LinkedListNode* next;};
struct DataItem* hashArrayLP[TABLE_SIZE];
struct DataItem* hashArrayQP[TABLE_SIZE];
struct DataItem* hashArrayDH[TABLE_SIZE];
struct LinkedListNode* hashArraySC[TABLE_SIZE];
int hashCode1(int key) {
    return key % TABLE_SIZE;}
int hashCode2(int key) {
    return 7 - (key % 7);}
void initializeHashTables() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashArrayLP[i] = NULL;
        hashArrayQP[i] = NULL;
        hashArrayDH[i] = NULL;
        hashArraySC[i] = NULL;}}
void insertLP(int key, int data) {
    struct DataItem* item = (struct DataItem*)malloc(sizeof(struct DataItem));
    item->key = key;
    item->data = data;
    int hashIndex = hashCode1(key);
    while (hashArrayLP[hashIndex] != NULL && hashArrayLP[hashIndex] != DELETED_NODE) {
        if (hashArrayLP[hashIndex]->key == key) {
            hashArrayLP[hashIndex]->data = data;
            free(item);
            return;}
        hashIndex = (hashIndex + 1) % TABLE_SIZE;} 
    hashArrayLP[hashIndex] = item;}
void insertQP(int key, int data) {
    struct DataItem* item = (struct DataItem*)malloc(sizeof(struct DataItem));
    item->key = key;
    item->data = data;
    int hashIndex = hashCode1(key);
    int i = 0;
    while (hashArrayQP[(hashIndex + i*i) % TABLE_SIZE] != NULL && 
           hashArrayQP[(hashIndex + i*i) % TABLE_SIZE] != DELETED_NODE) {
        if (hashArrayQP[(hashIndex + i*i) % TABLE_SIZE]->key == key) {
            hashArrayQP[(hashIndex + i*i) % TABLE_SIZE]->data = data;
            free(item);
            return;}
        i++;} 
    hashArrayQP[(hashIndex + i*i) % TABLE_SIZE] = item;}
void insertDH(int key, int data) {
    struct DataItem* item = (struct DataItem*)malloc(sizeof(struct DataItem));
    item->key = key;
    item->data = data; 
    int hashIndex = hashCode1(key);
    int stepSize = hashCode2(key);
    while (hashArrayDH[hashIndex] != NULL && hashArrayDH[hashIndex] != DELETED_NODE) {
        if (hashArrayDH[hashIndex]->key == key) {
            hashArrayDH[hashIndex]->data = data;
            free(item);
            return;}
        hashIndex = (hashIndex + stepSize) % TABLE_SIZE;} 
    hashArrayDH[hashIndex] = item;}
void insertSC(int key, int data) {
    int hashIndex = hashCode1(key);
    struct LinkedListNode* newNode = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
    newNode->key = key;
    newNode->data = data;
    newNode->next = NULL;
    if (hashArraySC[hashIndex] == NULL) {
        hashArraySC[hashIndex] = newNode;
    } else {
        struct LinkedListNode* current = hashArraySC[hashIndex];
        struct LinkedListNode* prev = NULL;
        while (current != NULL) {
            if (current->key == key) {
                current->data = data;
                free(newNode);
                return;}
            prev = current;
            current = current->next;}
        prev->next = newNode;}}
struct DataItem* searchLP(int key) {
    int hashIndex = hashCode1(key);
    int originalIndex = hashIndex;
    while (hashArrayLP[hashIndex] != NULL) {
        if (hashArrayLP[hashIndex]->key == key) {
            return hashArrayLP[hashIndex];}
        hashIndex = (hashIndex + 1) % TABLE_SIZE;
        if (hashIndex == originalIndex) {
            break;}}
    return NULL;}
struct DataItem* searchQP(int key) {
    int hashIndex = hashCode1(key);
    int i = 0;
    int indexToCheck;
    do {
        indexToCheck = (hashIndex + i*i) % TABLE_SIZE;
        if (hashArrayQP[indexToCheck] == NULL) {
            return NULL;} 
        if (hashArrayQP[indexToCheck]->key == key) {
            return hashArrayQP[indexToCheck];}
        i++;
    } while (i < TABLE_SIZE);
    return NULL;}
struct DataItem* searchDH(int key) {
    int hashIndex = hashCode1(key);
    int stepSize = hashCode2(key);
    int originalIndex = hashIndex;
    while (hashArrayDH[hashIndex] != NULL) {
        if (hashArrayDH[hashIndex]->key == key) {
            return hashArrayDH[hashIndex];}
        hashIndex = (hashIndex + stepSize) % TABLE_SIZE;
        if (hashIndex == originalIndex) {
            break;}}
    return NULL;}
struct LinkedListNode* searchSC(int key) {
    int hashIndex = hashCode1(key);
    struct LinkedListNode* current = hashArraySC[hashIndex];
    while (current != NULL) {
        if (current->key == key) {
            return current;}
        current = current->next;}
    return NULL;}
bool deleteLP(int key) {
    int hashIndex = hashCode1(key);
    int originalIndex = hashIndex;
    while (hashArrayLP[hashIndex] != NULL) {
        if (hashArrayLP[hashIndex]->key == key) {
            free(hashArrayLP[hashIndex]);
            hashArrayLP[hashIndex] = DELETED_NODE;
            return true;}
        hashIndex = (hashIndex + 1) % TABLE_SIZE;
        if (hashIndex == originalIndex) {
            break;}}
    return false;}
bool deleteQP(int key) {
    int hashIndex = hashCode1(key);
    int i = 0;
    int indexToCheck;
    do {
        indexToCheck = (hashIndex + i*i) % TABLE_SIZE;
        if (hashArrayQP[indexToCheck] == NULL) {
            return false;}
        if (hashArrayQP[indexToCheck]->key == key) {
            free(hashArrayQP[indexToCheck]);
            hashArrayQP[indexToCheck] = DELETED_NODE;
            return true;}
        i++;} while (i < TABLE_SIZE); 
    return false;}
bool deleteDH(int key) {
    int hashIndex = hashCode1(key);
    int stepSize = hashCode2(key);
    int originalIndex = hashIndex;
    while (hashArrayDH[hashIndex] != NULL) {
        if (hashArrayDH[hashIndex]->key == key) {
            free(hashArrayDH[hashIndex]);
            hashArrayDH[hashIndex] = DELETED_NODE;
            return true;}
        hashIndex = (hashIndex + stepSize) % TABLE_SIZE;
        if (hashIndex == originalIndex) {
            break;}} 
    return false;}
bool deleteSC(int key) {
    int hashIndex = hashCode1(key);
    struct LinkedListNode* current = hashArraySC[hashIndex];
    struct LinkedListNode* prev = NULL;
    if (current == NULL) {
        return false;}
    if (current->key == key) {
        hashArraySC[hashIndex] = current->next;
        free(current);
        return true;}
    while (current != NULL && current->key != key) {
        prev = current;
        current = current->next;}
    if (current == NULL) {
        return false;}
    prev->next = current->next;
    free(current);
    return true;}
void displayLP() {
    printf("\nLinear Probing Hash Table:\n");
    printf("Index\tKey\tValue\n");
    printf("---------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashArrayLP[i] != NULL && hashArrayLP[i] != DELETED_NODE) {
            printf("%d\t%d\t%d\n", i, hashArrayLP[i]->key, hashArrayLP[i]->data);
        } else if (hashArrayLP[i] == DELETED_NODE) {
            printf("%d\t<deleted>\n", i);
        } else {
            printf("%d\t<empty>\n", i);}}}
void displayQP() {
    printf("\nQuadratic Probing Hash Table:\n");
    printf("Index\tKey\tValue\n");
    printf("---------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashArrayQP[i] != NULL && hashArrayQP[i] != DELETED_NODE) {
            printf("%d\t%d\t%d\n", i, hashArrayQP[i]->key, hashArrayQP[i]->data);
        } else if (hashArrayQP[i] == DELETED_NODE) {
            printf("%d\t<deleted>\n", i);
        } else {
            printf("%d\t<empty>\n", i);}}}
void displayDH() {
    printf("\nDouble Hashing Hash Table:\n");
    printf("Index\tKey\tValue\n");
    printf("---------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashArrayDH[i] != NULL && hashArrayDH[i] != DELETED_NODE) {
            printf("%d\t%d\t%d\n", i, hashArrayDH[i]->key, hashArrayDH[i]->data);
        } else if (hashArrayDH[i] == DELETED_NODE) {
            printf("%d\t<deleted>\n", i);
        } else {
            printf("%d\t<empty>\n", i);}}}
void displaySC() {
    printf("\nSeparate Chaining Hash Table:\n");
    printf("Index\tEntries\n");
    printf("----------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d\t", i);
        if (hashArraySC[i] == NULL) {
            printf("<empty>");
        } else {
            struct LinkedListNode* current = hashArraySC[i];
            while (current != NULL) {
                printf("[%d,%d]", current->key, current->data);
                if (current->next != NULL) {
                    printf(" -> ");}
                current = current->next;}}
        printf("\n");}}
void cleanupHashTables() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashArrayLP[i] != NULL && hashArrayLP[i] != DELETED_NODE) {
            free(hashArrayLP[i]);}
        if (hashArrayQP[i] != NULL && hashArrayQP[i] != DELETED_NODE) {
            free(hashArrayQP[i]);}
        if (hashArrayDH[i] != NULL && hashArrayDH[i] != DELETED_NODE) {
            free(hashArrayDH[i]);}
        struct LinkedListNode* current = hashArraySC[i];
        while (current != NULL) {
            struct LinkedListNode* temp = current;
            current = current->next;
            free(temp);}}}
void insertInAllTables(int key, int data) {
    insertLP(key, data);
    insertQP(key, data);
    insertDH(key, data);
    insertSC(key, data);}
void displayMenu() {
    printf("\n===== HASH TABLE DEMONSTRATION =====\n");
    printf("1. Insert a key-value pair");}
int main() {
    int choice, key, data;
    struct DataItem* item;
    struct LinkedListNode* node;
    bool deleted;
    initializeHashTables();
    insertInAllTables(1, 20);
    insertInAllTables(11, 30); 
    insertInAllTables(21, 40); 
    insertInAllTables(31, 50);  
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key and value to insert: ");
                scanf("%d %d", &key, &data);
                insertInAllTables(key, data);
                printf("Inserted [%d, %d] in all tables\n", key, data);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                item = searchLP(key);
                if (item != NULL) {
                    printf("Linear Probing: Found [%d, %d]\n", item->key, item->data);
                } else {
                    printf("Linear Probing: Key %d not found\n", key);}
                item = searchQP(key);
                if (item != NULL) {
                    printf("Quadratic Probing: Found [%d, %d]\n", item->key, item->data);
                } else {
                    printf("Quadratic Probing: Key %d not found\n", key);}
                item = searchDH(key);
                if (item != NULL) {
                    printf("Double Hashing: Found [%d, %d]\n", item->key, item->data);
                } else {
                    printf("Double Hashing: Key %d not found\n", key);}
                node = searchSC(key);
                if (node != NULL) {
                    printf("Separate Chaining: Found [%d, %d]\n", node->key, node->data);
                } else {
                    printf("Separate Chaining: Key %d not found\n", key);}
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleted = deleteLP(key);
                printf("Linear Probing: %s\n", deleted ? "Deleted successfully" : "Key not found");
                deleted = deleteQP(key);
                printf("Quadratic Probing: %s\n", deleted ? "Deleted successfully" : "Key not found");
                deleted = deleteDH(key);
                printf("Double Hashing: %s\n", deleted ? "Deleted successfully" : "Key not found");
                deleted = deleteSC(key);
                printf("Separate Chaining: %s\n", deleted ? "Deleted successfully" : "Key not found");
                break;
            case 4:
                displayLP();
                displayQP();
                displayDH();
                displaySC();
                break;
            case 5:
                cleanupHashTables();
                printf("Exiting program. Memory cleaned up.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");}}
    return 0;}