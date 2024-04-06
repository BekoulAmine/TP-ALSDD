#include "Library.C"
#include "Menu.C"

int main()
{
    while (true)
    {
    GENERAL_MENU:
        clearScreen();

        int choice;

        char fileName1[] = "Item.txt";
        char fileName2[] = "Vehicle.txt";
        char fileName3[] = "Report.txt";
        int numItems = linesInFile(fileName1);
        int numVehicle = linesInFile(fileName2);

        dataItem itemData[numItems];
        dataVehicle vehicleData[numVehicle];

        readItemFile(fileName1, itemData, numItems);
        readVehicleFile(fileName2, vehicleData, numVehicle);

        ptrItem itemList;
        ptrVehicle vehicleList;
        ptrQueue van, moto;

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

            clearScreen();

            readItemFile(fileName1, itemData, numItems);
            readVehicleFile(fileName2, vehicleData, numVehicle);

            itemList = createItemL(itemData, numItems);
            vehicleList = createVehicleL(vehicleData, numVehicle);

            van = createVansQ(vehicleData, numVehicle);
            moto = createMotoQ(vehicleData, numVehicle);

            printf("\nList of Items:\n\n");
            displayItemL(itemList);
            printf("\nList of Vehicles:\n\n");
            displayVehicleL(vehicleList);
            printf("\nList of Vans:\n\n");
            displayVehicleL(getHead(van));
            printf("\nList of Moto:\n\n");
            displayVehicleL(getHead(moto));

            printf("\nPress ESC to return to the menu...");
            while (getch() != 27)
                ;
            goto GENERAL_MENU;
            break;

        case 2:

            clearScreen();

            dataItem newItem;

            printf("----- Add Item -------\n");

            printf("Enter the weight of the Item: ");
            scanf("%f", &(newItem.weight));
            printf("Enter the wilaya: ");
            scanf("%d", &(newItem.wilaya));

            newItem.identifier = lengthOfItemList(itemList) + 1;
            strcpy(newItem.entryDate, "2024/04/14");
            strcpy(newItem.status, "awaiting delivery");

            addItem(&itemList, newItem);

            printf("\n\n");
            displayItemL(itemList);

            printf("\nPress ESC to return to the menu...");
            while (getch() != 27)
                ;
            goto GENERAL_MENU;
            break;

        case 3:

            while (1)
            {
            MENU_VEHICLE_LIST:
                clearScreen();

                int choice2;
                int counterOfDelete = 0;
                int counterOfAdd = 0;

                printf("\n|--------------------------------------------|");
                printf("\n|              Vehicle Management            |");
                printf("\n|--------------------------------------------|");
                printf("\n| 1. Add Vehicle.                            |");
                printf("\n| 2. Delete Vehicle.                         |");
                printf("\n| 3. Exit                                    |");
                printf("\n|--------------------------------------------|");

                printf("\n\nPlease enter your choice: ");
                scanf("%d", &choice2);

                switch (choice2)
                {
                case 1:
                {
                    clearScreen();
                    dataVehicle newVehicle;

                    printf("Enter Type of vehicle (Moto or Vans): ");
                    scanf("%s", newVehicle.type);
                    printf("Enter the capacity of the %s (in Moto case doesn't pass 2 items ): ", newVehicle.type);
                    scanf("%d", &(newVehicle.capacity));

                    newVehicle.identifier = infoIdentifierVehicle(findTailVehicle(vehicleList)) + 1;

                    printf("\n\nVehicleList\n\n");
                    addVehicle(&vehicleList, createVehicle(newVehicle));
                    counterOfAdd++;

                    displayVehicleL(vehicleList);

                    printf("\nPress ESC to return to the menu...");
                    while (getch() != 27)
                        ;

                    goto GENERAL_MENU;
                    break;
                }

                case 2:
                {
                    clearScreen();

                    int identifier;

                    printf("Enter the identifier of the vehicle you want to delete: ");
                    scanf("%d", &identifier);

                    deleteVehicle(&vehicleList, identifier);
                    counterOfDelete++;

                    displayVehicleL(vehicleList);

                    printf("\nPress ESC to return to the menu...");
                    while (getch() != 27)
                        ;
                    break;
                }

                case 3:
                {
                    goto GENERAL_MENU;
                    break;
                }

                default:

                    printf("\nInvalid option. Please choose a valid menu item.\n");
                    break;
                }
                goto MENU_VEHICLE_LIST;
            }
            break;

        case 4:

            clearScreen();
            ptrVehicle goneToDeliver;

            simulateDelivery(itemList, moto, van, &goneToDeliver);

            printf("\nList of Items:\n\n");
            displayItemL(itemList);
            printf("\nList of Vehicles that are gone to deliver:\n\n");
            displayVehicleL(goneToDeliver);
            printf("\nList of remaining vans:\n\n");
            displayVehicleL(getHead(van));
            printf("\nList of remaining moto:\n\n");
            displayVehicleL(getHead(moto));

            printf("\nPress ESC to return to the menu...");
            while (getch() != 27)
                ;

            goto GENERAL_MENU;
            break;

        case 5:

            clearScreen();

            simulateComeback(&itemList, &goneToDeliver, moto, van);

            printf("\nList of Items:\n\n");
            displayItemL(itemList);
            printf("\nList of not returned Vehicles:\n\n");
            displayVehicleL(goneToDeliver);
            printf("\nList of available Vans:\n\n");
            displayVehicleL(getHead(van));
            printf("\nList of available Moto:\n\n");
            displayVehicleL(getHead(moto));

            printf("\nPress ESC to return to the menu...");
            while (getch() != 27)
                ;
            goto GENERAL_MENU;

            break;
        case 6:

            clearScreen();
            simulatePickup(&itemList, &goneToDeliver, moto, van);

            printf("\nList of available Items:\n\n");
            displayItemL(itemList);
            printf("\nList of not returned Vehicles:\n\n");
            displayVehicleL(goneToDeliver);
            printf("\nList of available Vans:\n\n");
            displayVehicleL(getHead(van));
            printf("\nList of available Moto:\n\n");
            displayVehicleL(getHead(moto));

            printf("\nPress ESC to return to the menu...");
            while (getch() != 27)
                ;
            goto GENERAL_MENU;

            break;
        case 7:
            clearScreen();

            updateItemsFile(itemList, fileName3);

            printf("\nPress ESC to return to the menu...");
            while (getch() != 27)
                ;
            goto GENERAL_MENU;

            break;
        case 8:
            exit(false);
            break;
        default:
            printf("\nInvalid option. Please choose a valid menu item.\n");
            break;
        }
    }
    return 0;
}
