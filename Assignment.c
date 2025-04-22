/*
Name : Mohamed Nawfel M
Roll Number : ME24B1072

Assignment Question 4: Mars Habitat Builder Bot 
Scenario: You’re designing a Mars Habitat Builder Bot to construct habitat modules (e.g., "Wall", "Roof", "Door", "Window", "Airlock") for a Martian colony. 
The bot uses:
●	Part Delivery System (Queue): Parts arrive via rover and queue for construction.
●	Bot Task Manager (Stack): Bots stack parts in LIFO order for structural sequencing.
●	Assembly Storage Unit (Array): Finished habitats store in an array-based colony (size: 5 slots). If full, the oldest is occupied.
●	Repair and Upgrade Tracker (Linked Lists):
○	Damaged habitats go to a singly linked list.
○	Repaired habitats move to a doubly linked list for inspection.
○	High-priority habitats cycle in a circular linked list for urgent upgrades.
Objective: Simulate habitat construction, storage, and repair on Mars.
Tasks:

a) Part Delivery and Bot 
●	Simulate 6 parts (e.g., "Wall", "Roof", "Door", "Window", "Airlock", "Vent") in a queue.
●	Bots stack them in LIFO order. Write pseudocode or an algorithm to:
○	Enqueue all 6 parts.
○	Dequeue and push onto a stack.
○	Pop to show construction order.
●	Creativity Bonus: Describe (in 2-3 sentences) why LIFO fits (e.g., "Vent" last for air sealing).
b) Assembly Storage Unit 
●	Store habitats in a 5-slot array.
●	Simulate adding 7 habitats (e.g., "Hab1", "Hab2", ..., "Hab7"). If full, occupy the oldest. Write pseudocode or an algorithm to:
○	Insert the first 5 habitats.
○	Handle overflow for "Hab6" and "Hab7".
●	Creativity Bonus: Suggest (in 2-3 sentences) a reason for occupation (e.g., settler arrival).
c) Damaged Habitat Tracker 
●	"Hab3" and "Hab6" are damaged. Add to a singly linked list.
●	Move "Hab3" to a doubly linked list post-repair. Write pseudocode or an algorithm to:
○	Insert "Hab3" and "Hab6".
○	Delete "Hab3" and insert it into the doubly linked list.
○	Traverse forward and backward.
●	Creativity Bonus: Propose (in 2-3 sentences) a damage and fix (e.g., "Hab3’s door cracked by dust storm, sealed by bots").
d) Priority Upgrades 
●	"Hab1" and "Hab4" need upgrades (e.g., solar panels). Add to a circular linked list. Write pseudocode or an algorithm to:
○	Insert "Hab1" and "Hab4".
○	Traverse twice.
●	Creativity Bonus: Invent (in 2-3 sentences) an upgrade (e.g., "Hab4 gets a greenhouse dome").
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_PARTS 6
#define MAX_HABITATS 5


// ---------------------------- Part Delivery and Bot  ----------------------------


// Queue

char *queue[MAX_PARTS];
int front = -1;
int rear = -1;

void enqueue (char *part) 
{
    if (rear == MAX_PARTS - 1) 
    {
        return;
    }

    if (front == -1) 
    {
        front = 0;
    }

    queue[++rear] = part;
}

char* dequeue () 
{
    if (front == -1 || front > rear) 
    {
        return NULL;
    }

    return queue[front++];
}

// Stack

char *stack[MAX_PARTS];
int top = -1;

void push (char *part) 
{
    if (top == MAX_PARTS - 1)
    {
        return;
    } 

    stack[++top] = part;
}

char *pop () 
{
    if (top == -1) 
    {
        return NULL;
    }

    return stack[top--];
}


// ---------------------------- Assembly Storage Unit ----------------------------


char *HA[MAX_HABITATS];
int HI = 0;

void addHabitat (char *hab) 
{
    if (HI < MAX_HABITATS) 
    {
        HA[HI++] = hab;
    } 
    else 
    {
        // Occupy oldest

        for (int i = 1; i < MAX_HABITATS; i++) 
        {
            HA[i - 1] = HA[i];
        }

        HA[MAX_HABITATS - 1] = hab;
    }
}


// ---------------------------- Damaged Habitat Tracker ----------------------------


// Singly Linked List

struct Node 
{
    char name[10];
    struct Node *next;
};

struct Node *DH = NULL;

void insertDamaged (char *name) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->next = DH;
    DH = newNode;
}

void removeDamaged (char *name) 
{
    struct Node *temp = DH;
    struct Node *prev = NULL;
    while (temp && strcmp(temp->name, name) != 0) 
    {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) 
    {
        return;
    }

    if (!prev) 
    {
        DH = temp->next;
    }
    else 
    {
        prev->next = temp->next;
    }

    free(temp);
}

// Doubly Linked List


struct DNode 
{
    char name[10];
    struct DNode *prev;
    struct DNode *next;
};

struct DNode *RH = NULL;

void insertRepaired (char *name) 
{
    struct DNode* newNode = (struct DNode*)malloc(sizeof(struct DNode));

    strcpy(newNode->name, name);
    newNode->prev = NULL;
    newNode->next = RH;

    if (RH) 
    {
        RH->prev = newNode;
    }

    RH = newNode;
}

void traverseForward () 
{
    struct DNode* temp = RH;

    printf("Traverse forward: ");

    while (temp) 
    {
        printf("%s -> ", temp->name);
        temp = temp->next;
    }

    printf("NULL\n");
}

void traverseBackward () 
{
    struct DNode* temp = RH;

    while (temp && temp->next) 
    {
        temp = temp->next;
    }

    printf("Traverse backward: ");

    while (temp) 
    {
        printf("%s -> ", temp->name);
        temp = temp->prev;
    }

    printf("NULL\n");
}

// ---------------------------- Damaged Habitat Tracker ----------------------------
struct CNode 
{
    char name[10];
    struct CNode *next;
};

struct CNode *CH = NULL;

void insertCircular (char *name) 
{
    struct CNode* newNode = (struct CNode *)malloc(sizeof(struct CNode));
    strcpy(newNode->name, name);
    if (!CH) 
    {
        CH = newNode;
        newNode->next = CH;
    } 
    else 
    {
        struct CNode* temp = CH;

        while (temp->next != CH)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->next = CH;
    }
}

void traverseCircular (int times) 
{
    if (!CH) 
    {
        return;
    }

    struct CNode* temp = CH;

    printf("Circular traversal: ");

    for (int i = 0; i < times * 2; i++) 
    {
        printf("%s -> ", temp->name);
        temp = temp->next;
    }

    printf("...\n");
}

// ---------------------------- MAIN ----------------------------


int main () 
{
    // Part Delivery and Bot


    printf("=== Part A: Part Delivery and Bot ===\n");

    char* parts[MAX_PARTS] = {"Wall", "Roof", "Door", "Window", "Airlock", "Vent"};

    for (int i = 0; i < MAX_PARTS; i++)
    {
        enqueue(parts[i]);
    }

    for (int i = 0; i < MAX_PARTS; i++)
    {
        push(dequeue());
    }

    printf("Construction Order (LIFO): ");

    for (int i = 0; i < MAX_PARTS; i++)
    {
        printf("%s ", pop());
    }

    printf("\n");

    // Bonus

    printf("// LIFO fits since 'Vent' (last pushed) is placed last for air sealing after core structures.\n\n");

    // Assembly Storage Unit


    printf("=== Part B: Assembly Storage Unit ===\n");

    char *habitats[7] = {"Hab1", "Hab2", "Hab3", "Hab4", "Hab5", "Hab6", "Hab7"};
    for (int i = 0; i < 7; i++)
    {
        addHabitat(habitats[i]);
    }
    printf("Current Habitats in Storage:\n");
    
    for (int i = 0; i < MAX_HABITATS; i++)
    {
        printf("%s ", HA[i]);
    }
    
    printf("\n");
    
    // Bonus
    
    printf("// Older habitats replaced due to new settlers requiring immediate shelter.\n\n");

    
    // Damaged Habitat Tracker

    
    printf("=== Part C: Damaged Habitat Tracker ===\n");
    
    insertDamaged("Hab3");
    insertDamaged("Hab6");
    
    printf("Damaged List: ");
    
    struct Node* temp = DH;
    
    while (temp) 
    {
        printf("%s -> ", temp->name);
        temp = temp->next;
    }
    
    printf("NULL\n");
    
    removeDamaged("Hab3");
    insertRepaired("Hab3");
    
    traverseForward();
    traverseBackward();
    
    // Bonus
    
    printf("// Hab3’s door cracked due to a dust storm; bots repaired and sealed it airtight.\n\n");
    
    
    // Priority Upgrades

    
    printf("=== Part D: Priority Upgrades ===\n");
    insertCircular("Hab1");
    insertCircular("Hab4");
    
    traverseCircular(2);
    
    // Bonus
    printf("// Hab4 receives a greenhouse dome for sustainable oxygen and crops.\n");
    
    return 0;
}
