#include "Library.C"

int main()
{

    int choice;

    printf("your choice ? : ");
    scanf("%d", &choice);

    char fileName1[] = "Item.txt";
    char fileName2[] = "Vehicle.txt";
    int numItems = linesInFile(fileName1);
    int numVehicle = linesInFile(fileName2);

    dataItem itemData[numItems];
    dataVehicle vehicleData[numVehicle];

    readItemFile(fileName1, itemData, numItems);
    readVehicleFile(fileName2, vehicleData, numVehicle);

    ptrItem itemList = createItemL(itemData, numItems);
    ptrVehicle vehicleList = createVehicleL(vehicleData, numVehicle);

    switch (choice)
    {
    case 1:
    {
        printf("List of Items:\n");
        printf("\n");
        displayItemL(itemList);

        break;
    }
    case 2:
    {
        printf("List of Items:\n");
        printf("\n");
        displayVehicleL(vehicleList);

        break;
    }
    case 3:
    {
        ptrQueue vans = createVansQ(vehicleData, numVehicle);
        ptrQueue moto = createMotoQ(vehicleData, numVehicle);

        linkItemMoto(itemList, moto);
        linkItemsVans(itemList, vans);

        ptrVehicle test = getHead(moto);
        // ptrVehicle test = getHead(vans);

        while (test != NULL)
        {
            displayItemL(getAssignedItem(test));
            test = nextVehicle(test);
            printf("\n");
        }

        /*while (test != NULL)
        {
            displayItemL(getAssignedItem(test));
            test = nextVehicle(test);
            printf("\n");
        }*/

        break;
    }
    default:
    {
        printf("choose right choice .");
        break;
    }
    }

    return 0;
}