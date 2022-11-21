//this script extends main.c
#include "main.h"

int mainmenu(int sela, int disable){
    char inp = 0;
    int errCode = 0;
    char * errMess[] = {"","nem megfelelo bemenet","ez a funkcio sajnos meg nem implementalt, valassz masikat!"};
    do {
        system("cls");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 15);
        printf("   __ _  __ _                    _          \n  / /(_)/ _| |_    ___  ___  ___| |__       \n / / | | |_| __|  / _ \\/ __|/ __| '_ \\    \n/ /__| |  _| |_  |  __/\\__ \\ (__| | | |   \n\\____/_|_|  \\__|  \\___||___/\\___|_| |_| \n\n");

        SetConsoleTextAttribute(hConsole, 9);
        printf("  Fomenu\n");
        SetConsoleTextAttribute(hConsole, 8);
        printf("     >muveletek\n");
        SetConsoleTextAttribute(hConsole, 15);
        printf("        [1] - kerelem lista szerkesztese\n");
        printf("        [2] - szimulacio futtatasa\n");

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("        %s \n",errMess[errCode]);
        SetConsoleTextAttribute(hConsole, 15);

        inp = getchar();
        inp -= 48;

        errCode = 1;
        if(inp == 1) errCode = 2;
    }while(!(inp > 1 && inp < 3));          //todo edit to be >0 when file editing becomes avaible

    sela = inp-1;
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    printf("   __ _  __ _                    _          \n  / /(_)/ _| |_    ___  ___  ___| |__       \n / / | | |_| __|  / _ \\/ __|/ __| '_ \\    \n/ /__| |  _| |_  |  __/\\__ \\ (__| | | |   \n\\____/_|_|  \\__|  \\___||___/\\___|_| |_| \n\n");

    SetConsoleTextAttribute(hConsole, 9);
    printf("  Fomenu\n");
    SetConsoleTextAttribute(hConsole, 8);
    printf("     >muveletek\n");
    SetConsoleTextAttribute(hConsole, 15);
    if (sela == 0) SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("        [1] - kerelem lista szerkesztese\n");
    SetConsoleTextAttribute(hConsole, 15);
    if (sela == 1) SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("        [2] - szimulacio futtatasa\n");
    Sleep(disable);
    return inp;
}

int menu(int sela, int disable){
    //sel %= 4;
    getchar();
    char inp = 0;
    int errCode = 0;
    char * errMess[] = {"","nem megfelelo bemenet"};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    do{
        system("cls");
        SetConsoleTextAttribute(hConsole, 15);
        printf("   __ _  __ _                    _          \n  / /(_)/ _| |_    ___  ___  ___| |__       \n / / | | |_| __|  / _ \\/ __|/ __| '_ \\    \n/ /__| |  _| |_  |  __/\\__ \\ (__| | | |   \n\\____/_|_|  \\__|  \\___||___/\\___|_| |_| \n\n");
        SetConsoleTextAttribute(hConsole,9);
        printf("<<szimulaciok\n");
        SetConsoleTextAttribute(hConsole,8);
        printf("     >diszjunktiv algoritmusok\n");
        SetConsoleTextAttribute(hConsole,15);
        printf("        [1] - uj   primitiv   szimulacio inditasa\n");
        printf("        [2] - uj     moho     szimulacio inditasa\n");
        printf("        [3] - uj tervezo(ETA) szimulacio inditasa\n");
        printf("     >atfedo algoritmusok\n");
        printf("        [4] - uj intelligens  szimulacio inditasa\n");

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("        %s \n",errMess[errCode]);
        SetConsoleTextAttribute(hConsole, 15);

        inp = getchar();
        inp -= 48;

        errCode = 1;
    }while(!(inp > 0 && inp < 5));

    sela = inp-1;
    system("cls");
    SetConsoleTextAttribute(hConsole, 15);
    printf("   __ _  __ _                    _          \n  / /(_)/ _| |_    ___  ___  ___| |__       \n / / | | |_| __|  / _ \\/ __|/ __| '_ \\    \n/ /__| |  _| |_  |  __/\\__ \\ (__| | | |   \n\\____/_|_|  \\__|  \\___||___/\\___|_| |_| \n\n");
    SetConsoleTextAttribute(hConsole,9);
    printf("<<szimulaciok\n");
    SetConsoleTextAttribute(hConsole,8);
    printf("     >diszjunktiv algoritmusok\n");
    SetConsoleTextAttribute(hConsole,15);
    if(sela==0) SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
    printf("        [1] - uj   primitiv   szimulacio inditasa\n");
    SetConsoleTextAttribute(hConsole,15);
    if(sela==1) SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
    printf("        [2] - uj     moho     szimulacio inditasa\n");
    SetConsoleTextAttribute(hConsole,15);
    if(sela==2) SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
    printf("        [3] - uj tervezo(ETA) szimulacio inditasa\n");
    SetConsoleTextAttribute(hConsole,8);
    printf("     >atfedo algoritmusok\n");
    SetConsoleTextAttribute(hConsole,15);
    if(sela==3) SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
    printf("        [4] - uj intelligens  szimulacio inditasa\n");
    SetConsoleTextAttribute(hConsole,15);
    Sleep(disable);
    return inp;
}

void editmenu(int *cel,int mode){
    getchar();
    char inp = 0;
    int errCode = 0;
    char * errMess[] = {"","tul nagy vagy tul kicsi bemenet"};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    do{
        system("cls");
        SetConsoleTextAttribute(hConsole, 15);
        printf("   __ _  __ _                    _          \n  / /(_)/ _| |_    ___  ___  ___| |__       \n / / | | |_| __|  / _ \\/ __|/ __| '_ \\    \n/ /__| |  _| |_  |  __/\\__ \\ (__| | | |   \n\\____/_|_|  \\__|  \\___||___/\\___|_| |_| \n\n");
        SetConsoleTextAttribute(hConsole,9);
        printf("<<tulajdonsagok\n");
        SetConsoleTextAttribute(hConsole,15);
        if(mode == 1) {printf("     >szintek szama\n");}
        else {printf("     >liftek szama\n");}
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("        %s\n",errMess[errCode]);
        SetConsoleTextAttribute(hConsole,8);
        printf("        %d\n",*cel);
        printf("        ");
        SetConsoleTextAttribute(hConsole,15);
        scanf("%d",&inp);

        errCode = 1;
    }while(!(inp > 0 && inp < 20));

    *cel = inp;
    system("cls");
    return;
}

int menuend(){
    getchar();
    int sela = 0;
    char inp = 0;
    int errCode = 0;
    char * errMess[] = {"","nem megfelelo bemenet"};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    do{
        SetConsoleTextAttribute(hConsole,9);
        printf("<<eredmeny eltarolasa\n");
        SetConsoleTextAttribute(hConsole,15);
        printf("    [1] - a szimulacio eredmenyenek file-ba valo kiirasa\n");
        printf("    [2] - kiiras mellozese\n");


        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("        %s \n",errMess[errCode]);
        SetConsoleTextAttribute(hConsole, 15);

        inp = getchar();
        getchar();
        inp -= 48;
        errCode = 1;
    }while(!(inp > 0 && inp < 3));
    return inp;
}