#include "main.h"
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