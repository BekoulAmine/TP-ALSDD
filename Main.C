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

    ptrQueue van = createVansQ(vehicleData, numVehicle);
    ptrQueue moto = createMotoQ(vehicleData, numVehicle);

    switch (choice)
    {
    case 1:
    {
        printf("List of Items:\n");
        printf("\n");

        displayItemL(itemList);
        printf("\n");

        removeDeliveredItem(&itemList);
        displayItemL(itemList);

        break;
    }
    case 2:
    {
        printf("List of Items:\n");
        printf("\n");

        displayVehicleL(vehicleList);

        addVehicle(&vehicleList, createVehicle(vehicleData[0]));
        displayVehicleL(vehicleList);
        break;
    }
    case 3:
    {
        linkItemMoto(itemList, moto);
        linkItemVan(itemList, van);

        displayItemL(itemList);

        break;
    }
    case 4:
    {
        ptrVehicle vehicles;
        simulateDelivery(itemList, moto, van, &vehicles);

        displayItemL(itemList);
        printf("\n");
        displayVehicleL(vehicles);
        displayItemL(getAssignedItem(findTailVehicle(vehicles)));
    }
    case 5:
    {
        ptrVehicle test = dequeue(moto);

        displayVehicleL(test);
        enqueue(moto, test);

        displayVehicleL(getHead(moto));
        printf("\n");
    }
    default:
    {
        break;
    }
    }

    return 0;
}