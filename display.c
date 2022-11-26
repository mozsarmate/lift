//this script extends main.c
#include "main.h"

void disp(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = maxlvl; i >= minlvl; --i) {
        printf("%.2d ", i);
        for (int j = 0; j < liftdb; ++j) {
            if(lifts[j].state == 0) SetConsoleTextAttribute(hConsole, 8);
            else if(lifts[j].state > 0 && 5 >lifts[j].state) SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            else if(lifts[j].state == 5) SetConsoleTextAttribute(hConsole, 15);
            else if(lifts[j].state > 5 && 10 >lifts[j].state) SetConsoleTextAttribute(hConsole, FOREGROUND_RED);


            if(lifts[j].lvl == i) printf(" %c ",219);
            else if(lifts[j].lvl == i+0.5f) printf(" %c ",223);
            else if(lifts[j].lvl == i-0.5f) printf(" %c ",220);
            else printf("   ");
            SetConsoleTextAttribute(hConsole,15);
        }
        printf("\n");
    }
    printf("    ");
    for (int i = 0; i < liftdb; ++i) {
        printf("%c  ",65+i);
    }
    printf("\n");
}
void disp_req_data(req bem){
    printf("kerelem__ id: %d   at: %.3d    %.2d -> %.2d \n",bem.id,bem.time,bem.from,bem.to);
}
void disp_new_req(req bem, int _lift_ordered){
    printf("  - uj kerelem__  %.2d -> %.2d   >>%c<< \n",bem.from,bem.to,_lift_ordered+65);
}

void disp_lift_info(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int heading_symbols[] = {'-','^','v'};
    printf("-----------------------------------------------\n");
    for (int i = 0; i < liftdb; ++i) {
        printf("%c %c (%.2d) [%d] >> ",i+65,heading_symbols[lifts[i].heading+1],lifts[i].state,lifts[i].capacity);
        for (int j = 0; j < lifts[i].capacity; ++j) {
            printf("%d: #%.2d(%.2d>>%.2d),  ",reqs[lifts[i].reqs_serving[j]].shortlist,lifts[i].reqs_serving[j],reqs[lifts[i].reqs_serving[j]].from, reqs[lifts[i].reqs_serving[j]].to);
        }
        printf("\n");
    }
    printf("-----------------------------------------------\n");
}

void disp_lift_info_adv(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int heading_symbols[] = {'v','^'};
    printf("-----------------------------------------------\n");
    for (int i = 0; i < liftdb; ++i) {
        printf("%c %c (%.2d) [%d] >> ",i+65,heading_symbols[lifts[i].sl_serving[0].up],lifts[i].state,lifts[i].shortlists);
        for (int j = 0; j < lifts[i].shortlists; ++j) {
            if(j > 0){
                SetConsoleTextAttribute(hConsole,8);
                printf("%d:{",j+1);
                for (int k = 0; k < lifts[i].sl_serving[j].meret; ++k) {
                    printf("#%.2d( ",reqs[lifts[i].sl_serving[j].t[k]].id);
                    printf("%.2d ",reqs[lifts[i].sl_serving[j].t[k]].from);
                    printf(">> ");
                    printf("%.2d ",reqs[lifts[i].sl_serving[j].t[k]].to);
                    printf(") ");
                }
                printf("} ");
                SetConsoleTextAttribute(hConsole,15);
            } else {
                printf("%d:{", j + 1);
                for (int k = 0; k < lifts[i].sl_serving[j].meret; ++k) {
                    printf("#%.2d( ", reqs[lifts[i].sl_serving[j].t[k]].id);
                    if (reqs[lifts[i].sl_serving[j].t[k]].getintime > -1)
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    printf("%.2d ", reqs[lifts[i].sl_serving[j].t[k]].from);
                    SetConsoleTextAttribute(hConsole, 15);
                    printf(">> ");
                    if (reqs[lifts[i].sl_serving[j].t[k]].getouttime > -1)
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    printf("%.2d ", reqs[lifts[i].sl_serving[j].t[k]].to);
                    SetConsoleTextAttribute(hConsole, 15);
                    printf(") ");
                }
                printf("} ");
                SetConsoleTextAttribute(hConsole, 15);
            }
        }
        printf("\n");
    }
    printf("-----------------------------------------------\n");
}

void disp_logo(){
    printf("   __ _  __ _                    _          \n  / /(_)/ _| |_    ___  ___  ___| |__       \n / / | | |_| __|  / _ \\/ __|/ __| '_ \\    \n/ /__| |  _| |_  |  __/\\__ \\ (__| | | |   \n\\____/_|_|  \\__|  \\___||___/\\___|_| |_| \n\n");
}
