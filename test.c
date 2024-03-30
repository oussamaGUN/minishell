#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a command node
typedef struct Node {
    char *command;
    struct Node *next;
} Node;

// Function to create a new node
Node* createNode(char *command) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->command = strdup(command);
    newNode->next = NULL;
    return newNode;
}

// Function to parse the input expression and create the parsing tree
Node* parseExpression(char *expression) {
    Node *head = NULL;
    Node *current = NULL;
    char *token = strtok(expression, "|");

    while (token != NULL) {
        Node *newNode = createNode(token);
        if (head == NULL) {
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
        token = strtok(NULL, "|");
    }

    return head;
}

// Function to execute the parsing tree
void executeTree(Node *root) {
    Node *current = root;
    while (current != NULL) {
        printf("Executing command: %s\n", current->command);
        // Execute current command
        // Example: system(current->command);
        current = current->next;
    }
}

int main() {
    char expression[] = "ls -l | grep 'test' | wc";
    Node *root = parseExpression(expression);
    executeTree(root);

    // Free allocated memory
    Node *current = root;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->command);
        free(temp);
    }

    return 0;
}
