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
        printf("Identifier %d not found\n", identifier); // Print error message
        return;
    }
}

// Function to delete an item from the linked list by identifier
void deleteItem(ptrItem *head, int identifier)
{
    ptrItem current;
    ptrItem previous;

    accessByIdentifierItem(*head, identifier, &current, &previous); // Access item by identifier

    if (current == NULL) // If vehicle is not found
    {
        return; // Return
    }
    if (previous == NULL) // If vehicle is the head of the list
    {
        *head = nextItem(*head); // Set head to next vehicle
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

//------------------------------------------------------Delivery Part------------------------------------------

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
            int value = rand() % 2;
            // Assign "delivered" status if the random value is 1, otherwise assign "returned" status
            (value) ? assignStatus(item, "delivered") : assignStatus(item, "returned");
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
void simulateComeback(ptrItem items, ptrVehicle *dequeuedVehicles, ptrQueue moto, ptrQueue van)
{
    ptrVehicle tempVehicle = *dequeuedVehicles;

    // Randomly assign statuses to items
    deliveredOrReturned(*dequeuedVehicles);

    // Update the status of items based on assigned items in vehicles
    updateStatusItem(*dequeuedVehicles, items);

    // Remove delivered items from the main list of items
    removeDeliveredItem(&items);

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

// Sorts a linked list of items in reverse order based on their dates.
void reversedSort(ptrItem head)
{
    bool swapped = false; // Initialize swapped to false
    ptrItem temp;         // Temporary pointer

    do
    {
        swapped = false;                               // Reset swapped to false
        temp = head;                                   // Set temp to head
        while (temp != NULL && nextItem(temp) != NULL) // Loop through items
        {
            if (convertDate(temp) < convertDate(nextItem(temp))) // Compare dates
            {
                ptrItem next = nextItem(temp); // Get next item
                swap(temp, next);              // Swap items
                swapped = true;                // Set swapped to true
            }
            temp = nextItem(temp); // Move to next item
        }
    } while (swapped); // Continue until no swaps are made
}

// Calculates the number of new items in the list.
int numberOfNewItem(ptrItem itemList)
{
    int count = 0;
    if (itemList == NULL)
    {
        return -1; // Error condition: list is empty or invalid
    }
    else
    {
        reversedSort(itemList);        // Sort the list in reverse order
        int s = convertDate(itemList); // Calculate converted date value

        ptrItem temp = itemList;
        while (temp != NULL && convertDate(temp) == s)
        {
            count++;               // Increment count for each item with the same date
            temp = nextItem(temp); // Move to next item
        }
    }
    return count; // Return total count of new items
}

// Calculates the number of delivered items.
int numberOfDeliveredItem(ptrItem itemList, char *fileName)
{
    // Subtract the length of itemList from the total lines in the specified file
    return linesInFile(fileName) - lengthOfItemList(itemList);
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
