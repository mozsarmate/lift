//this script extends main.c
#include "main.h"

int mainmenu( int disable){
    int inp = 0;
    int errCode = 0;
    char * errMess[] = {"","nem megfelelo bemenet","ez a funkcio sajnos meg nem implementalt, valassz masikat!"};
    do {
        system("cls");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 15);
    disp_logo();

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

        scanf("%d",&inp);

        errCode = 1;

    }while(inp != 1 && inp != 2 );

    int sela = inp-1;
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
disp_logo();

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

int menu(int disable){
    int inp = 0;
    int errCode = 0;
    char * errMess[] = {"","nem megfelelo bemenet"};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    do{
        system("cls");
        SetConsoleTextAttribute(hConsole, 15);
    disp_logo();
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

        scanf("%d",&inp);

        errCode = 1;
    }while(!(inp > 0 && inp < 5));

    int sela = inp-1;
    system("cls");
    SetConsoleTextAttribute(hConsole, 15);
disp_logo();
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
    char inp[20];
    int inp2 = 0;
    int errCode = 0;
    char * errMess[] = {"","nem megfelelo bemenet"};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    do{
        system("cls");
        SetConsoleTextAttribute(hConsole, 15);
    disp_logo();
        SetConsoleTextAttribute(hConsole,9);
        printf("<<tulajdonsagok\n");
        SetConsoleTextAttribute(hConsole,15);
        if(mode == 1) {
            SetConsoleTextAttribute(hConsole,15);
            printf("     >szintek szama\n");
        }
        else {
            SetConsoleTextAttribute(hConsole,15);
            printf("     >liftek szama\n");
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("        %s\n",errMess[errCode]);
        SetConsoleTextAttribute(hConsole,8);
        printf("        %d\n",*cel);
        printf("        ");
        SetConsoleTextAttribute(hConsole,15);
        scanf("%s",&inp);
        inp2 = charstartoint(inp);
        errCode = 1;
    }while(!(inp2 > 0 && inp2 < 20));

    *cel = inp2;
    system("cls");
    return;
}

int menuend(){
    int sela = 0;
    int inp = 0;
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

        scanf("%d",&inp);
        errCode = 1;
    }while(!(inp > 0 && inp < 3));
    return inp;
}