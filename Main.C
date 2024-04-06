#include "Library.C"

int main()
{
    int choice;

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

    printf("\n|--------------------------------------------|");
    printf("\n|              Delivery Management           |");
    printf("\n|--------------------------------------------|");
    printf("\n| 1. Create lists and queues                 |");
    printf("\n| 2. Add item to ItemL list                  |");
    printf("\n| 3. Manage vehicles                         |");
    printf("\n| 4. Simulate delivery operation             |");
    printf("\n| 5. Simulate vehicle comeback               |");
    printf("\n| 6. Simulate returns pick-up                |");
    printf("\n| 7. End of day                              |");
    printf("\n| 8. Exit                                    |");
    printf("\n|--------------------------------------------|");

    printf("\n\nPlease enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        printf("List of Items:\n");
        printf("\n");
        displayItemL(itemList);

        printf("\n");

        break;
    }
    case 2:
    {
        printf("List of Items:\n");
        printf("\n");

        displayVehicleL(vehicleList);
        printf("\n");

        ptrVehicle deleted = deleteVehicle(&vehicleList, 4);
        displayVehicleL(vehicleList);
        printf("\n");

        displayVehicleL(deleted);
        break;
    }
    case 3:
    {
        ptrVehicle vehicles;

        simulateDelivery(itemList, moto, van, &vehicles);
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
        printf("\n");
        displayVehicleL(getHead(moto));
        printf("\n");
        displayVehicleL(getHead(van));
        printf("\n");

        simulateComeback(&itemList, &vehicles, moto, van);

        displayItemL(itemList);
        printf("\n");
        displayVehicleL(vehicles);
        printf("\n");
        displayVehicleL(getHead(moto));
        printf("\n");
        displayVehicleL(getHead(van));
        printf("\n");

        simulatePickup(&itemList, &vehicles, moto, van);

        displayItemL(itemList);
        printf("\n");
        displayVehicleL(vehicles);
        printf("\n");
        displayVehicleL(getHead(moto));
        printf("\n");
        displayVehicleL(getHead(van));
        printf("\n");

        break;
    }
    default:
    {

        break;
    }
    }

    return 0;
}