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

        displayItemL(itemList);

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
        simulateComeback(itemList, &vehicles, moto, van);
        simulatePickup(&itemList, &vehicles, moto, van);

        displayItemL(itemList);
        printf("\n");
        displayVehicleL(vehicles);
        printf("\n");
        displayVehicleL(getHead(moto));
        printf("\n");
        displayVehicleL(getHead(van));
        break;
    }
    default:
    {

        break;
    }
    }

    return 0;
}