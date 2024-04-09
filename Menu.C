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

void homePage()
{
    clearScreen();

    printf(
        "\t\t\t\t\033[93m                                              iiii\n"
        "\t\t\t\t\033[93m                                             iiiii\n"
        "\t\t\t\t\033[93m                                              iiii\n\n"
        "\t\t\t\t\033[93m        eeeeeeeeeeee          ssssssssss    iiiiiii\n"
        "\t\t\t\t\033[93m      eeeeeeeeeeeeeeee      sssssssssssss   iiiiiii\n"
        "\t\t\t\t\033[93m     eeeeeeeeeeeeeeeeeee  ssssssssssssssss   iiiiii\n"
        "\t\t\t\t\033[93m    eeeeeeee     eeeeeee  sssssssssssssssss  iiiiii\n"
        "\t\t\t\t\033[93m    eeeeeeeeeeeeeeeeeeee   sssssss  ssssss   iiiiii\n"
        "\t\t\t\t\033[93m    eeeeeeeeeeeeeeeeeee      ssssssss        iiiiii\n"
        "\t\t\t\t\033[93m    eeeeeeeeeeeeeeeeee          ssssssss     iiiiii\n"
        "\t\t\t\t\033[93m    eeeeeeeee             ssssss   sssssss   iiiiii\n"
        "\t\t\t\t\033[93m    eeeeeeeeee            sssssssssssssssss iiiiiiii\n"
        "\t\t\t\t\033[93m     eeeeeeeeeeeeeeeee    ssssssssssssssss  iiiiiiii\n"
        "\t\t\t\t\033[93m      eeeeeeeeeeeeeeee     ssssssssssssss   iiiiiiii\n"
        "\t\t\t\t\033[93m        eeeeeeeeeeeeee      sssssssssss     iiiiiiii\n\n\n");

    printf("\t\t\t\t\033[97m  1CP - 1st Year - Academic Year 2023/2024 \n");
    printf("\t\t\t\033[97m ___________________________________________________________________\n");
    printf("\t\t\t\033[97m|                                                                   |\n");
    printf("\t\t\t\033[97m|     DONE BY :         BEKOUL MOHAMED AMINE                        |\n");
    printf("\t\t\t\033[97m|                                &                                  |\n");
    printf("\t\t\t\033[97m|                       SEFFAI AHMED YACINE                         |\n");
    printf("\t\t\t\033[97m|                                                                   |\n");
    printf("\t\t\t\033[97m|                                                                   |\n");
    printf("\t\t\t\033[97m|                 SECTION : B          GROUP: 05                    |\n");
    printf("\t\t\t\033[97m|                                                                   |\n");
    printf("\t\t\t\033[97m|             TP1 :  Linear Linked Lists                            |\n");
    printf("\t\t\t\033[97m|                                                                   |\n");
    printf("\t\t\t\033[97m|                        Delivery Management                        |\n");
    printf("\t\t\t\033[97m|___________________________________________________________________|\n\n\n");

    // Displaying last two lines in red
    printf("\t\t\t                            \033[91mPlease                         \n");
    printf("\t\t\t                  Press any key to continue...\033[0m               ");
    getch();

    clearScreen();
}
