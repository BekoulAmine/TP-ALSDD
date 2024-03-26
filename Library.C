#include "Library.H"

//------------------------------------------------------File Part------------------------------------------

int linesInFile(char *filename)
{
    int count = 1;
    ptrFile file = fopen(filename, "r");

    char column = fgetc(file);
    while (column != EOF)
    {
        if (column == '\n')
        {
            count++;
        }
        column = fgetc(file);
    }
    fclose(file);
    return count;
}

void readItemFile(char *fileName, dataItem items[], int size)
{
    ptrFile file = fopen(fileName, "r");
    int count = 0;

    while (count < size && !feof(file))
    {
        fscanf(file, "%d %10s %d %f %20[^\n]", &items[count].identifier, items[count].entryDate, &items[count].wilaya, &items[count].weight, items[count].status);
        count++;
    }
    fclose(file);
}

void readVehicleFile(char *fileName, dataVehicle vehicles[], int size)
{
    ptrFile file = fopen(fileName, "r");
    int count = 0;

    while (count < size && !feof(file))
    {
        fscanf(file, "%[^ ] %d %d\n", vehicles[count].type, &vehicles[count].identifier, &vehicles[count].capacity);
        count++;
    }
    fclose(file);
}

//------------------------------------------------------Item Part------------------------------------------

ptrItem createItemL(dataItem info[], int numberOfItems)
{
    ptrItem head = NULL;
    ptrItem current = NULL;

    for (int i = 0; i < numberOfItems; i++)
    {
        ptrItem temp = createItem(info[i]);
        if (head == NULL)
        {
            head = temp;
            current = temp;
        }
        else
        {
            assignAddressItem(current, temp);
            current = temp;
        }
    }
    return head;
}

void displayItemL(ptrItem head)
{
    ptrItem current = head;

    printf("| ID | Entry Date  | Wilaya | Weight | Status            |\n");
    printf("|----|-------------|--------|--------|-------------------|\n");

    while (current != NULL)
    {
        dataItem item = infoItem(current);
        printf("| %02d | %10s  |   %02d   |  %.1f   | %-17s |\n", item.identifier, item.entryDate, item.wilaya, item.weight, item.status);
        current = nextItem(current);
    }
}

void addItem(ptrItem head, dataItem newInfo)
{
    ptrItem newItem = createItem(newInfo);

    if (head == NULL)
    {
        head = newItem;
    }
    else
    {
        assignAddressItem(findTailItem(head), newItem);
    }
}

int convertDate(ptrItem item)
{
    char date[11];
    int converted = 0;

    strcpy(date, item->dataI.entryDate);

    for (int i = 0; i < strlen(date); i++)
    {
        if (i == 4 || i == 7)
        {
            continue;
        }
        else
        {
            converted *= 10;
            converted += atoi(&date[i]);
        }
    }
    return converted;
}

void swap(ptrItem first, ptrItem second)
{
    dataItem temp = infoItem(first);

    assignItem(first, infoItem(second));
    assignItem(second, temp);
}

void bubbleSort(ptrItem head)
{
    bool swapped = false;
    ptrItem temp;
    do
    {
        swapped = false;
        temp = head;
        while (temp != NULL && nextItem(temp) != NULL)
        {
            if (convertDate(temp) > convertDate(nextItem(temp)))
            {
                ptrItem next = nextItem(temp);
                swap(temp, next);
                swapped = true;
            }
            temp = nextItem(temp);
        }
    } while (swapped);
}

//------------------------------------------------------Vehicle Part------------------------------------------

ptrVehicle createVehicleL(dataVehicle info[], int numberOfVehicle)
{
    ptrVehicle head = NULL;
    ptrVehicle current = NULL;

    for (int i = 0; i < numberOfVehicle; i++)
    {
        ptrVehicle temp = createVehicle(info[i]);

        if (head == NULL)
        {
            head = temp;
            current = temp;
        }
        else
        {
            assignAddressVehicle(current, temp);
            current = temp;
        }
    }
    return head;
}

void displayVehicleL(ptrVehicle head)
{
    ptrVehicle current = head;

    printf("| Type  | ID | Capacity |\n");
    printf("|-------|----|----------|\n");

    while (current != NULL)
    {
        dataVehicle vehicle = infoVehicle(current);
        printf("| %-5s | %02d |%2d items  |\n", vehicle.type, vehicle.identifier, vehicle.capacity);
        current = nextVehicle(current);
    }
}

void addVehicle(ptrVehicle head, dataVehicle info)
{
    ptrVehicle newVehicle = createVehicle(info);

    if (head == NULL)
    {
        head = newVehicle;
    }
    else
    {
        assignAddressVehicle(findTailVehicle(head), newVehicle);
    }
}

void accessByIdentifier(ptrVehicle head, int identifier, ptrVehicle *current, ptrVehicle *previous)
{
    *current = head;
    *previous = NULL;

    while (*current != NULL && infoIdentifierVehicle(*current) != identifier)
    {
        *previous = *current;
        *current = nextVehicle(*current);
    }
    if (*current == NULL)
    {
        printf("Identifier %d not found\n", identifier);
        return;
    }
}

void deleteVehicle(ptrVehicle *head, int identifier)
{
    ptrVehicle current;
    ptrVehicle previous;

    accessByIdentifier(*head, identifier, &current, &previous);

    if (current == NULL)
    {
        return;
    }
    if (previous == NULL)
    {
        *head = nextVehicle(*head);
    }
    else
    {
        assignAddressVehicle(previous, nextVehicle(current));
    }

    free(current);
}

//------------------------------------------------------Queue Part------------------------------------------

ptrQueue createMotoQ(dataVehicle info[], int size)
{
    ptrQueue motoQ = createQueue();

    for (int i = 0; i < size; i++)
    {
        if (strcmp(info[i].type, "Moto") == 0)
        {
            enqueue(motoQ, info[i]);
        }
    }
    return motoQ;
}

ptrQueue createVansQ(dataVehicle info[], int size)
{
    ptrQueue vansQ = createQueue();

    for (int i = 0; i < size; i++)
    {
        if (strcmp(info[i].type, "Vans") == 0)
        {
            enqueue(vansQ, info[i]);
        }
    }

    return vansQ;
}

//------------------------------------------------------Delivery Part------------------------------------------

void linkItemsVans(ptrItem item, ptrQueue vans)
{
    ptrVehicle tempVans = getHead(vans);
    ptrItem tempItem = item;
    ptrItem newItem;

    bubbleSort(tempItem);

    while (tempItem != NULL || tempVans != NULL)
    {
        if (infoWilaya(tempItem) != 16)
        {
            if (infoAssignedItem(tempVans) == NULL)
            {
                addItem(infoAssignedItem(tempVans), infoItem(tempItem));
            }
            else
            {
                if (infoWilaya(infoAssignedItem(tempVans)) != infoWilaya(tempItem))
                {
                    tempVans = nextVehicle(tempVans);
                    addItem(infoAssignedItem(tempVans), infoItem(tempItem));
                }
                else
                {
                    addItem(infoAssignedItem(tempVans), infoItem(tempItem));
                }
            }
        }
        else
        {
            if (infoWeight(tempItem) > 3)
            {
                addItem(infoAssignedItem(tempVans), infoItem(tempItem));
            }
        }
        tempItem = nextItem(tempItem);
    }
}
