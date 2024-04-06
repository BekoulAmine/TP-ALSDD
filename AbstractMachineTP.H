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
