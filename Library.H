#include "AbstractMachineTP.C"

//------------------------------------------------------File Part------------------------------------------
int linesInFile(char *filename);

void readItemFile(char *fileName, dataItem items[], int size);

void readVehicleFile(char *fileName, dataVehicle vehicles[], int size);

//------------------------------------------------------Item Part------------------------------------------

ptrItem createItemL(dataItem info[], int numberOfItems);

void displayItemL(ptrItem head);

void addItem(ptrItem *head, dataItem newInfo);

int convertDate(ptrItem item);

void swap(ptrItem first, ptrItem second);

void bubbleSort(ptrItem head);

//------------------------------------------------------Vehicle Part------------------------------------------

ptrVehicle createVehicleL(dataVehicle info[], int numberOfVehicle);

void displayVehicleL(ptrVehicle head);

void addVehicle(ptrVehicle *head, ptrVehicle newVehicle);

void accessByIdentifier(ptrVehicle head, int identifier, ptrVehicle *current, ptrVehicle *previous);

void deleteVehicle(ptrVehicle *head, int identifier);

//------------------------------------------------------Queue Part------------------------------------------

ptrQueue createMotoQ(dataVehicle info[], int size);

ptrQueue createVansQ(dataVehicle info[], int size);

//------------------------------------------------------Delivery Part------------------------------------------

void addItemToVehicle(ptrItem item, ptrVehicle vehicle);

void linkItemVan(ptrItem item, ptrQueue van);

void linkItemMoto(ptrItem item, ptrQueue Moto);

void simulateDelivery(ptrItem item, ptrQueue moto, ptrQueue van, ptrVehicle *dequeuedVehicle);

void removeDeliveredItem(ptrItem *item);