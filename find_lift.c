//
// Created by Máté on 2022. 11. 23..
//
#include "main.h"

int find_most_empty(){
    int minindex = 0;
    for (int i = 0; i < liftdb; ++i) {
        if(lifts[i].capacity < lifts[minindex].capacity) minindex = i;
    }
    return minindex;
}
int find_most_near(int lvl){
    int minindex = 0;
    int mini = 20;
    for (int i = 0; i < liftdb; ++i) {
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
    for (int i = 0; i < liftdb; i++) {
        int curcap = lifts[i].capacity;
        int curcount = 0;
        int j = 0;
        if(0 < lifts[i].state && lifts[i].state < 5) { curcount -= lifts[i].state; }
        if(lifts[i].state == 5)                      { /*j=1;*/ curcount += 2*abs(reqs[lifts[i].reqs_serving[j]].from-reqs[lifts[i].reqs_serving[j]].to); }
        if(5 < lifts[i].state)                       { /*j=1;*/ curcount += 9-lifts[i].state; }
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
    int minshortlist = lifts[flvl%liftdb].shortlists;         //worst case scenario: return a new, (random?) created shortlist for a
    int mini = INT_MAX;
    int up = flvl < tlvl ? 1 : 0;
    for (int i = 0; i < liftdb; i++) {                // check each lift
        if(lifts[i].shortlists == 0){
            ans[0] = i; ans[1] = 0;
            return;
        }   // if no task >> do this
        for (int j = 0; j < lifts[i].shortlists; ++j) {
            if(lifts[i].sl_serving[j].up == up && lifts[i].sl_serving[j].meret < 5) {   //last val could be 20 as well TODO
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

                    curcount += j*30;           //TODO this with exact travel time
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