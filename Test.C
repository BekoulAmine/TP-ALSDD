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
