#include "Library.C"

int main()
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

    return 0;
}