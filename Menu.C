#include <conio.h>
#include <windows.h>

void clearScreen()

{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
