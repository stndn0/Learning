/* Basic Hash Table Implementation via Linked List */
/*
    Takes value and generates a hash key. Insert value into a hash table slot (slot = key).
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


#define SIZE 26
#define LENGTH 50

int key;
char value[LENGTH];

typedef struct node
{
    char data[LENGTH];
    struct node* next;
}   
node;
node* head = NULL;



// Hash Function 
unsigned int hash(const char *word)
{
    key = tolower(word[0]) - 'a';  // return a key between 0 and 26-1
    key = key % SIZE;
    return key++;
}

// Function to create a single new node at the end of a list
void createNode (struct node** head, char new_data[LENGTH])
{
    // 1. Allocate memory for the new node.
    node* new_node = malloc(sizeof(node));
    node* last = *head;

    // 2. Place data within the new node.
    strcpy(new_node -> data, new_data);

    // 3. As this new node will be the last node in the list, point it to NULL.
    new_node -> next = NULL;

    // 4. If the list is empty, make this new node the head.
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    // 5. Otherwise, traverse until you find the last node.
    while (last -> next != NULL)
    {
        last = last -> next;
    }

    // 6. Then make the last node point to our new node.
    last -> next = new_node;
    return;
}

// Function to create a hash table with size = 10 nodes
void createTable (int size)
{
    for (int i = 1; i <= size; i++)
    {
        createNode(&head, "Empty");
    }
}

// Function to modify a specific node
void modifyNode (int pos, char new_data[LENGTH])
{
    struct node *temp;

    // If list is empty
    if (head == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    temp = head;

    for (int i = 1; i < pos; i++)
    {
            temp = temp->next;
    }
    strcpy(temp -> data, new_data);
}

// Print the entire table
void printTable(struct node *node) 
{ 
    int counter = 1;
    while (node != NULL) 
    { 
        printf("Slot %d: %s \n", counter, node->data); 
        node = node->next; 
        counter++;
    } 
} 

// Print an individual node
void printNode(struct node *node, int pos)
{
    struct node *temp;

    // If list is empty
    if (head == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    temp = head;

    for (int i = 1; i < pos; i++)
    {
            temp = temp->next;
    }
    printf("Node %d = %s \n", pos, temp->data);
}

// You must free memory used by the Linked List when you are finished.
void deleteList(struct node** head)
{
    // Create a new pointer called Current to keep track of where we are in the list.
    struct node* current = *head;
    struct node* next;

    // Delete the contents of the list until the end of the list is reached.
    while (current != NULL) // Repeat until we reach the end of the list.
    {
        // Point the pointer "next" to the adjacent node of where we currently are in the list.
        // If we don't do this, our link with the rest of the list is lost.
        next = current -> next;

        free(current);
        current = next;
    }
    *head = NULL;
}

int main()
{
    // Function call to create a hash table of size N
    createTable(SIZE);
    
    while(1)
    {
        // Get a user value and generate a hash key
        printf("Enter a value to generate a hash key: ");
        scanf(" %s", value);
        hash(value);
        printf("Hash Value: %s | Hash Key: %d  \n", value, key);
        
        //Function call(s) to add entries to the hash table
        modifyNode(key, value);
        
        // Function call to print the contents of the hash table
        printf("\n**Hash Table**\n");
        printf("Key     Value \n");
        printTable(head);
        printf("\n");
    }
    // Delete the list.
    deleteList(&head);
}