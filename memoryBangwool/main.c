#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HRT 0
#define SPDE 1
#define CLVR 2
#define DMD 3
#define JKR 4

typedef struct plyr *pl_ptr;

struct plyr{
    int hand[47];
    int indx;
};

int card[54]={0};
int stack[54];
int ind=0;

struct plyr computer;
struct plyr Me;

void init_card(void);
void init_hand(pl_ptr);
void print_board(void);
void print_card(int);
void print_shpe(int);
void print_num(int);

int main(){
    init_card();
    init_hand(&computer);
    init_hand(&Me);
    print_board();
    //print_card(52);
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
void init_hand(pl_ptr p){
    
    for(int i=0;i<7;i++)
        p->hand[i]=stack[--ind];
    p->indx=7;
}

void print_board(){
    int i=ind-1;
    
    print_card(stack[i]);
    printf("  █ █ █ █ █\n\n");
    
    printf("======your card======\n");
    for(i=0;i<Me.indx;i++){
        print_card(Me.hand[i]);
        printf("  ");
    }
}

void print_card(int num){
    print_shpe(num);
    print_num(num);
}

void print_shpe(int num){
    int shape=num/13;
    switch (shape) {
        case 0:
            printf("♥");
            break;
        case 1:
            printf("♣");
            break;
        case 2:
            printf("♠");
            break;
        case 3:
            printf("♦");
            break;
        default:
            printf("◑");
            break;
    }
}

void print_num(int num){
    int number=num%13;
    if(num/13==4)
        return;
    
    switch (number) {
        case 0:
            printf("A");
            break;
        case 10:
            printf("J");
            break;
        case 11:
            printf("Q");
            break;
        case 12:
            printf("K");
            break;
        default:
            printf("%d", number+1);
            break;
    }
}
