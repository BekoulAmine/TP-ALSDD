#include "Library.H"

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
    ptrItem current = head; // Initialize current to head

    printf("| ID | Entry Date  | Wilaya | Weight | Status            |\n");
    printf("|----|-------------|--------|--------|-------------------|\n");

    while (current != NULL) // Loop until end of list
    {
        dataItem item = infoItem(current);                                                                                                 // Get information of current item
        printf("| %02d | %10s  |   %02d   |  %.1f   | %-17s |\n", item.identifier, item.entryDate, item.wilaya, item.weight, item.status); // Display item information
        current = nextItem(current);                                                                                                       // Move to next item
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

// Function to convert date format for sorting
int convertDate(ptrItem item)
{
    char date[11];     // Array to store date
    int converted = 0; // Initialize converted to 0

    strcpy(date, item->dataI.entryDate); // Copy entry date to date array

    for (int i = 0; i < strlen(date); i++) // Loop through characters in date
    {
        if (i == 4 || i == 7) // Skip '-' characters
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
void bubbleSort(ptrItem head)
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
    ptrVehicle current = head; // Initialize current to head

    printf("| Type  | ID | Capacity |\n");
    printf("|-------|----|----------|\n");

    while (current != NULL) // Loop until end of list
    {
        dataVehicle vehicle = infoVehicle(current);                                                  // Get information of current vehicle
        printf("| %-5s | %02d |%2d items  |\n", vehicle.type, vehicle.identifier, vehicle.capacity); // Display vehicle information
        current = nextVehicle(current);                                                              // Move to next vehicle
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
void deleteVehicle(ptrVehicle *head, int identifier)
{
    ptrVehicle current;
    ptrVehicle previous;

    accessByIdentifier(*head, identifier, &current, &previous); // Access vehicle by identifier

    if (current == NULL) // If vehicle is not found
    {
        return; // Return
    }
    if (previous == NULL) // If vehicle is the head of the list
    {
        *head = nextVehicle(*head); // Set head to next vehicle
    }
    else
    {
        assignAddressVehicle(previous, nextVehicle(current)); // Remove current vehicle from the list
    }

    free(current); // Free memory allocated to current vehicle
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

//------------------------------------------------------Delivery Part------------------------------------------

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

    bubbleSort(item); // Sort items by entry date

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
    bubbleSort(item);

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

// Function to simulate deliveries
void simulateDelivery(ptrItem item, ptrQueue moto, ptrQueue van, ptrVehicle *dequeuedVehicle)
{
    ptrVehicle infoMoto;
    ptrVehicle infoVan;

    *dequeuedVehicle = NULL;

    // Link items to motorcycles and vans
    linkItemMoto(item, moto);
    linkItemVan(item, van);

    // Check and dequeue fully loaded motorcycles
    while (!isEmpty(moto) && lengthOfItemList(getAssignedItem(getHead(moto))) == infoCapacity(getHead(moto)))
    {
        infoMoto = dequeue(moto);
        addVehicle(dequeuedVehicle, infoMoto);
    }
    // Check and dequeue fully loaded vans
    while (!isEmpty(van) && lengthOfItemList(getAssignedItem(getHead(van))) == infoCapacity(getHead(van)))
    {
        infoVan = dequeue(van);
        addVehicle(dequeuedVehicle, infoVan);
    }
}

//------------------------------------------------------Delivery comeback Part------------------------------------------

void removeDeliveredItem(ptrItem *head)
{
    if (*head == NULL)
    {
        return;
    }
    ptrItem temp = *head;

    while (nextItem(temp) != NULL)
    {
        if (strcmp(infoStatus(nextItem(temp)), "delivered") == 0)
        {
            ptrItem removed = nextItem(temp);
            assignAddressItem(temp, nextItem(nextItem(temp)));
            free(removed);
        }
        temp = nextItem(temp);
    }
}

void simulateComeback(ptrItem item, ptrVehicle vehicle)
{
    removeDeliveredItem(&item);

    while (vehicle != NULL)
    {
        if (infoTrips(vehicle) == 3)
        {
        }
        else
        {
        }
        vehicle = nextVehicle(vehicle);
    }
}