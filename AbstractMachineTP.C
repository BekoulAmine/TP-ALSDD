#include "AbstractMachineTP.H"

//------------------------------------------------------Item Part------------------------------------------

void allocateItem(ptrItem *item)
{
    *item = (ptrItem)malloc(sizeof(ItemL));
}

void assignIdentifierItem(ptrItem item, int identifier)
{
    item->dataI.identifier = identifier;
}

void assignDate(ptrItem item, char date[])
{
    strcpy(item->dataI.entryDate, date);
}

void assignWilaya(ptrItem item, int wilaya)
{
    item->dataI.wilaya = wilaya;
}

void assignWeight(ptrItem item, float weight)
{
    item->dataI.weight = weight;
}

void assignStatus(ptrItem item, char status[])
{
    strcpy(item->dataI.status, status);
}

void assignItem(ptrItem item, dataItem source)
{
    assignIdentifierItem(item, source.identifier);
    assignDate(item, source.entryDate);
    assignWilaya(item, source.wilaya);
    assignWeight(item, source.weight);
    assignStatus(item, source.status);
}

void assignAddressItem(ptrItem first, ptrItem second)
{
    first->next = second;
}

int infoIdentifierItem(ptrItem item)
{
    return item->dataI.identifier;
}

int infoWilaya(ptrItem item)
{
    return item->dataI.wilaya;
}

float infoWeight(ptrItem item)
{
    return item->dataI.weight;
}

dataItem infoItem(ptrItem item)
{
    return item->dataI;
}

ptrItem nextItem(ptrItem item)
{
    return item->next;
}

ptrItem findTailItem(ptrItem head)
{
    ptrItem temp = head;
    while (nextItem(temp) != NULL)
    {
        temp = nextItem(temp);
    }
    return temp;
}

ptrItem createItem(dataItem info)
{
    ptrItem item;
    allocateItem(&item);
    assignItem(item, info);
    assignAddressItem(item, NULL);
    return item;
}

int lengthOfItemList(ptrItem head)
{
    int length = 0;
    while (head != NULL)
    {
        length++;
        head = nextItem(head);
    }
    return length;
}

//------------------------------------------------------Vehicle Part------------------------------------------

void allocateVehicle(ptrVehicle *vehicle)
{
    *vehicle = (ptrVehicle)malloc(sizeof(VehicleL));
}

void assignType(ptrVehicle vehicle, char type[])
{
    strcpy(vehicle->dataV.type, type);
}

void assignIdentifierVehicle(ptrVehicle vehicle, int identifier)
{
    vehicle->dataV.identifier = identifier;
}

void assignCapacity(ptrVehicle vehicle, int capacity)
{
    vehicle->dataV.capacity = capacity;
}

void assignVehicle(ptrVehicle vehicle, dataVehicle source)
{
    assignType(vehicle, source.type);
    assignIdentifierVehicle(vehicle, source.identifier);
    assignCapacity(vehicle, source.capacity);
}

void assignTrips(ptrVehicle vehicle, int trips)
{
    vehicle->trips = trips;
}

void assignAddressVehicle(ptrVehicle first, ptrVehicle second)
{
    first->next = second;
}

int infoIdentifierVehicle(ptrVehicle vehicle)
{
    return vehicle->dataV.identifier;
}

int infoCapacity(ptrVehicle vehicle)
{
    return vehicle->dataV.capacity;
}

int infoTrips(ptrVehicle vehicle)
{
    return vehicle->trips;
}

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

dataVehicle infoVehicle(ptrVehicle vehicle)
{
    return vehicle->dataV;
}

ptrVehicle nextVehicle(ptrVehicle vehicle)
{
    return vehicle->next;
}

ptrVehicle findTailVehicle(ptrVehicle head)
{
    if (head == NULL)
    {
        return NULL;
    }

    ptrVehicle temp = head;
    while (nextVehicle(temp) != NULL)
    {
        temp = nextVehicle(temp);
    }
    return temp;
}

ptrVehicle createVehicle(dataVehicle info)
{
    ptrVehicle vehicle;

    allocateVehicle(&vehicle);
    assignVehicle(vehicle, info);
    assignAddressVehicle(vehicle, NULL);
    return vehicle;
}

//------------------------------------------------------Vehicle Part------------------------------------------

void allocateQueue(ptrQueue *queue)
{
    *queue = (ptrQueue)malloc(sizeof(vehicleQueue));
}

void assignHead(ptrQueue queue, ptrVehicle vehicle)
{
    queue->head = vehicle;
}

void assignTail(ptrQueue queue, ptrVehicle vehicle)
{
    queue->tail = vehicle;
}

ptrVehicle getHead(ptrQueue queue)
{
    return queue->head;
}

ptrVehicle getTail(ptrQueue queue)
{
    return queue->tail;
}

ptrQueue createQueue()
{
    ptrQueue queue;

    allocateQueue(&queue);
    assignHead(queue, NULL);
    assignTail(queue, NULL);
    return queue;
}

bool isEmpty(ptrQueue queue)
{
    return getHead(queue) == NULL;
}

void enqueue(ptrQueue queue, dataVehicle info)
{
    ptrVehicle newVehicle = createVehicle(info);

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

void dequeue(ptrQueue queue, dataVehicle *dequeued)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty\n");
        return;
    }
    else
    {
        ptrVehicle temp = getHead(queue);

        *dequeued = infoVehicle(temp);
        assignHead(queue, nextVehicle(getHead(queue)));

        if (isEmpty(queue))
        {
            assignTail(queue, NULL);
        }

        free(temp);
        return;
    }
}