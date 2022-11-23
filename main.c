/***
 *       __ _  __ _                    _
 *      / /(_)/ _| |_    ___  ___  ___| |__
 *     / / | | |_| __|  / _ \/ __|/ __| '_ \
 *    / /__| |  _| |_  |  __/\__ \ (__| | | |
 *    \____/_|_|  \__|  \___||___/\___|_| |_|
 *
 * @author Mozsár Máté
 * @date 2022.10.09.
 *
 */


#include "main.h"

//TODO kicserelni linked listre
//TODO halalfejes hibak?
//TODO kesobb legyen vege, az utsokat is vegyuk le a canvasrol
//TODO valamiert nem jo a szinezese az editmenunek (errMess)
/*
 *  0  heading to from level
 * 1-4 waiting at from level
 *  5  heading to  to  level
 * 6-9 waiting at  to  level
*/


int *s_times_eplapsed = {-1}; //TODO not needed to be global
int s_waitingsum = 0;                 // not needed to be global
int s_uselesssum = 0;                 // not needed to be global
int s_usefullsum = 0;                 // not needed to be global
double s_deviation = 0;               // not needed to be global
float s_avg = 0;                      // not needed to be global
int curtime = 0;

int charstartoint(char bem[20]);

void editFile(FILE *fp, int curid);

int getmin(int *t, int m){
    int mini = reqs[t[0]].from;
    for (int i = 1; i < m; ++i) {
        if(mini > reqs[t[i]].from) mini =  reqs[t[i]].from;
    }
    return mini;
}
int getmax(int *t, int m){
    int maxi = reqs[t[0]].from;
    for (int i = 1; i < m; ++i) {
        if(maxi < reqs[t[i]].from) maxi = reqs[t[i]].from;
    }
    return maxi;
}
int shouldstop(int *t, int m, int k){
    if(m > 1 && k == 10){
        printf("NAGO");
    }
    for (int i = 0; i < m; ++i) {
        if(reqs[t[i]].to   == k && reqs[t[i]].getouttime <= -1)    return  1;        //priorize passengers who are getting off than on
        if(reqs[t[i]].from == k && reqs[t[i]].getintime <= -1)    return -1;
    }
    return 0;                                   //TODO maybe could be replaced with a sorted t array for each sl
}
int *startedindexes(int *t, int m, int k){
    int *ans= (int *) malloc(sizeof(int)*20);
    int j = 0;
    for (int i = 0; i < m; ++i) {
        if(reqs[t[i]].from == k){
            ans[++j] = t[i];
        }
    }
    ans[0] = j;
    return ans;
}
int *finishedindexes(int *t, int m, int k){
    int *ans= (int *) malloc(sizeof(int)*20);
    int j = 0;
    for (int i = 0; i < m; ++i) {
        if(reqs[t[i]].to == k){
            ans[++j] = t[i];
        }
    }
    ans[0] = j;
    return ans;
}
void clearlifts(int n){
    for (int i = 0; i < n; ++i) {
        lifts[i].state = 0;
        lifts[i].lvl = 0.0;
        lifts[i].capacity = 0;
        lifts[i].shortlists = 0;
        lifts[i].sl_serving->up = 0;
        lifts[i].heading = 0;
    }
}


int main() {

    minlvl = 0;
    maxlvl = lvldb;
    FILE * fp;
    fp = fopen("input.txt","r");

    if (NULL == fp) {
        printf("Nem lehetett megnyitni a fajlt :( \n");
        return 0;
    }
    int curid = 0;
    int ervenytelen = 0;
    int input_size = 0;
    fscanf(fp,"%d",&input_size);
    reqs = (req *) malloc(sizeof(req)*(input_size+1));
    s_times_eplapsed = (int *) malloc(sizeof(int)*(input_size+1));
    while(!feof(fp) && curid < input_size){
        fscanf(fp,"%d",&curid);
        if(curid < 0) ervenytelen++;
        else {
            fscanf(fp, "%d %d %d", &reqs[curid].time, &reqs[curid].from, &reqs[curid].to);
            reqs[curid].id = curid;
            reqs[curid].getintime = -1;
            reqs[curid].getouttime = -1;
        }
    }
    fclose(fp);
    /*
    for (int i = 0; i < curid; ++i) {
        disp_req_data(reqs[i]);
    }*/


    int selb = mainmenu(-1,300);
    system("cls");
    if(selb == 1){
        editFile(fp, curid);
        return 0;
    }
    int sela =     menu(-1,300);
    //suggestions
    lvldb = 18;
    liftdb = 4;
    //user updates?
    editmenu(&lvldb, 1);
    editmenu(&liftdb,2);
    maxlvl = lvldb;
    lifts = (lift*) malloc(sizeof(lift)*liftdb);
    clearlifts(liftdb);








    int last_req_processed = 0;
    int last_req_served = 0;

    curid--;
    while(curtime <= reqs[curid].time || last_req_served < curid+1){
        //TODO enable?disable
        system("cls");
        //
        if(curtime == 10){
            printf("NAGO");
        }
        disp();
        if(sela < 4)
            disp_lift_info();
        else
            disp_lift_info_adv();

        printf("\n > ido:                        00:%02d:%02d ", (curtime/60),(curtime%60));
        printf("\n\n > kerelmek:                   %d felveve,  %d teljesitve\n   ",last_req_processed,last_req_served+1);
        for (int i = 0; i < input_size; ++i) {

            if(last_req_served >= i+1) printf("%c",178);
            else if(last_req_processed >= i+1) printf("%c",177);
            else printf("%c",176);
        }
        printf(" %d\n\n", input_size);
        if(last_req_served > 0) printf(" > atlagos kiszolgalasi ido:   %d mp\n",(s_waitingsum/last_req_served+1));
        if(s_uselesssum > 0)      printf(" > hatasfok:                   %d / %d (%.3f) \n",s_usefullsum,s_uselesssum,((float)s_usefullsum/(float)s_uselesssum));
        if(last_req_served > 0) printf(" > szoras:                     %.2lf \n",s_deviation);

        while(reqs[last_req_processed+1].time <= curtime && last_req_processed < curid+1){

        //ide kell a logika
            int lift_ordered = 0;
            int ans[2];

            //algo 1 - greedy
            if(sela == 1){ lift_ordered = find_most_empty(); }

            //algo 2 - greedy but more optimal
            else if(sela == 2){ lift_ordered = find_most_near(reqs[last_req_processed+1].from); }

            //algo 3 - greedy but most optimal
            else if(sela == 3){ lift_ordered = find_fastest(reqs[last_req_processed+1].from); }

            //algo 4 - complex, can handle multiple reqs at the same time
            else if(sela == 4){
                find_complex(reqs[last_req_processed+1].from,reqs[last_req_processed+1].to,ans);
            }
            //----------------------------------------------------------------------------------------------------------
            if(sela <= 3) {         //post process for simple algs
                lifts[lift_ordered].reqs_serving[lifts[lift_ordered].capacity] = reqs[last_req_processed + 1].id; //add req id to lift array
                lifts[lift_ordered].capacity++;
                reqs[last_req_processed + 1].shortlist = lifts[lift_ordered].capacity;
                reqs[last_req_processed+1].servedby = lift_ordered;
                disp_new_req(reqs[last_req_served+1],lift_ordered);
            } else {                //post process for advanced algs
                if(lifts[ans[0]].shortlists > ans[1]){ //if returned shortlist is existent WAS:lifts[ans[0]].sl_serving[ans[1]].meret > 0
                    sl cursl = lifts[ans[0]].sl_serving[ans[1]];
                    int curmeret = cursl.meret;
                    lifts[ans[0]].sl_serving[ans[1]].t[curmeret] = reqs[last_req_processed + 1].id;
                    lifts[ans[0]].sl_serving[ans[1]].meret++;

                } else{
                    //create shortlist
                    sl newsl;
                    newsl.t[0] = reqs[last_req_processed+1].id;
                    newsl.meret = 1;
                    newsl.up = reqs[last_req_processed+1].from > reqs[last_req_processed+1].to ? 0 : 1;
                    lifts[ans[0]].sl_serving[ans[1]] = newsl;
                    lifts[ans[0]].shortlists++;
                    printf("set to 1");
                    //if(lifts[ans[0]].shortlists)
                }
                reqs[last_req_processed+1].servedby = ans[0];
                disp_new_req(reqs[last_req_processed+1], ans[0]);
            }

            last_req_processed++;
        }
        printf("\n \n");
        //stattttt  vvv

        if(sela < 4){
            int completed_now = 0;
            for (int i = 0; i < liftdb; ++i) {
                int a = move_lift(i,curtime);
                if(a > 0){                                                               //each time a request is served
                    last_req_served++;
                    int time_eplapsed = curtime - reqs[reqs[last_req_served].id-1].time; //TODO make for adv
                    s_waitingsum += time_eplapsed;
                    s_avg = (float)s_waitingsum / (float)last_req_served + 1;
                    s_times_eplapsed[last_req_served + 1] = time_eplapsed;
                    double curdeviation = 0;
                    for (int j = 0; j < last_req_served+2; ++j) {
                        curdeviation += pow((double)(s_times_eplapsed[j] - s_avg), 2);
                    }
                    curdeviation /= last_req_served;
                    s_deviation = sqrt(curdeviation);
                    completed_now++;
                }
                if(lifts[i].state == 0) s_uselesssum++;
                else if(lifts[i].state == 5) s_usefullsum++;
            }
        }
        else{
            for (int i = 0; i < liftdb; ++i) {
                int *a = move_lift_adv(i,curtime);
                if(a != NULL){
                    for (int j = 0; j < a[0]; ++j) {//each time a request is served
                        last_req_served++; // not really valid for us today, anyways
                        int time_eplapsed = curtime - reqs[a[j+1]].getintime;
                        s_waitingsum += time_eplapsed;
                        s_avg = (float)s_waitingsum / (float)last_req_served + 1;
                        s_times_eplapsed[last_req_served + 1] = time_eplapsed;
                        double curdeviation = 0;
                        for (int j = 0; j < last_req_served+2; ++j) {
                            curdeviation += pow((double)(s_times_eplapsed[j] - s_avg), 2);
                        }
                        curdeviation /= last_req_served;
                        s_deviation = sqrt(curdeviation);
                    }
                }
                free(a);
                if(lifts[i].state == 0) s_uselesssum++;
                else if(lifts[i].state == 5) s_usefullsum++;
            }
        }
        //getchar();
        Sleep(6);
        curtime++;

    }

    printf("   __ _  __ _                    _          \n  / /(_)/ _| |_    ___  ___  ___| |__       \n / / | | |_| __|  / _ \\/ __|/ __| '_ \\    \n/ /__| |  _| |_  |  __/\\__ \\ (__| | | |   \n\\____/_|_|  \\__|  \\___||___/\\___|_| |_| \n\n");
    int selc = menuend();
    if(selc == 1){
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
    printf("\n \n \n Nyomja meg az ENTER-t a kilepeshez!");


    free(lifts);
    free(reqs);
    free(s_times_eplapsed);
    getchar();
    return 0;
}

void editFile(FILE *fp, int curid) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    printf("   __ _  __ _                    _          \n  / /(_)/ _| |_    ___  ___  ___| |__       \n / / | | |_| __|  / _ \\/ __|/ __| '_ \\    \n/ /__| |  _| |_  |  __/\\__ \\ (__| | | |   \n\\____/_|_|  \\__|  \\___||___/\\___|_| |_| \n\n");

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
        while (bemint < curid && bemint > 0) {
            SetConsoleTextAttribute(hConsole, 8);
            printf("     >>>Add meg a %d. sor maradek 2 adatjat (szokozzel elvalasztva)!\n         %d %d ", bemint,
                   bemint, reqs[bemint].time);
            SetConsoleTextAttribute(hConsole, 15);
            scanf("%d %d", &reqs[bemint].from, &reqs[bemint].to);


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

int charstartoint(char *bem) {
    int d;
    int c = 0;
    while(bem[c] != '\0'){
        if(bem[c] < 48 || bem[c] > 57) return -1;
        d *= 10;
        d += bem[c]-48;
        c++;
    }
    return d;
}
