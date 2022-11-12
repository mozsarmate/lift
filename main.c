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

//TODO kicserelni linked listra
//TODO halalfejes hibak?
//TODO tobb algo -- make for adv
//TODO kesobb legyen vege, az utsokat is vegyuk le a canvasrol
/*
 *  0  heading to from level
 * 1-4 waiting at from level
 *  5  heading to  to  level
 * 6-9 waiting at  to  level
*/


int s_times_eplapsed[101] = {-1}; //TODO not needed to be global
int s_waitingsum = 0;                 // not needed to be global
int s_uselesssum = 0;                 // not needed to be global
int s_usefullsum = 0;                 // not needed to be global
double s_deviation = 0;               // not needed to be global
float s_avg = 0;                      // not needed to be global
int curtime = 0;


int mainmenu(int sela, int disable){
    char inp = 0;
    do {
        system("cls");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
        inp = getchar();
        inp -= 48;
    }while(!(inp > 0 && inp < 3));
    return inp;
}

int menu(int sela, int disable){
    //sel %= 4;
    char inp = 0;
    do{
        system("cls");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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

        inp = getchar();
        inp -= 48;
    }while(!(inp > 0 && inp < 5));
    return inp;
}
/*
void disp(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = maxlvl; i >= minlvl; --i) {
        printf("%.2d ", i);
        for (int j = 0; j < 4; ++j) {
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
    printf("    A  B  C  D\n");
}
void disp_req_data(req bem){
    printf("kerelem__ id: %d   at: %.3d    %.2d -> %.2d \n",bem.id,bem.time,bem.from,bem.to);
}
void disp_new_req(req bem, int _lift_ordered){
    printf("  - uj kerelem__  %.2d -> %.2d   >>%c<< \n",bem.from,bem.to,_lift_ordered+65);
}

void disp_lift_info(){
    int heading_symbols[] = {33,45,173};
    printf("-----------------------------------------------\n");
    for (int i = 0; i < 4; ++i) {
        printf("%c %c (%d) [%d] >> ",i+65,heading_symbols[lifts[i].heading+1],lifts[i].state,lifts[i].capacity);
        for (int j = 0; j < lifts[i].capacity; ++j) {
            printf("%d: #%.2d(%.2d>>%.2d),  ",reqs[lifts[i].reqs_serving[j]].shortlist,lifts[i].reqs_serving[j],reqs[lifts[i].reqs_serving[j]].from, reqs[lifts[i].reqs_serving[j]].to);
        }
        printf("\n");
    }
    printf("-----------------------------------------------\n");
}

void disp_lift_info_adv(){
    int heading_symbols[] = {33,45,173};
    printf("-----------------------------------------------\n");
    for (int i = 0; i < 4; ++i) {
        printf("%c %c (%d) [%d] >> ",i+65,heading_symbols[lifts[i].heading+1],lifts[i].state,lifts[i].shortlists);
        for (int j = 0; j < lifts[i].shortlists; ++j) {
            printf("%d: {",j+1);
            for (int k = 0; k < lifts[i].sl_serving[j].meret; ++k) {
                printf("#%.2d(%.2d>>%.2d),  ",reqs[lifts[i].sl_serving[j].t[k]].id,reqs[lifts[i].sl_serving[j].t[k]].from,reqs[lifts[i].sl_serving[j].t[k]].to);
            }
            printf("} ");
        }
        printf("\n");
    }
    printf("-----------------------------------------------\n");
}
*/
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
int *startededindexes(int *t, int m, int k){
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

int find_most_empty(){
    int minindex = 0;
    for (int i = 0; i < 4; ++i) {
        if(lifts[i].capacity < lifts[minindex].capacity) minindex = i;
    }
    return minindex;
}
int find_most_near(int lvl){
    int minindex = 0;
    int mini = 20;
    for (int i = 0; i < 4; ++i) {
        if(lifts[i].capacity == 0) return i;
        if(lifts[i].capacity < 20) {
            if (abs(reqs[lifts[i].reqs_serving[lifts[i].capacity - 1]].to - lvl) < mini) {
                minindex = i;
                mini = abs(reqs[lifts[i].reqs_serving[lifts[i].capacity - 1]].to - lvl);
            }
        }
    }
    return minindex;
}
int find_fastest(int lvl){
    int minindex = 0;
    int mini = INT_MAX;
    for (int i = 0; i < 4; i++) {
        int curcap = lifts[i].capacity;
        int curcount = 0;
        int j = 0;
        if(0 < lifts[i].state && lifts[i].state < 5) { curcount -= lifts[i].state; }
        if(lifts[i].state == 5)                      { j=1; curcount += 2*abs(reqs[lifts[i].reqs_serving[j]].from-reqs[lifts[i].reqs_serving[j]].to); }
        if(5 < lifts[i].state)                       { j=1; curcount += 9-lifts[i].state; }
        while (j < curcap) {
            if(j > 0) {
                curcount += 2*abs(reqs[lifts[i].reqs_serving[j-1]].to-reqs[lifts[i].reqs_serving[j]].from);  //adding travel to from
            }
            curcount += 4;                                                                                      //adding waiting
            curcount += 2*abs(reqs[lifts[i].reqs_serving[j]].from-reqs[lifts[i].reqs_serving[j]].to);        //adding transporting travel time
            curcount += 4;                                                                                      //adding waiting
            j++;
        }
        if(curcount < mini){
            mini = curcount;
            minindex = i;
        }
    }
    return minindex;
}
void find_complex(int flvl,int tlvl, int *ans){           //
    int minindex = 0;
    int minshortlist = lifts[flvl%4].shortlists;         //worst case scenario: return a new, created shortlist for a
    int mini = INT_MAX;
    int up = flvl < tlvl ? 1 : 0;
    for (int i = 0; i < 4; i++) {                // check each lift
        if(lifts[i].shortlists == 0){
            ans[0] = i; ans[1] = 0;
            return;
        }   // if no task >> do this
        for (int j = 0; j < lifts[i].shortlists; ++j) {
            if(lifts[i].sl_serving[j].up == up && lifts[i].sl_serving[j].meret < 10) {   //last val could be 20 as well TODO
                int curcount = 0;
                int curmin = getmin(lifts[i].sl_serving[j].t,lifts[i].sl_serving[j].meret);
                int curmax = getmax(lifts[i].sl_serving[j].t,lifts[i].sl_serving[j].meret);
                if(!(j == 0 && ((up && flvl < lifts[i].lvl) || (!up && flvl > lifts[i].lvl)))){         //only if not passed
                    if(curmin > flvl){
                        curcount += 2*abs(curmin-flvl);
                    } else if(curmax < flvl){
                        curcount += 2*abs(curmax-flvl);
                    }
                    if(curmin > tlvl){
                        curcount += 2*abs(curmin-tlvl);
                    } else if(curmax < tlvl){
                        curcount += 2*abs(curmax-tlvl);
                    }
                    int vane1 = 0, vane2 = 0;               //if somebody else also gets off there, dont charge time
                    for (int k = 0; k < lifts[i].sl_serving[j].meret; ++k) {
                        if(reqs[lifts[i].sl_serving[j].t[k]].from == flvl) vane1++;
                        if(reqs[lifts[i].sl_serving[j].t[k]].to == tlvl) vane2++;
                    }
                    if(vane1 == 0) curcount += 4;
                    if(vane2 == 0) curcount += 4;

                    curcount += j*20;           //TODO this with exact travel time
                    if(curcount < mini){
                        mini = curcount;
                        minindex = i;
                        minshortlist = j;
                    }
                }

            }
        }
        int curcounta = lifts[i].shortlists * 30;
        if(curcounta < mini){
            mini = curcounta;
            minindex = i;
            minshortlist = lifts[i].shortlists;
            printf("allocated:NEW:NEW:NEW: (%2d >> %2d)    - lift %d    shortlist %d",flvl,tlvl,minindex,minshortlist);
        }
    }
    ans[0] = minindex;
    ans[1] = minshortlist;
    printf("allocated:::: (%2d >> %2d)    - lift %d    shortlist %d",flvl,tlvl,minindex,minshortlist);
    return;
}
/*
int find_complex_csicska(int flvl,int tlvl){
    int minindex = 0;
    int mini = INT_MAX;
    int up = flvl < tlvl ? 1 : 0;
    for (int i = 0; i < 4; i++) {                // check each lift
        int layer = 0;
        int j = 0;
        while(layer <= lifts[i].shortlists){     // check each shortlist layer
            req curreq = reqs[lifts[i].reqs_serving[j]];
            int curup = curreq.from < curreq.to ? 1 : 0;
            if(curup != up){                                                                                    //if this shortlist does not go into the same dir, jump to the next one
                while(layer >= reqs[lifts[i].reqs_serving[j]].shortlist){
                    j++;
                }
                layer++;
            }
            else{
                int curcount = 0;
                //should get shortlist border indexes

            }
        }

    }
}
*/

int move_lift(int cur){
    if(lifts[cur].capacity == 0) return 0;
    if(lifts[cur].state == 0){
        int heading = reqs[lifts[cur].reqs_serving[0]].from;
        if(heading == lifts[cur].lvl){
            lifts[cur].state = 1;
        }
        else if(heading > lifts[cur].lvl) lifts[cur].lvl += 0.5f;
        else lifts[cur].lvl -= 0.5f;

        if(heading > lifts[cur].lvl) lifts[cur].heading = 1;
        else if(heading < lifts[cur].lvl) lifts[cur].heading = -1;
    }
    else if(lifts[cur].state > 0 && 5 >lifts[cur].state){ lifts[cur].state++; lifts[cur].heading = 0;}
    else if(lifts[cur].state == 5){
        int heading = reqs[lifts[cur].reqs_serving[0]].to;
        if(heading == lifts[cur].lvl){
            lifts[cur].state = 6;
        }
        else if(heading > lifts[cur].lvl) lifts[cur].lvl += 0.5f;
        else lifts[cur].lvl -= 0.5f;

        if(heading > lifts[cur].lvl) lifts[cur].heading = 1;
        else if(heading < lifts[cur].lvl) lifts[cur].heading = -1;
    }
    else if(lifts[cur].state > 5 && 10 >lifts[cur].state){ lifts[cur].state++; lifts[cur].heading = 0;}
    //move req blocks
    //TODO do that with a queue
    if(lifts[cur].state == 4) reqs[lifts[cur].reqs_serving[0]].getintime = curtime; //TODO make for adv
    if(lifts[cur].state == 10){ //TELJESÍTVE
        int returned = lifts[cur].reqs_serving[0];
        for (int i = 0; i < 20; ++i) {
            lifts[cur].reqs_serving[i] = lifts[cur].reqs_serving[i+1];
            reqs[lifts[cur].reqs_serving[i]].shortlist--;
            reqs[lifts[cur].reqs_serving[i]].getouttime = curtime;
        }
        lifts[cur].state = 0;
        lifts[cur].capacity--;
        return returned+1;
    }

    return 0;
}
int *move_lift_adv(int cur){
    if(lifts[cur].shortlists == 0) return 0;
    int heading_up = lifts[cur].sl_serving[0].up;
    int *t = lifts[cur].sl_serving[0].t;
    int m = lifts[cur].sl_serving[0].meret;

    if(lifts[cur].state == 0){
        int heading_to_start = heading_up == 1 ? getmin(t,m) : getmax(t,m);
        if(heading_to_start == lifts[cur].lvl){
            lifts[cur].state = 1;
        }
        else if(heading_to_start > lifts[cur].lvl) lifts[cur].lvl += 0.5f;
        else lifts[cur].lvl -= 0.5f;
    }
    else if(lifts[cur].state > 0 && 5 >lifts[cur].state){
        lifts[cur].state++; //lifts[cur].heading = 0;
        if(lifts[cur].state == 4){
            int *tf = startededindexes(lifts[cur].sl_serving[0].t,lifts[cur].sl_serving[0].meret,lifts[cur].lvl);
            int started_now = tf[0];
            for (int i = 0; i < started_now; ++i) {
                reqs[tf[i+1]].getintime = curtime;
            }
            free(tf);
        }
    }

    else if(lifts[cur].state == 5){
        int curshouldstop = 0;
        if((int) (lifts[cur].lvl*10) % 10 == 0) {                   //if lift is on an actual floor should stop?
            curshouldstop = shouldstop(t, m, lifts[cur].lvl);
        }

        if (curshouldstop == 1) {
            lifts[cur].state = 6;
        } else if (curshouldstop == -1) {
            lifts[cur].state = 1;//todo not =1 ?  ??what nem értem a saját kommentem
        } else {
            if (heading_up == 1) lifts[cur].lvl += 0.5f;
            else lifts[cur].lvl -= 0.5f;

        }

    }
    else if(lifts[cur].state > 5 && 10 > lifts[cur].state){
        lifts[cur].state++; //lifts[cur].heading = 0;
    }

    else if(lifts[cur].state == 10){ //1 TELJESÍTVE
        //asdf
        int *tf = finishedindexes(t,m,lifts[cur].lvl);  //returns size + array of ids of finished reqs
        int finished_now = tf[0];
        lifts[cur].sl_serving[0].meret -= finished_now;
        int *returned = (int *) malloc (sizeof(int)*20);
        for (int i = 0; i < finished_now; ++i) {
            reqs[tf[i+1]].getouttime = curtime;

            for (int j = 0; j < m; ++j) {
                if(tf[i+1] == lifts[cur].sl_serving[0].t[j]){
                    for (int k = j; k < m-1; ++k) {
                        lifts[cur].sl_serving[0].t[k] = lifts[cur].sl_serving[0].t[k+1];
                    }
                    //lifts[cur].sl_serving[0].meret--;
                }
            }
            returned[i+1] = tf[i+1];
        }
        returned[0] = finished_now;
        if(lifts[cur].sl_serving[0].meret == 0){                    //if this shortlist is finished, move all one step closer
            for (int i = 0; i < lifts[cur].shortlists-1; ++i) {
                lifts[cur].sl_serving[i] = lifts[cur].sl_serving[i+1];
            }
            lifts[cur].shortlists--;
            lifts[cur].state = 0;
        } else {                                                    //if this is not finished, go and find the next station
            lifts[cur].state = 5;
        }
        free(tf);
        return returned;
    }

    if(lifts[cur].lvl < 0){
        printf("ER");
    }



    return 0;
}       //returns array (until -1) of served reqs

int main() {

    minlvl = 0;
    maxlvl = 18;
    FILE * fp;
    fp = fopen("input.txt","r");

    if (NULL == fp) {
        printf("Nem lehetett megnyitni a fajlt :( \n");
        return 0;
    }
    int curid = 0;
    int input_size = 0;
    fscanf(fp,"%d",&input_size);
    while(!feof(fp) && curid < input_size){
        fscanf(fp,"%d",&curid);
        fscanf(fp,"%d %d %d", &reqs[curid].time, &reqs[curid].from, &reqs[curid].to);
        reqs[curid].id = curid;
        reqs[curid].getintime = -1;
        reqs[curid].getouttime = -1;
    }
    for (int i = 0; i < curid; ++i) {
        disp_req_data(reqs[i]);
    }

    int selb = mainmenu(-1,-1);
    int sela =     menu(-1,-1);


    system("cls"); //jelenlegi idő
    int last_req_processed = 0;
    int last_req_served = 0;

    curid--;
    for (int i = 0; i < 4; ++i) { lifts[i].shortlists = 0; }
    while(curtime <= reqs[curid].time || last_req_served < curid){
        //TODO enable?disable
        system("cls");
        //
        disp();
        if(sela < 4)
            disp_lift_info();
        else
            disp_lift_info_adv();

        printf("\n > ido:                        00:%02d:%02d ", (curtime/60),(curtime%60));
        printf("\n\n > kerelmek:                   %d felveve,  %d teljesitve\n   ",last_req_processed+1,last_req_served+1);
        for (int i = 0; i < input_size; ++i) {

            if(last_req_served >= i+1) printf("%c",178);
            else if(last_req_processed >= i+1) printf("%c",177);
            else printf("%c",176);
        }
        printf(" %d\n\n", input_size);
        if(last_req_served > 0) printf(" > atlagos kiszolgalasi ido:   %d mp\n",(s_waitingsum/last_req_served+1));
        if(s_uselesssum > 0)      printf(" > hatasfok:                   %d / %d (%.3f) \n",s_usefullsum,s_uselesssum,((float)s_usefullsum/(float)s_uselesssum));
        if(last_req_served > 0) printf(" > szoras:                     %.2lf \n",s_deviation);

        while(reqs[last_req_processed+1].time <= curtime && last_req_processed < curid){

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
            }
            disp_new_req(reqs[last_req_processed+1], ans[0]);
            last_req_processed++;
        }
        printf("\n \n");
        //stattttt  vvv

        if(sela < 4){
            int completed_now = 0;
            for (int i = 0; i < 4; ++i) {
                int a = move_lift(i);
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
            for (int i = 0; i < 4; ++i) {
                int *a = move_lift_adv(i);
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
        Sleep(1);
        curtime++;





    }
    fclose(fp);
    getchar();
    getchar();
    getchar();
    getchar();
    return 0;
}
