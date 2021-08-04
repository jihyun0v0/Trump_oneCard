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
    int indx;           //핸드 카드 인덱스
};

int card[54]={0};
int draw_stack[54];             //뽑는 스택
int ind=-1;              //뽑는 스텍 인덱스
int put_stack[54];      //카드 내는 스택
int p_ind=-1;            //카드 내는 스택 인덱스
int LOOSE=1;
int put_ind;         //카드 낼 때 해당 카드의 번호

struct plyr computer;
struct plyr Me;



void init_card(void);
void init_hand(pl_ptr);
void print_board(void);
void print_card(int);
void print_shpe(int);
void print_num(int);
void put_card(int num);
int set_attack(int index);
int attack(int index);
int defend(int from);
int check_defend(int card, int input_card);
int get_score(int card);
int put_check(int card);
void put_card(int index);
void remove_hand(int index);


int main(){
    init_card();
    init_hand(&computer);
    init_hand(&Me);
    
    //while(LOOSE){
    print_board();

    printf("\nput index of card :");
    scanf("%d", &put_ind);
    put_card(put_ind);
    

    
}

void put_card(int index)
{
    int card = Me.hand[index];
    int damage = 0;

    if (!put_check(card)) return ;

    put_stack[++p_ind]=card;
    remove_hand(index);

    if (card==52||card==53||card%13==0||card%13==1) 
    {
        damage += attack(index);
    }
    
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

int put_check(card){
    int test_card=put_stack[p_ind];
    if(card>=52||card%13==test_card%13||card/13==test_card/13)
        return 1;

    printf("your card is not right");
    return 0;
    
}


int attack(int index)
{
    int Card=Me.hand[index];
    
    if (Card == 52) return 9;
    else if (Card == 53) return 7;
    else
    {
        if (Card % 13 == 0)
        {
            if (Card / 13 == SPDE) return 5;
            return 3;
        }
        else if (Card % 13 == 1) return 2;
    }
    
    // A=0(3), 2=1(2), Joker=52,53
    return 0;
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

void remove_hand(int index)
{
    for (int i = index; i < Me.indx; i++)
    {
        Me.hand[i] = Me.hand[i + 1];
    }
    --Me.indx;
}