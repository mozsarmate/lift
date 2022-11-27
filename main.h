#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include "debugmalloc.h"

#ifndef LIFT_MAIN_H
#define LIFT_MAIN_H

typedef enum states{
    tobase, getin1, getin2, getin3, getin4, totarg, getou1, getou2, getou3, getou4
} states;
typedef struct req{
    int id, time, from, to;                         //Fájlból beolvasott
    int shortlist, getintime, getouttime, servedby; //Később hozzáírt
} req;
typedef struct sl{
    int meret;
    int t[20];              //showing req id
    int shortlist;          //TODO maybe add serving time as a detail
    int up;
} sl;
typedef struct lift{
    float lvl;
    int capacity;
    int shortlists;
    states state;
    req *reqs_serving[22];   //TODO make it not int but req **to make it more understandable
    sl sl_serving[22];
    int heading;
} lift;

int maxlvl;
int minlvl;
int lvldb;
int liftdb;
lift *lifts;
req *reqs;


void draw_canvas(int input_size, int sela, int last_req_processed, int last_req_served, int curtime, int s_waitingsum, int s_usefullsum, int s_uselesssum, double s_deviation);
void disp();
void disp_req_data(req bem);
void disp_new_req(req bem, int _lift_ordered);
void disp_lift_info();
void disp_lift_info_adv();
void disp_logo();

int menu(int disable);
int mainmenu(int disable);
void editmenu(int *cel, int mode);
int menuend();

int find_most_empty();
int find_most_near(int lvl);
int find_fastest(int lvl);
void find_complex(int flvl,int tlvl, int *ans);

int move_lift(int cur, int curtime);
int *move_lift_adv(int cur, int curtime);

int charstartoint(char *bem);
int getmin(int *t, int m);
int getmax(int *t, int m);
int *startedindexes(int *t, int m, int k);
int *finishedindexes(int *t, int m, int k);
int shouldstop(int *t, int m, int k);
void clearlifts(int n);

void beolvasas(int *curid, int *input_size, FILE *fp);
void editFile(FILE *fp, int curid);
void kiiras(int curid, int sela, int last_req_served, int curtime, int s_waitingsum, int s_usefullsum, int s_uselesssum, int s_deviation);


#endif //LIFT_MAIN_H
