#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct ItemL *ptrItem;
typedef struct VehicleL *ptrVehicle;
typedef struct vehicleQueue *ptrQueue;
typedef FILE *ptrFile;

// Define a struct for data related to an item
struct dataItem
{
    int identifier;     // Unique identifier for the item
    char entryDate[11]; // Date of entry (formatted as "YYYY/MM/DD")
    int wilaya;         // Wilaya (region) associated with the item
    float weight;       // Weight of the item
    char status[21];    // Status of the item
};

// Define a struct for data related to a vehicle
struct dataVehicle
{
    char type[5];   // Type of vehicle
    int identifier; // Unique identifier for the vehicle
    int capacity;   // Maximum capacity of the vehicle (how many items it can carry)
};

// Define a linked list node for items
struct ItemL
{
    struct dataItem dataI; // Data associated with the item
    struct ItemL *next;    // Pointer to the next item in the list
};

// Define a linked list node for vehicles
struct VehicleL
{
    struct dataVehicle dataV; // Data associated with the vehicle
    int trips;                // Maximum trips
    ptrItem item;             // Item assigned to vehicle
    struct VehicleL *next;    // Pointer to the next vehicle in the list
};

// Define a queue structure for vehicles
typedef struct vehicleQueue
{
    ptrVehicle head; // Pointer to the head of the queue
    ptrVehicle tail; // Pointer to the tail of the queue
} vehicleQueue;

//-----------------------------------------------------------HEADER PART----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------Abstract Machine item Part------------------------------------------

void allocateItem(ptrItem *item);
void assignIdentifierItem(ptrItem item, int identifier);
void assignDate(ptrItem item, const char *date);
void assignWilaya(ptrItem item, int wilaya);
void assignWeight(ptrItem item, float weight);
void assignStatus(ptrItem item, const char *status);
void assignItem(ptrItem item, dataItem source);
void assignAddressItem(ptrItem first, ptrItem second);
int infoIdentifierItem(ptrItem item);
const char *infoEntryDate(ptrItem item);
int infoWilaya(ptrItem item);
float infoWeight(ptrItem item);
const char *infoStatus(ptrItem item);
dataItem infoItem(ptrItem item);
ptrItem nextItem(ptrItem item);
ptrItem findTailItem(ptrItem *head);
ptrItem createItem(dataItem info);
int lengthOfItemList(ptrItem head);
ptrItem cloneItemList(ptrItem head);
void readItemInfo(dataItem *info);

//------------------------------------------------------Abstract Machine Vehicle Part------------------------------------------

void allocateVehicle(ptrVehicle *vehicle);
void assignType(ptrVehicle vehicle, char type[]);
void assignIdentifierVehicle(ptrVehicle vehicle, int identifier);
void assignCapacity(ptrVehicle vehicle, int capacity);
void assignTrips(ptrVehicle vehicle, int trips);
void assignItemToVehicle(ptrVehicle vehicle, ptrItem item);
void assignVehicle(ptrVehicle vehicle, dataVehicle source);
void assignAddressVehicle(ptrVehicle first, ptrVehicle second);
const char *infoType(ptrVehicle vehicle);
int infoIdentifierVehicle(ptrVehicle vehicle);
int infoCapacity(ptrVehicle vehicle);
int infoTrips(ptrVehicle vehicle);
ptrItem getAssignedItem(ptrVehicle vehicle);
dataVehicle infoVehicle(ptrVehicle vehicle);
ptrVehicle nextVehicle(ptrVehicle vehicle);
ptrVehicle findTailVehicle(ptrVehicle head);
ptrVehicle createVehicle(dataVehicle info);
int lengthOfVehicleList(ptrVehicle head);
void readVehicleInfo(dataVehicle *info);

//------------------------------------------------------Abstract Machine Queue Part------------------------------------------

void allocateQueue(ptrQueue *queue);
void assignHead(ptrQueue queue, ptrVehicle vehicle);
void assignTail(ptrQueue queue, ptrVehicle vehicle);
ptrVehicle getHead(ptrQueue queue);
ptrVehicle getTail(ptrQueue queue);
ptrQueue createQueue();
bool isEmpty(ptrQueue queue);
void enqueue(ptrQueue queue, ptrVehicle newVehicle);
ptrVehicle dequeue(ptrQueue queue);

//------------------------------------------------------File Part------------------------------------------

int linesInFile(char *filename);
void readItemFile(char *fileName, dataItem items[], int size);
void readVehicleFile(char *fileName, dataVehicle vehicles[], int size);

//------------------------------------------------------Item Part------------------------------------------

ptrItem createItemL(dataItem info[], int numberOfItems);
void displayItemL(ptrItem head);
void addItem(ptrItem *head, dataItem newInfo);
void accessByIdentifierItem(ptrItem head, int identifier, ptrItem *current, ptrItem *previous);
void deleteItem(ptrItem *head, int identifier);

//------------------------------------------------------Vehicle Part------------------------------------------

ptrVehicle createVehicleL(dataVehicle info[], int numberOfVehicle);
void displayVehicleL(ptrVehicle head);
void addVehicle(ptrVehicle *head, ptrVehicle newVehicle);
void accessByIdentifier(ptrVehicle head, int identifier, ptrVehicle *current, ptrVehicle *previous);
ptrVehicle deleteVehicle(ptrVehicle *head, int identifier);

//------------------------------------------------------Queue Part------------------------------------------

ptrQueue createMotoQ(dataVehicle info[], int size);
ptrQueue createVansQ(dataVehicle info[], int size);
void synchronizeAddQueue(ptrVehicle vehicle, ptrQueue moto, ptrQueue van);
void synchronizeDeleteQueue(ptrVehicle vehicle, int identifier, ptrQueue moto, ptrQueue van);

//------------------------------------------------------Delivery Part------------------------------------------

int convertDate(ptrItem item);
void swap(ptrItem first, ptrItem second);
void sortByDate(ptrItem head);
void addItemToVehicle(ptrItem item, ptrVehicle vehicle);
void linkItemVan(ptrItem item, ptrQueue van);
void linkItemMoto(ptrItem item, ptrQueue Moto);
bool searchAwaiting(ptrItem item);
void simulateDelivery(ptrItem item, ptrQueue moto, ptrQueue van, ptrVehicle *dequeuedVehicle);

//------------------------------------------------------Delivery comeback Part------------------------------------------

void deliveredOrReturned(ptrVehicle head);
void removeDeliveredItem(ptrItem *item);
void updateStatusItem(ptrVehicle vehicle, ptrItem item);
void vehicleComeback(ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van);
void simulateComeback(ptrItem *items, ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van);

//------------------------------------------------------Return pick-up Part------------------------------------------

void removeReturnedItem(ptrItem *item);
void vehicleReturn(ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van);
void simulatePickup(ptrItem *item, ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van);

//------------------------------------------------------Report Part------------------------------------------

void updateItemsFile(ptrItem head, char *filename);
int numberOfDeliveredItem(ptrItem original, ptrItem updated);
int numberOfReturnedItem(ptrItem itemList);
int numberOfRetiredVehicle(ptrVehicle vehicleList);

//------------------------------------------------------Next day Part------------------------------------------

void resetTrips(ptrVehicle vehicle);

//-----------------------------------------------------------FUNCTION PART--------------------------------------------
//---------------------------------------------------------------------------------------------------------------
//------------------------------------------------------Abstract Machine item Part------------------------------------------

// Function to allocate memory for an item
void allocateItem(ptrItem *item)
{
    *item = (ptrItem)malloc(sizeof(ItemL));
}

// Function to assign identifier to an item
void assignIdentifierItem(ptrItem item, int identifier)
{
    item->dataI.identifier = identifier;
}

// Function to assign entry date to an item
void assignDate(ptrItem item, const char *date)
{
    strcpy(item->dataI.entryDate, date);
}

// Function to assign Wilaya (region) to an item
void assignWilaya(ptrItem item, int wilaya)
{
    item->dataI.wilaya = wilaya;
}

// Function to assign weight to an item
void assignWeight(ptrItem item, float weight)
{
    item->dataI.weight = weight;
}

// Function to assign status to an item
void assignStatus(ptrItem item, const char *status)
{
    strcpy(item->dataI.status, status);
}

// Function to assign all attributes of an item
void assignItem(ptrItem item, dataItem source)
{
    assignIdentifierItem(item, source.identifier);
    assignDate(item, source.entryDate);
    assignWilaya(item, source.wilaya);
    assignWeight(item, source.weight);
    assignStatus(item, source.status);
}

// Function to assign address of the next item
void assignAddressItem(ptrItem first, ptrItem second)
{
    first->next = second;
}

// Function to retrieve identifier of an item
int infoIdentifierItem(ptrItem item)
{
    return item->dataI.identifier;
}

// Function to retrieve entryDate of an item
const char *infoEntryDate(ptrItem item)
{
    return item->dataI.entryDate;
}

// Function to retrieve Wilaya of an item
int infoWilaya(ptrItem item)
{
    if (item != NULL)
    {
        return item->dataI.wilaya;
    }
    else
    {
        return 0; // Return a default value or handle it according to your application logic
    }
}

// Function to retrieve weight of an item
float infoWeight(ptrItem item)
{
    return item->dataI.weight;
}

// Function to retrieve status of an item
const char *infoStatus(ptrItem item)
{
    return item->dataI.status;
}

// Function to retrieve all information about an item
dataItem infoItem(ptrItem item)
{
    return item->dataI;
}

// Function to retrieve the next item
ptrItem nextItem(ptrItem item)
{
    if (item == NULL)
    {
        // Handle error or empty list
        return NULL;
    }
    return item->next;
}

// Function to find the last item in the list
ptrItem findTailItem(ptrItem *head)
{
    ptrItem temp = *head;
    while (nextItem(temp) != NULL)
    {
        temp = nextItem(temp);
    }
    return temp;
}

// Function to create a new item
ptrItem createItem(dataItem info)
{
    ptrItem item;
    allocateItem(&item);
    assignItem(item, info);
    assignAddressItem(item, NULL);
    return item;
}

// Function to calculate the length of the item list
int lengthOfItemList(ptrItem head)
{
    if (head == NULL)
    {
        return 0;
    }

    int length = 0;
    while (head != NULL)
    {
        length++;
        head = nextItem(head);
    }
    return length;
}

// Function to clone a linked list of items
ptrItem cloneItemList(ptrItem head)
{
    if (head == NULL)
    {
        return NULL;
    }

    ptrItem newHead = createItem(infoItem(head)); // Create a new head node for the cloned list with the same data as the original head
    ptrItem current = nextItem(head);             // Pointer to the current node in the original list
    ptrItem newCurrent = newHead;                 // Pointer to the current node in the cloned list

    // Traverse the original list
    while (current != NULL)
    {
        assignAddressItem(newCurrent, createItem(infoItem(current))); // Create a new node in the cloned list with the same data as the current node in the original list

        // Move to the next node in both the original and cloned lists
        newCurrent = nextItem(newCurrent);
        current = nextItem(current);
    }
    return newHead; // Return the head of the cloned list
}

// Function to read item data from the user
void readItemInfo(dataItem *info)
{
    printf("Enter the weight of the Item: ");
    scanf("%f", &(info->weight));

    printf("Enter the wilaya: ");
    scanf("%d", &(info->wilaya));

    // Assuming the entry date is always set to "2024/04/14"
    strcpy(info->entryDate, "2024/04/14");

    // Assuming the status is always set to "awaiting delivery"
    strcpy(info->status, "awaiting delivery");
}

//------------------------------------------------------Abstract Machine Vehicle Part------------------------------------------

// Function to allocate memory for a vehicle
void allocateVehicle(ptrVehicle *vehicle)
{
    *vehicle = (ptrVehicle)malloc(sizeof(VehicleL));
}

// Function to assign type to a vehicle
void assignType(ptrVehicle vehicle, char type[])
{
    strcpy(vehicle->dataV.type, type);
}

// Function to assign identifier to a vehicle
void assignIdentifierVehicle(ptrVehicle vehicle, int identifier)
{
    vehicle->dataV.identifier = identifier;
}

// Function to assign capacity to a vehicle
void assignCapacity(ptrVehicle vehicle, int capacity)
{
    vehicle->dataV.capacity = capacity;
}

// Function to assign number of trips to a vehicle
void assignTrips(ptrVehicle vehicle, int trips)
{
    vehicle->trips = trips;
}

// Functions to assign an item to a vehicle
void assignItemToVehicle(ptrVehicle vehicle, ptrItem item)
{
    vehicle->item = item;
}

// Function to assign all attributes of a vehicle
void assignVehicle(ptrVehicle vehicle, dataVehicle source)
{
    assignType(vehicle, source.type);
    assignIdentifierVehicle(vehicle, source.identifier);
    assignCapacity(vehicle, source.capacity);
}

// Function to assign address of the next vehicle
void assignAddressVehicle(ptrVehicle first, ptrVehicle second)
{
    first->next = second;
}

// Function to retrieve type of the vehicle
const char *infoType(ptrVehicle vehicle)
{
    return vehicle->dataV.type;
}

// Function to retrieve identifier of a vehicle
int infoIdentifierVehicle(ptrVehicle vehicle)
{
    return vehicle->dataV.identifier;
}

// Function to retrieve capacity of a vehicle
int infoCapacity(ptrVehicle vehicle)
{

    if (vehicle == NULL)
    {
        return 0;
    }
    return vehicle->dataV.capacity;
}

// Function to retrieve number of trips of a vehicle
int infoTrips(ptrVehicle vehicle)
{
    return vehicle->trips;
}

// Function to retrieve assigned item of a vehicle
ptrItem getAssignedItem(ptrVehicle vehicle)
{
    if (vehicle != NULL)
    {
        return vehicle->item;
    }
    else
    {
        return NULL;
    }
}

// Function to retrieve all information about a vehicle
dataVehicle infoVehicle(ptrVehicle vehicle)
{
    return vehicle->dataV;
}

// Function to retrieve the next vehicle
ptrVehicle nextVehicle(ptrVehicle vehicle)
{
    return vehicle->next;
}

// Function to find the last vehicle in the list
ptrVehicle findTailVehicle(ptrVehicle head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        ptrVehicle temp = head;
        while (nextVehicle(temp) != NULL)
        {
            temp = nextVehicle(temp);
        }
        return temp;
    }
}

// Function to create a new vehicle
ptrVehicle createVehicle(dataVehicle info)
{
    ptrVehicle vehicle;

    allocateVehicle(&vehicle);
    assignVehicle(vehicle, info);
    assignTrips(vehicle, 0);
    assignItemToVehicle(vehicle, NULL);
    assignAddressVehicle(vehicle, NULL);
    return vehicle;
}

// Function to calculate the length of the vehicle list
int lengthOfVehicleList(ptrVehicle head)
{
    if (head == NULL)
    {
        return 0;
    }

    int length = 0;
    while (head != NULL)
    {
        length++;
        head = nextVehicle(head);
    }
    return length;
}

// Function to read vehicle information from the user
void readVehicleInfo(dataVehicle *info)
{
    printf("Enter type of vehicle (Moto or Vans): ");
    scanf("%s", info->type);

    while (strcmp(info->type, "Moto") != 0 && strcmp(info->type, "Vans") != 0)
    {
        printf("Invalid vehicle type entered. Please re-enter: \n");
        scanf("%s", info->type);
    }

    printf("Enter the capacity of the %s (in Moto case doesn't pass 2 items): ", info->type);
    scanf("%d", &(info->capacity));

    while (strcmp(info->type, "Moto") == 0 && info->capacity >= 3)
    {
        printf("Enter the capacity of the %s (in Moto case doesn't pass 2 items): ", info->type);
        scanf("%d", &(info->capacity));
    }
}

//------------------------------------------------------Abstract Machine Queue Part------------------------------------------

// Function to allocate memory for a queue
void allocateQueue(ptrQueue *queue)
{
    *queue = (ptrQueue)malloc(sizeof(vehicleQueue));
}

// Function to assign head of the queue
void assignHead(ptrQueue queue, ptrVehicle vehicle)
{
    queue->head = vehicle;
}

// Function to assign tail of the queue
void assignTail(ptrQueue queue, ptrVehicle vehicle)
{
    queue->tail = vehicle;
}

// Function to retrieve head of the queue
ptrVehicle getHead(ptrQueue queue)
{
    return queue->head;
}

// Function to retrieve tail of the queue
ptrVehicle getTail(ptrQueue queue)
{
    return queue->tail;
}

// Function to create a new queue
ptrQueue createQueue()
{
    ptrQueue queue;

    allocateQueue(&queue);
    assignHead(queue, NULL);
    assignTail(queue, NULL);
    return queue;
}

// Function to check if the queue is empty
bool isEmpty(ptrQueue queue)
{
    return getHead(queue) == NULL;
}

// Function to add a vehicle to the queue
void enqueue(ptrQueue queue, ptrVehicle newVehicle)
{

    if (isEmpty(queue))
    {
        assignHead(queue, newVehicle);
        assignTail(queue, newVehicle);
    }
    else
    {
        assignAddressVehicle(getTail(queue), newVehicle);
        assignTail(queue, newVehicle);
    }
}

// Function to remove a vehicle from the queue
ptrVehicle dequeue(ptrQueue queue)
{
    if (isEmpty(queue))
    {
        return NULL;
    }
    else
    {
        ptrVehicle temp = getHead(queue);

        assignTrips(temp, infoTrips(temp) + 1);
        assignHead(queue, nextVehicle(getHead(queue)));
        assignAddressVehicle(temp, NULL);

        if (isEmpty(queue))
        {
            assignTail(queue, NULL);
        }
        return temp;
    }
}

//------------------------------------------------------File Part------------------------------------------

// Function to count the number of lines in a file
int linesInFile(char *filename)
{
    int count = 0;                       // Initialize count to 0
    ptrFile file = fopen(filename, "r"); // Open file in read mode

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return -1; // Return -1 if file cannot be opened
    }

    char column = fgetc(file); // Read characters from file
    while (column != EOF)      // Loop until end of file
    {
        if (column == '\n') // Check for newline character
        {
            count++; // Increment count for each newline
        }
        column = fgetc(file); // Read next character
    }
    count++;
    fclose(file); // Close file
    return count; // Return count of lines
}

// Function to read item data from file
void readItemFile(char *fileName, dataItem items[], int size)
{
    ptrFile file = fopen(fileName, "r"); // Open file in read mode

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return; // Return if file cannot be opened
    }

    int count = 0; // Initialize count to 0
    while (count < size && fscanf(file, "%d %10s %d %f %20[^\n]", &items[count].identifier, items[count].entryDate, &items[count].wilaya, &items[count].weight, items[count].status) == 5)
    {
        count++; // Increment count for each successfully read item
    }
    fclose(file); // Close file
}

// Function to read vehicle data from file
void readVehicleFile(char *fileName, dataVehicle vehicles[], int size)
{
    ptrFile file = fopen(fileName, "r"); // Open file in read mode

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return; // Return if file cannot be opened
    }

    int count = 0; // Initialize count to 0
    while (count < size && fscanf(file, "%[^ ] %d %d\n", vehicles[count].type, &vehicles[count].identifier, &vehicles[count].capacity) == 3)
    {
        count++; // Increment count for each successfully read vehicle
    }
    fclose(file); // Close file
}

//------------------------------------------------------Item Part------------------------------------------

// Function to create a linked list of items
ptrItem createItemL(dataItem info[], int numberOfItems)
{
    ptrItem head = NULL;    // Initialize head to NULL
    ptrItem current = NULL; // Initialize current to NULL

    for (int i = 0; i < numberOfItems; i++)
    {
        ptrItem temp = createItem(info[i]); // Create a new item
        if (head == NULL)                   // If list is empty
        {
            head = temp;    // Set head to temp
            current = temp; // Set current to temp
        }
        else
        {
            assignAddressItem(current, temp); // Assign address of temp to current
            current = temp;                   // Set current to temp
        }
    }
    return head; // Return head of the list
}

// Function to display items in the linked list
void displayItemL(ptrItem head)
{
    if (head == NULL)
    {
        printf("\t\t\t\t\t\t\033[91mNo item available.\033[0m\n");
        return;
    }
    ptrItem current = head; // Initialize current to head

    printf("\t\t\t\t| ID | Entry Date  | Wilaya | Weight | Status            |\n");
    printf("\t\t\t\t|----|-------------|--------|--------|-------------------|\n");

    while (current != NULL) // Loop until end of list
    {
        dataItem item = infoItem(current);                                                                                                         // Get information of current item
        printf("\t\t\t\t| %02d | %10s  |   %02d   |  %.1f   | %-17s |\n", item.identifier, item.entryDate, item.wilaya, item.weight, item.status); // Display item information
        current = nextItem(current);                                                                                                               // Move to next item
    }
}

// Function to add a new item to the end of the linked list
void addItem(ptrItem *head, dataItem newInfo)
{
    ptrItem newItem = createItem(newInfo); // Create a new item

    if (*head == NULL) // If list is empty
    {
        *head = newItem; // Set head to new item
    }
    else
    {
        assignAddressItem(findTailItem(head), newItem); // Assign address of new item to the tail of the list
    }
}

// Function to access item by identifier
void accessByIdentifierItem(ptrItem head, int identifier, ptrItem *current, ptrItem *previous)
{
    *current = head;  // Set current to head
    *previous = NULL; // Set previous to NULL

    while (*current != NULL && infoIdentifierItem(*current) != identifier) // Loop until identifier is found or end of list
    {
        *previous = *current;          // Set previous to current
        *current = nextItem(*current); // Move to next item
    }
    if (*current == NULL) // If identifier is not found
    {
        return;
    }
}

// Function to delete an item from the linked list by identifier
void deleteItem(ptrItem *head, int identifier)
{
    ptrItem current;
    ptrItem previous;

    accessByIdentifierItem(*head, identifier, &current, &previous); // Access item by identifier

    if (current == NULL) // If item is not found
    {
        return; // Return
    }
    if (previous == NULL) // If item is the head of the list
    {
        *head = nextItem(*head); // Set head to next item
    }
    else
    {
        assignAddressItem(previous, nextItem(current)); // Remove current Item from the list
    }
    free(current); // Delete current item
}

//------------------------------------------------------Vehicle Part------------------------------------------

// Function to create a linked list of vehicles
ptrVehicle createVehicleL(dataVehicle info[], int numberOfVehicle)
{
    ptrVehicle head = NULL;    // Initialize head to NULL
    ptrVehicle current = NULL; // Initialize current to NULL

    for (int i = 0; i < numberOfVehicle; i++)
    {
        ptrVehicle temp = createVehicle(info[i]); // Create a new vehicle
        if (head == NULL)                         // If list is empty
        {
            head = temp;    // Set head to temp
            current = temp; // Set current to temp
        }
        else
        {
            assignAddressVehicle(current, temp); // Assign address of temp to current
            current = temp;                      // Set current to temp
        }
    }
    return head; // Return head of the list
}

// Function to display vehicles in the linked list
void displayVehicleL(ptrVehicle head)
{
    if (head == NULL)
    {
        printf("\t\t\t\t\t\t\033[91mNo vehicle available.\033[0m\n");
        return;
    }

    ptrVehicle current = head; // Initialize current to head

    printf("\t\t\t\t\t\t| Type  | ID | Capacity |\n");
    printf("\t\t\t\t\t\t|-------|----|----------|\n");

    while (current != NULL) // Loop until end of list
    {
        dataVehicle vehicle = infoVehicle(current);                                                              // Get information of current vehicle
        printf("\t\t\t\t\t\t| %-5s | %02d |%2d items  |\n", vehicle.type, vehicle.identifier, vehicle.capacity); // Display vehicle information
        current = nextVehicle(current);                                                                          // Move to next vehicle
    }
}

// Function to add a new vehicle to the end of the linked list
void addVehicle(ptrVehicle *head, ptrVehicle newVehicle)
{

    if (*head == NULL) // If list is empty
    {
        *head = newVehicle; // Set head to new vehicle
    }
    else
    {
        assignAddressVehicle(findTailVehicle(*head), newVehicle); // Assign address of new vehicle to the tail of the list
    }
}

// Function to access vehicle by identifier
void accessByIdentifier(ptrVehicle head, int identifier, ptrVehicle *current, ptrVehicle *previous)
{
    *current = head;  // Set current to head
    *previous = NULL; // Set previous to NULL

    while (*current != NULL && infoIdentifierVehicle(*current) != identifier) // Loop until identifier is found or end of list
    {
        *previous = *current;             // Set previous to current
        *current = nextVehicle(*current); // Move to next vehicle
    }
    if (*current == NULL) // If identifier is not found
    {
        printf("Identifier %d not found\n", identifier); // Print error message
        return;
    }
}

// Function to delete a vehicle from the linked list by identifier
ptrVehicle deleteVehicle(ptrVehicle *head, int identifier)
{
    ptrVehicle current;
    ptrVehicle previous;

    accessByIdentifier(*head, identifier, &current, &previous); // Access vehicle by identifier

    if (current == NULL) // If vehicle is not found
    {
        return NULL; // Return
    }
    if (previous == NULL) // If vehicle is the head of the list
    {
        *head = nextVehicle(*head); // Set head to next vehicle
    }
    else
    {
        assignAddressVehicle(previous, nextVehicle(current)); // Remove current vehicle from the list
    }
    assignAddressVehicle(current, NULL); // Clear address of removed vehicle
    return current;
}

//------------------------------------------------------Queue Part------------------------------------------

// Function to create a queue of motorcycles from vehicle data
ptrQueue createMotoQ(dataVehicle info[], int size)
{
    ptrQueue motoQ = createQueue(); // Create an empty queue

    for (int i = 0; i < size; i++) // Loop through vehicle data
    {
        if (strcmp(info[i].type, "Moto") == 0) // If vehicle type is motorcycle
        {
            enqueue(motoQ, createVehicle(info[i])); // Add vehicle to the queue
        }
    }
    return motoQ; // Return motorcycle queue
}

// Function to create a queue of vans from vehicle data
ptrQueue createVansQ(dataVehicle info[], int size)
{
    ptrQueue vansQ = createQueue(); // Create an empty queue

    for (int i = 0; i < size; i++) // Loop through vehicle data
    {
        if (strcmp(info[i].type, "Vans") == 0) // If vehicle type is van
        {
            enqueue(vansQ, createVehicle(info[i])); // Add vehicle to the queue
        }
    }

    return vansQ; // Return van queue
}

// Function to synchronize adding a vehicle to the appropriate queue based on its type
void synchronizeAddQueue(ptrVehicle vehicle, ptrQueue moto, ptrQueue van)
{
    // Check if the vehicle pointer is not NULL
    if (vehicle != NULL)
    {
        // Check if the vehicle type is "Moto"
        if (infoType(vehicle) == "Moto")
        {
            // If the vehicle is a motorcycle, enqueue it in the motorcycle queue
            enqueue(moto, vehicle);
        }
        else
        {
            // If the vehicle is not a motorcycle (i.e., it's a van), enqueue it in the van queue
            enqueue(van, vehicle);
        }
    }
}

// Function to synchronize deleting a vehicle from the appropriate queue based on its type and identifier
void synchronizeDeleteQueue(ptrVehicle vehicle, int identifier, ptrQueue moto, ptrQueue van)
{
    // Check if the vehicle type is "Moto"
    if (infoType(vehicle) == "Moto")
    {
        // If the vehicle is a motorcycle, delete it from the motorcycle queue
        deleteVehicle(&(moto->head), identifier);
    }
    else
    {
        // If the vehicle is not a motorcycle (i.e., it's a van), delete it from the van queue
        deleteVehicle(&(van->head), identifier);
    }
}

//------------------------------------------------------Delivery Part------------------------------------------

// Function to convert date format for sorting
int convertDate(ptrItem item)
{
    char date[11];     // Array to store date
    int converted = 0; // Initialize converted to 0

    strcpy(date, infoEntryDate(item)); // Copy entry date to date array

    for (int i = 0; i < strlen(date); i++) // Loop through characters in date
    {
        if (i == 4 || i == 7) // Skip '/' characters
        {
            continue;
        }
        else
        {
            converted *= 10;             // Multiply converted by 10
            converted += atoi(&date[i]); // Convert character to integer and add to converted
        }
    }
    return converted; // Return converted date
}

// Function to swap two items
void swap(ptrItem first, ptrItem second)
{
    dataItem temp = infoItem(first); // Store information of first item in temp

    assignItem(first, infoItem(second)); // Assign information of second item to first
    assignItem(second, temp);            // Assign temp (information of first item) to second
}

// Function to sort items using bubble sort
void sortByDate(ptrItem head)
{
    bool swapped = false; // Initialize swapped to false
    ptrItem temp;         // Temporary pointer

    do
    {
        swapped = false;                               // Reset swapped to false
        temp = head;                                   // Set temp to head
        while (temp != NULL && nextItem(temp) != NULL) // Loop through items
        {
            if (convertDate(temp) > convertDate(nextItem(temp))) // Compare dates
            {
                ptrItem next = nextItem(temp); // Get next item
                swap(temp, next);              // Swap items
                swapped = true;                // Set swapped to true
            }
            temp = nextItem(temp); // Move to next item
        }
    } while (swapped); // Continue until no swaps are made
}

// Function to add an item to vehicle
void addItemToVehicle(ptrItem item, ptrVehicle vehicle)
{
    addItem(&(vehicle->item), infoItem(item));
}

// Function to assign items to motorcycles
void linkItemMoto(ptrItem item, ptrQueue motoQueue)
{
    if (item == NULL || motoQueue == NULL)
    {
        return;
    }

    sortByDate(item); // Sort items by entry date

    ptrItem currentItem = item;
    ptrVehicle currentMoto = getHead(motoQueue);

    while (currentItem != NULL && currentMoto != NULL)
    {
        if (infoWilaya(currentItem) == 16 && infoWeight(currentItem) <= 3 && strcmp(infoStatus(currentItem), "awaiting delivery") == 0)
        {
            if (lengthOfItemList(getAssignedItem(currentMoto)) < infoCapacity(currentMoto))
            {
                assignStatus(currentItem, "delivering");
                addItemToVehicle(currentItem, currentMoto);
                currentItem = nextItem(currentItem);
            }
            else
            {
                currentMoto = nextVehicle(currentMoto);
            }
        }
        else
        {
            currentItem = nextItem(currentItem);
        }
    }
}

// Function to assign items to vans
void linkItemVan(ptrItem item, ptrQueue van)
{
    sortByDate(item);

    ptrVehicle currentVan = getHead(van);
    int counter = 0;

    while (item != NULL)
    {
        if (infoWilaya(item) != 16 || (infoWilaya(item) == 16 && infoWeight(item) > 3))
        {
            if (counter < infoCapacity(currentVan))
            {
                assignStatus(item, "delivering");
                addItemToVehicle(item, currentVan);
                item = nextItem(item);
                counter++;
            }
            else
            {
                currentVan = nextVehicle(currentVan);
                if (currentVan == NULL)
                {
                    return; // Exit the function to avoid accessing invalid memory
                }
                counter = 0;
            }
        }
        else
        {
            item = nextItem(item);
        }
    }
}

// Function returns True if it exists an item with status "awaiting delivery"
bool searchAwaiting(ptrItem item)
{
    if (item == NULL)
    {
        return false;
    }
    while (item != NULL)
    {
        if (strcmp(infoStatus(item), "awaiting delivery") == 0)
        {
            return true;
        }
        item = nextItem(item);
    }
    return false;
}

// Function to simulate deliveries
void simulateDelivery(ptrItem item, ptrQueue moto, ptrQueue van, ptrVehicle *dequeuedVehicle)
{
    *dequeuedVehicle = NULL;

    linkItemMoto(item, moto);
    linkItemVan(item, van);

    if (searchAwaiting(item))
    {
        while (!isEmpty(moto) && lengthOfItemList(getAssignedItem(getHead(moto))) == infoCapacity(getHead(moto)))
        {
            addVehicle(dequeuedVehicle, dequeue(moto));
        }
        while (!isEmpty(van) && lengthOfItemList(getAssignedItem(getHead(van))) == infoCapacity(getHead(van)))
        {
            addVehicle(dequeuedVehicle, dequeue(van));
        }
    }
    else
    {
        while (!isEmpty(moto) && lengthOfItemList(getAssignedItem(getHead(moto))) != 0)
        {
            addVehicle(dequeuedVehicle, dequeue(moto));
        }
        while (!isEmpty(van) && lengthOfItemList(getAssignedItem(getHead(van))) != 0)
        {
            addVehicle(dequeuedVehicle, dequeue(van));
        }
    }
}

//------------------------------------------------------Delivery comeback Part------------------------------------------

// Function to randomly assign "delivered" or "returned" status to items
void deliveredOrReturned(ptrVehicle head)
{
    // Seed the random number generator
    srand(time(NULL));

    // Iterate through each vehicle
    while (head != NULL)
    {
        ptrItem item = getAssignedItem(head);
        // Iterate through each item assigned to the vehicle
        while (item != NULL)
        {
            // Generate a random value (0 or 1)
            int value = rand() % 3;
            // Assign "delivered" status if the random value is 1, otherwise assign "returned" status
            if (value == 1 || value == 2)
            {
                assignStatus(item, "delivered");
            }
            else
            {
                assignStatus(item, "returned");
            }

            // Move to the next item
            item = nextItem(item);
        }
        // Move to the next vehicle
        head = nextVehicle(head);
    }
}

// Function to remove delivered items from the list
void removeDeliveredItem(ptrItem *head)
{
    ptrItem current = *head;

    while (current != NULL)
    {
        if (strcmp(infoStatus(current), "delivered") == 0)
        {
            deleteItem(head, infoIdentifierItem(current));
            current = *head;
        }
        else
        {
            current = nextItem(current);
        }
    }
}

// Function to update the status of items based on assigned items in vehicles
void updateStatusItem(ptrVehicle vehicle, ptrItem item)
{
    ptrItem temp = item;
    ptrItem Current = NULL;
    while (vehicle != NULL)
    {
        temp = item;
        Current = getAssignedItem(vehicle);

        while (Current != NULL)
        {
            temp = item;
            while (temp != NULL)
            {
                if (infoIdentifierItem(temp) == infoIdentifierItem(Current))
                {
                    // Update the status of the item to match the assigned item in the vehicle
                    assignStatus(temp, infoStatus(Current));
                    break;
                }
                temp = nextItem(temp);
            }
            Current = nextItem(Current);
        }
        vehicle = nextVehicle(vehicle);
    }
}

// Function to enqueue vehicles that have no assigned items back to their respective queues
void vehicleComeback(ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van)
{
    ptrVehicle tempVehicle = *dequeuedVehicles;

    while (tempVehicle != NULL)
    {
        removeDeliveredItem(&(tempVehicle->item));

        if (lengthOfItemList(getAssignedItem(tempVehicle)) == 0)
        {
            // Delete the vehicle from the dequeued list
            ptrVehicle deletedVehicle = deleteVehicle(dequeuedVehicles, infoIdentifierVehicle(tempVehicle));
            tempVehicle = *dequeuedVehicles;
            // Enqueue the deleted vehicle back to its respective queue based on its type
            if (strcmp(infoType(deletedVehicle), "Moto") == 0)
            {
                enqueue(moto, deletedVehicle);
            }
            else
            {
                enqueue(van, deletedVehicle);
            }
        }
        tempVehicle = nextVehicle(tempVehicle);
    }
}

// Function to simulate the comeback process for items and vehicles
void simulateComeback(ptrItem *items, ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van)
{
    ptrVehicle tempVehicle = *dequeuedVehicles;

    // Randomly assign statuses to items
    deliveredOrReturned(*dequeuedVehicles);

    // Update the status of items based on assigned items in vehicles
    updateStatusItem(*dequeuedVehicles, *items);

    // Remove delivered items from the main list of items
    removeDeliveredItem(items);

    // Enqueue vehicles that have no assigned items back to their respective queues
    vehicleComeback(dequeuedVehicles, moto, van);
}

//------------------------------------------------------Return pick-up Part------------------------------------------

// Function to remove items marked as "returned" from a linked list of items
void removeReturnedItem(ptrItem *item)
{
    ptrItem current = *item; // Initialize current pointer to the beginning of the list

    // Traverse the list
    while (current != NULL)
    {
        // Check if the current item's status is "returned"
        if (strcmp(infoStatus(current), "returned") == 0)
        {
            // If the item's status is "returned", delete it from the list
            deleteItem(item, infoIdentifierItem(current));
            current = *item; // Reset current pointer to the beginning for re-traversal
        }
        else
        {
            current = nextItem(current); // Move to the next item
        }
    }
}

// Function to process returned vehicles and enqueue them into respective queues
void vehicleReturn(ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van)
{
    ptrVehicle tempVehicle = *dequeuedVehicles; // Initialize tempVehicle pointer to the beginning of the dequeued vehicles list

    // Traverse the list of dequeued vehicles
    while (tempVehicle != NULL)
    {
        // Remove returned items associated with the current vehicle
        removeReturnedItem(&(tempVehicle->item));

        // Delete the current vehicle from the dequeued vehicles list
        ptrVehicle deleted = deleteVehicle(dequeuedVehicles, infoIdentifierVehicle(tempVehicle));
        tempVehicle = *dequeuedVehicles; // Reset tempVehicle pointer to the beginning for re-traversal

        // Enqueue the deleted vehicle into respective queues based on its type
        if (strcmp(infoType(deleted), "Moto") == 0)
        {
            enqueue(moto, deleted); // Enqueue into the moto queue
        }
        else
        {
            enqueue(van, deleted); // Enqueue into the van queue
        }
    }
}

// Function to simulate pickup process by removing returned items and processing returned vehicles
void simulatePickup(ptrItem *item, ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van)
{
    // Remove returned items from the item list
    removeReturnedItem(item);

    // Process returned vehicles
    vehicleReturn(dequeuedVehicles, moto, van);
}

//------------------------------------------------------Report Part------------------------------------------

// Function to update the items file with the latest information
void updateItemsFile(ptrItem head, char *filename)
{
    // Open the file for writing
    ptrFile file = fopen(filename, "w");

    // Iterate through the list and write item information to the file
    ptrItem current = head;
    while (current != NULL)
    {
        // Extract item data
        dataItem data = infoItem(current);
        // Write item information to the file
        fprintf(file, "%d %s %d %.1f %s\n", infoIdentifierItem(current), infoEntryDate(current), infoWilaya(current), infoWeight(current), infoStatus(current));
        // Move to the next item
        current = nextItem(current);
    }

    // Close the file
    fclose(file);
}

// Calculates the number of delivered items.
int numberOfDeliveredItem(ptrItem original, ptrItem updated)
{
    // Subtract the length of itemList from the total lines in the specified file
    return lengthOfItemList(original) - lengthOfItemList(updated);
}

// Calculates the number of returned items in the list.
int numberOfReturnedItem(ptrItem itemList)
{
    int count = 0;

    if (itemList == NULL)
    {
        return -1; // Error condition: list is empty or invalid
    }
    else
    {
        ptrItem temp = itemList;
        while (temp != NULL)
        {
            if (!strcmp(infoStatus(temp), "returned"))
            {
                count++; // Increment count for each returned item
            }
            temp = nextItem(temp); // Move to next item
        }
    }
    return count; // Return total count of returned items
}

// Function to count the number of retired vehicles in a linked list of vehicles
int numberOfRetiredVehicle(ptrVehicle vehicleList)
{
    // Initialize a counter to keep track of the number of retired vehicles
    int count = 0;

    // Loop through the linked list until the end is reached (NULL)
    while (vehicleList != NULL)
    {
        // Check if the current vehicle in the list has completed 3 trips (retired)
        if (infoTrips(vehicleList) == 3)
        {
            // If the vehicle has completed 3 trips, increment the counter
            count++;
        }
        // Move to the next vehicle in the linked list
        vehicleList = nextVehicle(vehicleList);
    }
    // Return the total count of retired vehicles
    return count;
}

//------------------------------------------------------Next day Part------------------------------------------

// Function to reset the number of trips for all vehicles in a linked list
void resetTrips(ptrVehicle vehicle)
{
    // If the vehicle list is empty, there's nothing to reset, so return
    if (vehicle == NULL)
    {
        return;
    }

    // Traverse the vehicle list
    while (vehicle != NULL)
    {
        assignTrips(vehicle, 0);        // Reset the number of trips on this vehicle
        vehicle = nextVehicle(vehicle); // Move to the next vehicle in the list
    }
}
