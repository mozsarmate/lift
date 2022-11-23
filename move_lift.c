//
// Created by Máté on 2022. 11. 23..
//
#include "main.h"

int move_lift(int cur, int curtime){
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
        reqs[lifts[cur].reqs_serving[0]].getouttime = curtime;
        for (int i = 0; i < 20; ++i) {
            lifts[cur].reqs_serving[i] = lifts[cur].reqs_serving[i+1];
            reqs[lifts[cur].reqs_serving[i]].shortlist--;
        }
        lifts[cur].state = 0;
        lifts[cur].capacity--;
        return returned+1;
    }

    return 0;
}
int *move_lift_adv(int cur, int curtime){
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
            int *tf = startedindexes(lifts[cur].sl_serving[0].t, lifts[cur].sl_serving[0].meret, lifts[cur].lvl);
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