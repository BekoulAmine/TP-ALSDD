#include "Library.C"

int main()
{

    char fileName[] = "Vehicle.txt";
    int numVehicle = linesInFile(fileName);

    dataVehicle vehicleData[numVehicle];
    readVehicleFile(fileName, vehicleData, numVehicle);
    ptrVehicle vehicleList = createVehicleL(vehicleData, numVehicle);
    ptrQueue queue1 = createMotoQ(vehicleData, numVehicle);
    dataVehicle dequeued;

    printf("List of Items:\n");

    printf("\n");

    displayVehicleL(vehicleList);

    printf("\n");

    dequeue(queue1, &dequeued);

    displayVehicleL(getHead(queue1));

    printf("\n");

    enqueue(queue1, dequeued);

    displayVehicleL(getHead(queue1));
}