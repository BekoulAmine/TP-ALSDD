#include "Library.H"
#include "Menu.C"

int main()
{
    int choice;
    int deletedVehicle = 0;
    int addedVehicle = 0;
    int addedItem = 0;
    int returnedItem = 0;
    int deliveredItem = 0;

    char fileName1[] = "Item.txt";
    char fileName2[] = "Vehicle.txt";
    char fileName3[] = "Report.txt";
    int numItems = linesInFile(fileName1);
    int numVehicle = linesInFile(fileName2);

    ptrItem itemList;
    ptrVehicle vehicleList;
    ptrQueue van, moto;

    dataItem itemData[numItems];
    dataVehicle vehicleData[numVehicle];

    homePage();

    while (true)
    {
    GENERAL_MENU:
        clearScreen();

        printf("\n\t\t\t\t|--------------------------------------------|");
        printf("\n\t\t\t\t|              Delivery Management           |");
        printf("\n\t\t\t\t|--------------------------------------------|");
        printf("\n\t\t\t\t| 1. Create lists and queues                 |");
        printf("\n\t\t\t\t| 2. Add item to ItemL list                  |");
        printf("\n\t\t\t\t| 3. Manage vehicles                         |");
        printf("\n\t\t\t\t| 4. Simulate delivery operation             |");
        printf("\n\t\t\t\t| 5. Simulate vehicle comeback               |");
        printf("\n\t\t\t\t| 6. Simulate returns pick-up                |");
        printf("\n\t\t\t\t| 7. End of day                              |");
        printf("\n\t\t\t\t| 8. Exit                                    |");
        printf("\n\t\t\t\t|--------------------------------------------|");

        printf("\n\n\t\t\t\t\033[93mPlease enter your choice: \033[0m");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            clearScreen();

            int maxIdentifier;

            readItemFile(fileName1, itemData, numItems);
            readVehicleFile(fileName2, vehicleData, numVehicle);

            itemList = createItemL(itemData, numItems);
            vehicleList = createVehicleL(vehicleData, numVehicle);

            van = createVansQ(vehicleData, numVehicle);
            moto = createMotoQ(vehicleData, numVehicle);

            maxIdentifier = infoIdentifierItem(findTailItem(&itemList));

            printf("\n\t\t\t\tList of Items:\n\n");
            displayItemL(itemList);

            printf("\n\t\t\t\tList of Vehicles:\n\n");
            displayVehicleL(vehicleList);

            printf("\n\t\t\t\tList of Vans:\n\n");
            displayVehicleL(getHead(van));

            printf("\n\t\t\t\tList of Moto:\n\n");
            displayVehicleL(getHead(moto));

            printf("\n\t\t\t\t\033[93mPress ESC to return to the menu...\033[0m");
            while (getch() != 27)
                ;
            goto GENERAL_MENU;
            break;

        case 2:

            clearScreen();

            dataItem newItem;

            printf("\t\t\t\t\033[93mEnter Weight of new Item : \033[0m");
            scanf("%f", &newItem.weight);

            printf("\t\t\t\t\033[93mEnter Wilaya of new Item : \033[0m");
            scanf("%d", &newItem.wilaya);

            strcpy(newItem.entryDate, "2024/04/14");
            strcpy(newItem.status, "awaiting delivery");
            newItem.identifier = maxIdentifier + addedItem + 1;

            addItem(&itemList, newItem);
            addedItem++;

            printf("\n\n");
            displayItemL(itemList);

            printf("\n\t\t\t\t\033[93mPress ESC to return to the menu...\033[0m");
            while (getch() != 27)
                ;
            goto GENERAL_MENU;
            break;

        case 3:
            clearScreen();
            addedVehicle = deletedVehicle = 0;
            while (1)
            {
            MENU_VEHICLE_LIST:
                clearScreen();

                int choice2;

                printf("\n\t\t\t\t|--------------------------------------------|");
                printf("\n\t\t\t\t|              Vehicle Management            |");
                printf("\n\t\t\t\t|--------------------------------------------|");
                printf("\n\t\t\t\t| 1. Add Vehicle.                            |");
                printf("\n\t\t\t\t| 2. Delete Vehicle.                         |");
                printf("\n\t\t\t\t| 3. Exit                                    |");
                printf("\n\t\t\t\t|--------------------------------------------|");

                printf("\n\n\t\t\t\t\033[93mPlease enter your choice: \033[0m");
                scanf("%d", &choice2);

                switch (choice2)
                {
                case 1:
                    clearScreen();

                    dataVehicle newVehicle;
                    ptrVehicle Vehicle;

                    do
                    {
                        printf("\t\t\t\t\033[93mEnter Vehicle type (Moto or Vans) : \033[0m");
                        scanf("%s", newVehicle.type);

                    } while (strcmp(newVehicle.type, "Moto") != 0 && strcmp(newVehicle.type, "Vans") != 0);

                    do
                    {
                        printf("\t\t\t\t\033[93mEnter Capacity of the %s (Moto's Capacity Does not Surpass 2 Items): \033[0m", newVehicle.type);
                        scanf("%d", &newVehicle.capacity);

                    } while (strcmp(newVehicle.type, "Moto") == 0 && newVehicle.capacity > 2);

                    newVehicle.identifier = infoIdentifierVehicle(findTailVehicle(vehicleList)) + 1;

                    Vehicle = createVehicle(newVehicle);
                    addVehicle(&vehicleList, Vehicle);
                    synchronizeAddQueue(Vehicle, moto, van);

                    addedVehicle++;

                    printf("\n\t\t\t\t\t\tList of vehicles :\n\n");
                    displayVehicleL(vehicleList);

                    printf("\n\t\t\t\t\033[93mPress ESC to return to the menu...\033[0m");
                    while (getch() != 27)
                        ;

                    goto MENU_VEHICLE_LIST;
                    break;

                case 2:

                    clearScreen();
                    ptrVehicle deleted;
                    int identifier;

                    printf("\t\t\t\tEnter the identifier of the vehicle you want to delete: ");
                    scanf("%d", &identifier);

                    if (!searchIdentifier(vehicleList, identifier))
                    {
                        do
                        {
                            printf("\t\t\t\tidentifier %d not found\n", identifier);
                            printf("\t\t\t\tEnter the identifier of the vehicle you want to delete: ");
                            scanf("%d", &identifier);

                        } while (!searchIdentifier(vehicleList, identifier));
                    }

                    deleted = deleteVehicle(&vehicleList, identifier);

                    synchronizeDeleteQueue(deleted, identifier, moto, van);
                    deletedVehicle++;

                    printf("\n\t\t\t\t\t\tList of vehicles :\n\n");
                    displayVehicleL(vehicleList);

                    printf("\n\t\t\t\t\033[93mPress ESC to return to the menu...\033[0m");
                    while (getch() != 27)
                        ;

                    goto MENU_VEHICLE_LIST;
                    break;

                case 3:

                    goto GENERAL_MENU;
                    break;

                default:

                    printf("\n\t\t\t\tInvalid option. Please choose a valid menu item.\n");

                    while (getch() != 27)
                        ;

                    goto MENU_VEHICLE_LIST;
                    break;
                }
            }
            goto GENERAL_MENU;
            break;

        case 4:

            clearScreen();
            ptrVehicle goneToDeliver;
            ptrItem clonedItems;

            clonedItems = cloneItemList(itemList);
            simulateDelivery(itemList, moto, van, &goneToDeliver);

            printf("\n\t\t\t\tList of Items:\n\n");
            displayItemL(itemList);
            printf("\n\t\t\t\tList of Vehicles that are gone to deliver:\n\n");
            displayVehicleL(goneToDeliver);
            printf("\n\t\t\t\tList of remaining vans:\n\n");
            displayVehicleL(getHead(van));
            printf("\n\t\t\t\tList of remaining moto:\n\n");
            displayVehicleL(getHead(moto));

            printf("\n\t\t\t\t\033[93mPress ESC to return to the menu...\033[0m");
            while (getch() != 27)
                ;

            goto GENERAL_MENU;
            break;

        case 5:

            clearScreen();

            simulateComeback(&itemList, &goneToDeliver, moto, van);

            returnedItem += numberOfReturnedItem(itemList);
            deliveredItem += numberOfDeliveredItem(clonedItems, itemList);

            printf("\n\t\t\t\tList of Items:\n\n");
            displayItemL(itemList);
            printf("\n\t\t\t\tList of not returned Vehicles:\n\n");
            displayVehicleL(goneToDeliver);
            printf("\n\t\t\t\tList of available Vans:\n\n");
            displayVehicleL(getHead(van));
            printf("\n\t\t\t\tList of available Moto:\n\n");
            displayVehicleL(getHead(moto));

            printf("\n\t\t\t\t\033[93mPress ESC to return to the menu...\033[0m");
            while (getch() != 27)
                ;
            goto GENERAL_MENU;

            break;

        case 6:

            clearScreen();
            simulatePickup(&itemList, &goneToDeliver, moto, van);

            printf("\n\t\t\t\tList of available Items:\n\n");
            displayItemL(itemList);
            printf("\n\t\t\t\tList of not returned Vehicles:\n\n");
            displayVehicleL(goneToDeliver);
            printf("\n\t\t\t\tList of available Vans:\n\n");
            displayVehicleL(getHead(van));
            printf("\n\t\t\t\tList of available Moto:\n\n");
            displayVehicleL(getHead(moto));

            printf("\n\t\t\t\t\033[93mPress ESC to return to the menu...\033[0m");
            while (getch() != 27)
                ;
            goto GENERAL_MENU;

            break;

        case 7:
            clearScreen();

            updateItemsFile(itemList, fileName3);

            displayItemL(itemList);
            printf("\n");
            printf("\t\t\t\titems Added : %d\n", addedItem);
            printf("\t\t\t\titems Delivered : %d\n", deliveredItem);
            printf("\t\t\t\titems Returned : %d\n", returnedItem);
            printf("\t\t\t\tvehicle Added :%d\n", addedVehicle);
            printf("\t\t\t\tvehicle Deleted :%d\n", deletedVehicle);
            printf("\t\t\t\tvehicle Retired :%d\n", numberOfRetiredVehicle(vehicleList, moto, van));

            printf("\n\t\t\t\t\033[93mPress ESC to return to the menu...\033[0m");
            while (getch() != 27)
                ;
            goto GENERAL_MENU;

            break;

        case 8:

            exit(false);
            break;

        default:

            clearScreen();

            printf("\n\t\t\t\t\033[91mInvalid option. Please choose a valid menu item.\n");
            printf("\n\t\t\t\t\033[93mPress ESC to return to the menu...\033[0m");
            while (getch() != 27)
                ;
            goto GENERAL_MENU;

            break;
        }
    }
    return 0;
}