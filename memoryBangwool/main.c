#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HRT 0
#define DMD 1
#define CLVR 2
#define SPDE 3
#define JKR 4

typedef struct plyr *pl_ptr;

struct plyr{
    int hand[47];
    int indx;
};

int card[54]={0};
int draw_stack[54];             //뽑는 스택
int ind=-1;              //뽑는 스텍 인덱스
int put_stack[54];      //카드 내는 스택
int p_ind=-1;            //카드 내는 스택 인덱스
int LOOSE=1;
int attack_ind;

struct plyr computer;
struct plyr Me;



void init_card(void);
void init_hand(pl_ptr);
void print_board(void);
void print_card(int);
void print_shpe(int);
void print_num(int);
void put_card(int num);
int set_attack(int *index);
int attack(int index);
void defend(void);
int check_defend(int card, int input_card)

int main(){
    init_card();
    init_hand(&computer);
    init_hand(&Me);
    
    //while(LOOSE){
    print_board();
   printf("\nput index of card to attack:");
    scanf("%d", &attack_ind);
    if(set_attack(&attack_ind));
       attack(attack_ind);
   
    

    
}

void init_card(){
    int random;
    
    srand(time(NULL));
    
    for(;ind<54;)
        if(!card[random=rand()%55]){
            draw_stack[++ind]=random;
            card[random]=1;
        }
    
    put_stack[++p_ind]=draw_stack[ind--];
}

void init_hand(pl_ptr p){
    
    for(int i=0;i<7;i++)
        p->hand[i]=draw_stack[ind--];
    p->indx=7;
}

void print_board(){
    int i=ind-1;
    
    print_card(put_stack[p_ind]);
    printf("  █ █ █ █ █\n\n");
    
    printf("======your card======\n");
    printf("index:\t");
    for(i=0;i<Me.indx;i++)
        printf("%d\t", i+1);
    printf("\ncard:\t");
    for(i=0;i<Me.indx;i++){
        print_card(Me.hand[i]);
        printf("\t");
    }
    printf("\n");
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
            printf("♦");
            break;
        case 2:
            printf("♣");
            break;
        case 3:
            printf("♠");
            break;
        default:
            printf("JKR");
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


int set_attack(int *index){
    (*index)--;
    while((Me.hand[*index])==-1)(*index)++;
   // (*index)--;
    
    int card=Me.hand[*index];
    int test_card=put_stack[p_ind];

    if(!(card>=52||card%13==test_card%13||card/13==test_card/13)){
        printf("your card is not right");
        return -1;
        }
    
    
        put_stack[++p_ind]=card;
        Me.hand[*index]=-1;
       if(card==52||card==53||card%13==0||card%13==1)
           return 1;
        return 0;
    
}

int attack(int index)
{
    while((Me.hand[index++])!=-1);
    index--;
    
    if(!set_attack(index)){
        printf("your card is not right\n");
        return -1;
    }
    
    int Card=Me.hand[index];
    
    switch (Card) {
        case 52:
            return 9;
            break;
        case 53:
            return 7;
            break;
        default:
            switch(Card%13){
                case 0:
                if((Card/13)==SPDE)
                    return 5;
                return 3;
                case 1:
                    return 2;
                default:
                    return 0;
            }
    }
    
    // A=0(3), 2=1(2), Joker=52,53
    
}

int defend(int from)
{   int i,j, MyC_ind, my_card;
    int def_score=0;
    
    for(i=from;i<=p_ind;i++){
        print_card(put_stack[i]);
        printf("======your card======\n");
        printf("index:\t");
        for(j=0;j<Me.indx;j++)
            printf("%d\t", j+1);
        printf("\ncard:\t");
        for(j=0;j<Me.indx;j++){
            print_card(Me.hand[j]);
            printf("\t");
        }
        printf("\ninput your card's index to defend");
        scanf("%d", &MyC_ind);
        my_card=Me.hand[MyC_ind-1];
        
        
        
        if(check_defend(put_stack[i], my_card)){
            def_score+=get_score(put_stack[i]);
        }
        
        
    }
    
}


int check_defend(int card, int input_card){
    //컬러조커는 스페이드 에이스로, 흑백조커는 컬러조커로,
    //에이스는 다른 에이스로
    //2는 2나 에이스나 조커나 3으로
    int attack=0, defend=0;
    
  
        
    
    
}
    

int get_score(int card){
    
}
