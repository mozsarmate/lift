//
// Created by Máté on 2022. 11. 26..
//
#include "main.h"

int * beolvasas(int *curid, int *input_size, FILE **fp) {
    (*fp) = fopen("input.txt", "r");

    if (NULL == (*fp)) {
        printf("Nem lehetett megnyitni a fajlt :( \n");
        //return 0;
    }
    int ervenytelen = 0;
    fscanf((*fp), "%d", input_size);
    reqs = (req *) malloc(sizeof(req)*((*input_size) + 1));
    int *s_times_eplapsed = (int *) malloc(sizeof(int)*((*input_size) + 1));
    while(!feof((*fp)) && (*curid) < (*input_size)){
        fscanf((*fp), "%d", curid);
        if((*curid) < 0) ervenytelen++;
        else {
            fscanf((*fp), "%d %d %d", &reqs[(*curid)].time, &reqs[(*curid)].from, &reqs[(*curid)].to);
            reqs[(*curid)].id = (*curid);
            reqs[(*curid)].getintime = -1;
            reqs[(*curid)].getouttime = -1;
        }
    }
    fclose((*fp));
    return s_times_eplapsed;
}


void editFile(FILE *fp, int curid) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);

    SetConsoleTextAttribute(hConsole, 9);
    printf("  Fajl szerkesztes\n");
    SetConsoleTextAttribute(hConsole, 8);
    printf("     >Ird be a szerkeszteni kivant sor szamat, vagy egy \"A\" karaktert a teljes fajl ujrairasahoz!\n      ");
    SetConsoleTextAttribute(hConsole, 15);
    char bem[20];
    scanf("%s",&bem);
    if(!strcmp(bem,"A")){       //teljes szerkesztése
        fp = fopen("input.txt","w");
        int n;
        int counter = 0;
        int lasttime = 0;
        int tmp1 = 0, tmp2, tmp3;
        SetConsoleTextAttribute(hConsole, 8);
        printf("     >>>Add meg az kerelmek vegso szamat!\n      ");
        SetConsoleTextAttribute(hConsole, 15);
        scanf("%d",&n);
        fprintf(fp,"%d\n",n);
        while(tmp1 != -1 && counter < n) {
            SetConsoleTextAttribute(hConsole, 8);
            printf("     >>>Add meg a %d. sor maradek 3 adatjat (szokozzel elvalasztva)!\n         %d ",counter+1,counter+1);
            SetConsoleTextAttribute(hConsole, 15);
            scanf("%d", &tmp1);
            if(tmp1 != -1){
                scanf("%d %d", &tmp2, &tmp3);
                if(tmp1 < lasttime || tmp2 == tmp3 || tmp2 < 0 || tmp3 < 0 || tmp2 > 19 || tmp3 > 19){
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
                    printf("            nem megfelelo bemenet\n");
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else {
                    fprintf(fp, "%d %d %d %d\n", counter + 1, tmp1, tmp2, tmp3);
                    lasttime = tmp1;
                    counter++;
                }
            }
        }
        for (int i = counter; i < n; ++i) {
            fprintf(fp,"-1 -1 -1 -1\n");
        }
        fclose(fp);
    }
    else {
        int bemint = charstartoint(bem);
        int tmp3 = 0, tmp2 = 0;
        while (bemint < curid && bemint > 0) {
            SetConsoleTextAttribute(hConsole, 8);
            printf("     >>>Add meg a %d. sor maradek 2 adatjat (szokozzel elvalasztva)!\n         %d %d ", bemint,
                   bemint, reqs[bemint].time);
            SetConsoleTextAttribute(hConsole, 15);

            scanf("%d %d", &tmp2, &tmp3);
            if( tmp2 == tmp3 || tmp2 < 0 || tmp3 < 0 || tmp2 > 19 || tmp3 > 19){
                SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
                printf("            nem megfelelo bemenet\n");
                SetConsoleTextAttribute(hConsole, 15);
            }
            else {
                reqs[bemint].from = tmp2;
                reqs[bemint].to = tmp3;
            }


            SetConsoleTextAttribute(hConsole, 8);
            printf("     >Ird be az ujabb szerkeszteni kivant sor szamat, vagy adj meg ervenytelen bemenetet a kilepeshez es menteshez!\n      ");
            SetConsoleTextAttribute(hConsole, 15);
            scanf("%s", &bem);
            bemint = charstartoint(bem);
        }
        fp = fopen("input.txt","w");
        fprintf(fp,"%d\n",curid);
        for (int i = 1; i < curid; ++i) {
            fprintf(fp, "%d %d %d %d\n",reqs[i].id,reqs[i].time,reqs[i].from,reqs[i].to);
        }
    }
    printf("\nA fajl szerkesztese veget ert, inditsd ujra a programot a megfelelo mukodeshez!\n");
    SetConsoleTextAttribute(hConsole, 8);
    printf("A program hamarosan bezarodik...");
    free(reqs);
    Sleep(3000);
}


void kiiras(int curid, int sela, int last_req_served, int curtime, int s_waitingsum, int s_usefullsum, int s_uselesssum, int s_deviation) {
    FILE *fp2;
    fp2 = fopen("output.txt","w");
    fprintf(fp2,"szimulacio kiertekelese: \n\n");
    fprintf(fp2,"alg:  %d\n",sela);
    fprintf(fp2,"time: %02d:%02d \n", (curtime/60),(curtime%60));
    fprintf(fp2,"avg:  %d mp\n",(s_waitingsum/last_req_served+1));
    fprintf(fp2,"htf:  %d / %d (%.3f) \n",s_usefullsum,s_uselesssum,((float)s_usefullsum/(float)s_uselesssum));
    fprintf(fp2,"dev:  %.2lf \n",s_deviation);
    for (int i = 1; i < curid+1; ++i) {
        req cur = reqs[i];
        fprintf(fp2,"#%.3d @%.3d (%.2d >> %.2d)    %c %d %d \n",cur.id,cur.time,cur.from,cur.to,cur.servedby+65,cur.getintime,cur.getouttime);
    }
    printf("kiiras kesz! \n");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,8);
    printf(">> output.txt");
    fclose(fp2);
}