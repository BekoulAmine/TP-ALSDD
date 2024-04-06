#include "AbstractMachineTP.H"

//------------------------------------------------------Item Part------------------------------------------

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
void assignDate(ptrItem item, char date[])
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

//------------------------------------------------------Vehicle Part------------------------------------------

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

// Function to clone a linked list of items
ptrVehicle cloneVehicleList(ptrVehicle head)
{
    if (head == NULL)
    {
        return NULL;
    }

    ptrVehicle newHead = createVehicle(infoVehicle(head));
    ptrVehicle current = nextVehicle(head);
    ptrVehicle newCurrent = newHead;

    // Traverse the original list
    while (current != NULL)
    {
        assignAddressVehicle(newCurrent, createVehicle(infoVehicle(current)));

        // Move to the next node in both the original and cloned lists
        newCurrent = nextVehicle(newCurrent);
        current = nextVehicle(current);
    }
    return newHead; // Return the head of the cloned list
}

//------------------------------------------------------Queue Part------------------------------------------

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
