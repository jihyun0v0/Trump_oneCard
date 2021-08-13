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
int turn=-1;            //플레이어가 공격할 때 0, 컴퓨터가 공격할 때 1, 공격이 아닐 때 -1
int a_turn=1;
int damage = 0;

struct plyr computer;
struct plyr Me;

void init_card(void);
void init_hand(pl_ptr);
void print_board(void);
void print_card(int);
void print_shpe(int);
void print_num(int);
void put_card();
int attack(int index);
int defend(int from);
int check_defend(int card, int input_card);
int get_score(int card);
int put_check(int card);
void put_card();
void remove_hand(pl_ptr plyr, int index);
void computer_put_card();

int main(){
    init_card();
    init_hand(&computer);
    init_hand(&Me);
    
    print_board();

    while ((Me.indx < 20 || computer.indx < 20) || (Me.indx > 0 || computer.indx > 0))
    {
        put_card();
        computer_put_card();
        if (turn == 0 && damage > 0)
        {
            for(int i=0;i<damage;i++) computer.hand[computer.indx++] = draw_stack[ind--];
            turn = -1;
            damage = 0;
            a_turn = 1;
        }
        else if (turn == 1 && damage > 0)
        {
            for(int i=0;i<damage;i++) Me.hand[Me.indx++] = draw_stack[ind--];
            turn = -1;
            damage = 0;
            a_turn = 1;
        }
    }
}

void put_card()
{
    int index;

    printf("\nput index of card (0 is skip):");
    scanf("%d", &index);

    if (!index)
    {
        if (turn == -1)
        {
            Me.hand[Me.indx++] = draw_stack[ind--];
            return ;
        }
        else
        {
            a_turn = 0;
            return ;
        }
    }

    int card = Me.hand[index-1];

    if (!put_check(card))
    {
        put_card();
        return ;
    }

    if(turn==1)
    {
        if (!(card==52||card==53||card%13==0||card%13==1))
        {
            printf("your card is not right");
            put_card();
            return ;
        }
    }

    put_stack[++p_ind]=card;
    remove_hand(&Me, index-1);

    if (card==52||card==53||card%13==0||card%13==1)
    {
        damage += attack(card);
        turn = 0;
    }
    
}

void init_card(){
    int random;
    
    srand(time(NULL));
    
    for(;ind<53;)
        if(!card[random=rand()%54]){
            draw_stack[++ind]=random;
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


int attack(int card)
{
    if (card == 52) return 9;
    else if (card == 53) return 7;
    else
    {
        if (card % 13 == 0)
        {
            if (card / 13 == SPDE) return 5;
            return 3;
        }
        else if (card % 13 == 1) return 2;
    }
    
    // A=0(3), 2=1(2), Joker=52,53
    return 0;
}

int get_score(int card){
    return 0;
}

void remove_hand(pl_ptr plyr, int index)
{
    for (int i = index; i < plyr->indx; i++)
    {
        plyr->hand[i] = plyr->hand[i + 1];
    }
    plyr->indx -= 1;
}

void computer_put_card()
{
    int card=put_stack[p_ind];
    int tmp;
    int putable[20]={0};
    int put_len=0;

    srand(time(NULL));
    
    if(card>51||card%13<2) {             //스택에 놓여진 카드가 공격 카드인 경우
       
            if(card%13==0) {             //스텍에 놓인 카드가 A
                for(int i=0;i<computer.indx;i++) {
                    if(computer.hand[i]%13==0)
                        putable[put_len++]=i;
                }
            }
            else if(card%13==1) {
                for(int i=0;i<computer.indx;i++) {
                    if(computer.hand[i]%13<3)       //A, 2, 3인 경우
                        putable[put_len++]=i;
                }
            }
            else {
                for(int i=0;i<computer.indx;i++) {
                    if(computer.hand[i]>51)
                        putable[put_len++]=i;
                }
            }
    }

    else {
        for(int i=0;i<computer.indx;i++) {              //일반 카드인 경우, 핸드 카드 중 가능한 카드를 랜덤으로 선택 해 놓는다.
            if(computer.hand[i]>51||computer.hand[i]%13==card%13||computer.hand[i]/13==card/13)
                putable[put_len++]=i;
            }
    }
    
    if(put_len==0) {      //낼 카드가 없을 경우
        computer.hand[computer.indx++]=draw_stack[ind--];
        return;
    }
    
    tmp=rand()%put_len;
    
    if(computer.hand[tmp]>51||computer.hand[tmp]%13<2) 
    {
        turn=1;
        if(computer.hand[tmp]==53)
            damage+=9;
        else if(computer.hand[tmp]==52)
            damage+=7;
        else if(computer.hand[tmp]%13==0&&computer.hand[tmp]/13==3)//spade A일 경우
            damage+=5;
        else if(computer.hand[tmp]%13==0)
                damage+=3;
        else if(computer.hand[tmp]%13==1)
            damage+=2;
    }
        
    put_stack[++p_ind]=computer.hand[tmp];
    remove_hand(&computer, tmp);
}

