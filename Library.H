#include "AbstractMachineTP.C"

//------------------------------------------------------File Part------------------------------------------
// Function to count the number of lines in a file
int linesInFile(char *filename);

// Function to read item data from a file and store it in an array of dataItem structures
void readItemFile(char *fileName, dataItem items[], int size);

// Function to read vehicle data from a file and store it in an array of dataVehicle structures
void readVehicleFile(char *fileName, dataVehicle vehicles[], int size);

//------------------------------------------------------Item Part------------------------------------------

// Function to create a linked list of items from an array of dataItem structures
ptrItem createItemL(dataItem info[], int numberOfItems);

// Function to display items stored in a linked list
void displayItemL(ptrItem head);

// Function to add a new item to the end of a linked list of items
void addItem(ptrItem *head, dataItem newInfo);

//------------------------------------------------------Vehicle Part------------------------------------------

// Function to create a linked list of vehicles from an array of dataVehicle structures
ptrVehicle createVehicleL(dataVehicle info[], int numberOfVehicle);

// Function to display vehicles stored in a linked list
void displayVehicleL(ptrVehicle head);

// Function to add a new vehicle to the end of a linked list of vehicles
void addVehicle(ptrVehicle *head, ptrVehicle newVehicle);

// Function to access a vehicle in a linked list by its identifier
void accessByIdentifier(ptrVehicle head, int identifier, ptrVehicle *current, ptrVehicle *previous);

// Function to delete a vehicle from a linked list by its identifier
ptrVehicle deleteVehicle(ptrVehicle *head, int identifier);

//------------------------------------------------------Queue Part------------------------------------------

// Function to create a queue of motorcycles from an array of dataVehicle structures
ptrQueue createMotoQ(dataVehicle info[], int size);

// Function to create a queue of vans from an array of dataVehicle structures
ptrQueue createVansQ(dataVehicle info[], int size);

// Function to synchronize adding a vehicle to the appropriate queue based on its type
void synchronizeAddQueue(ptrVehicle vehicle, ptrQueue moto, ptrQueue van);

// Function to synchronize deleting a vehicle from the appropriate queue based on its type and identifier
void synchronizeDeleteQueue(ptrVehicle vehicle, int identifier, ptrQueue moto, ptrQueue van);

//------------------------------------------------------Delivery Part------------------------------------------

// Function to convert the date format of an item for sorting
int convertDate(ptrItem item);

// Function to swap two items in a linked list
void swap(ptrItem first, ptrItem second);

// Function to sort items in a linked list by date using bubble sort
void sortByDate(ptrItem head);

// Function to add an item to a vehicle's list of assigned items
void addItemToVehicle(ptrItem item, ptrVehicle vehicle);

// Function to assign items to vans based on specific criteria
void linkItemVan(ptrItem item, ptrQueue van);

// Function to assign items to motorcycles based on specific criteria
void linkItemMoto(ptrItem item, ptrQueue Moto);

// Function to search for item in a linked list with the status "awaiting delivery"
bool searchAwaiting(ptrItem item);

// Function to simulate the delivery process
void simulateDelivery(ptrItem item, ptrQueue moto, ptrQueue van, ptrVehicle *dequeuedVehicle);

//------------------------------------------------------Delivery comeback Part------------------------------------------

// Function to randomly assign "delivered" or "returned" status to items
void deliveredOrReturned(ptrVehicle head);

// Function to remove items marked as delivered from a linked list of items
void removeDeliveredItem(ptrItem *item);

// Function to update the status of items based on assigned items in vehicles
void updateStatusItem(ptrVehicle vehicle, ptrItem item);

// Function to enqueue vehicles that have no assigned items back to their respective queues
void vehicleComeback(ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van);

// Function to simulate the comeback process for items and vehicles
void simulateComeback(ptrItem *items, ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van);

//------------------------------------------------------Return pick-up Part------------------------------------------

// Function to remove items marked as "returned" from a linked list of items
void removeReturnedItem(ptrItem *item);

// Function to process returned vehicles and enqueue them into respective queues
void vehicleReturn(ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van);

// Function to simulate pickup process by removing returned items and processing returned vehicles
void simulatePickup(ptrItem *item, ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van);

//------------------------------------------------------Report Part------------------------------------------

// Function to update the items file with the latest information
void updateItemsFile(ptrItem head, char *filename);

// Calculates the number of delivered items.
int numberOfDeliveredItem(ptrItem itemList, char *fileName);

// Calculates the number of returned items in the list.
int numberOfReturnedItem(ptrItem itemList);

// Function to count the number of retired vehicles in a linked list of vehicles
int numberOfRetiredVehicle(ptrVehicle vehicleList);