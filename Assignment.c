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
#include <string.h>


#define MP 6     // Max parts
#define MH 5     // Storage slots
#define MN 20


// ---------- Queue ----------


char *queue[MP];
int front = -1;
int rear = -1;

void enqueue (char *part) 
{
    if (rear == MP - 1) 
    {
        printf("Queue full! Cannot enqueue %s\n", part);
        return;
    }

    if (front == -1) 
    {
        front = 0;
    }

    queue[++rear] = part;
}

char *dequeue () 
{
    if (front == -1 || front > rear) 
    {
        return NULL;
    }

    return queue[front++];
}


// ---------- Stack ----------


char *stack[MP];
int top = -1;

void push (char *part) 
{
    if (top == MP - 1) 
    {
        printf("Stack overflow!\n");
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


// ---------- Assembly Storage (Array) ----------


char *HA[MH];
int HI = 0;

void AddHab (char *hab) 
{
    if (HI < MH) 
    {
        HA[HI++] = hab;
    } 
    else 
    {
        // Remove oldest

        free(HA[0]);

        for (int i = 1; i < MH; i++) 
        {
            HA[i-1] = HA[i];
        }

        HA[MH-1] = hab;
    }
}


// ---------- Singly Linked List (Damaged) ----------


struct Node 
{
    char name[MN];
    struct Node *next;
};


struct Node *DH = NULL;


void insDamaged (char *name) 
{
    struct Node *newNode = malloc(sizeof(*newNode));

    strcpy (newNode->name, name);

    newNode->next = DH;
    DH = newNode;
}

void remDamaged (char *name) 
{
    struct Node *curr = DH, *prev = NULL;

    while (curr && strcmp (curr->name, name) != 0) 
    {
        prev = curr; 
        curr = curr->next;
    }

    if (!curr) 
    {
        return;
    }

    if (!prev) 
    {
        DH = curr->next;
    }
    else 
    {
        prev->next = curr->next;
    }

    free (curr);
}


// ---------- Doubly Linked List (Repaired) ----------


struct DNode 
{
    char name[MN];
    struct DNode *prev, *next;
};

struct DNode *RH = NULL;

void insRepair (char *name) 
{
    struct DNode *newNode = malloc(sizeof(*newNode));

    strcpy (newNode->name, name);

    newNode->prev = NULL;
    newNode->next = RH;

    if (RH) 
    {
        RH->prev = newNode;
    }

    RH = newNode;
}

void travForward () 
{
    struct DNode *temp = RH;

    printf ("Forward: ");

    while (temp) 
    { 
        printf ("%s -> ", temp->name); 
        temp = temp->next; 
    }

    printf ("NULL\n");
}


void tracBackward () 
{
    struct DNode *temp = RH;

    if (!temp) 
    {
        return;
    }

    while (temp->next) 
    {
        temp = temp->next;
    }

    printf ("Backward: ");

    while (temp) 
    { 
        printf ("%s -> ", temp->name); 
        temp = temp->prev; 
    }

    printf ("NULL\n");
}


// ---------- Circular Linked List (Priority) ----------


struct CNode 
{
    char name[MN];
    struct CNode *next;
};

struct CNode *CH = NULL;

void insCir (char *name) 
{
    struct CNode *newNode = malloc (sizeof(*newNode));

    strcpy (newNode->name, name);

    if (!CH) 
    {
        CH = newNode;
        newNode->next = CH;
    } 
    else 
    {
        struct CNode *temp = CH;

        while (temp->next != CH) 
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->next = CH;
    }
}

void travCir (int laps) 
{
    if (!CH) 
    {
        return;
    }

    struct CNode *temp = CH;

    printf ("Circular: ");

    for (int i = 0; i < laps * 2; i++) 
    {
        printf ("%s -> ", temp->name);
        temp = temp->next;
    }

    printf ("...\n");
}

int main() 
{
    char buffer [MN];


    // Part A: User inputs for parts


    printf ("Enter %d part names for construction:\n", MP);

    char *parts [MP];

    for (int i = 0; i < MP; i++) 
    {
        printf ("Part %d: ", i+1);

        fgets (buffer, MN, stdin);
        buffer [strcspn(buffer, "\n")] = '\0';
        parts [i] = strdup(buffer);

        enqueue (parts [i]);
    }


    // Move to stack and build order


    for (int i = 0; i < MP; i++) 
    {
        push (dequeue ());
    }

    printf ("\nConstruction Order (LIFO): ");

    for (int i = 0; i < MP; i++) 
    {
        printf ("%s ", pop ());
    }

    printf ("\n\n");


    // Part B: User inputs for habitats


    int total;

    printf ("Enter total habitats to add (>=%d): ", MH+2);

    scanf ("%d", &total);

    getchar (); // consume newline

    for (int i = 0; i < total; i++) 
    {
        printf ("Habitat %d: ", i+1);

        fgets (buffer, MN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        char *name = strdup(buffer);

        AddHab (name);
    }


    printf ("\nCurrent Storage:\n");

    for (int i = 0; i < MH; i++) 
    {
        printf ("%s ", HA[i]);
    }

    printf ("\n\n");


    // Part C: Damaged habitats


    int dcount;

    printf ("Enter number of damaged habitats: ");

    scanf ("%d", &dcount);
    getchar ();

    for (int i = 0; i < dcount; i++) 
    {
        printf ("Damaged habitat #%d: ", i+1);

        fgets (buffer, MN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        insDamaged (buffer);
    }

    printf("Damaged List: ");

    struct Node *tempN = DH;

    while (tempN) 
    { 
        printf ("%s -> ", tempN->name); 
        tempN = tempN->next; 
    }

    printf ("NULL\n");


    // Repair one habitat


    printf ("Enter habitat name to repair: ");

    fgets(buffer, MN, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    remDamaged (buffer);

    insRepair (buffer);

    travForward ();

    tracBackward ();

    printf("\n");


    // Part D: Priority upgrades


    int pcount;

    printf ("Enter number of priority habitats: ");

    scanf ("%d", &pcount);
    getchar ();

    for (int i = 0; i < pcount; i++) 
    {
        printf ("Priority habitat #%d: ", i+1);

        fgets (buffer, MN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        
        insCir (buffer);
    }

    travCir (2);

    return 0;
}
