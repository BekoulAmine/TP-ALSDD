#include "Library.C"

int main()
{

    int choice;

    printf("your choice ? : ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        char fileName[] = "Item.txt";
        int numItems = linesInFile(fileName);

        dataItem itemData[numItems];
        readItemFile(fileName, itemData, numItems);
        ptrItem itemList = createItemL(itemData, numItems);

        printf("List of Items:\n");
        printf("\n");
        bubbleSort(itemList);
        displayItemL(itemList);

        break;
    }
    case 2:
    {
        char fileName[] = "Vehicle.txt";
        int numVehicle = linesInFile(fileName);

        dataVehicle vehicleData[numVehicle];
        readVehicleFile(fileName, vehicleData, numVehicle);
        ptrVehicle vehicleList = createVehicleL(vehicleData, numVehicle);

        printf("List of Items:\n");
        printf("\n");
        displayVehicleL(vehicleList);
    }
    break;

    default:
        printf("choose right choice .");
        break;
    }

    return 0;
}