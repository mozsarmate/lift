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



int curtime = 0;




int main() {

    minlvl = 0;
    maxlvl = lvldb;
    int curid = 0;
    int input_size = 0;
    int s_waitingsum = 0;                 
    int s_uselesssum = 0;                 
    int s_usefullsum = 0;                 
    double s_deviation = 0;               
    float s_avg = 0;                      
    FILE *fp;
    int *s_times_eplapsed = beolvasas(&curid, &input_size, &fp);

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

        system("cls");

        draw_canvas(input_size, sela, last_req_processed, last_req_served, curtime, s_waitingsum, s_usefullsum, s_uselesssum, s_deviation);

        while(reqs[last_req_processed+1].time <= curtime && last_req_processed < curid+2){      //todo was +1 (iso +2

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
            if(sela <= 3) {         //post process for simple algs      // V TODO not +1?
                lifts[lift_ordered].reqs_serving[lifts[lift_ordered].capacity] = &reqs[last_req_processed + 1]; //add req id to lift array
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
                }
                reqs[last_req_processed+1].servedby = ans[0];
                disp_new_req(reqs[last_req_processed+1], ans[0]);
            }

            last_req_processed++;
        }
        printf("\n \n");





        if(sela < 4){
            int completed_now = 0;
            for (int i = 0; i < liftdb; ++i) {
                int a = move_lift(i,curtime);
                if(a > 0){                                                               //each time a request is served
                    last_req_served++;
                    int time_eplapsed = curtime - reqs[a-1].time; //TODO make for adv
                    s_waitingsum += time_eplapsed;
                    s_avg = (float)s_waitingsum / (float)last_req_served;
                    s_times_eplapsed[last_req_served] = time_eplapsed;
                    double curdeviation = 0;
                    for (int j = 1; j < last_req_served; ++j) {         //todo was +1
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
                        last_req_served++;
                        int time_eplapsed = curtime - reqs[a[j+1]].time;
                        s_waitingsum += time_eplapsed;
                        s_avg = (float)s_waitingsum / (float)last_req_served;
                        s_times_eplapsed[last_req_served] = time_eplapsed;
                        double curdeviation = 0;
                        for (int k = 1; k < last_req_served+1; ++k) {
                            curdeviation += pow((double)(s_times_eplapsed[k] - s_avg), 2);
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
    system("cls");

    draw_canvas(input_size, sela, last_req_processed, last_req_served, curtime, s_waitingsum, s_usefullsum, s_uselesssum, s_deviation);
    disp_logo();
    int selc = menuend();
    if(selc == 1){
        kiiras(curid, sela, last_req_served,curtime,s_waitingsum,s_uselesssum,s_uselesssum,s_deviation);
    }
    printf("\n \n \n Nyomja meg az ENTER-t a kilepeshez!");


    free(lifts);
    free(reqs);
    free(s_times_eplapsed);
    getchar();
    return 0;
}


