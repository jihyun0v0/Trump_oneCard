#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HRT 0
#define SPDE 1
#define CLVR 2
#define DMD 3
#define JKR 4

int card[54]={0};
int stack[54];
int ind=0;

int plyr1[47];
int f_ind=7;
int plyr2[47];
int s_ind=7;

void init_card(void);
void init_hand(int *plyr);
void print_board(void);
//void print_shpe(int);
//void print_num(int);


int main(){
    init_card();
    init_hand(plyr1);
    init_hand(plyr2);
    
    print_board();
    
}

void init_card(){
    int random;
    
    srand(time(NULL));
    
    for(;ind<54;)
        if(!card[random=rand()%55]){
            stack[ind++]=random;
            card[random]=1;
        }
}
void init_hand(int *plyr){
    
    for(int i=0;i<7;i++)
        plyr[i]=stack[--ind];
}

void print_board(){
    int i=ind-1;
    printf("%d      ...\n", stack[i]);
    
    printf("======your card======\n");
    for(i=0;i<f_ind;i++)
        printf("%d  ", plyr1[i]);
    
    
    
}
